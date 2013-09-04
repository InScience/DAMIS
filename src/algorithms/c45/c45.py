# coding: utf-8
#! usr/bin/python

from math import log, sqrt
import scipy.stats
from sm_utils import printTree
from optparse import OptionParser
from tools import readData, writeData

class AttBestDetails:
    ''' For the best known gain on an attribute, stores associated split details '''
    cut = None
    gain = None
    splitInfo = None

    def __init__(self, cut, gain, splitInfo):
        self.cut = cut
        self.gain = gain
        self.splitInfo = splitInfo

    def printDetails(self, att):
        print 'att: %d, cut: %f, gain: %f, splitInfo: %f' % (att, self.cut, self.gain, self.splitInfo)

class Test:
    ''' testedAtt <= cut '''
    testedAtt = None
    cut = None

    def __init__(self, testedAtt, cut):
        self.testedAtt = testedAtt
        self.cut = cut

    def isValid(self, vector):
        if vector[self.testedAtt] <= self.cut:
            return True
        return False

class Tree:
    nodeType = None             # leaf or internal node
    leaf = None                 # class assigned at this leaf
    test = None                 # an instance of Test
    branches = None             # a list of Tree
    classDist = None            # class distribution for training vectors
    error = None                # estimated number of errors at this node
    N = None                    # number of vectors covered by this leaf (sum of classDist values)

    def __init__(self):
        pass

    def getClass(self, vector):
        '''Returns vectors class, using recursion.'''
        if self.nodeType == 'leaf':
            return self.leaf
        elif self.nodeType == 'internal':
            if self.test.isValid(vector):
                return self.branches[0].getClass(vector)
            return self.branches[1].getClass(vector)

    def countLeaves(self):
        '''Returns number of leaves.'''
        if self.nodeType == 'leaf':
            return 1
        elif self.nodeType == 'internal':
            leaf_count = 0
            for branch in self.branches:
                leaf_count += branch.countLeaves()
            return leaf_count

class C45:

    learnData = None # learning data to build the tree from
    nClasses = None # total number of classes
    costs = None    # cost matrix C(actual, predicted)
    priorCorrection = None  # use prior probabilities correction according to cost matrix

    def __init__(self, learnData, costs=None, priorCorrection=None):
        self.learnData = learnData
        self.nClasses=len(self.classDistribution(learnData).keys())
        self.costs = costs
        self.priorCorrection = priorCorrection

    def sortByAtt(self, att, data):
        return sorted(data, key = lambda data_entry: data_entry[att])

    def classDistribution(self, data):
        ''' Counts vectors in each class '''
        counts = {}
        for row in data:
            c = row[-1]
            if c not in counts.keys():
                counts[c]=1
            else:
                n = counts[c]
                counts[c] = n + 1
        return counts
    
    def classProbabilities(self, data):
        ''' Determines a proportion of each class vectors in data '''
        counts = self.classDistribution(data)
        for c in counts.keys():
            counts[c] = float(counts[c])/len(data)
        return counts
    
    def costSensitiveClassProbabilities(self, data):
        ''' Altered prior class probabilities according to cost-matrix '''
        # costVectors[actual]: cost of misclassifying a vector of class actual
        costVectors = [sum(self.costs[actual][predicted] for predicted in range(self.nClasses)) for actual in range(self.nClasses)]
        counts = self.classDistribution(data)
        costSum = 0
        for c in counts.keys():
            counts[c] *= costVectors[c]
            costSum += counts[c]
        for c in counts.keys():
            counts[c] = float(counts[c]) / costSum
        return counts
    
    def setInfo(self, data):
        ''' Returns info(S) '''
        if self.priorCorrection:
            return -sum([p * log(p,2) for p in self.costSensitiveClassProbabilities(data).values()])
        else:
            return -sum([p * log(p,2) for p in self.classProbabilities(data).values()])
    
    def testInfo(self, X, left, right):
        ''' Returns infoX(S) '''
        n = len(left) + len(right)
        infoLeft = self.setInfo(left)
        infoRight = self.setInfo(right)
        return float(len(left))/n * infoLeft + float(len(right))/n * infoRight, infoLeft, infoRight
    
    def splitInfo(self, left, right):
        ''' Returns splitInfo(X) '''
        n = len(left) + len(right)
        return -sum([float(len(s))/n * log(float(len(s))/n,2)  for s in [left, right]])
    
    
    def bestClassFromClassDist(self, counts):
        bestClass = None
        minCost = None
        N = sum([counts[cc] for cc in counts.keys()])
        for c in counts.keys(): # predicted
            if self.priorCorrection:
                cost = sum(self.costs[actual][c] for actual in range(self.nClasses))
            else:
                cost = N - counts[c]
            if minCost is None or cost < minCost:
                bestClass = c
                minCost = cost
        return bestClass, minCost, counts
    
    def bestClassFromData(self, data):
        ''' Selects the best class with respect to cost matrix for this data set'''
        counts = self.classDistribution(data)
        return self.bestClassFromClassDist(counts)
    
    def splitData(self, test, data):
        ''' Returns left and right subsets, as determined by the provided test '''
        left = []
        right = []
        for row in data:
            if row[test.testedAtt] <= test.cut:
                left.append(row)
            else:
                right.append(row)
        return left, right
    
    def constructTree(self, data=None, info=None):
        ''' Constructs a continuous-valued decision tree using the C4.5 algorithm '''
        if data is None:
            data = self.learnData

        if info is None:
            info = self.setInfo(data)
    
        # make a leaf first, then see if try branching
        leaf = Tree()
        leaf.nodeType = 'leaf'
        leaf.leaf, minCost, leaf.classDist = self.bestClassFromData(data)
        leaf.N = len(data)
        leaf.error = leaf.N - leaf.classDist[leaf.leaf] # factual number of errors at this leaf
    
        # no branching when:
        # - vectors belong to the same class
        # - there exist at least MINITEMS vectors for each subset
        MINITEMS = 2
        if leaf.classDist[leaf.leaf] > 0.999 * leaf.N or leaf.N < 2 * MINITEMS:
            return leaf
    
        # minSplit is between MINITEMS and 25
        minSplit = 0.1 * float(len(data))/self.nClasses
        if minSplit > 25:
            minSplit = 25
        if minSplit < MINITEMS:
            minSplit = MINITEMS
    
        availableAtts = range(len(data[0]) - 1) # all attributes allowed
        attBest = [None for i in range(len(availableAtts))] # stores best cut, gain and split info for each attribute
        for att in availableAtts:
            self.sortByAtt(att, data)
            for idx in range(len(data)):
                X = Test(att, data[idx][att])
                left, right = self.splitData(X, data)
                if len(left) < minSplit or len(right) < minSplit:
                    continue
                infoX, infoLeft, infoRight = self.testInfo(X, left, right)
                gainX = info - infoX
                splitInfoX = self.splitInfo(left, right)
                if attBest[att] is None or gainX > attBest[att].gain:
                    attBest[att] = AttBestDetails(X.cut, gainX, splitInfoX)
    
        # compute average gain accross all attributes
        avgGain = 0
        possible = 0
        for att in availableAtts:
            if attBest[att] is not None and attBest[att].gain > 0:
                possible += 1
                avgGain += attBest[att].gain
    
        # do not try to split if it is not possible to produce any gain
        if possible == 0:
            return leaf
    
        avgGain = float(avgGain) / possible
    
        # find attribute with the best gain ratio
        maxGainRatio = None
        bestTest = None
        for att in availableAtts: 
            if attBest[att] is not None and attBest[att].gain > 0.999 * avgGain and attBest[att].splitInfo > 0:
                gainRatio = float(attBest[att].gain) / attBest[att].splitInfo
                if maxGainRatio is None or gainRatio > maxGainRatio:
                    maxGainRatio = gainRatio
                    bestTest = Test(att, attBest[att].cut)
    
        # try branching using best test
        tree = Tree()
        tree.nodeType = 'internal'
        tree.test = bestTest
        left, right = self.splitData(bestTest, data)
        infoX, infoLeft, infoRight = self.testInfo(bestTest, left, right)
        tree.classDist = self.classDistribution(data)
        tree.branches = []
        tree.branches.append(self.constructTree(left, infoLeft))
        tree.branches.append(self.constructTree(right, infoRight))
        tree.error = tree.branches[0].error + tree.branches[1].error
        tree.N = len(data)
    
        # decide if branching gives a smaller error
        if tree.error < leaf.error:
            return tree
        else:
            return leaf
    
    def getErrors(self, classDist, cls):
        E = sum([classDist[k] for k in classDist.keys() if k != cls]) # erorrs
        N = E + classDist[cls] # total
        return E, N
    
    def pAgrestiCoull(self, E, N, Q):
        ''' Computes the upper confidence interval limit for binomial distribution p parameter '''
        ''' Used in C4.5 Programs For Machine Learning, Q = 0.75 '''
        ''' Wikipedia Agresti-Coull '''
        alpha = 1-Q
        z = scipy.stats.norm.ppf(1-(alpha/2)) # (1-alpha/2)th quantile
        p = float(E+z/2)/(N+pow(z,2))
        sp = sqrt(p*(1-p)/N)
        return p+z*sp
    
    def getErrorEstimate(self, E, N, Q):
        return N * self.pAgrestiCoull(E, N, Q);
    
    def pruneTree(self, tree, Q=0.75):
        if tree.nodeType == 'leaf':
            E, N = self.getErrors(tree.classDist, tree.leaf)
            tree.N = N
            tree.error = self.getErrorEstimate(E, N, Q) # estimated error for this leaf
        else:
            childrenError = 0
            for i in range(2):
                tree.branches[i] = self.pruneTree(tree.branches[i], Q)
                childrenError += tree.branches[i].error
            bestClass, minCost, classDist = self.bestClassFromClassDist(tree.classDist)
            E, N = self.getErrors(classDist, bestClass)
            subTreeError = self.getErrorEstimate(E, N, Q) # estimated error if this subtree were replaced with a leaf
            if subTreeError < childrenError:
                # remove this node
                leaf = Tree()
                leaf.nodeType = 'leaf'
                leaf.leaf = bestClass
                leaf.classDist = classDist
                leaf.error = subTreeError
                leaf.N = N
                return leaf
            else:
                tree.error = childrenError
                tree.N = N
        return tree
    
    def laplaceCorrection(self, tree):
        classDist = {}
        for c in range(self.nClasses):
            if c in tree.classDist.keys():
                v = tree.classDist[c]
            else:
                v = 0
            classDist[c] = float(v+1)/(tree.N+self.nClasses)
        tree.classDist = classDist
    
    def cheapestClass(self, tree):
        ''' Uses a cost matrix in cheapest class selection '''
        counts = tree.classDist
        bestClass = None
        minCost = None
        for predicted in range(self.nClasses): # predicted class
            cost = tree.N*sum([self.costs[actual][predicted] * counts[actual] for actual in counts.keys()])
            if minCost is None or cost < minCost:
                bestClass = predicted
                minCost = cost
        return bestClass, minCost, counts
    
    def laplacePruneTree(self, tree):
        if tree.nodeType == 'leaf':
            self.laplaceCorrection(tree)
            tree.leaf, tree.error, classDist = self.cheapestClass(tree)
        else:
            childrenCost = 0
            for i in range(2):
                tree.branches[i] = self.laplacePruneTree(tree.branches[i])
                childrenCost += tree.branches[i].error
            N = tree.N
            self.laplaceCorrection(tree)
            bestClass, leafCost, classDist = self.cheapestClass(tree)
            if leafCost < childrenCost:
                # remove this node
                leaf = Tree()
                leaf.nodeType = 'leaf'
                leaf.leaf = bestClass
                leaf.classDist = classDist
                leaf.error = leafCost
                leaf.N = N
                return leaf
            else:
                tree.error = childrenCost
        return tree

def classifyData(tree, data):
    errors = 0
    for row in data:
        cls = tree.getClass(row[:-1])
        if int(row[-1]) != cls:
            row[-1] = cls
            errors += 1
    return data, errors

if __name__ == "__main__":
    parser = OptionParser()
    parser.add_option("-l", "--lfile", dest="learnFile",
                              help="Learning data (CSV file name)")
    parser.add_option("-t", "--tfile", dest="testFile",
                              help="Testing data (CSV file name)")
    parser.add_option("-o", "--ofile", dest="outFile", help="Output file name to store testing data classification")
    (options, args) = parser.parse_args()

    learnFile = options.learnFile # e. g. vertebral_learn.csv
    testFile = options.testFile # e. g. vertebral_test.csv
    outFile = options.outFile # e. g. res

    learnData = readData(learnFile)
    c45= C45(learnData)
    tree = c45.constructTree()
    tree = c45.pruneTree(tree)
    printTree(tree)

    testData = readData(testFile)

    classifiedLearnData, learnErrors = classifyData(tree, learnData)
    classifiedTestData, testErrors = classifyData(tree, testData)

    writeData(classifiedTestData, outFile)

    print "Learning data error: %d/%d (%f)" % (learnErrors, len(learnData), float(learnErrors)/len(learnData))
    print "Testing data error: %d/%d (%f)" % (testErrors, len(testData), float(testErrors)/len(testData))
