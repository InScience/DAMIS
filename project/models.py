from django.contrib.auth.models import User
from subprocess import Popen, PIPE


class UosisMIFVUAuthBackend(object):
    def authenticate(self, username=None, password=None):
        login_check_cmd = """sshpass -p '%s' ssh -t -t -o \
StrictHostKeyChecking=no %s@uosis.mif.vu.lt 'pwd'""" % (password, username)
        login_response = Popen(login_check_cmd, shell=True, stdout=PIPE,
                                                            stderr=PIPE)
        login_response.wait()
        if not login_response.communicate()[0]:
            return None

        try:
            user = User.objects.get(username=username)
        except User.DoesNotExist:
            user = User(username=username)
            user.is_staff = False
            user.is_superuser = False
            user.set_unusable_password()
            user.save()
        return user

    def get_user(self, id):
        try:
            return User.objects.get(id=id)
        except User.DoesNotExist:
            return None
