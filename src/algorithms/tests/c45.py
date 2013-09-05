from unittest import TestCase
from algorithms.c45 import c45
from algorithms.c45 import tools
from algorithms.tests import TEST_FILE_PATH
from os.path import join

class C45Tests(TestCase):
    def test_tree(self):
        learnFile = join(TEST_FILE_PATH, "vertebral_learn.data")
        
        learnData = tools.readData(learnFile)
        alg = c45.C45(learnData)
        tree = alg.constructTree()
        tree = alg.pruneTree(tree)
        
        cls = tree.getClass(learnData[0])
        self.assertEquals(2, cls)
