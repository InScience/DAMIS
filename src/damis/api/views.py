from django.contrib.auth.models import User, Group
from rest_framework import viewsets
from damis.api.serializers import UserSerializer, GroupSerializer, DatasetSerializer, AlgorithmSerializer, ExperimentSerializer

from damis.models import Dataset, Algorithm, Experiment


class UserViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows users to be viewed or edited.
    """
    queryset = User.objects.all()
    serializer_class = UserSerializer

class GroupViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows groups to be viewed or edited.
    """
    queryset = Group.objects.all()
    serializer_class = GroupSerializer

class DatasetViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows datasets to be viewed or edited.
    """
    queryset = Dataset.objects.all()
    serializer_class = DatasetSerializer

class AlgorithmViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows algorithms to be viewed or edited.
    """
    queryset = Algorithm.objects.all()
    serializer_class = AlgorithmSerializer

class ExperimentViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows experiments to be viewed or edited.
    """
    queryset = Experiment.objects.all()
    serializer_class = ExperimentSerializer
