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

void TestFinishCondition(SMACOF s, int k, double e)
{
    std::cout << "-- Checking if calculations are stopped after meeting stop criterias --" << std::endl;
    if (s.getFinalEpsilon() <= e || s.getIteration() == k)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestFinishCondition (smacofTest) message=Test Failed!!!" << std::endl;
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

    std::cout << "%TEST_STARTED% TestFinishCondition (smacofTest)\n" << std::endl;
    TestFinishCondition(smf, iter, error);
    std::cout << "%TEST_FINISHED% time=0 TestFinishCondition (smacofTest)" << std::endl;
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl << std::endl;

    return (EXIT_SUCCESS);
}

