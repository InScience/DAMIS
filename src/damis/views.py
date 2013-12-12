#! coding: utf-8
import json
import re
from os.path import join, exists, getsize, splitext
from os import makedirs, listdir
from subprocess import Popen, PIPE

from django.conf import settings
from django.core.urlresolvers import reverse_lazy
from django.core.context_processors import csrf
from django.contrib.auth import login, logout, authenticate
from django.contrib.auth.decorators import login_required
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.models import User
from django.db.models import Q
from django.shortcuts import render, get_object_or_404, render_to_response
from django.http import HttpResponseRedirect, HttpResponse
from django.utils.decorators import method_decorator
from django.utils.translation import ugettext_lazy as _
from django.forms.models import modelformset_factory
from django.forms.models import inlineformset_factory
from django.views.generic import CreateView, UpdateView, DeleteView, ListView, DetailView

from damis.forms import LoginForm, RegistrationForm
from damis.forms import DatasetForm
from damis.forms import ComponentForm
from damis.forms import ParameterForm, ParameterFormset
from damis.forms import ExperimentForm
from damis.forms import TaskFormset, CreateExperimentFormset, ParameterValueFormset, ParameterValueForm
from damis.forms import DatasetSelectForm
from damis.forms import UserUpdateForm
from damis.forms import VALIDATOR_FIELDS


from damis.utils import slugify

from damis.models import Component
from damis.models import Parameter, ParameterValue
from damis.models import Dataset
from damis.models import Experiment
from damis.models import Task
from damis.models import Cluster


class LoginRequiredMixin(object):
    @method_decorator(login_required(login_url=reverse_lazy('login')))
    def dispatch(self, *args, **kwargs):
        return super(LoginRequiredMixin, self).dispatch(*args, **kwargs)

class SuperUserRequiredMixin(object):
    @method_decorator(login_required(login_url=reverse_lazy('login')))
    def dispatch(self, *args, **kwargs):
        user = self.request.user
        if not user.is_superuser:
            return HttpResponseRedirect(reverse_lazy('login'))
        return super(SuperUserRequiredMixin, self).dispatch(*args, **kwargs)

class ListDeleteMixin(object):
    success_url = reverse_lazy('home')

    def get_context_data(self, **kwargs):
        context = super(ListDeleteMixin, self).get_context_data(**kwargs)
        context['request'] = self.request
        return context

    def post(self, request, *args, **kwargs):
        action = request.POST.get('action')
        if action == 'delete':
            for pk in request.POST.getlist('pk'):
                obj = self.model.objects.get(pk=pk)
                obj.delete()
        return HttpResponseRedirect(self.success_url)

def index_view(request):
    return HttpResponseRedirect(reverse_lazy('experiment-new'))

def static_page_view(request, template):
    return render(request, template, {})

class DatasetCreate(LoginRequiredMixin, CreateView):
    model = Dataset
    template_name = 'damis/dataset_new.html'
    form_class = DatasetForm

    def form_valid(self, form):
        form.instance.slug = slugify(form.instance.title)
        return super(DatasetCreate, self).form_valid(form)


class DatasetList(ListDeleteMixin, LoginRequiredMixin, ListView):
    model = Dataset
    paginate_by = 50
    template_name = 'damis/dataset_list.html'
    success_url = reverse_lazy('dataset-list')

    def get_queryset(self):
        qs = super(DatasetList, self).get_queryset()
        return qs.order_by('-created')


class DatasetUpdate(LoginRequiredMixin, UpdateView):
    model = Dataset
    form_class = DatasetForm

class DatasetDetail(LoginRequiredMixin, DetailView):
    model = Dataset

class DatasetDelete(LoginRequiredMixin, DeleteView):
    model = Dataset
    success_url = reverse_lazy('dataset-list')

def dataset_download_view(request, pk, file_format):
    dataset = Dataset.objects.get(pk=pk)
    file = dataset.file
    response = HttpResponse(mimetype='text/csv')
    response['Content-Disposition'] = 'attachment; filename=%s.csv' % (file,)
    response.write(file.read())
    return response


class ComponentCreate(LoginRequiredMixin, CreateView):
    model = Component
    form_class = ComponentForm

    def get(self, request, *args, **kwargs):
        self.object = None
        form_class = self.get_form_class()
        form = self.get_form(form_class)
        parameter_form =  ParameterFormset()
        return self.render_to_response(
                self.get_context_data(form=form,
                    parameter_form=parameter_form))

    def post(self, request, *args, **kwargs):
        self.object = None
        form_class = self.get_form_class()
        form = self.get_form(form_class)
        parameter_form = ParameterFormset(self.request.POST)
        if form.is_valid() and parameter_form.is_valid():
            return self.form_valid(form, parameter_form)
        else:
            return self.form_invalid(form, parameter_form)

    def form_valid(self, form, parameter_form):
        self.object = form.save()
        parameter_form.instance = self.object
        parameter_form.save()
        return HttpResponseRedirect(self.get_success_url())

    def form_invalid(self, form, parameter_form):
        return self.render_to_response(self.get_context_data(form=form,
            parameter_form=parameter_form))


class ComponentList(ListDeleteMixin, LoginRequiredMixin, ListView):
    model = Component
    paginate_by = 30
    success_url = reverse_lazy('algorithm-list')


class UserList(ListDeleteMixin, SuperUserRequiredMixin, ListView):
    model = User
    template_name = 'damis/user_list.html'
    paginate_by = 30
    success_url = reverse_lazy('user-list')

class UserUpdate(LoginRequiredMixin, UpdateView):
    model = User
    form_class = UserUpdateForm
    template_name = 'damis/user_update.html'

    def get_success_url(self):
        return reverse_lazy('user-list')


class ComponentUpdate(LoginRequiredMixin, UpdateView):
    model = Component
    form_class = ComponentForm

    def post(self, request, *args, **kwargs):
        self.object = Component.objects.get(pk=self.kwargs['pk'])
        form_class = self.get_form_class()
        form = self.get_form(form_class)
        parameter_form = ParameterFormset(self.request.POST, instance=self.object)
        if form.is_valid() and parameter_form.is_valid():
            return self.form_valid(form, parameter_form)
        else:
            return self.form_invalid(form, parameter_form)

    def form_valid(self, form, parameter_form):
        self.object = form.save()
        parameter_form.instance = self.object
        parameter_form.save()
        return HttpResponseRedirect(self.get_success_url())

    def form_invalid(self, form, parameter_form):
        return self.render_to_response(self.get_context_data(form=form,
            parameter_form=parameter_form))

    def get_context_data(self, **kwargs):
        context = super(ComponentUpdate, self).get_context_data(**kwargs)
        ParameterFormset = inlineformset_factory(Component, Parameter, extra=0, can_delete=True)
        context['parameter_form'] = ParameterFormset(instance=self.object)
        return context

class ComponentDetail(LoginRequiredMixin, DetailView):
    model = Component

class ComponentDelete(LoginRequiredMixin, DeleteView):
    model = Component
    success_url = reverse_lazy('algorithm-list')


class ExperimentList(ListDeleteMixin, LoginRequiredMixin, ListView):
    model = Experiment
    paginate_by = 10
    success_url = reverse_lazy('experiment-list')

class ExperimentDetail(LoginRequiredMixin, DetailView):
    model = Experiment

class ExperimentDelete(LoginRequiredMixin, DeleteView):
    model = Experiment
    success_url = reverse_lazy('experiment-list')

class ExperimentUpdate(LoginRequiredMixin, UpdateView):
    model = Experiment

    def get(self, request, *args, **kwargs):
        self.object = None
        experiment = get_object_or_404(Experiment, pk=self.kwargs['pk'])
        task_formset = TaskFormset(instance=experiment)
        return self.render_to_response(self.get_context_data(
                    experiment=task_formset.instance,
                    task_formset=task_formset,
                ))

    def post(self, request, *args, **kwargs):
        self.object = None
        instance = Experiment.objects.get(pk=self.kwargs['pk'])

        task_formset = TaskFormset(self.request.POST, instance=instance)
        if task_formset.is_valid():
            return self.form_valid(task_formset)
        else:
            return self.form_invalid(task_formset)

    def form_valid(self, task_formset):
        self.object = task_formset.save_all()
        return HttpResponseRedirect(reverse_lazy('experiment-list'))

    def form_invalid(self, task_formset):
        return self.render_to_response(self.get_context_data(
                        experiment=task_formset.instance,
                        task_formset=task_formset,
                    ))


class ExperimentCreate(LoginRequiredMixin, CreateView):
    model = Experiment
    template_name = 'damis/experiment_create.html'

    def get(self, request, *args, **kwargs):
        self.object = None

        experiment_pk = self.kwargs.get('pk')
        if experiment_pk:
            experiment = Experiment.objects.get(pk=experiment_pk)
        else:
            experiment = Experiment()

        experiment_form = ExperimentForm(instance=experiment)
        task_formset = CreateExperimentFormset(instance=experiment)

        # Move one extra empty task formset to the begining of forms
        form_count = len(task_formset.forms)
        task_formset.forms.insert(0, task_formset.forms.pop(form_count - 1))

        return self.render_to_response(self.get_context_data(
                    experiment=task_formset.instance,
                    task_formset=task_formset,
                    experiment_form=experiment_form,
                ))

    def get_context_data(self, **kwargs):
        context = super(ExperimentCreate, self).get_context_data(**kwargs)
        context['dataset_form'] = DatasetSelectForm()
        context.update(csrf(self.request))

        # assign component to clusters by category
        algorithms = Component.objects.all()
        clusters = dict()
        for algorithm in algorithms:
            if not algorithm.cluster in clusters:
                clusters[algorithm.cluster] = dict()
            cat_name = algorithm.get_category_display()
            if not cat_name in clusters[algorithm.cluster]:
                clusters[algorithm.cluster][cat_name] = []
            clusters[algorithm.cluster][cat_name].append(algorithm)

        # sort algorithms by clusters and categories
        all_clusters = Cluster.objects.all()
        sorted_clusters = []
        for cluster in all_clusters:
            b = []
            for cat, cat_name in Component.CATEGORIES:
                if cluster in clusters and cat_name in clusters[cluster]:
                    b.append([cat_name, clusters[cluster][cat_name]]);
            a = [cluster, b]
            sorted_clusters.append(a);

        context['clusters'] = sorted_clusters
        return context

    def skip_validation(self, experiment_form, task_formset):
        experiment_form.full_clean()
        exp_data = experiment_form.cleaned_data
        exp_data.pop('skip_validation')
        if experiment_form.instance and experiment_form.instance.pk:
            exp = experiment_form.instance
        else:
            exp = Experiment.objects.create(**exp_data)

        task_formset.full_clean()
        sources = {}
        for task_form in task_formset.forms:
            data = task_form.cleaned_data
            data['experiment'] = exp
            if data.get('algorithm'):
                task = Task.objects.create(**data)

                pv_formset = task_form.parameter_values[0]
                pv_formset.instance = task
                pv_formset.full_clean()

                for pv_form in pv_formset.forms:
                    data = {}
                    data['parameter'] = pv_form.cleaned_data.get('parameter')
                    data['value'] = pv_form.cleaned_data.get('value')
                    data['task'] = task
                    pv_form.instance = ParameterValue.objects.create(**data)
                    sources[pv_form.prefix] = pv_form.instance

                for pv_form in pv_formset.forms:
                    source_ref = pv_form.cleaned_data['source_ref']
                    if source_ref:
                        source_ref = source_ref.split('-value')[0]
                        pv_form.instance.source = sources[source_ref]
                        pv_form.instance.save()

        return HttpResponse(reverse_lazy('experiment-update', kwargs={'pk': exp.pk}))

    def post(self, request, *args, **kwargs):
        self.object = None

        experiment_pk = self.kwargs.get('pk')
        if experiment_pk:
            experiment = Experiment.objects.get(pk=experiment_pk)
        else:
            experiment = Experiment()

        experiment_form = ExperimentForm(self.request.POST, instance=experiment)
        task_formset = CreateExperimentFormset(self.request.POST, instance=experiment)

        if self.request.POST.get('skip_validation'):
            return self.skip_validation(experiment_form, task_formset)

        if experiment_form.is_valid() and task_formset.is_valid():
            return self.form_valid(experiment_form, task_formset)
        else:
            return self.form_invalid(experiment_form, task_formset)

    def form_valid(self, experiment_form, task_formset):
        exp = experiment_form.save()
        self.object = task_formset.save_all(experiment=exp)

        # run_exp_cmd = "bin/fab run_experiment:%s -H %s@uosis.mif.vu.lt -p %s" % (
        #         experiment.pk,
        #         self.request.user.username,
        #         self.request.session['password'])
        # shell_response = Popen(run_exp_cmd, shell=True)

        return HttpResponse(reverse_lazy('experiment-update', kwargs={'pk': exp.pk}))

    def form_invalid(self, experiment_form, task_formset):
        return render_to_response('damis/_experiment_form.html',
                        self.get_context_data(
                            experiment=task_formset.instance,
                            task_formset=task_formset,
                            experiment_form=experiment_form,
                        ))


def gen_parameter_prefixes(request):
    prefixes = request.GET.getlist('prefixes[]')
    task_ids = request.GET.getlist('taskIds[]')
    task_prefixes = [re.findall('(tasks-\d+)', prefix)[0] for prefix in prefixes]
    pv_prefixes = []
    for task_id, task_prefix in zip(task_ids, task_prefixes):
        if task_id and task_id != '-':
            pv_prefixes.append('PV_PK%s' % (task_id,))
        else:
            pv_prefixes.append('PV_%s' % (str(hash(task_prefix)),))
    return HttpResponse(",".join(pv_prefixes))

def algorithm_parameter_form(request):
    algorithm = get_object_or_404(Component, pk=request.GET.get('algorithm_id'))
    task_form_prefix = re.findall('[id_]*(\w+-\d+)', request.GET.get('prefix'))[0]
    prefix = 'PV_%s' % hash(task_form_prefix)

    val_params = algorithm.parameters.filter(~Q(connection_type="OUTPUT_VALUE"))
    ParameterValueFormset = inlineformset_factory(Task,
                                ParameterValue,
                                form=ParameterValueForm,
                                extra=len(val_params),
                                can_delete=False
                            )
    parameter_formset = ParameterValueFormset(instance=None, prefix=prefix)
    for parameter, form in zip(val_params, parameter_formset.forms):
        form.fields['value'] = VALIDATOR_FIELDS[parameter.type]()
        form.fields['value'].label = str(parameter)
        form.initial.update({'parameter': parameter})

    return render_to_response('dynamic/parameter_form.html', {
        'formset': parameter_formset,
        })


def register_view(request):
    form = RegistrationForm()
    if request.method == 'POST':
        form = RegistrationForm(request.POST)
        if form.is_valid():
            username = form.cleaned_data.get('username')
            password = form.cleaned_data.get('password')
            user = form.save()
            user = authenticate(username=username, password=password)
            if user is not None and user.is_active:
                login(request, user)
                return HttpResponseRedirect(reverse_lazy('home'))
    return render(request, 'accounts/register.html', {
        'form': form,
    })


def profile_settings_view(request):
    pass

def reset_password_view(request):
    pass


def login_view(request):
    if request.method == 'POST':
        form = LoginForm(request.POST)
        if form.is_valid():
            user = form.cleaned_data['user']
            if user is not None and user.is_active:
                login(request, user)
                return HttpResponseRedirect(reverse_lazy('home'))
    else:
        form = LoginForm()

    return render(request, 'accounts/login.html', {
            'form': form,
        })

def logout_view(request):
    logout(request)
    request.session.clear()
    return HttpResponseRedirect('/login/')
