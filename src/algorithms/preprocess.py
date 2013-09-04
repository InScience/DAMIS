import csv
from os.path import split, splitext, join, exists
from os import makedirs


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
