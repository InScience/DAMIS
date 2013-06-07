from django.shortcuts import render_to_response
from forms import LoginForm


def index(request):
    return render_to_response('index.html', {})

def login(request):
    form = LoginForm()
    return render_to_response('login.html', {
        'form': form,
    })
