#! coding: utf-8
from django.shortcuts import render
from django.http import HttpResponseRedirect
from django.contrib.auth import login, logout

from forms import LoginForm, DataFileUploadForm


def index_view(request):
    return render(request, 'index.html', {})

def data_view(request):
    if request.method == 'POST':
        form = DataFileUploadForm(request.POST, request.FILES)
        if form.is_valid():
            # handle_uploaded_file(request.FILES['file'])
            return HttpResponseRedirect('/')
    form = DataFileUploadForm()
    return render(request, 'data.html', {
            'form': form,
        })

def experiments_view(request):
    return render(request, 'experiments.html', {})

def algorithms_view(request):
    return render(request, 'algorithms.html', {})

## User views
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

def logout_view(request):
    logout(request)
    request.session.clear()
    return HttpResponseRedirect('/login')
