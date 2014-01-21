#! coding: utf-8
import csv
import json
import re
import tempfile
from os.path import join, exists, getsize, splitext, split
from os import makedirs, listdir
from subprocess import call, Popen, PIPE

from collections import OrderedDict

from django.conf import settings
from django.contrib.auth import login, logout, authenticate
from django.contrib.auth.decorators import login_required
from django.contrib.auth import get_user_model
User = get_user_model()
from django.core.urlresolvers import reverse_lazy
from django.core.context_processors import csrf
from django.core.mail import send_mail
from django.db.models import Q
from django.http import HttpResponseRedirect, HttpResponse
from django.shortcuts import render, get_object_or_404, render_to_response
from django.template.loader import render_to_string
from django.utils.decorators import method_decorator
from django.utils.translation import ugettext_lazy as _
from django.utils.translation import ugettext
from django.forms.models import inlineformset_factory
from django.views.generic import CreateView, UpdateView, DeleteView, ListView, DetailView
from django.views.decorators.csrf import csrf_exempt

from damis.settings import BUILDOUT_DIR
from damis.constants import COMPONENT_TITLE__TO__FORM_URL, FILE_TYPE__TO__MIME_TYPE
from damis.utils import slugify, strip_arff_header

from damis.forms import LoginForm, RegistrationForm, EmailForm
from damis.forms import DatasetForm
from damis.forms import ComponentForm
from damis.forms import ParameterForm, ParameterFormset
from damis.forms import ExperimentForm
from damis.forms import WorkflowTaskFormset, CreateExperimentFormset, ParameterValueFormset, ParameterValueForm
from damis.forms import DatasetSelectForm
from damis.forms import UserUpdateForm
from damis.forms import VALIDATOR_FIELDS

from damis.models import Component
from damis.models import Cluster
from damis.models import Connection
from damis.models import Parameter, ParameterValue
from damis.models import Dataset
from damis.models import Experiment
from damis.models import WorkflowTask


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
    template_name = 'damis/algorithm_form.html'

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
    template_name = 'damis/algorithm_list.html'
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
    template_name = 'damis/algorithm_form.html'

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

    def get_queryset(self):
        qs = super(ExperimentList, self).get_queryset()
        return qs.order_by('-created')


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
        task_formset = WorkflowTaskFormset(instance=experiment)
        return self.render_to_response(self.get_context_data(
                    experiment=task_formset.instance,
                    task_formset=task_formset,
                ))

    def post(self, request, *args, **kwargs):
        self.object = None
        instance = Experiment.objects.get(pk=self.kwargs['pk'])

        task_formset = WorkflowTaskFormset(self.request.POST,
                                           instance=instance)
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
        context['component_form_urls'] = COMPONENT_TITLE__TO__FORM_URL.items()
        context['component_details'] = [[c.pk, {"title": c.title, "label": c.get_label_display(), "cluster_ico": c.cluster.icon.url, "ico": c.icon.url}] for c in Component.objects.all()]
        return context

    def skip_validation(self, experiment_form, task_formset):
        experiment_form.full_clean()
        exp_data = experiment_form.cleaned_data
        exp_data.pop('skip_validation')
        if experiment_form.instance and experiment_form.instance.pk:
            exp = experiment_form.instance
            experiment_form.save()
        else:
            exp = Experiment.objects.create(**exp_data)

        task_formset.full_clean()
        sources = {}
        for task_form in task_formset.forms:
            data = task_form.cleaned_data
            data['experiment'] = exp
            if data.get('algorithm'):
                task = data.get('id')
                if not task and not data.get('DELETE'):
                    if data.has_key('DELETE'):
                        data.pop('DELETE')
                    task = WorkflowTask.objects.create(**data)

                pv_formset = task_form.parameter_values[0]
                pv_formset.instance = task
                pv_formset.full_clean()

                for pv_form in pv_formset.forms:
                    data = {}
                    data['parameter'] = pv_form.cleaned_data.get('parameter')
                    data['value'] = pv_form.cleaned_data.get('value')
                    data['task'] = task

                    pv_form_prefix = pv_form.prefix

                    pv_instance = pv_form.cleaned_data.get('id')
                    if not pv_instance:
                        pv_instance = ParameterValue.objects.create(**data)
                    else:
                        if pv_form.cleaned_data.has_key('related'):
                            pv_form.cleaned_data.pop('related')
                        pv_form.save()
                    pv_form.instance = pv_instance

                    sources[pv_form_prefix] = pv_form.instance

        for task_form in task_formset.forms:
            for pv_form in task_form.parameter_values[0].forms:
                source_ref = pv_form.cleaned_data['source_ref']
                if source_ref:
                    source_ref = source_ref.split('-value')[0]
                    source = sources[source_ref]
                    target = pv_form.instance
                    exist = Connection.objects.filter(target=target, source=source)
                    if not exist:
                        Connection.objects.create(target=target, source=source)

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

        command = '{0}/bin/python {0}/src/damis/run_experiment.py {1}'.format(BUILDOUT_DIR, exp.pk)
        response = Popen(command, shell=True, stdout=PIPE, stderr=PIPE)
        # response.wait()
        # response.communicate()
        exp.status = 'RUNNING'
        exp.save()
        return HttpResponse(reverse_lazy('experiment-list'))

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

    val_params = algorithm.parameters.filter(Q(connection_type="INPUT_VALUE")|Q(connection_type="INPUT_CONNECTION")|Q(connection_type="OUTPUT_CONNECTION"))
    ParameterValueFormset = inlineformset_factory(WorkflowTask,
                                ParameterValue,
                                form=ParameterValueForm,
                                extra=len(val_params),
                                can_delete=False
                            )
    parameter_formset = ParameterValueFormset(instance=None, prefix=prefix)
    for parameter, form in zip(val_params, parameter_formset.forms):
        field_class = VALIDATOR_FIELDS[parameter.type]['class']
        field_attrs = VALIDATOR_FIELDS[parameter.type]['attrs']
        form.fields['value'] = field_class(**field_attrs)
        form.fields['value'].label = str(parameter)
        form.initial.update({'parameter': parameter, 'value': parameter.default})
        if form.instance and form.instance.value:
            form.initial['value'] = form.instance.value

    return render_to_response('dynamic/parameter_formset.html', {
        'formset': parameter_formset,
        })


def upload_file_form_view(request):
    context = csrf(request)
    if request.method == 'POST':
        form = DatasetForm(request.POST, request.FILES)
        if form.is_valid():
            dataset = form.save()
            context['file_path'] = dataset.file.url
    else:
        form = DatasetForm()
    context['form'] = form
    return render_to_response('damis/_dataset_form.html', context)


class ExistingFileView(LoginRequiredMixin, ListView):
    model = Dataset
    paginate_by = 10
    template_name = 'damis/_existing_file.html'
    success_url = reverse_lazy('dataset-list')

    def get_queryset(self):
        qs = super(ExistingFileView, self).get_queryset()
        return qs.order_by('-created')

    def get_context_data(self, **kwargs):
        context = super(ExistingFileView, self).get_context_data(**kwargs)
        context['request'] = self.request
        return context


def midas_file_form_view(request):
    return HttpResponse(_('Not implemented, yet'))

def select_features_form_view(request):
    return HttpResponse(_('Not implemented, yet'))

def file_to_table(file_url):
    '''Splits the file into header (rows) and content (structured as a matrix) portions.
    file_url - file path on the server
    '''
    f = open(BUILDOUT_DIR + '/var/www' + file_url)
    file_table = []
    header = []
    data_sec = False
    for row in f:
        if data_sec:
            file_table.append([cell for cell in row.split(",")])
        else:
            row_std = row.strip().lower()
            if row_std.startswith("@data"):
                data_sec = True
            elif row_std.startswith("@attribute"):
                parts = row.split()
                col_name = parts[1]
                col_type = parts[2]
                header.append([col_name, col_type])
    f.close()
    return header, file_table

def convert(file_path, file_format):
    '''Opens, converts file to specified format and returns it.
    file_path - file path on the server 
    file_format - result file format, desired by the user
    '''
    f = open(BUILDOUT_DIR + '/var/www' + file_path)
    if file_format == "arff":
        return f
    elif file_format == "csv" or file_format == "tab" or file_format == "txt" or file_format == "xls" or file_format == "xlsx":
        # strip the header
        file_no_header = tempfile.NamedTemporaryFile()
        data_sec = False
        for row in f:
            if data_sec:
                file_no_header.write(row)
            else:
                row_std = row.strip().lower()
                if row_std.startswith("@data"):
                    data_sec = True
        file_no_header.seek(0)
        res = file_no_header

        if file_format == "tab":
            # read stripped file as csv
            csv_reader = csv.reader(file_no_header, delimiter=',', quotechar='"')
            file_res = tempfile.NamedTemporaryFile()
            # write file as csv with a specific delimiter
            csv_writer = csv.writer(file_res, delimiter='\t', quotechar='"', quoting=csv.QUOTE_MINIMAL)
            for row in csv_reader:
                csv_writer.writerow(row)
            file_no_header.close()
            file_res.seek(0)
            res = file_res
        return res
    else:
        return f # default action - return arff

def technical_details_form_view(request):
    '''Handles Ajax GET request to update the technical details component.

    request - Ajax GET request. Fields:
        pv_name - OUTPUT_CONNECTION parameter form input name; used to track down the task, output of which should be rendered by the technical details component
    '''
    pv_name = request.GET.get('pv_name')
    context = {}
    if pv_name and re.findall('PV_PK(\d+)-\d+-value', pv_name):
        task_pk = re.findall('PV_PK(\d+)-\d+-value', pv_name)[0]
        task = WorkflowTask.objects.get(pk=task_pk)
        params = task.parameter_values.filter(parameter__connection_type="OUTPUT_VALUE")
        context['values'] = params

    if not context.get('values'):
        return HttpResponse(_('You have to execute this experiment first to see the result.'))
    else:
        return render_to_response('damis/_technical_details.html', context)

def download_file(file_url, file_format):
    '''Prepares the HTTP response to download a file in a given format.

    file_url - url from which to download the file
    file_format - file download format
    '''
    filename = splitext(split(file_url)[1])[0]
    response = HttpResponse(mimetype=FILE_TYPE__TO__MIME_TYPE[file_format])
    response['Content-Disposition'] = 'attachment; filename=%s.%s' % (filename, file_format)
    converted_file = convert(file_url, file_format=file_format)
    response.write(converted_file.read())
    return response

def matrix_form_view(request):
    '''Handles Ajax GET request to update the matrix view component.

    request - Ajax GET request. Fields:
        pv_name - OUTPUT_CONNECTION parameter form input name; used to track down the task, output of which should be rendered by the matrix view component
        dataset_url - url of the data file, which is to be rendered ty the matrix view component
        download - if True return a downloadable file, else return HTML
        format - file format
    '''
    pv_name = request.GET.get('pv_name')
    dataset_url = request.GET.get('dataset_url');
    context = {}
    if not pv_name or re.findall('PV_\d+-\d+-value', pv_name):
        if dataset_url:
            if request.GET.get('download'):
                return download_file(dataset_url, request.GET.get('format'))
            else:
                context['header'], context['file'] = file_to_table(dataset_url)
                return render_to_response('damis/_matrix_view.html', context)
        else:
            return HttpResponse(_('You have to execute this experiment first to see the result.'))
    else:
        task_pk = re.findall('PV_PK(\d+)-\d+-value', pv_name)[0]
        task = WorkflowTask.objects.get(pk=task_pk)
        file_params = task.parameter_values.filter(parameter__connection_type='OUTPUT_CONNECTION')
        # XXX: constraint: can download only first file OUTPUT_CONNECTION
        file_path = None
        if len(file_params) and file_params[0].value:
            file_path = file_params[0].value
            if request.GET.get('download'):
                return download_file(file_path, request.GET.get('format'))
            else:
                context['header'], context['file'] = file_to_table(file_path)
                return render_to_response('damis/_matrix_view.html', context)
        else:
            return HttpResponse(_('You have to execute this experiment first to see the result.'))

def read_classified_data(file_url):
    f = open(BUILDOUT_DIR + '/var/www' + file_url)
    f = strip_arff_header(f)
    clsCol = -1
    result = OrderedDict()
    minX = None; maxX = None
    minY = None; maxY = None
    for line in f:
        cells = line.rstrip().split(",")
        cls = cells[clsCol]
        if not cls in result:
            result[cls] = []
        result[cls].append([cells[0], cells[1]])

        if minX is None or float(cells[0]) < minX:
            minX = float(cells[0])
        if maxX is None or float(cells[0]) > maxX:
            maxX = float(cells[0])
        if minY is None or float(cells[1]) < minY:
            minY = float(cells[1])
        if maxY is None or float(cells[1]) > maxY:
            maxY = float(cells[1])

    f.close()
    result = [{"group": cls, "data": data} for cls, data in result.items()]
    return {"data": result, "minX": minX, "maxX": maxX, "minY": minY, "maxY": maxY}

def download_image(image, file_format):
    '''Prepares the HTTP response to download an image in a given format.

    image - image, as returned by the HTML5 canvas.toDataUrl() function
    file_format - image download format
    '''
    imgstr = re.findall(r'base64,(.*)', image)[0]

    response = HttpResponse(mimetype=FILE_TYPE__TO__MIME_TYPE[file_format])
    response['Content-Disposition'] = 'attachment; filename=%s.%s' % (ugettext("image"), file_format)
    response.write(imgstr.decode("base64"));
    return response

@csrf_exempt
def chart_form_view(request):
    '''Handles Ajax (GET or POST) request to update the chart component.

    request - Ajax request. 
        GET fields:
            pv_name - OUTPUT_CONNECTION parameter form input name; used to track down the task, output of which should be rendered by the chart component
            dataset_url - url of the data file, which is to be rendered ty the chart component

        POST fields:
            format - image file format
            image - image data, as returned by HTML5 canvas.toDataUrl() function
    '''
    if request.method == 'POST':
        return download_image(request.POST.get("image"), request.POST.get("format"))

    pv_name = request.GET.get('pv_name')
    dataset_url = request.GET.get('dataset_url');
    if not pv_name or re.findall('PV_\d+-\d+-value', pv_name):
        if dataset_url:
            content = read_classified_data(dataset_url)
            resp = {"status": "SUCCESS", "content": content}
            return HttpResponse(json.dumps(resp), content_type="application/json")
        else:
            resp = {"status": "ERROR", "message": unicode(_('You have to execute this experiment first to see the result.'))}
            return HttpResponse(json.dumps(resp), content_type="applicatioin/json")
    else:
        task_pk = re.findall('PV_PK(\d+)-\d+-value', pv_name)[0]
        task = WorkflowTask.objects.get(pk=task_pk)
        file_params = task.parameter_values.filter(parameter__connection_type='OUTPUT_CONNECTION')
        # XXX: constraint: can download only first file OUTPUT_CONNECTION
        file_path = None
        if len(file_params) and file_params[0].value:
            file_path = file_params[0].value
            content = read_classified_data(file_path)
            resp = {"status": "SUCCESS", "content": content}
            return HttpResponse(json.dumps(resp), content_type="application/json") 
        else:
            resp = {"status": "ERROR", "message": unicode(_('You have to execute this experiment first to see the result.'))}
            return HttpResponse(json.dumps(resp), content_type="applicatioin/json")

# User views
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

def profile_settings_view(request):
    pass


def reset_password_view(request):
    if request.method == 'POST':
        email_form = EmailForm(request.POST)
        if email_form.is_valid():
            receiver = email_form.cleaned_data.get('email')
            user = User.objects.get(email=receiver)
            # Get the domain.
            domain = 'test.damis.lt'
            subject = _('{0} password recovery').format(domain)
            body = render_to_string('accounts/mail/reset_password.html', {
                'domain': domain,
                'user': user.username,
                'recovery_url': domain,
            })
            sender = settings.DEFAULT_FROM_EMAIL
            send_mail(subject, body, sender, [receiver])
    else:
        email_form = EmailForm()
    return render(request, 'accounts/reset_password.html', {
                'form': email_form,
            })
