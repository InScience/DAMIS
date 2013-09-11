from django.conf.urls import patterns, url, include
from rest_framework import routers
from damis.api import views

router = routers.DefaultRouter()
router.register(r'users', views.UserViewSet)
router.register(r'datasets', views.DatasetViewSet)
router.register(r'algorithms', views.AlgorithmViewSet)
router.register(r'experiments', views.ExperimentViewSet)

urlpatterns = patterns('',
    url(r'^', include(router.urls)),
    url(r'^api-auth/', include('rest_framework.urls', namespace='rest_framework'))
)
