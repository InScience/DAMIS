from unittest import TestCase
from algorithms.tests import TEST_FILE_PATH
from os.path import join


class ChangeFileFormatTests(TestCase):
    def test_convert_arff_to_csv(self):
        source = join(TEST_FILE_PATH, 'pauksciai.arff')
        expected = join(TEST_FILE_PATH, 'pauksciai.csv')

    def test_convert_csv_to_arff(self):
        pass

    def test_convert_xml_to_csv(self):
        pass

    def test_convert_csv_to_xml(self):
        pass
