from django.conf.urls import patterns, url, include
from django.conf import settings
from django.conf.urls.i18n import i18n_patterns

from django.contrib.staticfiles.urls import staticfiles_urlpatterns

from damis.views import *


urlpatterns = patterns('',
    (r'^api/', include('damis.api.urls')),
    (r'^i18n/', include('django.conf.urls.i18n')),
    url(r'^api-token-auth/', 'rest_framework.authtoken.views.obtain_auth_token'),
)

urlpatterns += i18n_patterns('',
    url(r'^$', index_view, name='home'),
    url(r'^about/$', static_page_view, name='home', kwargs={'template': 'index.html'}),
    url(r'^help/$', static_page_view, name='help', kwargs={'template': 'help.html'}),
    url(r'^faq/$', static_page_view, name='faq', kwargs={'template': 'faq.html'}),

    url(r'^login/$', login_view, name='login'),
    url(r'^register/$', register_view, name='register'),
    url(r'^profile/$', profile_settings_view, name='profile-settings'),
    url(r'^reset-password/$', reset_password_view, name='reset-password'),
    url(r'^logout/$', logout_view, name='logout'),

    url(r'^datasets/$', DatasetList.as_view(), name='dataset-list'),
    url(r'^datasets/new/$', DatasetCreate.as_view(), name='dataset-new'),
    url(r'^datasets/(?P<pk>\d*)/$', DatasetDetail.as_view(), name='dataset-detail'),
    url(r'^datasets/(?P<pk>\d*)/edit/$', DatasetUpdate.as_view(), name='dataset-update'),
    url(r'^datasets/(?P<pk>\d*)/delete/$', DatasetDelete.as_view(), name='dataset-delete'),

    url(r'^algorithms/$', AlgorithmList.as_view(), name='algorithm-list'),
    url(r'^algorithms/new/$', AlgorithmCreate.as_view(), name='algorithm-new'),
    url(r'^algorithms/(?P<pk>\d*)/edit/$', AlgorithmUpdate.as_view(), name='algorithm-update'),
    url(r'^algorithms/(?P<pk>\d*)/delete/$', AlgorithmDelete.as_view(), name='algorithm-delete'),

    url(r'^experiments/$', ExperimentList.as_view(), name='experiment-list'),
    url(r'^experiments/new/$', ExperimentCreate.as_view(), name='experiment-new'),
    url(r'^experiments/(?P<pk>\d*)/edit/$', ExperimentCreate.as_view(), name='experiment-update'),
    url(r'^experiments/(?P<pk>\d*)/delete/$', ExperimentDelete.as_view(), name='experiment-delete'),

    url(r'^experiments/(?P<pk>\d*)/confirm/$', ExperimentDetail.as_view(), name='experiment-confirm'),

    # Dynamic urls
    url(r'^x/algorithm-parameter-form/$', algorithm_parameter_form, name='parameters-form'),
    url(r'^x/gen-parameter-prefixes/$', gen_parameter_prefixes, name='gen-parameter-prefixes'),

)

urlpatterns += staticfiles_urlpatterns()
urlpatterns += patterns('',
    (r'^media/(?P<path>.*)$', 'django.views.static.serve',
     {'document_root': settings.MEDIA_ROOT}),
)
