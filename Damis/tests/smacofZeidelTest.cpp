/* 
 * File:   smacofZeidelTest.cpp
 * Author: mindaugas
 *
 * Created on Oct 24, 2013, 10:49:02 PM
 */

#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "../SMACOFZEIDEL.h"
#include "../ObjectMatrix.h"
#include "../Statistics.h"

/*
 * Simple C++ Test Suite
 */

void TestNumOfRowsOfMatrixY(ObjectMatrix X, ObjectMatrix Y) {
    std::cout << "-- Checking if number of rows of matrix Y is the same as X --" << std::endl;
    if (X.getObjectCount() == Y.getObjectCount())
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestNumOfRowsOfMatrixY (smacofZeidelTest) message=Test Failed!!!" << std::endl;
}

void TestMatrixYDimmension(ObjectMatrix Y, int d) {
    std::cout << "-- Checking if number of columns of matrix Y is the same as preffered dimension --" << std::endl;
    int k = 0;
    int m = Y.getObjectCount();
    for (int i = 0; i < m; i++)
        if (Y.getObjectAt(i).getFeatureCount() == d)
            k++;
    
    if (k == m)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestMatrixYDimmension (smacofZeidelTest) message=Test Failed!!!" << std::endl;
}

void TestFinishCondition(SMACOFZEIDEL s, int k, double e)
{
    std::cout << "-- Checking if calculations are stopped after meeting stop criterias --" << std::endl;
    if (s.getFinalEpsilon() <= e || s.getIteration() == k)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestFinishCondition (smacofZeidelTest) message=Test Failed!!!" << std::endl;
}

void TestResultsOfShuffleStrategies(ObjectMatrix random, ObjectMatrix asc, ObjectMatrix dsc, double error, int dim)
{
    std::cout << "-- Checking difference of results returned using different shuffle strategies --" << std::endl;
    int n = random.getObjectCount();
    int k = 0, t;
    
    for (int i = 0; i < n; i++)
    {
        t = 0;
        for (int j = 0; j < dim; j++)
            if (fabs(random.getObjectAt(i).getFeatureAt(j) - asc.getObjectAt(i).getFeatureAt(j)) <= 0.01 && fabs(dsc.getObjectAt(i).getFeatureAt(j) - asc.getObjectAt(i).getFeatureAt(j)) <= 0.1)
                t++;
        if (t == dim)
            k++;
        else
            break;
    }
    
    if (k == n)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestResultsOfShuffleStrategies (smacofZeidelTest) message=Test Failed!!!" << std::endl;
}

int main(int argc, char** argv) {
    int d = 2, iter = 50;
    double error = 0.001;
    
    std::cout << std::endl;
    std::cout << "%SUITE_STARTING% smacofZeidelTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;   
    
    std::cout << "Testing SMACOFZEIDEL with parameters: epsilon="<< error<<", max iterations="<<iter<<", dimmension="<<d
              << ", shuffle - randomly" << std::endl;
    
    SMACOFZEIDEL smf_rand(error, iter, d, RANDOM);
    ObjectMatrix Y_rand = smf_rand.getProjection();
    ObjectMatrix X = smf_rand.X;
    
    int n = X.getObjectCount();
    
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY shuffled randomly (smacofZeidelTest)" << std::endl;
    TestNumOfRowsOfMatrixY(X, Y_rand);
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (smacofZeidelTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestMatrixYDimmension shuffled randomly (smacofZeidelTest)\n" << std::endl;
    TestMatrixYDimmension(Y_rand, d);
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (smacofZeidelTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestFinishCondition shuffled randomly (smacofZeidelTest)\n" << std::endl;
    TestFinishCondition(smf_rand, iter, error);
    std::cout << "%TEST_FINISHED% time=0 TestFinishCondition (smacofZeidelTest)" << std::endl;
    
    SMACOFZEIDEL smf_bubbleasc(error, iter, d, BUBLESORTASC);
    ObjectMatrix Y_bubbleasc = smf_bubbleasc.getProjection();
    X = smf_bubbleasc.X;
    
    std::cout << std::endl;
    std::cout << "Testing SMACOFZEIDEL with parameters: epsilon="<< error<<", max iterations="<<iter<<", dimmension="<<d
              << ", shuffle - bubble sort ascending" << std::endl; 
    
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY shuffled bubble sort asc (smacofZeidelTest)" << std::endl;
    TestNumOfRowsOfMatrixY(X, Y_bubbleasc);
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (smacofZeidelTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestMatrixYDimmension shuffled bubble sort asc (smacofZeidelTest)\n" << std::endl;
    TestMatrixYDimmension(Y_bubbleasc, d);
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (smacofZeidelTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestFinishCondition shuffled bubble sort asc (smacofZeidelTest)\n" << std::endl;
    TestFinishCondition(smf_bubbleasc, iter, error);   
    std::cout << "%TEST_FINISHED% time=0 TestFinishCondition (smacofZeidelTest)" << std::endl;
    
    
    SMACOFZEIDEL smf_bubbledsc(error, iter, d, BUBLESORTDSC);
    ObjectMatrix Y_bubbledsc = smf_bubbledsc.getProjection();
    Y_bubbledsc.saveDataMatrix("dsc.arff");
    X = smf_bubbledsc.X;
    std::cout << std::endl;

    std::cout << "Testing SMACOFZEIDEL with parameters: epsilon="<< error<<", max iterations="<<iter<<", dimmension="<<d
              << ", shuffle - bubble sort descending" << std::endl; 
    
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY shuffled bubble sort desc (smacofZeidelTest)" << std::endl;
    TestNumOfRowsOfMatrixY(X, Y_bubbledsc);
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (smacofZeidelTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestMatrixYDimmension shuffled bubble sort desc (smacofZeidelTest)\n" << std::endl;
    TestMatrixYDimmension(Y_bubbledsc, d);
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (smacofZeidelTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestFinishCondition shuffled bubble sort desc (smacofZeidelTest)\n" << std::endl;
    TestFinishCondition(smf_bubbledsc, iter, error);   
    std::cout << "%TEST_FINISHED% time=0 TestFinishCondition (smacofZeidelTest)" << std::endl;
    
    ObjectMatrix Y(n);
    std::vector<double> DataObjectItem;
    double r = 0.0;
    for (int j = 0; j < d; j++)
        DataObjectItem.push_back(0.0);
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < d; j++)
        {
            r = Statistics::getRandom(-0.1, 0.1, (i + j * 5));
            DataObjectItem[j] = r;
        }
        Y.addObject(DataObject(DataObjectItem));
    }
    
    std::cout<<"Testing results gathered using different shufle strategy, but the same initial projection matrix"<<std::endl;
    
    smf_rand = SMACOFZEIDEL(error, iter, d, RANDOM, Y);
    Y_rand = smf_rand.getProjection();
    Y_rand.saveDataMatrix("rand.arff");
    smf_bubbleasc = SMACOFZEIDEL(error, iter, d, BUBLESORTASC, Y);
    Y_bubbleasc = smf_bubbleasc.getProjection();
    Y_bubbleasc.saveDataMatrix("asc.arff");
    smf_bubbledsc = SMACOFZEIDEL(error, iter, d, BUBLESORTDSC, Y);
    Y_bubbledsc = smf_bubbledsc.getProjection();
    Y_bubbledsc.saveDataMatrix("dsc.arff");
    
    std::cout << "%TEST_STARTED% TestResultsOfShuffleStrategies (smacofZeidelTest)\n" << std::endl;
    TestResultsOfShuffleStrategies(Y_rand, Y_bubbleasc, Y_bubbledsc, error, d);  
    std::cout << "%TEST_FINISHED% time=0 TestResultsOfShuffleStrategies (smacofZeidelTest)" << std::endl;
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl << std::endl;

    return (EXIT_SUCCESS);
}

