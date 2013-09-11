from django.db import models
from django.contrib.auth.models import User
from django.utils.translation import ugettext_lazy as _
from django.core.urlresolvers import reverse
# from django.contrib.contenttypes import generic
# from django.contrib.contenttypes.models import ContentType


class DatasetLicense(models.Model):
    title = models.CharField(max_length=255)
    description = models.TextField(_('Description'), blank=True, null=True)
    url = models.URLField(null=True, blank=True)
    summary = models.TextField()
    updated = models.DateTimeField(auto_now=True)
    created = models.DateTimeField(auto_now_add=True)

    def get_absolute_url(self):
        return "/datasets/"

    def __unicode__(self):
        return self.title


def get_dataset_upload_path(instance, filename):
    username = 'anonymous'
    if instance.user:
        username = instance.user.username
    return  '%s/datasets/%s' % (username, filename)


class Dataset(models.Model):
    title = models.CharField(_('Title'), max_length=255)
    license = models.ForeignKey('DatasetLicense', blank=True, null=True, verbose_name=_('Dataset License'))
    file = models.FileField(upload_to=get_dataset_upload_path)
    description = models.TextField(_('Description'), blank=True, null=True)
    user = models.ForeignKey(User, blank=True, null=True, verbose_name=_('User'))
    updated = models.DateTimeField(_('Updated'), auto_now=True, blank=True, null=True)
    created = models.DateTimeField(_('Created'), auto_now_add=True, blank=True, null=True)

    def get_absolute_url(self):
        return reverse('dataset-list')

    def __unicode__(self):
        return self.title



def get_algorithm_file_upload_path(instance, filename):
    username = 'anonymous'
    if instance.user:
        username = instance.user.username
    return  '%s/algorithms/%s' % (username, filename)


#class File(models.Model):
#    file = models.FileField(upload_to=get_algorithm_file_upload_path)
#    algorithm = models.ForeignKey('Algorithm', related_name='files')

class Algorithm(models.Model):
    title = models.CharField(_('Title'), max_length=255, null=True, blank=True)
    user = models.ForeignKey(User, blank=True, null=True, verbose_name=_('User'))
    file = models.FileField(upload_to=get_algorithm_file_upload_path)
    executable_file = models.CharField(_('Executable'), max_length=255, null=True, blank=True)
    updated = models.DateTimeField(_('Updated'), auto_now=True, blank=True, null=True)
    created = models.DateTimeField(_('Created'), auto_now_add=True, blank=True, null=True)

    def get_absolute_url(self):
        return reverse('algorithm-list')

    def __unicode__(self):
        return self.title

class Parameter(models.Model):
    algorithm = models.ForeignKey(Algorithm, related_name='parameters')
    name = models.CharField(_('Title'), max_length=255, null=True, blank=True)
    type = models.CharField(max_length=255)
    required = models.BooleanField()
    default = models.CharField(max_length=255)

class Experiment(models.Model):
    start = models.DateTimeField(_('Updated'), auto_now=True, blank=True, null=True)
    finish = models.DateTimeField(_('Updated'), auto_now=True, blank=True, null=True)
    user = models.ForeignKey(User, blank=True, null=True, verbose_name=_('User'), related_name='experiments')
    processors = models.IntegerField()


def get_result_file_upload_path(instance, filename):
    username = 'anonymous'
    if instance.algorithm.user:
        username = instance.algorithm.user.username
    return  '%s/result/%s' % (username, filename)

class Task(models.Model):
    experiment = models.ForeignKey('Experiment', related_name='tasks', blank=True, null=True)
    dataset = models.ForeignKey('Dataset', blank=True, null=True)
    algorithm = models.ForeignKey('Algorithm')
    sequence = models.IntegerField(blank=True, null=True)
    stdout = models.TextField(blank=True, null=True)
    stderr = models.TextField(blank=True, null=True)

class TaskFile(models.Model):
    file = models.FileField(upload_to=get_algorithm_file_upload_path)
    task = models.ForeignKey('Task', related_name='files')

class ParameterValue(models.Model):
    parameter = models.ForeignKey('Parameter')
    value = models.CharField(max_length=255)
    task = models.ForeignKey('Task', related_name='parameter_values')
