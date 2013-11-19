/* 
 * File:   smacofTest.cpp
 * Author: mindaugas
 *
 * Created on Oct 24, 2013, 9:45:09 AM
 */

#include <stdlib.h>
#include <iostream>
#include "../SMACOF.h"
#include "../ObjectMatrix.h"

/*
 * Simple C++ Test Suite
 */

void TestNumOfRowsOfMatrixY(ObjectMatrix X, ObjectMatrix Y) {
    std::cout << "-- Checking if number of rows of matrix Y is the same as X --" << std::endl;
    if (X.getObjectCount() == Y.getObjectCount())
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestNumOfRowsOfMatrixY (smacofTest) message=Test Failed!!!" << std::endl;
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
        std::cout << "%TEST_FAILED% time=0 testname=TestMatrixYDimmension (smacofTest) message=Test Failed!!!" << std::endl;
}

void TestMethodConvergence(SMACOF s, int k, double e)
{
    std::cout << "-- Checking if Method is Converging --" << std::endl;
    ObjectMatrix Y = s.getProjection();
    std::vector<double> stressErrors = s.getStressErrors();
    int n = stressErrors.size();
    bool isConverging = true;
    
    for (int i = 0; i < n - 1; i++)
    {
        if (stressErrors.at(i) < stressErrors.at(i + 1))
        {
            isConverging = false;
            break;
        }
    }
    
    if (isConverging == true)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestMethodConvergence (smacofTest) message=Test Failed!!!" << std::endl;
}

void TestMethodWithLargeXMatrix(ObjectMatrix X, ObjectMatrix Y, int d){
    std::cout << "-- Checking if Method is Working on Large Set of Data --" << std::endl;
    int m1 = X.getObjectCount();
    int m2 = Y.getObjectCount();
    int n = 0;

    if (m1 == m2)
    {
        n = Y.getObjectAt(0).getFeatureCount();
        if (n == d)
            std::cout << "Test passed." << std::endl;
        else
            std::cout << "%TEST_FAILED% time=0 testname=TestMethodWithLargeXMatrix (smacofTest) message=Test Failed!!!" << std::endl;
    }
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestMethodWithLargeXMatrix (smacofTest) message=Test Failed!!!" << std::endl; 
    
}

void TestMethodConvergenceWithLargeXMatrix(std::vector<double> stressErrors){
    std::cout << "-- Checking if method is converging then working on large set of data --" << std::endl;
    int n = stressErrors.size();
    bool isConverging = true;
    
    for (int i = 0; i < n - 1; i++)
    {
        if (stressErrors.at(i) < stressErrors.at(i + 1))
        {
            isConverging = false;
            break;
        }
    }
    
    if (isConverging == true)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestMethodConvergenceWithLargeXMatrix (smacofTest) message=Test Failed!!!" << std::endl;
}

int main(int argc, char** argv) {
    int d = 2, iter = 5;
    double error = 0.001;
    SMACOF smf(error, iter, d);
    ObjectMatrix Y = smf.getProjection();
    ObjectMatrix X = smf.X;
    std::cout << std::endl;
    
    std::cout << "Testing SMACOF with parameters: error="<< error<<", max iterations="<<iter<<", dimmension="<<d << std::endl;   
    std::cout << "%SUITE_STARTING% smacofTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;   
    
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (smacofTest)" << std::endl;
    TestNumOfRowsOfMatrixY(X, Y);
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (smacofTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestMatrixYDimmension (smacofTest)\n" << std::endl;
    TestMatrixYDimmension(Y, d);
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (smacofTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestMethodConvergence (smacofTest)\n" << std::endl;
    TestMethodConvergence(smf, iter, error);
    std::cout << "%TEST_FINISHED% time=0 TestMethodConvergence (smacofTest)" << std::endl;
    
    ObjectMatrix large("arff_files/random_10K.arff");
    large.loadDataMatrix();
    smf = SMACOF(error, iter, d, large, 1);
    ObjectMatrix Y = smf.getProjection();
    std::vector<double> stressErrors = smf.getStressErrors();
    
    std::cout << "%TEST_STARTED% TestMethodWithLargeXMatrix (smacofTest)\n" << std::endl;
    TestMethodWithLargeXMatrix(smf.X, Y, d);
    std::cout << "%TEST_FINISHED% time=0 TestMethodWithLargeXMatrix (smacofTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMethodConvergenceWithLargeXMatrix (smacofTest)\n" << std::endl;
    TestMethodConvergenceWithLargeXMatrix(stressErrors);
    std::cout << "%TEST_FINISHED% time=0 TestMethodConvergenceWithLargeXMatrix (smacofTest)" << std::endl;
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl << std::endl;

    return (EXIT_SUCCESS);
}

