from django.conf.urls import patterns, url, include
from django.conf import settings
from django.conf.urls.i18n import i18n_patterns

from django.contrib.staticfiles.urls import staticfiles_urlpatterns

from damis.views import *


urlpatterns = patterns('',
    (r'^api/', include('damis.api.urls')),
    (r'^i18n/', include('django.conf.urls.i18n')),
)

urlpatterns += i18n_patterns('',
    url(r'^$', index_view, name='home'),
    url(r'^login/$', login_view, name='login'),
    url(r'^logout/$', logout_view, name='logout'),
    url(r'^datasets/$', DatasetList.as_view(), name='dataset-list'),
    url(r'^dataset/new/$', DatasetCreate.as_view(), name='dataset-new'),
    url(r'^dataset/(?P<pk>\d*)/$', DatasetDetail.as_view(), name='dataset-detail'),
    url(r'^dataset/(?P<pk>\d*)/edit/$', DatasetUpdate.as_view(), name='dataset-update'),
    url(r'^dataset/(?P<pk>\d*)/delete/$', DatasetDelete.as_view(), name='dataset-delete'),
    url(r'^datasets/licenses/create/$', DatasetLicenseCreate.as_view()),

    url(r'^algorithms/$', AlgorithmList.as_view(), name='algorithm-list'),
    url(r'^algorithm/new/$', AlgorithmCreate.as_view(), name='algorithm-new'),

    url(r'^experiments/$', ExperimentList.as_view(), name='experiment-list'),
    url(r'^experiment/new/$', ExperimentCreate.as_view(), name='experiment-new'),
)

urlpatterns += staticfiles_urlpatterns()
urlpatterns += patterns('',
    (r'^media/(?P<path>.*)$', 'django.views.static.serve',
     {'document_root': settings.MEDIA_ROOT}),
)
