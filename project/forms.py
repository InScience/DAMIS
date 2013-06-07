#! coding: utf-8
from django import forms
from django.utils.translation import ugettext_lazy as _

class LoginForm(forms.Form):
    username = forms.CharField(label=_('Naudotojo vardas'), max_length=100)
    password = forms.CharField(label=_(u'Slaptažodis'), max_length=128,
                        widget=forms.PasswordInput(render_value=False))
