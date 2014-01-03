import sys
from damis.models import Experiment

exp_pk = sys.argv[1]
exp = Experiment.objects.get(pk=exp_pk)
exp.status = 'FINISHED'
exp.save()
