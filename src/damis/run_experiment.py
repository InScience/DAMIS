import sys
from os.path import splitext
from datetime import datetime

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
    print Y_absolute
    print Y
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

def do_nothing(*args, **kwargs):
    return []

# Collables which get
SERVICES = {
    "UPLOAD FILE": do_nothing,
    "EXISTING FILE": do_nothing,
    "MIDAS FILE": do_nothing,
    "TECHNICAL DETAILS": do_nothing,
    "CHART": do_nothing,
    # "CLEAN DATA",
    # "FILTER DATA",
    # "SPLIT DATA",
    "TRANSPOSE DATA": transpose_data_service,
    # "TRANSFORM DATA",
    "STAT PRIMITIVES": stat_primitives_service,
    # "MLP",
    # "C45",
    # "KMEANS",
    # "PCA",
    # "SMACOF",
    # "DMA",
    # "SDS",
    # "SAMANN",
    # "SOM",
    # "SOMMDS",
    # "SELECT FEATURES",
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
    service = SERVICES[task.algorithm.title]
    response = service(**kwargs) # Response dict: name -> value

    # Set OUTPUT parameter values and save.
    for name, value in response:
        param_qs = task.algorithm.parameters.filter(name=name)
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
            if next_task.status == 'SAVED':
                execute_tasks(next_task)


if __name__ == '__main__':
    exp_pk = sys.argv[1]
    exp = Experiment.objects.get(pk=exp_pk)
    first_task = exp.tasks.filter(algorithm__category='DATA')[0]
    execute_tasks(first_task)
    exp.status = 'FINISHED'
    exp.save()
