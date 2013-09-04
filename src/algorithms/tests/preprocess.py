import csv
from os.path import split, splitext, join
from os import remove
from unittest import TestCase

from algorithms.tests import TEST_FILE_PATH
from algorithms.preprocess import divide


class CleanTests(TestCase):
    def test_check_attr_types(self):
        pass

    def test_fill_missing_values(self):
        pass


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
