import sys
from damis.models import Experiment, Connection
from damis.settings import BUILDOUT_DIR
from os.path import splitext
from algorithms.preprocess import transpose

def transpose_data_callable(X, c, arff=False, *args, **kwargs):
    X_absolute = BUILDOUT_DIR + '/var/www' + X
    Y = '%s_transposed%s' % splitext(X)
    Y_absolute = BUILDOUT_DIR + '/var/www' + Y
    if X.endswith('arff'):
        arff = True
    transpose(X_absolute, Y_absolute, int(c), arff=arff)
    return [('Y', Y)]

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
    "TRANSPOSE DATA": transpose_data_callable,
    # "TRANSFORM DATA": transform_data_callable,
    # "STAT PRIMITIVES",
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
    # Get INPUT and COMMON parameter values.
    kwargs = {}
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
        pv = task.parameter_values.get(parameter__name=name)
        pv.value = value
        pv.save()

    task.status = 'SAVED'
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
