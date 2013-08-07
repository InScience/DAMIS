from django.conf.urls.defaults import *
from django.conf import settings
from django.conf.urls.i18n import i18n_patterns

from django.contrib.staticfiles.urls import staticfiles_urlpatterns

from project.views import *


urlpatterns = patterns('',
    (r'^i18n/', include('django.conf.urls.i18n')),
)

urlpatterns += i18n_patterns('',
    (r'^$', index_view),
    (r'^login/$', login_view),
    (r'^logout/$', logout_view),
    (r'^data/$', data_view),
    (r'^algorithms/$', algorithms_view),
    (r'^experiments/$', experiments_view),

)

urlpatterns += staticfiles_urlpatterns()
urlpatterns += patterns('',
    (r'^media/(?P<path>.*)$', 'django.views.static.serve',
     {'document_root': settings.MEDIA_ROOT}),
)
