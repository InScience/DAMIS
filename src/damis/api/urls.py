from django.conf.urls.defaults import *
from piston.resource import Resource
from damis.api.handlers import DatasetHandler

dataset_handler = Resource(DatasetHandler)

urlpatterns = patterns('',
    url(r'^dataset/(?P<dataset_slug>[^/]+)/', dataset_handler),
    url(r'^datasets/', dataset_handler),
)
