from django.db import models
from django.contrib.auth.models import User
from django.utils.translation import ugettext_lazy as _
from django.core.urlresolvers import reverse


def get_dataset_upload_path(instance, filename):
    username = 'anonymous'
    if instance.user:
        username = instance.user.username
    return  '%s/datasets/%s' % (username, filename)


class Dataset(models.Model):
    title = models.CharField(_('Title'), max_length=255)
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


class Algorithm(models.Model):
    CATEGORIES= (
        ('DATA', _('Upload data')),
        ('PREPROCESSING', _('Preprocessing')),
        ('STAT_PRIMITIVES', _('Statistical primitives')),
        ('DIMENSIONALITY_REDUCTION', _('Dimensionality reduction')),
        ('DATA_MINING',_('Data mining')),
        ('RESULTS', _('View results')),
    )
    title = models.CharField(_('Title'), max_length=255, null=True, blank=True)
    user = models.ForeignKey(User, blank=True, null=True, verbose_name=_('User'))
    category = models.CharField(_('Category'), max_length=255, null=True, blank=True, choices=CATEGORIES)
    file = models.FileField(upload_to=get_algorithm_file_upload_path)
    executable_file = models.CharField(_('Executable'), max_length=255, null=True, blank=True)
    updated = models.DateTimeField(_('Updated'), auto_now=True, blank=True, null=True)
    created = models.DateTimeField(_('Created'), auto_now_add=True, blank=True, null=True)
    icon = models.ImageField(upload_to='icons', blank=True, null=True)

    def get_absolute_url(self):
        return reverse('algorithm-list')

    def __unicode__(self):
        return str(self.title)

class Parameter(models.Model):
    CONNECTION_TYPES = (
        ('INPUT_VALUE', 'Input value'),
        ('INPUT_CONNECTION', 'Input connection'),
        ('OUTPUT_VALUE', 'Output value'),
        ('OUTPUT_CONNECTION', 'Output connection'),
    )
    algorithm = models.ForeignKey(Algorithm, related_name='parameters', null=True, blank=True)
    name = models.CharField(_('Option'), max_length=255, null=True)
    type = models.CharField(max_length=255, null=True, blank=True)
    required = models.BooleanField(blank=True)
    default = models.CharField(max_length=255, null=True, blank=True)
    is_output = models.BooleanField(blank=True, default=False)
    is_input = models.BooleanField(blank=True, default=False)
    connection_type = models.CharField(_('Connection type'), max_length=255, null=True, blank=True,
                              choices=CONNECTION_TYPES, default='INPUT_VALUE')

    def __unicode__(self):
        return '%s (%s)' % (self.name, self.type)


class Experiment(models.Model):
    STATUSES = (
        ('SAVED', 'Saved'),
        ('RUNNING', 'Running'),
        ('ERROR', 'Error'),
        ('FINISHED', 'Finished'),
    )
    CLUSTERS = (
            ('MII-CLUSTER', _('MII cluster, http://cluster.mii.lt')),   # http://cluster.mii.lt/ganglia/
            ('MIF-SK2', _('MIF VU SK2, http://mif.vu.lt/cluster/')),    # http://k007.mif.vu.lt/ganglia2/
    )
    title = models.CharField(_('Experiment title'), max_length=255, null=True)
    start = models.DateTimeField(_('Start'), blank=True, null=True)
    finish = models.DateTimeField(_('Finish'), blank=True, null=True)
    status = models.CharField(_('Status'), max_length=255, null=True, blank=True,
                              choices=STATUSES, default='SAVED')
    user = models.ForeignKey(User, blank=True, null=True, verbose_name=_('User'), related_name='experiments')
    workflow_state = models.TextField(blank=True, null=True)

    max_calc_time = models.TimeField(default="2:00", null=True)
    p = models.IntegerField(default=1, null=True)
    cluster = models.CharField(_('Cluster'), max_length=255, null=True,
                              choices=CLUSTERS, default='MII-CLUSTER')


    def get_absolute_url(self):
        return reverse('experiment-list')

    def __unicode__(self):
        return str(self.title)


def get_result_file_upload_path(instance, filename):
    username = 'anonymous'
    if instance.algorithm.user:
        username = instance.algorithm.user.username
    return  '%s/result/%s' % (username, filename)

class Task(models.Model):
    experiment = models.ForeignKey('Experiment', related_name='tasks', null=True)
    algorithm = models.ForeignKey('Algorithm')
    is_workflow_start = models.BooleanField(blank=True, default=False)

    def __unicode__(self):
        return '%s %s' % (self.sequence, self.algorithm.title)

class ParameterValue(models.Model):
    parameter = models.ForeignKey('Parameter')
    value = models.CharField(max_length=255, blank=True)
    task = models.ForeignKey('Task', related_name='parameter_values')
    source = models.ForeignKey('ParameterValue', null=True, blank=True)

    def __unicode__(self):
        return '%s: %s' % (self.task.algorithm, self.value)
