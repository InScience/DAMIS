import unicodedata
import re
from os.path import join, exists, split
from django.conf import settings
from os import makedirs
from shutil import copy


def slugify(s, sep='-', allowed_chars='._-'):
    """
    >>> print slugify(u'a.b@gmail.com')
    a.b-at-gmail.com
    >>> print slugify(u'a.b@gmail.com', allowed_chars='-')
    a-b-at-gmail-com
    >>> print slugify(u'A - b -- c -')
    a-b-c
    >>> print slugify(u'A - b -- c - . Ttt')
    a-b-c.ttt
    >>> print slugify(U'2012-05-02 12:12.txt')
    2012-05-02-12-12.txt
    >>> print slugify(u'2012-05-02 12:12.txt', sep='_', allowed_chars='-_.:')
    2012-05-02_12:12.txt
    """
    if not sep in allowed_chars:
        raise Exception('Separator should be in allowed characters')
    s = s.replace('@', '-at-')
    slug = unicodedata.normalize('NFKD', s)
    slug = slug.encode('ascii', 'ignore').lower()
    rsep = re.escape(sep)
    rchars = re.escape(allowed_chars)
    r = r'([^\w%s]+)' % rchars
    slug = re.sub(r, sep, slug).strip(sep)
    r = r'(%s*)([%s])(%s*)' % (rsep, rchars, rsep)
    slug = re.sub(r, r'\2', slug)
    return slug

def strip_arff_header(opened_file):
    for row in opened_file:
        if row.strip().lower().startswith("@data"):
            break
    return opened_file


def save_task(exp, task_formset):
    from damis.models import WorkflowTask, ParameterValue
    sources = {}
    for task_form in task_formset.forms:
        data = task_form.cleaned_data
        data['experiment'] = exp
        if data.get('algorithm'):
            task = data.get('id')
            if not task and not data.get('DELETE'):
                if data.has_key('DELETE'):
                    data.pop('DELETE')
                task = WorkflowTask.objects.create(**data)

            pv_formset = task_form.parameter_values[0]
            pv_formset.instance = task

            for pv_form in pv_formset.forms:
                data = {}
                data['parameter'] = pv_form.cleaned_data.get('parameter')
                data['value'] = pv_form.cleaned_data.get('value')
                data['task'] = task

                pv_form_prefix = pv_form.prefix

                pv_instance = pv_form.cleaned_data.get('id')
                if not pv_instance:
                    pv_instance = ParameterValue.objects.create(**data)
                else:
                    if pv_form.cleaned_data.has_key('related'):
                        pv_form.cleaned_data.pop('related')
                    pv_form.save()
                pv_form.instance = pv_instance

                if pv_instance.parameter.type == 'dataset' and pv_instance.value:
                    file_path = pv_instance.value
                    exp_path = join('/media/experiments', str(exp.pk)) + '/'
                    if not file_path.startswith(exp_path):
                        pdir = settings.BUILDOUT_DIR + '/var/www'
                        if not exists(pdir + exp_path):
                            makedirs(pdir + exp_path)
                        copy(pdir + file_path, pdir + exp_path)
                        pv_instance.value = join(exp_path, split(file_path)[1])
                        pv_instance.save()
                sources[pv_form_prefix] = pv_form.instance
    return sources

