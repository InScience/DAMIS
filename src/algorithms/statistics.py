import csv
from arff import dump as dump_arff
from math import sqrt
from django.utils.translation import ugettext as _


def statistics(source, output, arff=False, *args, **kwargs):
    '''Return min, max, mean, std, median for each column.'''
    mins = []
    maxs = []
    attr_sums = []
    attr_sq_sums = []
    each_value_counts = []
    stats = []
    total_rows = 0.0
    with open(source) as source_file:
        if arff:
            for row in source_file:
                if row.strip().lower().startswith("@data"):
                    break
        attr_count = None
        for attr_list in csv.reader(source_file):
            if not attr_sums:
                attr_count = len(attr_list)
                for i in range(attr_count):
                    attr_sums.append(0.0)
                    attr_sq_sums.append(0.0)
                    each_value_counts.append({})
                    stats.append({})
                    mins.append(None)
                    maxs.append(None)

            total_rows += 1
            for i, attr in enumerate(attr_list):
                try:
                    attr_float = float(attr)
                except ValueError:
                    stats[i]['min'] = '-'
                    stats[i]['max'] = '-'
                    stats[i]['mean'] = '-'
                    stats[i]['std'] = '-'
                    stats[i]['median'] = '-'
                    continue
                attr_sums[i] += attr_float
                attr_sq_sums[i] += attr_float * attr_float
                if not mins[i] or attr_float < mins[i]:
                    mins[i] = attr
                if not maxs[i] or attr_float > maxs[i]:
                    maxs[i] = attr

                value = attr.strip()
                if each_value_counts[i].has_key(value):
                    each_value_counts[i][value] += 1
                else:
                    each_value_counts[i][value] = 1

        for i in range(attr_count):
            if not stats[i].has_key('min'):
                stats[i]['min'] = mins[i]
            if not stats[i].has_key('max'):
                stats[i]['max'] = maxs[i]
            if not stats[i].has_key('mean'):
                stats[i]['mean'] = attr_sums[i] / total_rows
            if not stats[i].has_key('std'):
                stats[i]['std'] = sqrt(attr_sq_sums[i] / total_rows - stats[i]['mean']**2)
            if not stats[i].has_key('median'):
                stats[i]['median'] = None
                viewed = 0
                for key, count in sorted(each_value_counts[i].items(), key=lambda x: float(x[0])):
                    viewed += count
                    if stats[i]['median'] is None and viewed > 0.5 * (total_rows + 1):
                        stats[i]['median'] = key

    content = []
    for i in range(attr_count):
        s = stats[i]
        line = [s['min'], s['max'], s['mean'], s['std'], s['median']]
        content.append(line)
    dump_arff(output, content, relation=_("Statistical primitives"),
                           names=["min", "max", "mean", "std", "median"])
