#! coding: utf-8
from django.shortcuts import render_to_response, render
from django.http import HttpResponseRedirect
from django.contrib.auth import login

from forms import LoginForm


def index(request):
    return render_to_response('index.html', {})

def login_view(request):
    if request.method == 'POST':
        form = LoginForm(request.POST)
        if form.is_valid():
            user = form.cleaned_data['user']
            if user is not None and user.is_active:
                request.session['password'] = form.cleaned_data['password']
                login(request, user)
                return HttpResponseRedirect('/')
    else:
        form = LoginForm()

    return render(request, 'login.html', {
            'form': form,
        })
