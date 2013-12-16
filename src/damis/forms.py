#! coding: utf-8
from django import forms
from django.forms.util import ErrorList
from django.utils.translation import ugettext_lazy as _
from django.contrib.auth import authenticate
from django.contrib.auth.models import User

from damis.models import Dataset
from damis.models import Component
from damis.models import Parameter
from damis.models import ParameterValue
from damis.models import Experiment
from damis.models import WorkflowTask

from django.forms.models import inlineformset_factory, BaseInlineFormSet
from django.forms.formsets import DELETION_FIELD_NAME

VALIDATOR_FIELDS = {
    'dataset': forms.CharField, # Text
    'int': forms.IntegerField,
    'string': forms.CharField,
    'text': forms.CharField, # Text
    'boolean': forms.BooleanField,
    'date': forms.DateField,
    'datetime': forms.DateTimeField,
    'time': forms.TimeField,
    'float': forms.FloatField,
    'double': forms.FloatField,
}

class DatasetForm(forms.ModelForm):
    class Meta:
        model = Dataset
        fields = ('title', 'file', 'description')

class DatasetSelectForm(forms.Form):
    dataset = forms.ModelChoiceField(queryset=Dataset.objects.all())


class LoginForm(forms.Form):
    username = forms.CharField(label=_('Username'), max_length=100,)
    password = forms.CharField(label=_('Password'), max_length=128,
                        widget=forms.PasswordInput(render_value=False))

    def clean(self):
        cleaned_data = super(LoginForm, self).clean()
        if self.errors:
            return cleaned_data

        user = authenticate(**cleaned_data)
        if not user:
            raise forms.ValidationError(_('Username or password is incorrect'))
        cleaned_data['user'] = user
        return cleaned_data

class RegistrationForm(forms.Form):
    username = forms.CharField(label=_('Username'), max_length=100,)
    password = forms.CharField(label=_('Password'), max_length=128,
                        widget=forms.PasswordInput(render_value=False))
    password_repeat = forms.CharField(label=_('Repeat Password'),
            max_length=128, widget=forms.PasswordInput(render_value=False))
    first_name = forms.CharField(label=_('First name'), max_length=100,)
    last_name = forms.CharField(label=_('Last name'), max_length=100,)
    email = forms.EmailField(label=_('E-mail'), max_length=100)

    def clean_username(self):
        username = self.cleaned_data.get('username')
        if User.objects.filter(username=username).exists():
            raise forms.ValidationError('This username is already taken.')
        return username

    def is_valid(self):
        valid = super(RegistrationForm, self).is_valid()
        if not valid:
            return valid

        first_password = self.cleaned_data.get('password')
        repeat_password = self.cleaned_data.get('password_repeat')

        if first_password == repeat_password:
            return True
        errors = self._errors.setdefault('password_repeat', ErrorList())
        errors.append(u'Passwords do not match')
        return False

    def save(self):
        data = self.cleaned_data
        password = data.pop('password')
        data.pop('password_repeat')
        user = User.objects.create(**self.cleaned_data)
        user.set_password(password)
        user.save()
        return user


class DataFileUploadForm(forms.Form):
    title = forms.CharField(label=_('Title'))
    data_file = forms.FileField(label=_('Dataset file'))
    comment = forms.CharField(label=_('Description'),
            widget=forms.Textarea(attrs={'rows':'5', 'cols': '25'}),
            required=False)


class ComponentForm(forms.ModelForm):
    class Meta:
        model = Component
        exclude = ['user']

class ParameterForm(forms.ModelForm):
    class Meta:
        model = Parameter
        fields = ['name', 'type', 'connection_type', 'required', 'default',
                  'label', 'description', 'label_LT', 'description_LT']

ParameterFormset = inlineformset_factory(Component, Parameter, extra=1, form=ParameterForm, can_delete=False)


class ExperimentForm(forms.ModelForm):
    workflow_state = forms.CharField(widget=forms.HiddenInput(), required=False)
    skip_validation = forms.CharField(widget=forms.HiddenInput(), required=False)

    class Meta:
        model = Experiment
        exclude = ['user', 'start', 'finish', 'status']


class UserUpdateForm(forms.ModelForm):
    class Meta:
        model = User
        fields = ['first_name', 'last_name', 'email', 'is_active']


class ParameterValueForm(forms.ModelForm):
    parameter = forms.ModelChoiceField(queryset=Parameter.objects.all(),
                                       widget=forms.HiddenInput())
    source_ref = forms.CharField(max_length=255, widget=forms.HiddenInput(), required=False)

    def __init__(self, *args, **kwargs):
        super(ParameterValueForm, self).__init__(*args, **kwargs)
        parameter = None
        if self.instance is not None and self.instance.pk:
            parameter = self.instance.parameter
        elif kwargs.get('instance'):
            parameter = kwargs['instance'].parameter
        elif self.data:
            parameter_id = self.data.get(self.prefix + '-parameter')
            if parameter_id:
                parameter = Parameter.objects.get(pk=parameter_id)

        if parameter:
            self.fields['value'] = VALIDATOR_FIELDS[parameter.type]()
            self.fields['value'].label = str(parameter)
            self.initial.update({'parameter': parameter})

        if self.instance and self.instance.source.all():
            pks = self.instance.source.task.algorithm.parameters.values_list('pk', flat=True)
            index = tuple(pks).index(self.instance.source.parameter.pk)
            self.initial.update({'source_ref': 'PV_PK%s-%s-value' % (self.instance.source.task.pk, index)})

    def is_valid(self):
        valid = super(ParameterValueForm, self).is_valid()
        if not valid:
            return valid

        value = self.cleaned_data.get('value')
        source_ref = self.cleaned_data.get('source_ref')
        if value or source_ref:
            return True
        errors = self._errors.setdefault('value', ErrorList())
        errors.append(u'Parameter value must be specified')
        return False

    def source_ref_to_obj(self, pv_prefix_to_obj):
        source_ref = self.cleaned_data['source_ref']
        if source_ref:
            obj = pv_prefix_to_obj[source_ref.split('-value')[0]]
            self.instance.source = obj
            self.instance.save()

    class Meta:
        model = ParameterValue


ParameterValueFormset = inlineformset_factory(WorkflowTask, ParameterValue,
                            form=ParameterValueForm, extra=0, can_delete=False)

class BaseWorkflowTaskFormset(BaseInlineFormSet):
    def add_fields(self, form, index):
        super(BaseWorkflowTaskFormset, self).add_fields(form, index)

        # Create the nested formset
        try:
            instance = self.get_queryset()[index]
            pk_value = instance.pk
            pv_prefix = 'PV_PK%s' % pk_value
        except IndexError:
            instance = None
            pk_value = hash(form.prefix)
            pv_prefix = 'PV_%s' % pk_value

        data = self.data if self.data and index is not None else None
        # Do not create PV formset if post data do not contain any elems with
        # pv_value prefix.
        if data and not [a for a in data.keys() if pv_prefix in a]:
            form.parameter_values = []
            return

        form.parameter_values = [ParameterValueFormset(data=data,
                                                      instance=instance,
                                                      prefix=pv_prefix)]

    def is_valid(self):
        result = super(BaseWorkflowTaskFormset, self).is_valid()
        for form in self.forms:
            if hasattr(form, 'parameter_values'):
                for pv_form in form.parameter_values:
                    result = result and pv_form.is_valid()
        return result


    def save_new(self, form, commit=True):
        """Saves and returns a new model instance for the given form."""
        instance = super(BaseWorkflowTaskFormset, self).save_new(form, commit=commit)

        form.instance = instance

        for pv in form.parameter_values:
            pv.instance = instance

            for cd in pv.cleaned_data:
                cd[pv.fk.name] = instance

        return instance

    def save_all(self, experiment=None, commit=True):
        if experiment:
            self.instance = experiment

        objects = self.save(commit=False)
        if commit:
            for o in objects:
                o.save()

        if not commit:
            self.save_m2m()

        pv_prefix_to_obj = {}
        for form in set(self.initial_forms + self.saved_forms):
            if self.should_delete(form):
                continue
            for pv in form.parameter_values:
                pv.save(commit=commit)
                for f in pv.forms:
                    pv_prefix_to_obj[f.prefix] = f.instance

        for form in set(self.initial_forms + self.saved_forms):
            for pv in form.parameter_values:
                for f in pv.forms:
                    f.source_ref_to_obj(pv_prefix_to_obj)


    def should_delete(self, form):
        if self.can_delete:
            raw_delete_value = form._raw_value(DELETION_FIELD_NAME)
            should_delete = form.fields[DELETION_FIELD_NAME].clean(raw_delete_value)
            return should_delete
        return False


class WorkflowTaskForm(forms.ModelForm):
    class Meta:
        model = WorkflowTask
        exclude = ['stdout', 'stderr', 'processors', 'sequence']

WorkflowTaskFormset = inlineformset_factory(Experiment, WorkflowTask,
        formset=BaseWorkflowTaskFormset, form=WorkflowTaskForm, extra=0,
        can_delete=False)
CreateExperimentFormset = inlineformset_factory(Experiment, WorkflowTask,
        formset=BaseWorkflowTaskFormset, form=WorkflowTaskForm, extra=1,
        can_delete=False)
