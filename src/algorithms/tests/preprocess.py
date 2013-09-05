import csv
import json
from os.path import split, splitext, join
from os import remove
from unittest import TestCase

from algorithms.tests import TEST_FILE_PATH
from algorithms.preprocess import divide, get_types, fill_missing_values
from random import seed


class CleanTests(TestCase):
    def test_check_attr_types(self):
        source = join(TEST_FILE_PATH, 'pauksciai.csv')
        types = get_types(source)
        source_meta = json.load(open(splitext(source)[0] + '.meta'))
        self.assertEqual(types, source_meta['types'])

    def probability(self, filename, attr):
        total = 0.0
        each_value_count = {}
        with open(filename) as file:
            for value_list in csv.reader(file):
                total += 1
                value = value_list[attr].strip()
                if each_value_count.has_key(value):
                    each_value_count[value] += 1
                else:
                    each_value_count[value] = 1

        missing_values = 0
        if each_value_count.has_key('?'):
            missing_values = each_value_count.pop('?')

        for key in each_value_count:
            each_value_count[key] /= total - missing_values

        return each_value_count

    def test_fill_missing_values_with_same_probability(self):
        seed(201308)
        attr = 1  # Attribute number we are testing
        source = join(TEST_FILE_PATH, 'neisbaigti_stebejimai.csv')
        output = join(TEST_FILE_PATH, 'tmp', 'neisbaigti_stebejimai.csv')
        orig_probs = self.probability(source, attr=attr)

        fill_missing_values(source, output=output, attr=attr)

        new_probs = self.probability(output, attr=attr)

        for key in orig_probs:
            self.assertTrue(new_probs.has_key(key))
            self.assertEqual(round(orig_probs[key], 3), round(new_probs[key], 3))


class TransposeTests(TestCase):
    # Categorical attr is changed to an attr for each category {0, 1}
    def test_transpose(self):
        pass


class TransformTests(TestCase):
    def test_z_normalisation(self):
        # Selected attr is normalised: sub mean, div std
        pass


class FilteringTests(TestCase):
    def test_z_filter(self):
        # Selected attr is normalised and filtered by chosen or default value
        pass

    def test_quartile_filter(self):
        # Selected attr is normalised using quartile transformation and filtered
        pass


class DivideFileIntoShardsTests(TestCase):
    def line_count(self, filename, i=0):
        for i, line in enumerate(open(filename)):
            pass
        return i

    def test_divide_file_into_shards_with_equal_line_count(self):
        shards = 3
        source = join(TEST_FILE_PATH, 'pauksciai.csv')
        output_dir = join(TEST_FILE_PATH, 'tmp')
        source_dir, source_filename = split(source)
        source_filename, source_ext = splitext(source_filename)
        shard_filename = join(output_dir, source_filename + '_%s' + source_ext)

        # Divide into equal shards
        divide(source, output_dir, method='line', N=shards)

        # Does output_dir contain shards with equal line count
        first_shard_size = None
        for i in range(shards):
            shard_size = self.line_count(shard_filename % i)
            if first_shard_size is None:
                first_shard_size = shard_size
            else:
                self.assertTrue(shard_size != 0)
                self.assertTrue(shard_size <= first_shard_size)
                self.assertTrue(shard_size >= first_shard_size -1)
            remove(shard_filename % i)

    def test_divide_file_into_shards_by_class_attribute(self):
        attr = 1
        source = join(TEST_FILE_PATH, 'pauksciai.csv')
        output_dir = join(TEST_FILE_PATH, 'tmp')
        source_dir, source_filename = split(source)
        source_filename, source_ext = splitext(source_filename)
        shard_filename = join(output_dir, source_filename + '_%s' + source_ext)

        # Divide into shards by class attribute value
        divide(source, output_dir, method='attr', attr=attr)

        # Get unique source vectors classes
        with open(source) as source_file:
            classes = set()
            for attr_list in csv.reader(source_file):
                classes.add(attr_list[attr].strip())

        # Does output_dir contain shards with unique class vectors
        for cls in classes:
            with open(shard_filename % cls) as shard_file:
                shard_classes = set()
                for attr_values in csv.reader(shard_file):
                    shard_classes.add(attr_values[attr])
                self.assertEqual(len(shard_classes), 1)
            remove(shard_filename % cls)
