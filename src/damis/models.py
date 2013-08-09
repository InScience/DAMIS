from django.db import models
from django.contrib.auth.models import User


class DatasetLicence(models.Model):
    title = models.CharField(max_length=255)
    short_title = models.CharField(max_length=30)
    url = models.URLField()
    summary = models.TextField()
    updated = models.DatetimeField(auto_now=True)
    created = models.DatetimeField(auto_now_add=True)


class FileFormat(models.Model):
    extension = models.CharField(max_length=10)
    description = models.TextField()
    updated = models.DatetimeField(auto_now=True)
    created = models.DatetimeField(auto_now_add=True)


class Dataset(models.Model):
    title = models.CharField(max_length=255)
    licence = models.ForeignKey('DatasetLicence')
    file = models.FileField()
    file_format = models.ForeignKey('FileFormat')
    description = models.TextField()
    author = models.ForeignKey(User)
    updated = models.DatetimeField(auto_now=True)
    created = models.DatetimeField(auto_now_add=True)
