from django.db import models
from django.contrib.auth.models import User
from django.utils.translation import ugettext_lazy as _

from os.path import splitext


class DatasetLicense(models.Model):
    title = models.CharField(max_length=255)
    short_title = models.CharField(max_length=30)
    url = models.URLField(null=True, blank=True)
    summary = models.TextField()
    updated = models.DateTimeField(auto_now=True)
    created = models.DateTimeField(auto_now_add=True)

    def get_absolute_url(self):
        return "/datasets/"

    def __unicode__(self):
        return self.short_title


class FileFormat(models.Model):
    extension = models.CharField(max_length=10)
    description = models.TextField()
    updated = models.DateTimeField(auto_now=True)
    created = models.DateTimeField(auto_now_add=True)

    def get_absolute_url(self):
        return "/datasets/"

    def __unicode__(self):
        return self.extension


def get_dataset_upload_path(instance, filename):
    username = 'test'
    if instance.author:
        username = instance.author.username
    return  '%s/%s%s' % (username, instance.slug, splitext(filename)[1])


class Dataset(models.Model):
    title = models.CharField(_('Title'), max_length=255)
    license = models.ForeignKey('DatasetLicense', blank=True, null=True, verbose_name=_('Dataset License'))
    file = models.FileField(upload_to=get_dataset_upload_path)
    file_format = models.ForeignKey('FileFormat', blank=True, null=True, verbose_name=_('File Format'))
    description = models.TextField(_('Description'), blank=True, null=True)
    author = models.ForeignKey(User, blank=True, null=True, verbose_name=_('User'))
    slug = models.SlugField(_('Slug'), max_length=40, blank=True, null=True)
    updated = models.DateTimeField(_('Updated'), auto_now=True, blank=True, null=True)
    created = models.DateTimeField(_('Created'), auto_now_add=True, blank=True, null=True)

    def get_absolute_url(self):
        return "/datasets/"

    def __unicode__(self):
        return self.title
