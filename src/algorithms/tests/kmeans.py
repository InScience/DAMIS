from unittest import TestCase
from algorithms import kmeans
import os
import os.path
import shutil
from numpy.random import seed


class KMeansTests(TestCase):
    def test_kmeans_grouping(self):
        seed(2013)
        testDir = 'kmeans_test'

        if not os.path.exists(testDir):
            os.makedirs(testDir)

        kMax = int(10)
        iFileName = testDir + '/gauss_5_groups.csv'
        oDir = testDir + '/res'
        tmpDir = testDir + '/tmp'
        uKMeans = kmeans.UnsupervisedKMeans(tmpDir)


        X = uKMeans.generateGaussData()
        uKMeans.writeData(X, iFileName)

        bestK, bestRatio = uKMeans.run(kMax, iFileName, oDir)

        if os.path.exists(testDir):
            shutil.rmtree(testDir)

        self.assertEqual(bestK, 5)
        self.assertEqual(bestRatio, 169.55817157830558)
