from __future__ import absolute_import
from __future__ import division

from django import template
from os.path import split

register = template.Library()


@register.filter
def filename(value):
    return split(value)[1]

@register.filter
def disable(value):
    value.field.widget.attrs['disabled'] = 'disabled'
    return value
