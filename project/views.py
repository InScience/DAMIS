from django.shortcuts import render_to_response
from django.core.context_processors import csrf

from forms import LoginForm


def index(request):
    return render_to_response('index.html', {})

def login(request):
    c = {'form': LoginForm()}
    c.update(csrf(request))

    return render_to_response('login.html', c)
