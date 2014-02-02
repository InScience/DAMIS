import sys
import csv
from os.path import splitext
from datetime import datetime

from django.utils.translation import ugettext as _

from damis.models import Experiment, Connection, ParameterValue
from damis.settings import BUILDOUT_DIR
from algorithms.preprocess import transpose
from algorithms.statistics import statistics


def stat_primitives_service(X, arff=False, *args, **kwargs):
    start_time = datetime.now()
    X_absolute = BUILDOUT_DIR + '/var/www' + X
    Y = '%s_stats%s' % splitext(X)
    Y_absolute = BUILDOUT_DIR + '/var/www' + Y
    if X.endswith('arff'):
        arff = True
    statistics(X_absolute, Y_absolute, arff=arff)
    duration = datetime.now() - start_time
    return [('Y', Y), ('calcTime', duration)]

def transpose_data_service(X, c, arff=False, *args, **kwargs):
    start_time = datetime.now()
    X_absolute = BUILDOUT_DIR + '/var/www' + X
    Y = '%s_transposed%s' % splitext(X)
    Y_absolute = BUILDOUT_DIR + '/var/www' + Y
    if X.endswith('arff'):
        arff = True
    transpose(X_absolute, Y_absolute, int(c), arff=arff)
    duration = datetime.now() - start_time
    return [('Y', Y), ('calcTime', duration)]

def not_implemented(*args, **kwargs):
    raise ValueError(_('This service is not implemented yet'))

def column_string_to_list(columns):
    column_list = []
    for c in columns.split(','):
        c = c.strip()
        if '-' in c:
            from_c, till_c = c.split('-')
            for i in range(int(from_c), int(till_c) + 1):
                column_list.append(i)
        else:
            column_list.append(int(c))
    return column_list

def select_features_service(X, columns, classColumn, *args, **kwargs):
    X_absolute = BUILDOUT_DIR + '/var/www' + X
    Y = '%s_select%s' % splitext(X)
    Y_absolute = BUILDOUT_DIR + '/var/www' + Y

    input_file = open(X_absolute)
    output_file = open(Y_absolute, 'w')

    columns = column_string_to_list(columns)

    attr = -1
    new_attr = -1
    for line in input_file:
        if '@attribute' in line.lower():
            attr += 1
            if attr in columns:
                new_attr += 1
                type_ = line.split()[-1].strip()
                title = 'attr{0}'.format(new_attr)
                if attr == int(classColumn):
                    title = 'class'
                output_file.write('@attribute %s %s\n' % (title, type_))
        else:
            output_file.write(line)
        if line.strip().lower().startswith("@data"):
            break

    for attr_list in csv.reader(input_file):
        attrs_to_write = []
        for c in columns:
            attrs_to_write.append(attr_list[c])
        output_file.write(', '.join(attrs_to_write) + '\n')

    input_file.close()
    output_file.close()

    return [('Y', Y)]


def do_nothing(*args, **kwargs):
    return []

# Collables which get
SERVICES = {
    "UPLOAD FILE": do_nothing,
    "EXISTING FILE": do_nothing,
    "MIDAS FILE": do_nothing,
    "TECHNICAL DETAILS": do_nothing,
    "MATRIX VIEW": do_nothing,
    "CHART": do_nothing,
    "CLEAN DATA": not_implemented,
    "FILTER DATA": not_implemented,
    "SPLIT DATA": not_implemented,
    "TRANSPOSE DATA": transpose_data_service,
    "TRANSFORM DATA": not_implemented,
    "SELECT FEATURES": select_features_service,
    "STAT PRIMITIVES": stat_primitives_service,
    "MLP": not_implemented,
    "C45": not_implemented,
    "KMEANS": not_implemented,
    "PCA": not_implemented,
    "SMACOF": not_implemented,
    "DMA": not_implemented,
    "SDS": not_implemented,
    "SAMANN": not_implemented,
    "SOM": not_implemented,
    "SOMMDS": not_implemented,
}

## Recursively walk through through tasks.
def execute_tasks(task):
    task.status = 'RUNNING'
    task.save()

    # Get INPUT and COMMON parameter values.
    kwargs = {
        'maxCalcTime': exp.max_calc_time,
        'p': exp.p,
    }

    for pv in task.parameter_values.all():
        cons = Connection.objects.filter(target=pv)
        if cons:
            value = cons[0].source.value
        else:
            value = pv.value
        kwargs[pv.parameter.name] = value

    # Call executable
    service = SERVICES[task.component.title]
    try:
        response = service(**kwargs) # Response dict: name -> value
    except Exception, e:
        task.status = 'ERROR'
        task.error = e.message
        task.save()
        task.experiment.status = 'ERROR'
        task.experiment.save()
        return

    # Set OUTPUT parameter values and save.
    for name, value in response:
        param_qs = task.component.parameters.filter(name=name)
        parameter = param_qs[0] if param_qs else None
        if parameter:
            pv_qs = task.parameter_values.filter(parameter__name=name)
            if not pv_qs:
                pv = ParameterValue(task=task, parameter=parameter)
            else:
                pv = pv_qs[0]
            pv.value = value
            pv.save()

    task.status = 'FINISHED'
    task.save()

    ## Call its following tasks
    for pv in task.parameter_values.all():
        for con in Connection.objects.filter(source=pv):
            next_task = con.target.task
            if next_task.status != 'FINISHED':
                execute_tasks(next_task)


if __name__ == '__main__':
    exp_pk = sys.argv[1]
    exp = Experiment.objects.get(pk=exp_pk)
    first_task = exp.tasks.filter(component__category='DATA')[0]
    execute_tasks(first_task)
    if exp.status != 'ERROR':
        exp.status = 'FINISHED'
        exp.save()
