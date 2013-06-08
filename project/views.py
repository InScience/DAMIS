#! coding: utf-8
from django.shortcuts import render_to_response, render
from django.utils.translation import ugettext_lazy as _
from django.http import HttpResponseRedirect

from forms import LoginForm


def index(request):
    return render_to_response('index.html', {})

def login(request):
    if request.method == 'POST':
        form = LoginForm(request.POST)
        if form.is_valid():
            return HttpResponseRedirect('/')
    else:
        form = LoginForm()

    return render(request, 'login.html', {
            'form': form,
        })
