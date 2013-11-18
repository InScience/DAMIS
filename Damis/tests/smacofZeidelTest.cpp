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

void TestMethodConvergence(SMACOFZEIDEL s, int k, double e)
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
        std::cout << "%TEST_FAILED% time=0 testname=TestMethodConvergence (smacofZeidelTest) message=Test Failed!!!" << std::endl;
}

int main(int argc, char** argv) {
    int d = 2, iter = 5;
    double error = 0.01;
    
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

    std::cout << "%TEST_STARTED% TestMethodConvergence shuffled randomly (smacofZeidelTest)\n" << std::endl;
    TestMethodConvergence(smf_rand, iter, error);
    std::cout << "%TEST_FINISHED% time=0 TestMethodConvergence (smacofZeidelTest)" << std::endl;
    
    std::cout << std::endl;
    std::cout << "Testing SMACOFZEIDEL with parameters: epsilon="<< error<<", max iterations="<<iter<<", dimmension="<<d
              << ", shuffle - bubble sort ascending" << std::endl; 
    
    SMACOFZEIDEL smf_bubbleasc(error, iter, d, BUBLESORTASC);
    ObjectMatrix Y_bubbleasc = smf_bubbleasc.getProjection();
    X = smf_bubbleasc.X;    
    
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY shuffled bubble sort asc (smacofZeidelTest)" << std::endl;
    TestNumOfRowsOfMatrixY(X, Y_bubbleasc);
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (smacofZeidelTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestMatrixYDimmension shuffled bubble sort asc (smacofZeidelTest)\n" << std::endl;
    TestMatrixYDimmension(Y_bubbleasc, d);
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (smacofZeidelTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestMethodConvergence shuffled bubble sort asc (smacofZeidelTest)\n" << std::endl;
    TestMethodConvergence(smf_bubbleasc, iter, error);   
    std::cout << "%TEST_FINISHED% time=0 TestMethodConvergence (smacofZeidelTest)" << std::endl;
    
    std::cout << "Testing SMACOFZEIDEL with parameters: epsilon="<< error<<", max iterations="<<iter<<", dimmension="<<d
              << ", shuffle - bubble sort descending" << std::endl;
    
    SMACOFZEIDEL smf_bubbledsc(error, iter, d, BUBLESORTDSC);
    ObjectMatrix Y_bubbledsc = smf_bubbledsc.getProjection();
    X = smf_bubbledsc.X;
    std::cout << std::endl; 
    
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY shuffled bubble sort desc (smacofZeidelTest)" << std::endl;
    TestNumOfRowsOfMatrixY(X, Y_bubbledsc);
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (smacofZeidelTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestMatrixYDimmension shuffled bubble sort desc (smacofZeidelTest)\n" << std::endl;
    TestMatrixYDimmension(Y_bubbledsc, d);
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (smacofZeidelTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestMethodConvergence shuffled bubble sort desc (smacofZeidelTest)\n" << std::endl;
    TestMethodConvergence(smf_bubbledsc, iter, error);   
    std::cout << "%TEST_FINISHED% time=0 TestMethodConvergence (smacofZeidelTest)" << std::endl;
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl << std::endl;

    return (EXIT_SUCCESS);
}

