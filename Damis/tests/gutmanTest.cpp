/* 
 * File:   gutmanTest.cpp
 * Author: mindaugas
 *
 * Created on Oct 28, 2013, 12:04:58 PM
 */

#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "../ObjectMatrix.h"
#include "../SMACOF.h"
#include "../Statistics.h"
#include "../DistanceMetrics.h"


/*
 * Simple C++ Test Suite
 */

void testGutmanDimmension(ObjectMatrix gutman, int rowCount) {
    bool ans = true;
    std::cout << "-- Testing if Gutman matrix is " <<rowCount<<"x"<<rowCount <<" matrix --" << std::endl;
    if (gutman.getObjectCount() == rowCount)
    {
        for (int i = 0; i < rowCount; i++)
            if (gutman.getObjectAt(i).getFeatureCount() != rowCount)
            {
                ans = false;
                break;
            }
        if (ans == true)
            std::cout<<"Test passed."<<std::endl;
        else
            std::cout << "%TEST_FAILED% time=0 testname=testGutmanDimmension (gutmanTest) message=Test failed!!!" << std::endl;
    }
    else
        std::cout << "%TEST_FAILED% time=0 testname=testGutmanDimmension (gutmanTest) message=Test failed!!!" << std::endl;
}

void testSumOfGutmanElements(ObjectMatrix gMatrix, int rowCount) {
    std::cout << "-- Testing if [i][i] element is the sum of the remainder elements in the i-th row --" << std::endl;
    bool ats = true;
    double sum = 0.0;
    
    for (int i = 0; i < rowCount; i++)
    {
        sum = 0.0;
        for (int j = 0; j < rowCount; j++)
            if (i != j)
                sum += gMatrix.getObjectAt(i).getFeatureAt(j);

        if (fabs(sum) - fabs(gMatrix.getObjectAt(i).getFeatureAt(i)) > 0.0001)
        {
            ats = false;
            break;
        }
    }
    
    if (ats == true)
        std::cout<<"Test passed."<<std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=testSumOfGutmanElements (gutmanTest) message=Test failed!!!" << std::endl;
}

void testValuesOfIdenticalObjects(ObjectMatrix gMatrix, ObjectMatrix Y, int rowCount)
{
    std::cout << "-- Testing if elements are 0 in the i-th row if objects i and j are identical --" << std::endl;
    bool ats = true;
    double distYij = 0.0;
    
    for (int i = 0; i < rowCount - 1; i++)
        for (int j = i + 1; j < rowCount; j++)
        {
            distYij = DistanceMetrics::getDistance(Y.getObjectAt(i), Y.getObjectAt(j), EUCLIDEAN);
            if (distYij == 0.0)
            {
                if (fabs(gMatrix.getObjectAt(i).getFeatureAt(j)) > 0.00000001)
                {
                    ats = false;
                    break;
                }
            }
        }
        
    if (ats == true)
        std::cout<<"Test passed."<<std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=testValuesOfIdenticalObjects (gutmanTest) message=Test failed!!!" << std::endl;
}

void TestConstructionOfLargeGutmanMatrix(SMACOF smacof){
    std::cout << "-- Testing construction of large Gutman matrix --" << std::endl;
    int n = smacof.X.getObjectCount();
    ObjectMatrix gutman = smacof.getGutmanMatrix();
    int m = gutman.getObjectCount();
    if (n == m)
    {
        if (gutman.getObjectAt(0).getFeatureCount() == n)
            std::cout << "Test passed." <<std::endl;
        else
            std::cout << "%TEST_FAILED% time=0 testname=TestConstructionOfLargeGutmanMatrix (gutmanTest) message=Test failed!!!" << std::endl;
    }
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestConstructionOfLargeGutmanMatrix (gutmanTest) message=Test failed!!!" << std::endl;
}

int main(int argc, char** argv) {
    double epsilon = 0.001;
    int maxIter = 10, d = 2;
    std::cout << "%SUITE_STARTING% gutmanTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;
    SMACOF smcf(epsilon, maxIter, d);
    ObjectMatrix gMatrix = smcf.getGutmanMatrix();
    int n = smcf.X.getObjectCount();
    
    std::cout<<std::endl;
    std::cout << "%TEST_STARTED% testGutmanDimmension (gutmanTest)" << std::endl;
    testGutmanDimmension(gMatrix, n);
    std::cout << "%TEST_FINISHED% time=0 testGutmanDimmension (gutmanTest)" << std::endl;

    std::cout << "%TEST_STARTED% testSumOfGutmanElements (gutmanTest)\n" << std::endl;
    testSumOfGutmanElements(gMatrix, n);
    std::cout << "%TEST_FINISHED% time=0 testSumOfGutmanElements(gutmanTest)" << std::endl;
    
    ObjectMatrix Y(n);
    std::vector<double> DataObjectItem;
    double r = 0.0;
    for (int j = 0; j < d; j++)
        DataObjectItem.push_back(0.0);
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < d; j++)
        {
            r = Statistics::getRandom(-0.1, 0.1);
            DataObjectItem[j] = r;
        }
        Y.addObject(DataObject(DataObjectItem));
    }
    
    for (int i = 3; i < n; i++)
    {     
        for (int j = 0; j < d; j++)
        {
            r = Statistics::getRandom(-0.1, 0.1, (i + j * 5));
            DataObjectItem[j] = r;
        }
        Y.addObject(DataObject(DataObjectItem));
    }
    
    smcf = SMACOF(epsilon, maxIter, d, Y);
    gMatrix = smcf.getGutmanMatrix();
    
    std::cout << "%TEST_STARTED% testValuesOfIdenticalObjects (gutmanTest)\n" << std::endl;
    testValuesOfIdenticalObjects(gMatrix, Y, n);
    std::cout << "%TEST_FINISHED% time=0 testValuesOfIdenticalObjects (gutmanTest)" << std::endl;
    
    ObjectMatrix large("arff_files/random_10K.arff");
    large.loadDataMatrix();
    smcf = SMACOF(epsilon, maxIter, d, large, 1);
    std::cout << "%TEST_STARTED% TestConstructionOfLargeGutmanMatrix (gutmanTest)\n" << std::endl;
    TestConstructionOfLargeGutmanMatrix(smcf);
    std::cout << "%TEST_FINISHED% time=0 TestConstructionOfLargeGutmanMatrix (gutmanTest)" << std::endl;
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

