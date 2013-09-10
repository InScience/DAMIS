#! coding: utf-8
from django import forms
from django.utils.translation import ugettext_lazy as _
from django.contrib.auth import authenticate

from damis.models import Dataset
from damis.models import Algorithm
from damis.models import Parameter
from damis.models import Experiment
from damis.models import Task


class DatasetForm(forms.ModelForm):
    class Meta:
        model = Dataset
        fields = ('title', 'license', 'file', 'description')


class LoginForm(forms.Form):
    username = forms.CharField(label=_('Username'), max_length=100,
                               help_text=_('@uosis.mif.vu.lt'))
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

DATA_LICENSES = (
    ('private', _('Private')),
    ('open', _('Open under http://opendatacommons.org/licenses/pddl/')),
)

class DataFileUploadForm(forms.Form):
    title = forms.CharField(label=_('Title'))
    data_file = forms.FileField(label=_('Dataset file'))
    license = forms.ChoiceField(label=_('License'), choices=DATA_LICENSES)
    comment = forms.CharField(label=_('Description'),
            widget=forms.Textarea(attrs={'rows':'5', 'cols': '25'}),
            required=False)


class AlgorithmForm(forms.ModelForm):
    class Meta:
        model = Algorithm
        exclude = ['user']

class ExperimentForm(forms.ModelForm):
    class Meta:
        model = Experiment
        exclude = ['user']

class TaskForm(forms.ModelForm):
    class Meta:
        model = Task
        fields = ['dataset', 'algorithm']

class ParameterForm(forms.ModelForm):
    class Meta:
        model = Parameter
        fields = ['name', 'type', 'required', 'default']
