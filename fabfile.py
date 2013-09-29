from fabric.api import task, run

@task
def upload_files():
    run("a command")
