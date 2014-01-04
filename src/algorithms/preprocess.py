import csv
from datetime import datetime
from os.path import split, splitext, join, exists
from os import makedirs
from random import random
from math import sqrt, fabs


def z_factor(source, output, attr=-1, filter=None, update_value=True):
    # First scan to get mean and deviation
    attr_sum = 0.0
    attr_sq_sum = 0.0
    total_rows = 0
    with open(source) as source_file:
        for attr_list in csv.reader(source_file):
            attr_sum += float(attr_list[attr])
            attr_sq_sum += float(attr_list[attr]) * float(attr_list[attr])
            total_rows += 1

    mean = attr_sum / total_rows
    deviation = sqrt(attr_sq_sum / total_rows  - mean**2)

    # Second file scan to normalise (or filter by) the attribute
    output_file = open(output, 'w')
    output_writer = csv.writer(output_file)
    with open(source) as source_file:
        for attr_list in csv.reader(source_file):
            if update_value:
                attr_list[attr] = (float(attr_list[attr]) - mean) / deviation
            if (filter is None) or\
               (filter == 'outliers' and fabs(float(attr_list[attr])) > 3) or\
               (filter != 'outliers' and fabs(float(attr_list[attr])) < 3):
                output_writer.writerow(attr_list)
    output_file.close()


def quartil(source, output, attr=-1, filter=None, update_value=True):
    # First scan to get first and second quartils
    total = 0
    each_value_count = {}
    with open(source) as file:
        for value_list in csv.reader(file):
            total += 1
            value = value_list[attr].strip()
            if each_value_count.has_key(value):
                each_value_count[value] += 1
            else:
                each_value_count[value] = 1

    Q1, Q2, viewed = None, None, 0
    for key, count in sorted(each_value_count.items(), key=lambda x: float(x[0])):
        viewed += count
        if Q1 is None and viewed > 0.25 * (total + 1):
            Q1 = float(key)
        if Q2 is None and viewed > 0.75 * (total + 1):
            Q2 = float(key)

    IQR = Q2 - Q1

    # Second file scan to normalise (or filter by) the attribute
    output_file = open(output, 'w')
    output_writer = csv.writer(output_file)
    with open(source) as source_file:
        for attr_list in csv.reader(source_file):
            is_outlier = bool(float(attr_list[attr]) <= Q1 - 1.5*IQR or\
                              float(attr_list[attr]) >= Q2 + 1.5*IQR)
            if (filter == 'outliers' and is_outlier) or\
               (filter != 'outliers' and is_outlier):
                output_writer.writerow(attr_list)
    output_file.close()


def filter(source, output, attr=-1, filter=None, method='z-factor', update_value=False):
    '''Applies one for the filters to the attribute:
            Z-factor - normalised value is not in [-3, 3]
            Quartil - value is <= Q1 - 1.5 * (Q2 - Q1)
                            or >= Q2 + 1.5 * (Q2 - Q1)
            '''
    if method == 'z-factor':
        z_factor(source, output, attr, filter, update_value)
    elif method == 'quartil':
        quartil(source, output, attr, filter, update_value)


def normalise(source, output, attr=-1, filter=None):
    '''Applies Z normalisation for the attribute: substracts mean and divides
    by deviation.'''
    z_factor(source, output, attr, filter, update_value=True)


def transpose(source, output, attr=-1, arff=False, *args, **kwargs):
    '''Categorical attribute is changed to attribute list: an attribute for
    each category is created, which value is 1 if the vector belongs to this
    category and 0 if it does not.'''

    values = set()
    with open(source) as source_file:
        if arff:
            for row in source_file:
                if row.strip().lower().startswith("@data"):
                    break
        for attr_list in csv.reader(source_file):
            value = attr_list[attr].strip()
            values.add(value)

    values = sorted(list(values))

    output_file = open(output, 'w')
    output_writer = csv.writer(output_file)
    with open(source) as source_file:
        if arff:
            for row in source_file:
                output_file.write(row)
                if row.strip().lower().startswith("@data"):
                    break
        for attr_list in csv.reader(source_file):
            value = attr_list[attr]
            transposed = []
            for v in values:
                if v.strip() == value.strip():
                    transposed.append(' 1')
                else:
                    transposed.append(' 0')
            output_writer.writerow(attr_list[:attr] + transposed + attr_list[attr:][1:])
    output_file.close()


def _value_by_prob(each_value_count, total):
    missing = each_value_count.get('?', 0)

    random_value = random()

    cum_prob = 0
    for key, value in sorted(each_value_count.items(), key=lambda x: x[0]):
        if key != '?':
            probability = value / (total - missing)
            cum_prob += probability
            if cum_prob >= random_value:
                return key

def fill_missing_values(source, output, attr=-1):
    total = 0.0
    each_value_count = {}
    output_file = open(output, 'w')
    output_writer = csv.writer(output_file)
    with open(source) as file:
        for value_list in csv.reader(file):
            total += 1
            value = value_list[attr].strip()

            if each_value_count.has_key(value):
                each_value_count[value] += 1
            else:
                each_value_count[value] = 1

            if value == '?':
                new_value = _value_by_prob(each_value_count, total)
                value_list[attr] = new_value
            output_writer.writerow(value_list)
    output_file.close()



separators = {
        'f': ['.'],            # float
        'd': ['%Y-%m-%d']      # date formats
    }

def _get_type(value):
    try:
        return 'int', int(value)
    except ValueError:
        try:
            float_value = value
            for e in separators['f']:
                float_value = float_value.replace(e, '.')
            return 'float', float(float_value)
        except ValueError:
            for fmt in separators['d']:
                try:
                    return 'date', datetime.strptime(value, fmt)
                except ValueError:
                    pass
            return 'string', value


def _update_type(old_type, new_type):
    types = ['int', 'float', 'date', 'str']
    if types.index(old_type) < types.index(new_type):
        return new_type
    return old_type


def get_types(source, *args, **kwargs):
    types = {}
    with open(source) as source_file:
        for nr, line_args in enumerate(csv.reader(source_file)):
            if nr > 0:  # Skip first line
                for i, value in enumerate(line_args):
                    current_type, python_value = _get_type(value.strip())
                    if not types.get(i, None):
                        types[i] = current_type
                    else:
                        if types[i] != current_type:
                            types[i] = _update_type(types[i], current_type)
    return [item[1] for item in sorted(types.items(), key=lambda x: x[0])]



def divide(source, output_dir="", method='line', N=None, attr=-1, **kwargs):
    '''Divides CSV file into ``N`` shard files using one of these methods:
            ``line`` - each shard has equal number of lines
            ``attr`` - each shard has vectors with same attribute value'''
    source_dir, source_filename = split(source)
    source_filename, source_ext = splitext(source_filename)
    shard_filename = join(output_dir, source_filename + '_%s' + source_ext)
    if not output_dir:
        output_dir = source_dir
    if not exists(output_dir):
        makedirs(output_dir)

    # Divide file into shards by attribute
    if method == 'attr':
        shard_files = {}
        with open(source) as source_file:
            delimiter = kwargs.get('delimiter', ',')
            for attr_list in csv.reader(source_file, delimiter=delimiter):
                attr_value = attr_list[attr].strip()
                if not shard_files.has_key(attr_value):
                    shard_files[attr_value] = open(shard_filename % attr_value, 'w')
                shard_files[attr_value].write(delimiter.join(attr_list))
        return

    # Divide file into equal shards
    elif method == 'line':
        # Create and open Shard files
        shard_files = []
        for i in range(N):
            shard_files.append(open(shard_filename % i, 'w'))

        with open(source) as source_file:
            for nr, line in enumerate(source_file):
                shard_files[nr % N].write(line)

        [f.close() for f in shard_files]
