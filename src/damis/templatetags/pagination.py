"""
Based on algorythm in django.contrib.admin.templatetags.paginate
"""
from __future__ import absolute_import
import urllib
import itertools


from django.forms.util import flatatt
from django.utils.translation import ugettext as _
from django import template
from django.utils.safestring import mark_safe

register = template.Library()


def recursive_encode(data, encoding):
    if isinstance(data, list):
        return [recursive_encode(item, encoding) for item in data]
    elif isinstance(data, tuple):
        return tuple(recursive_encode(item, encoding) for item in data)
    elif isinstance(data, dict):
        return [(key, recursive_encode(item, encoding))
                for key, item in data.items()]
    elif isinstance(data, unicode):
        return data.encode(encoding)
    else:
        return unicode(data).encode(encoding)


class PageNode(object):
    def __unicode__(self):
        css_class = self.css_class()
        css_class = css_class and ' class="{0}"'.format(css_class)
        return '<li{0}><a href="{1}">{2}</a></li>'.format(
            css_class,
            self.url(),
            self.text()
        )


class Space(PageNode):
    def url(self):
        return '#'

    def css_class(self):
        return 'disabled'

    def text(self):
        return '..'


class Page(PageNode):
    def __init__(self, request, page, current=False):
        self._request = request
        self.number = page
        self.current = current

    def text(self):
        return unicode(self.number)

    def css_class(self):
        return 'active' if self.current else ''

    def url(self):
        get = self._request.GET
        path = self._request.path
        lists = [(k, l) for k, l in get.iterlists() if k != 'page']
        args = [(k, v) for (k, l) in lists for v in l]
        args.insert(0, ('page', self.number))


        args = recursive_encode(args, 'utf-8')
        return '?'.join((path, urllib.urlencode(args)))


class Next(Page):
    def text(self):
        return _('Next')


class Prev(Page):
    def text(self):
        return _('Prev')


class SmartPager(object):
    on_each_side = 1
    on_ends = 1

    def __init__(self, request, paginator, page_obj):
        self.request = request
        self.current = page_obj.number
        self.total = paginator.num_pages
        self.next = page_obj.has_next() and page_obj.next_page_number()
        self.prev = page_obj.has_previous() and page_obj.previous_page_number()

    def __iter__(self):
        return itertools.chain(
            self.left(),
            [self.page(self.current, current=True)],
            self.right(),
        )

    def left(self):
        if self.prev:
            yield self.prev_page()
        stop = self.current
        if stop < self.on_each_side + self.on_ends:
            for i in range(1, stop):
                yield self.page(i)
        else:
            for i in range(1, 1 + self.on_ends):
                yield self.page(i)
            yield self.space()
            for i in range(stop - self.on_each_side, stop):
                yield self.page(i)

    def right(self):
        start = self.current + 1
        stop = self.total + 1
        if stop - start <= self.on_each_side + self.on_ends:
            for i in range(start, stop):
                yield self.page(i)
        else:
            for i in range(start, start + self.on_each_side):
                yield self.page(i)
            yield self.space()
            for i in range(stop - self.on_ends, stop):
                yield self.page(i)
        if self.next:
            yield self.next_page()

    def space(self):
        return Space()

    def page(self, number, current=False):
        return Page(self.request, number, current=current)

    def next_page(self):
        return Next(self.request, self.next)

    def prev_page(self):
        return Prev(self.request, self.prev)


@register.simple_tag()
def paginate(request, paginator, page_obj, **kw):
    """
    Generates the series of links to the pages in a paginated list.
    """
    if paginator.num_pages == 1:
        return ''
    kw = dict({
        'class': 'pagination pagination-centered'
    }, **kw)
    t = ['<div{0}><ul>'.format(flatatt(kw) if kw else '')]
    pager = SmartPager(request, paginator, page_obj)
    t.extend(unicode(i) for i in pager)
    t.append('</ul></div>')
    return mark_safe(''.join(t))
