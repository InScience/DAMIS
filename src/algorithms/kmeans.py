import numpy as np
from numpy.random import normal
# from scipy.stats import anderson 
from matplotlib import pyplot as plt
from random import randint
import csv
import shutil
import os
import os.path

from optparse import OptionParser

class UnsupervisedKMeans:
    fileIdx = -1

    def __init__(self, tmpDir="kmeans_tmp"):
        self.tmpDir = tmpDir

    def gauss(self, n=100, C=[[0, 1], [1, 0]], M=[[0, 0]]):
        ''' Returns ndarray n x p of normally distributed vectors (rows)'''

        C = np.array(C)
        M = np.array(M)
    
        evals, evects = np.linalg.eig(C)
        D = evals.real 
        V = evects.real
    
        ni, nj = C.shape
        p = ni # vectors dimensionality
    
        X = normal(size=(n, p))
        #import pdb; pdb.set_trace()
        X.dot(np.diag(np.sqrt(D)))
        X.dot(np.transpose(V))
        X += np.ones((n, 1)).dot(M)
        #print anderson(X[:, 0]), anderson(X[:, 1])
        return X
    
    def generateGaussData(self):
        X1 = self.gauss(C=[[1, 0.8], [0.8, 1]])
        X2 = self.gauss(C=[[1, 0.6], [0.6, 1]], M=[[4, 4]])
        X3 = self.gauss(C=[[1, -0.6], [-0.6, 1]], M=[[-4, -4]])
        X4 = self.gauss(C=[[1, -0.6], [-0.6, 1]], M=[[-4, 4]])
        X5 = self.gauss(C=[[1, 0.6], [0.6, 1]], M=[[4, -4]])
        X = [X1, X2, X3, X4, X5]
        return X
    
    def writeData(self, X, oFile):
        csvfile = open(oFile, 'wb')
        writer = csv.writer(csvfile, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
        for x in X:
            for row in list(x):
                writer.writerow(row)
        csvfile.close()
    
    def readData(self, inFile):
        csvfile = open(inFile, 'rb')
        reader = csv.reader(csvfile, delimiter=',', quotechar='"')
        X = []
        for row in reader:
            B = map(float, row)
            X.append(B)
        return X
    
    def readClasses(self, iFileName):
        iFile = open(iFileName, 'rb')
        reader = csv.reader(iFile, delimiter=',', quotechar='"')
    
        X = {}
        for row in reader:
            cls = int(row[-1])
            if cls not in X:
                X[cls] = []
            X[cls].append(map(float, row[0:-1]))
    
        iFile.close()
    
        return [np.array(lst) for lst in X.values()]
    
    def drawData(self, X):
        colors = ['#e3ff05', '#f14548', '#000000', '#0553ff', '#ff05d8', '#48a956', '#924b1a', '#7e1a92', '#7de31b', '#34bbc3']
        k = len(X)
        for i in range(k):
            plt.scatter(X[i][:, 0], X[i][:, 1], c=colors[i])
        plt.title('k' + str(k))
        plt.show()
    
    def getNextFileName(self):
        self.fileIdx += 1
        fileName = self.tmpDir + "/o" + str(self.fileIdx)
        return fileName

    def assignRandomClasses(self, k, iFileName):
        iFile = open(iFileName, 'rb')
        reader = csv.reader(iFile, delimiter=',', quotechar='"')
    
        oFileName = self.getNextFileName()
        oFile = open(oFileName, 'wb')
        writer = csv.writer(oFile, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    
        for row in reader:
            cls = randint(0, k - 1)
            row.append(cls)
            writer.writerow(row)
    
        iFile.close()
        oFile.close()
    
        return oFileName
    
    def computeMeans(self, k, iFileName):
        iFile = open(iFileName, 'rb')
        reader = csv.reader(iFile, delimiter=',', quotechar='"')
    
        means = None
        sizes = None # sizes of the k groups
        for row in reader:
            cls = int(row[-1])
        
            # update group size
            if sizes == None:
                sizes = [0] * k
            sizes[cls] += 1
        
            # update mean
            if means == None:
                # set here because dimensionality is only known after starting reading
                means = [np.zeros(len(row)-1) for i in range(k)]
            means[cls] += np.array(map(float, row[0:-1]))
        
        iFile.close()
    
        # complete means calculation
        for cls in range(k):
            means[cls] = means[cls]/float(sizes[cls])
    
        return means
    
    def closestClass(self, vect, means):
        minD = None
        bestCls = None
        for cls in range(len(means)):
            d = np.linalg.norm(vect - means[cls])
            if minD == None or d < minD:
                minD = d
                bestCls = cls
        return bestCls
    
    def reassignVectors(self, iFileName, means):
        iFile = open(iFileName, 'rb')
        oFileName = self.getNextFileName()
        oFile = open(oFileName, 'wb')
        reader = csv.reader(iFile, delimiter=',', quotechar='"')
        writer = csv.writer(oFile, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
        
        nMoved = 0
        for row in reader:
            cls = self.closestClass(np.array(map(float, row[0:-1])), means)
            if cls != int(row[-1]):
                row[-1] = cls
                nMoved += 1
            writer.writerow(row)
        iFile.close()
        oFile.close()
    
        return nMoved, oFileName
    
    def computeInter(self, means):
        k = len(means)
        inter = None
        for i in range(k):
            for j in range(k-1-i):
                l = i + 1 + j
                d = np.linalg.norm(means[i] - means[l])
                if inter == None or d < inter:
                    inter = d
        return inter
    
    def group(self, k, iFileName):
        ''' Groups vectors in iFileName into k groups
            returns: 
                oFileName - vector groups
                means - group means
                minVals - minimum values of all attributes
                maxVals - maximum values of all attributes
                sig - variances of all attributes
                inter - minimum distance between cluster centers
                intra - sum of distances between vectors and their group centers'''
        nMoved = -1
        for it in range(100):
            means = self.computeMeans(k, iFileName)
            nMoved, oFileName = self.reassignVectors(iFileName, means)
            if nMoved == 0: # nothing changed; means are consistent with class assignments
                break
            else:
                # delete previous tmp input file
                os.remove(iFileName)
            iFileName = oFileName
        # Available: means and grouping in oFileName
    
        # compute inter
        inter = self.computeInter(means)
    
        iFile = open(oFileName, 'rb')
        reader = csv.reader(iFile, delimiter=',', quotechar='"')
    
        p = means[0].shape[0] # dimensionality
    
        minVals = [[None for i in range(p)] for j in range(k)] # minimum attribute vals in each group
        maxVals = [[None for i in range(p)] for j in range(k)] # maximum attribute vals in each group
        sig = [np.zeros(p) for i in range(k)] # attribute variances in each group
    
        sizes = [0] * k # sizes of all groups
        intra = 0
    
        for row in reader:
            cls = int(row[-1])
            sizes[cls] += 1
    
            intra += sum([d**2 for d in means[cls] - np.array(map(float, row[0:-1]))]) # squared Euclidian norm
    
            for i in range(p):
                val = float(row[i])
    
                # minimal feature value
                if minVals[cls][i] == None or val < minVals[cls][i]:
                    minVals[cls][i] = val
    
                # maximal feature value
                if maxVals[cls][i] == None or val > maxVals[cls][i]:
                    maxVals[cls][i] = val
                
                # feature variances
                sig[cls][i] += (val - means[cls][i])**2
        iFile.close()
    
        # complete variances calculation
        sig = [sig[cls]/float(sizes[cls] - 1) for cls in range(k)]
    
        return (means, oFileName, inter, intra, minVals, maxVals, sig)
    
    def divideMean(self, baseMean, clsMinVals, clsMaxVals):
        ''' baseMean - np.array
            clsMinVals - list
            clsMaxVals - list
            returns:
                minusMean - np.array obtained by decreasing baseMean
                plusMean - np.array obtained by increasing baseMean '''
    
        p = baseMean.shape[0]
        a = [min(baseMean[i] - clsMinVals[i], clsMaxVals[i] - baseMean[i]) for i in range(p)]
        minusMean = baseMean - np.array(a)
        plusMean = baseMean + np.array(a)
        return minusMean, plusMean
    
    def run(self, maxK, iFileName, oDir):
        ''' Splits vectors in iFile into maximum maxK groups
            returns:
                bestK - best number of groups
                files with splits into k= 1,...,kMax groups in oDir'''
    
        if not os.path.exists(self.tmpDir):
            os.makedirs(self.tmpDir)

        if not os.path.exists(oDir):
            os.makedirs(oDir)

        oFileName = self.assignRandomClasses(2, iFileName)
        bestRatio = None
        bestK = None
        means = None # means of the k groups
        for k in range(2, maxK + 1):
            iFileName = oFileName
            means, oFileName, inter, intra, minVals, maxVals, sig = self.group(k, iFileName)
            
            # copy the split file into oDir
            shutil.copy(oFileName, oDir + '/k' + str(k))
    
            ratio = float(intra)/inter
            if bestRatio == None or ratio < bestRatio:
                bestRatio = ratio 
                bestK = k
           
            # splitting for the next k
    
            # choosing class with largest average attribute variance
            maxSig = None
            splitCls = None
            for cls in range(k):
                avgSig = np.average(sig[cls])
                if maxSig == None or avgSig > maxSig:
                    maxSig = avgSig
                    splitCls = cls 
    
            baseMean = means[splitCls]
    
            minusMean, plusMean = self.divideMean(baseMean, minVals[splitCls], maxVals[splitCls])
            del means[splitCls]
            means.append(minusMean)
            means.append(plusMean)
            isConverged, oFileName = self.reassignVectors(oFileName, means)

        shutil.rmtree(self.tmpDir)
    
        return bestK, bestRatio

if __name__ == "__main__":
    parser = OptionParser()
    parser.add_option("-f", "--file", dest="filename",
                              help="CSV input file name")
    parser.add_option("-d", "--dir", dest="dir", help="Existing directory to store groupings with all k")
    parser.add_option("-m", "--kMax", dest="kMax", help="Maximum k value (k - number of groups)")
    parser.add_option("-t", "--tmpDir", dest="tmpDir", help="Temporary directory (default is kmeans_tmp)")

    (options, args) = parser.parse_args()

    #X = generateGaussData()
    #writeData(X, 'kmeans/gaussData.csv')
    #drawData(X)

    kMax = int(options.kMax) # e. g. 10
    iFileName = options.filename # e. g. 'test/data/gauss_5_groups.csv'
    oDir = options.dir # e. g. 'test/kmeans/res'
    tmpDir = options.tmpDir # e. g. tmp

    uKMeans = UnsupervisedKMeans()
    bestK, bestRatio = uKMeans.run(kMax, iFileName, oDir)
    print 'bestK:', bestK, 'bestRatio: ', bestRatio

    #for k in range(2, kMax + 1):
    #    X = readClasses(oDir + 'k' + str(k))
    #    drawData(X)
