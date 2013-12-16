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
    file = models.FileField(_('File'), upload_to=get_dataset_upload_path)
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

class Cluster(models.Model):
    title = models.CharField(_('Title'), max_length=255, null=True)
    url = models.URLField(_('Cluster home page'), max_length=255, null=True, blank=True)
    workload_url = models.URLField(_('Workload page'), max_length=255, null=True)

    def __unicode__(self):
        return self.title

class Component(models.Model):
    CATEGORIES= (
        ('DATA', _('Upload data')),
        ('PREPROCESSING', _('Preprocessing')),
        ('STAT_PRIMITIVES', _('Statistical primitives')),
        ('DIMENSION_REDUCTION', _('Dimension reduction')),
        ('DATA_MINING', _('Classification, grouping')),
        ('RESULTS', _('View results')),
    )
    title = models.CharField(_('Title'), max_length=255, null=True, blank=True)
    user = models.ForeignKey(User, blank=True, null=True, verbose_name=_('User'))
    category = models.CharField(_('Category'), max_length=255, null=True, blank=True, choices=CATEGORIES)
    wsdl = models.URLField(_('WSDL link'), null=True, blank=True)
    function = models.CharField(_('WSDL function name'), max_length=255, null=True, blank=True)
    updated = models.DateTimeField(_('Updated'), auto_now=True, blank=True, null=True)
    created = models.DateTimeField(_('Created'), auto_now_add=True, blank=True, null=True)
    icon = models.ImageField(_('Icon'), upload_to='icons', blank=True, null=True)
    cluster = models.ForeignKey('Cluster', null=True, verbose_name=_('Cluster'))
    label = models.CharField(_('Label EN'), max_length=255, null=True, blank=True)
    label_lt = models.CharField(_('Label LT'), max_length=255, null=True, blank=True)
    description = models.TextField(_('Description'), null=True, blank=True)
    description_lt = models.TextField(_('Description LT'), null=True, blank=True)

    def get_absolute_url(self):
        return reverse('algorithm-list')

    def __unicode__(self):
        return str(self.title)

class Parameter(models.Model):
    CONNECTION_TYPES = (
        ('INPUT_VALUE', 'Input value'),
        ('INPUT_CONNECTION', 'Input connection'),
        ('INPUT_COMMON', 'Input common'),
        ('OUTPUT_VALUE', 'Output value'),
        ('OUTPUT_CONNECTION', 'Output connection'),
    )
    VALIDATORS = (
        ('dataset', _('Dataset')),
        ('int', _('Integer')),
        ('float', _('Float')),
        ('double', _('Double')),
        ('string', _('String')),
        ('text', _('Text')),
        ('boolean', _('Boolean')),
        ('date', _('Date')),
        ('datetime', _('Date and time')),
        ('time', _('Time')),
    )
    algorithm = models.ForeignKey(Component, related_name='parameters',
                                  null=True, blank=True,
                                  verbose_name=_('Component'))
    name = models.CharField(_('Option'), max_length=255, null=True)
    type = models.CharField(_('Type'), choices=VALIDATORS , max_length=255, null=True, blank=True)
    required = models.BooleanField(_('Required'), blank=True)
    default = models.CharField(_('Default'), max_length=255, null=True, blank=True)
    connection_type = models.CharField(_('Connection type'), max_length=255, null=True, blank=True,
                              choices=CONNECTION_TYPES, default='INPUT_VALUE')
    label = models.CharField(_('Label EN'), max_length=255, null=True, blank=True)
    label_LT = models.CharField(_('Label LT'), max_length=255, null=True, blank=True)
    description = models.TextField(_('Description EN'), null=True, blank=True)
    description_LT = models.TextField(_('Description LT'), null=True, blank=True)

    def __unicode__(self):
        return '%s (%s)' % (self.name, self.type)

class Experiment(models.Model):
    STATUSES = (
        ('SAVED', _('Saved')),
        ('RUNNING', _('Running')),
        ('ERROR', _('Error')),
        ('FINISHED', _('Finished')),
    )
    title = models.CharField(_('Experiment title'), max_length=255, null=True)
    start = models.DateTimeField(_('Start'), blank=True, null=True)
    finish = models.DateTimeField(_('Finish'), blank=True, null=True)
    status = models.CharField(_('Status'), max_length=255, null=True, blank=True,
                              choices=STATUSES, default='SAVED')
    user = models.ForeignKey(User, blank=True, null=True, verbose_name=_('User'), related_name='experiments')
    workflow_state = models.TextField(_('Workflow state'), blank=True, null=True)

    max_calc_time = models.TimeField(_('Maximum calculation time'),
                                     default="2:00", null=True)
    p = models.IntegerField(_('Processor number'), default=1, null=True)

    def get_absolute_url(self):
        return reverse('experiment-list')

    def __unicode__(self):
        return str(self.title)


def get_result_file_upload_path(instance, filename):
    username = 'anonymous'
    if instance.algorithm.user:
        username = instance.algorithm.user.username
    return  '%s/result/%s' % (username, filename)

class WorkflowTask(models.Model):
    experiment = models.ForeignKey('Experiment', related_name='tasks',
                                   null=True, verbose_name=_('Experiment'))
    algorithm = models.ForeignKey('Component', verbose_name=_('Component'))

    def __unicode__(self):
        return '%s' % (self.algorithm.title,)

class ParameterValue(models.Model):
    parameter = models.ForeignKey('Parameter', verbose_name=_('Parameter'))
    value = models.CharField(max_length=255, blank=True)
    task = models.ForeignKey('WorkflowTask', related_name='parameter_values',
                                             verbose_name=_('Workflow Task'))
    related = models.ManyToManyField('self', symmetrical=False, null=True,
                                     blank=True, through='Connection')

    def __unicode__(self):
        return '%s: %s' % (self.task.algorithm, self.value)


class Connection(models.Model):
    source = models.ForeignKey('ParameterValue', null=True, blank=True,
                             verbose_name=_('Source'), related_name='source')
    target = models.ForeignKey('ParameterValue', null=True, blank=True,
                             verbose_name=_('Target'), related_name='target')
