# coding: utf-8
from fabric.api import task, run, put
from damis.models import Experiment
from os.path import join, splitext, split

server_name = "demo.damis.lt"


@task
def run_experiment(pk):
    '''
    Uploads datasets and algorithms to supercomputer and starts task execution.

    Usage:
        bin/fab run_experiment:{pk} -H {username}@uosis.mif.vu.lt -p {password}
    '''
    experiment = Experiment.objects.get(pk=pk)
    experiment.status = 'UPLOADING'
    experiment.save()

    working_dir = '~/damis/%s/' % (experiment.pk,)
    for task in experiment.tasks.all():
        # Vars
        task_dir = join(working_dir, str(task.pk))
        proc = task.processors or 1

        # Upload files
        run('mkdir -p %s' % (task_dir,))
        archive = task.algorithm.file.path
        source_code_path = join(task_dir, 'source')
        run('mkdir -p %s' % (source_code_path,))
        put(archive, task_dir)
        if splitext(archive)[-1] == '.tar':
            run('tar -xzvf %s -C %s' % (join(task_dir, split(archive)[-1]), source_code_path))

        # Remotely create task executable
        cmd = "printf '#! /bin/sh\\nmpirun -np {proc} {exe}".format(proc=proc,
                        exe=join(source_code_path, task.algorithm.executable_file))
        for pv in task.parameter_values.all():
            cmd_name = pv.parameter.name
            value = pv.value
            cmd += ' %s=%s' % (cmd_name, value)

        cmd += '\n curl www.demo'
        cmd += "' | cat > {dir}/job.sh;".format(dir=task_dir)
        run(cmd)

        # Run command remotely
        ### run('chmod +x ~/{3}/job_{2}.sh')

        # Update experiment status remotely


    # Run first task execution with a wrapper, which informs about progress and
    # download results
    ### run('ssh cluster "mv ~/{3}/job_{2}.sh /scratch/lustre/damis/{1}/; '
    ###     'mv ~/{3}/{2} /scratch/lustre/damis/{1}/; '
    ###     'cd /scratch/lustre/damis/{1}; '
    ###     '/opt/slurm/bin/sbatch job_{2}.sh; '
    ###     'sleep 2; '
    ###     'mv /scratch/lustre/damis/{1}/result_{2} ~/{3}/; '
    ###     'exit"; '
    ###     'exit'.format(f, tmp_dir))
