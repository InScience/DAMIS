from __future__ import absolute_import
from __future__ import division

from django import template
from django.utils.translation import ugettext_lazy as _
from os.path import split

register = template.Library()


@register.filter
def filename(value):
    return split(value)[1]

@register.filter
def disable(value):
    value.field.widget.attrs['disabled'] = 'disabled'
    return value

@register.filter
def sizify(value):
    """
    Simple kb/mb/gb size snippet for templates:

    {{ product.file.size|sizify }}
    """
    value = int(value)
    if value < 512000:
        value = value / 1024.0
        ext = 'KB'
    elif value < 4194304000:
        value = value / 1048576.0
        ext = 'MB'
    else:
        value = value / 1073741824.0
        ext = 'GB'
    return '%s&nbsp;%s' % (str(round(value, 2)), ext)

@register.filter
def disable_if_connection(value):
    if value.form.initial.get('parameter'):
        parameter = value.form.initial.get('parameter')
    else:
        parameter = value.form.instance.parameter
    if parameter.connection_type == 'INPUT_CONNECTION':
        value.field.widget.attrs.update({'disabled': 'disabled'})
        value.field.initial = _('Comes from connection')
    return value
