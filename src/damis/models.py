from django.db import models
from django.contrib.auth.models import User


class DatasetLicence(models.Model):
    title = models.CharField(max_length=255)
    short_title = models.CharField(max_length=30)
    url = models.URLField()
    summary = models.TextField()
    updated = models.DateTimeField(auto_now=True)
    created = models.DateTimeField(auto_now_add=True)


class FileFormat(models.Model):
    extension = models.CharField(max_length=10)
    description = models.TextField()
    updated = models.DateTimeField(auto_now=True)
    created = models.DateTimeField(auto_now_add=True)


def get_dataset_upload_path(self, instance, filename):
    return '/%s/' % instance.author.username

class Dataset(models.Model):
    title = models.CharField(max_length=255)
    licence = models.ForeignKey('DatasetLicence')
    file = models.FileField(upload_to=get_dataset_upload_path)
    file_format = models.ForeignKey('FileFormat')
    description = models.TextField()
    author = models.ForeignKey(User)
    slug = models.SlugField(max_length=40)
    updated = models.DateTimeField(auto_now=True)
    created = models.DateTimeField(auto_now_add=True)
