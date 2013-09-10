#! coding: utf-8
import json
from os.path import join, exists, getsize, splitext
from os import makedirs, listdir

from django.core.urlresolvers import reverse_lazy
from django.views.generic import CreateView, UpdateView, DeleteView, ListView, DetailView
from django.shortcuts import render
from django.http import HttpResponseRedirect
from django.contrib.auth import login, logout
from django.contrib.auth.decorators import login_required
from django.conf import settings
from django.utils.decorators import method_decorator
from django.utils.translation import ugettext_lazy as _
from django.forms.models import modelformset_factory

from damis.forms import LoginForm
from damis.forms import ParameterForm
from damis.forms import DatasetForm
from damis.forms import AlgorithmForm
from damis.forms import ExperimentForm
from damis.forms import TaskForm

from damis.utils import slugify

from damis.models import Algorithm
from damis.models import Parameter
from damis.models import Dataset
from damis.models import DatasetLicense
from damis.models import Experiment
from damis.models import Task


class LoginRequiredMixin(object):
    @method_decorator(login_required(login_url=reverse_lazy('login')))
    def dispatch(self, *args, **kwargs):
        return super(LoginRequiredMixin, self).dispatch(*args, **kwargs)


def index_view(request):
    return render(request, 'index.html', {})


class DatasetCreate(LoginRequiredMixin, CreateView):
    model = Dataset
    template_name = 'damis/dataset_new.html'
    form_class = DatasetForm

    def form_valid(self, form):
        form.instance.slug = slugify(form.instance.title)
        return super(DatasetCreate, self).form_valid(form)

class DatasetList(LoginRequiredMixin, ListView):
    model = Dataset
    paginate_by = 50
    template_name = 'damis/dataset_list.html'

    def get_queryset(self):
        qs = super(DatasetList, self).get_queryset()
        return qs.order_by('-created')

class DatasetUpdate(LoginRequiredMixin, UpdateView):
    model = Dataset

class DatasetDetail(LoginRequiredMixin, DetailView):
    model = Dataset

class DatasetDelete(LoginRequiredMixin, DeleteView):
    model = Dataset
    success_url = reverse_lazy('dataset-list')


class AlgorithmCreate(LoginRequiredMixin, CreateView):
    model = Algorithm
    form_class = AlgorithmForm

    def post(self, request, *args, **kwargs):
        algorithm_form = AlgorithmForm(request.POST)
        ParameterFormSet = modelformset_factory(Parameter)
        parameter_form = ParameterFormSet(request.POST)
        if algorithm_form.is_valid() and parameter_form.is_valid():
            algorithm_form.save()
            parameter_form.save()

        kwargs.update({
            'form': algorithm_form,
            'parameter_forms': parameter_form,
            })
        # return self.get(request, *args, **kwargs)
        return super(AlgorithmCreate, self).get(request, *args, **kwargs)

    def get_context_data(self, **kwargs):
        context = super(AlgorithmCreate, self).get_context_data(**kwargs)
        context['parameter_forms'] = modelformset_factory(Parameter, form=ParameterForm)
        return context

class AlgorithmList(LoginRequiredMixin, ListView):
    model = Algorithm

class AlgorithmUpdate(LoginRequiredMixin, UpdateView):
    model = Algorithm

class AlgorithmDetail(LoginRequiredMixin, DetailView):
    model = Algorithm

class AlgorithmDelete(LoginRequiredMixin, DeleteView):
    model = Algorithm
    success_url = reverse_lazy('algorithm-list')


class ExperimentList(LoginRequiredMixin, ListView):
    model = Experiment

class ExperimentCreate(LoginRequiredMixin, CreateView):
    model = Experiment
    form_class = ExperimentForm

    def get_context_data(self, **kwargs):
        context = super(ExperimentCreate, self).get_context_data(**kwargs)
        context['tasks'] = modelformset_factory(Task, form=TaskForm, extra=1)
        return context



class DatasetLicenseCreate(LoginRequiredMixin, CreateView):
    model = DatasetLicense
    template_name = 'damis/obj_form.html'




## User views
def login_view(request):
    if request.method == 'POST':
        form = LoginForm(request.POST)
        if form.is_valid():
            user = form.cleaned_data['user']
            if user is not None and user.is_active:
                request.session['password'] = form.cleaned_data['password']
                login(request, user)
                return HttpResponseRedirect(reverse_lazy('home'))
    else:
        form = LoginForm()

    return render(request, 'login.html', {
            'form': form,
        })

def logout_view(request):
    logout(request)
    request.session.clear()
    return HttpResponseRedirect('/login/')
