#! coding: utf-8
from django import forms
from django.utils.translation import ugettext_lazy as _
from django.contrib.auth import authenticate


class LoginForm(forms.Form):
    username = forms.CharField(label=_('Naudotojo vardas'), max_length=100,
                               help_text=_('@uosis.mif.vu.lt'))
    password = forms.CharField(label=_(u'Slaptažodis'), max_length=128,
                        widget=forms.PasswordInput(render_value=False))

    def clean(self):
        cleaned_data = super(LoginForm, self).clean()
        if self.errors:
            return cleaned_data

        user = authenticate(**cleaned_data)
        if not user:
            raise forms.ValidationError(_(u'Naudotojo vardas arba slaptažodis '
                                            'yra neteisingas'))
        cleaned_data['user'] = user
        return cleaned_data

class DataFileUploadForm(forms.Form):
    title = forms.CharField(label=_('Pavadinimas'))
    data_file = forms.FileField(label=_(u'Duomenų failas'))
    comment = forms.CharField(label=_(u'Aprašymas'),
            widget=forms.Textarea(attrs={'rows':'5', 'cols': '25'}))
