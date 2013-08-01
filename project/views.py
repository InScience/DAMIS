#! coding: utf-8
import json
from os.path import join, exists, getsize, splitext
from os import makedirs, listdir

from django.shortcuts import render
from django.http import HttpResponseRedirect
from django.contrib.auth import login, logout
from django.contrib.auth.decorators import login_required
from django.conf import settings

from forms import LoginForm, DataFileUploadForm
from utils import slugify

DATA_LICENCE_SHORT = {
    'private': u'Privatūs',
    'public': u'Vieši'
}


def index_view(request):
    return render(request, 'index.html', {})

@login_required
def data_view(request):
    absolute_dir = settings.MEDIA_ROOT
    user_dir = join(absolute_dir, request.user.username)
    if not exists(user_dir):
        makedirs(user_dir)

    files = []
    for f in listdir(user_dir):
        if f.endswith('.names'):
            f_meta = json.load(open(join(user_dir, f)))
            f_meta['licence'] = DATA_LICENCE_SHORT[f_meta['licence']]
            files.append(f_meta)
            files[-1]['size'] = str(getsize(join(user_dir, splitext(f)[0]+'.csv'))) + ' B'
            # files.append(f_meta)

    # files = [f for f in listdir(user_dir) if f.endswith('.names')]

    if request.method == 'POST':
        form = DataFileUploadForm(request.POST, request.FILES)
        if form.is_valid():
            meta_data = {
                'title': form.cleaned_data['title'],
                'licence': form.cleaned_data['licence'],
                'comment': form.cleaned_data['comment'],
            }
            # STUB: aboslute_dir should be in supercomputer, not in web server

            filename = slugify(form.cleaned_data['title'])
            meta_file = open(join(user_dir, filename + '.names'), 'w')
            data_file = open(join(user_dir, filename + '.csv'), 'w')

            # TODO: SCP meta-data file and uploaded file to logged in user home directory
            json.dump(meta_data, meta_file, indent=4)
            data_file.write(form.cleaned_data['data_file'].read())
            meta_file.close()
            data_file.close()
            return HttpResponseRedirect('/')

    form = DataFileUploadForm()
    return render(request, 'data.html', {
            'form': form,
            'files': files,
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
