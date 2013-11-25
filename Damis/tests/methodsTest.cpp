/* 
 * File:   methodsTest.cpp
 * Author: mindaugas
 *
 * Created on Nov 22, 2013, 1:01:55 PM
 */

#include <stdlib.h>
#include <iostream>
#include "../DMA.h"
#include "../PCA.h"
#include "../SAMANN.h"
#include "../SDS.h"
#include "../SMACOF.h"
#include "../SMACOFZEIDEL.h"
#include "../SOM.h"
#include "../SOMMDS.h"
#include "../ObjectMatrix.h"

/*
 * Simple C++ Test Suite
 */

void TestNumOfRowsOfMatrixY(ObjectMatrix X, ObjectMatrix Y, const char* method) {
    std::cout << method << ": -- Checking if number of rows of matrix Y is the same as X --" << std::endl;
    if (X.getObjectCount() == Y.getObjectCount())
        std::cout << method << ": Test passed." << std::endl;
    else
        std::cout << " %TEST_FAILED% time=0 testname=TestNumOfRowsOfMatrixY (methodsTest) message=" << method<< ": Test Failed!!!" << std::endl;
}

void TestNumOfRowsOfMatrixY_SOM(ObjectMatrix X, ObjectMatrix Y, const char* method) {
    std::cout << method << ": -- Checking if number of rows of matrix Y is less or equal to matrix X --" << std::endl;
    if (X.getObjectCount() >= Y.getObjectCount())
        std::cout << method << ": Test passed." << std::endl;
    else
        std::cout << " %TEST_FAILED% time=0 testname=TestNumOfRowsOfMatrixY_SOM (methodsTest) message=" << method<< ": Test Failed!!!" << std::endl;
}

void TestMatrixYDimmension(ObjectMatrix Y, int d, const char* method) {
    std::cout << method <<": -- Checking if number of columns of matrix Y is the same as preffered dimension --" << std::endl;
    int k = 0;
    int m = Y.getObjectCount();
    for (int i = 0; i < m; i++)
        if (Y.getObjectAt(i).getFeatureCount() == d)
            k++;
    
    if (k == m)
        std::cout <<method << ": Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestMatrixYDimmension (methodsTest) message=" << method <<": Test Failed!!!" << std::endl;
}

void TestMethodConvergence(std::vector<double> stressErrors, const char* method)
{
    std::cout << method << ": -- Checking if Method is Converging --" << std::endl;
    int n = stressErrors.size();
    bool isConverging = true;
    
    for (int i = 0; i < n - 1; i++)
        if (stressErrors.at(i) < stressErrors.at(i + 1))
        {
            isConverging = false;
            break;
        }
    
    if (isConverging == true)
        std::cout << method << ": Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestMethodConvergence (methodsTest) message=" << method <<": Test Failed!!!" << std::endl;
}

void TestMethodWithLargeXMatrix(ObjectMatrix X, ObjectMatrix Y, int d, const char* method){
    std::cout << method << ": -- Checking if Method is Working on Large Set of Data --" << std::endl;
    int m1 = X.getObjectCount();
    int m2 = Y.getObjectCount();
    int n = 0;
    bool ans = true;

    if (m1 == m2)
    {
        for (int i = 0; i < m1; i++)
        {
            if (Y.getObjectAt(i).getFeatureCount() != d)
            {
                ans = false;
                break;
            }               
        }
        
        if (ans == true)
            std::cout << method << ": Test passed." << std::endl;
        else
            std::cout << "%TEST_FAILED% time=0 testname=TestMethodWithLargeXMatrix (methodsTest) message=" << method <<": Test Failed!!!" << std::endl;
    }
    else
        std::cout << "%TEST_FAILED% time=0 testname=TestMethodWithLargeXMatrix (methodsTest) message=" << method << ": Test Failed!!!" << std::endl;    
}

int main(int argc, char** argv) {
    int d = 2, n = 0, iter = 10, neighbours = 10, mTrain = 100, nNeurons = 10, k_x = 100, k_y = 3, eHat = 5;
    double epsilon = 0.001, dispPart = 1.0, eta = 1.0;
    ObjectMatrix Y;
    std::vector<double> stressErrors;
    
    DMA dma(epsilon, iter, d, neighbours);
    PCA::PCA pca(d);
    PCA::PCA pca_disp(dispPart);
    SAMANN smnn(mTrain, nNeurons, eta, iter);
    SDS sds_disp(epsilon, iter, d, DISPERSION, 50, EUCLIDEAN);
    SDS sds_pca(epsilon, iter, d, PCA, 50, EUCLIDEAN);
    SMACOF smcf(epsilon, iter, d);
    SMACOFZEIDEL smcfz_dsc(epsilon, iter, d, BUBLESORTDSC);
    SMACOFZEIDEL smcfz_asc(epsilon, iter, d, BUBLESORTASC);
    SMACOFZEIDEL smcfz_rndm(epsilon, iter, d, RANDOM);
    SOM som(k_x, k_y, eHat);
    SOMMDS sommds(epsilon, iter, d, k_x, k_y, eHat);
    ObjectMatrix X("arff_files/random_10K.arff");
    X.loadDataMatrix();
    
    std::cout << std::endl;
    std::cout << "%SUITE_STARTING% methodsTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    Y = dma.getProjection();
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (DMA) (methodsTest)" << std::endl;
    TestNumOfRowsOfMatrixY(dma.X, Y, "DMA");
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (DMA) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMatrixYDimmension (DMA) (methodsTest)" << std::endl;
    TestMatrixYDimmension(Y, d, "DMA");
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (DMA) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMethodConvergence (DMA) (methodsTest)" << std::endl;
    TestMethodConvergence(dma.getStressErrors(), "DMA");
    std::cout << "%TEST_FINISHED% time=0 TestMethodConvergence (DMA) (methodsTest)" << std::endl;
    
    dma = DMA(epsilon, 1, d, 1000, X);
    Y = dma.getProjection();
    std::cout << "%TEST_STARTED% TestMethodWithLargeXMatrix (DMA) (methodsTest)" << std::endl;
    TestMethodWithLargeXMatrix(X, Y, d, "DMA");
    std::cout << "%TEST_FINISHED% time=0 TestMethodWithLargeXMatrix (DMA) (methodsTest)" << std::endl;
    
    Y = pca.getProjection();
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (PCA -> d as parameter) (methodsTest)" << std::endl;
    TestNumOfRowsOfMatrixY(pca.X, Y, "PCA_d");
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (PCA) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMatrixYDimmension (PCA -> d as parameter) (methodsTest)" << std::endl;
    TestMatrixYDimmension(Y, d, "PCA_d");
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (PCA) (methodsTest)" << std::endl;
        
    pca = PCA::PCA(X, d);
    Y = pca.getProjection();
    std::cout << "%TEST_STARTED% TestMethodWithLargeXMatrix (PCA -> d as parameter) (methodsTest)" << std::endl;
    TestMethodWithLargeXMatrix(pca.X, Y, d, "PCA_d");
    std::cout << "%TEST_FINISHED% time=0 TestMethodWithLargeXMatrix (PCA) (methodsTest)" << std::endl;
    
    Y = pca_disp.getProjection();
    n = pca_disp.X.getObjectAt(0).getFeatureCount();
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (PCA -> disp as parameter) (methodsTest)" << std::endl;
    TestNumOfRowsOfMatrixY(pca_disp.X, Y, "PCA_disp");
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (PCA) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMatrixYDimmension (PCA -> disp as parameter) (methodsTest)" << std::endl;
    TestMatrixYDimmension(Y, n, "PCA_disp");
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (PCA) (methodsTest)" << std::endl;
    
    pca_disp = PCA::PCA(X, dispPart);
    Y = pca_disp.getProjection();
    n = pca_disp.X.getObjectAt(0).getFeatureCount();
    std::cout << "%TEST_STARTED% TestMethodWithLargeXMatrix (PCA -> disp as parameter) (methodsTest)" << std::endl;
    TestMethodWithLargeXMatrix(pca_disp.X, Y, n, "PCA_disp");
    std::cout << "%TEST_FINISHED% time=0 TestMethodWithLargeXMatrix (PCA) (methodsTest)" << std::endl;
    
    Y = smnn.getProjection();
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (SAMANN) (methodsTest)" << std::endl;
    TestNumOfRowsOfMatrixY(smnn.X, Y, "SAMANN");
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (SAMANN) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMatrixYDimmension (SAMANN) (methodsTest)" << std::endl;
    TestMatrixYDimmension(Y, d, "SAMANN");
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (SAMANN) (methodsTest)" << std::endl;    
    
    Y = sds_disp.getProjection();
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (SDS -> Dispersion) (methodsTest)" << std::endl;
    TestNumOfRowsOfMatrixY(sds_disp.X, Y, "SDS_disp");
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (SDS) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMatrixYDimmension (SDS -> Dispersion) (methodsTest)" << std::endl;
    TestMatrixYDimmension(Y, d, "SDS_disp");
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (SDS) (methodsTest)" << std::endl;
    
    Y = sds_pca.getProjection();
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (SDS -> PCA) (methodsTest)" << std::endl;
    TestNumOfRowsOfMatrixY(sds_pca.X, Y, "SDS_pca");
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (SDS) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMatrixYDimmension (SDS -> PCA) (methodsTest)" << std::endl;
    TestMatrixYDimmension(Y, d, "SDS_pca");
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (SDS) (methodsTest)" << std::endl;
    
    Y = smcf.getProjection();
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (SMACOF) (methodsTest)" << std::endl;
    TestNumOfRowsOfMatrixY(smcf.X, Y, "SMACOF");
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (SMACOF) (methodsTest)" << std::endl;

    std::cout << "%TEST_STARTED% TestMatrixYDimmension (SMACOF) (methodsTest)" << std::endl;
    TestMatrixYDimmension(Y, d, "SMACOF");
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (SMACOF) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMethodConvergence (SMACOF) (methodsTest)" << std::endl;
    TestMethodConvergence(smcf.getStressErrors(), "SMACOF");
    std::cout << "%TEST_FINISHED% time=0 TestMethodConvergence (SMACOF) (methodsTest)" << std::endl;
    
    smcf = SMACOF(epsilon, 1, d, X, 1);
    Y = smcf.getProjection();
    std::cout << "%TEST_STARTED% TestMethodWithLargeXMatrix (SMACOF) (methodsTest)" << std::endl;
    TestMethodWithLargeXMatrix(X, Y, d, "SMACOF");
    std::cout << "%TEST_FINISHED% time=0 TestMethodWithLargeXMatrix (SMACOF) (methodsTest)" << std::endl;
    
    Y = smcfz_dsc.getProjection();
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (SMACOFZEIDEL -> Descending) (methodsTest)" << std::endl;
    TestNumOfRowsOfMatrixY(smcfz_dsc.X, Y, "SMACOFZEIDEL_desc");
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (SMACOFZEIDEL) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMatrixYDimmension (SMACOFZEIDEL -> Descending) (methodsTest)" << std::endl;
    TestMatrixYDimmension(Y, d, "SMACOFZEIDEL_desc");
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (SMACOFZEIDEL) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMethodConvergence (SMACOFZEIDEL -> Descending) (methodsTest)" << std::endl;
    TestMethodConvergence(smcfz_dsc.getStressErrors(), "SMACOFZEIDEL_desc");
    std::cout << "%TEST_FINISHED% time=0 TestMethodConvergence (SMACOFZEIDEL) (methodsTest)" << std::endl;
    
    smcfz_dsc = SMACOFZEIDEL (epsilon, 1, d, BUBLESORTDSC, X, 1);
    Y = smcfz_dsc.getProjection();
    std::cout << "%TEST_STARTED% TestMethodWithLargeXMatrix (SMACOFZEIDEL -> Descending) (methodsTest)" << std::endl;
    TestMethodWithLargeXMatrix(X, Y, d, "SMACOFZEIDEL_desc");
    std::cout << "%TEST_FINISHED% time=0 TestMethodWithLargeXMatrix (SMACOFZEIDEL -> Descending) (methodsTest)" << std::endl;
    
    Y = smcfz_asc.getProjection();
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (SMACOFZEIDEL -> Ascending) (methodsTest)" << std::endl;
    TestNumOfRowsOfMatrixY(smcfz_asc.X, Y, "SMACOFZEIDEL_asc");
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (SMACOFZEIDEL) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMatrixYDimmension (SMACOFZEIDEL -> Ascending) (methodsTest)" << std::endl;
    TestMatrixYDimmension(Y, d, "SMACOFZEIDEL_asc");
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (SMACOFZEIDEL) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMethodConvergence (SMACOFZEIDEL -> Ascending) (methodsTest)" << std::endl;
    TestMethodConvergence(smcfz_asc.getStressErrors(), "SMACOFZEIDEL_asc");
    std::cout << "%TEST_FINISHED% time=0 TestMethodConvergence (SMACOFZEIDEL) (methodsTest)" << std::endl;
    
    smcfz_asc = SMACOFZEIDEL (epsilon, 1, d, BUBLESORTASC, X, 1);
    Y = smcfz_asc.getProjection();
    std::cout << "%TEST_STARTED% TestMethodWithLargeXMatrix (SMACOFZEIDEL -> Ascending) (methodsTest)" << std::endl;
    TestMethodWithLargeXMatrix(X, Y, d, "SMACOFZEIDEL_asc");
    std::cout << "%TEST_FINISHED% time=0 TestMethodWithLargeXMatrix (SMACOFZEIDEL -> Ascending) (methodsTest)" << std::endl;
    
    Y = smcfz_rndm.getProjection();
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (SMACOFZEIDEL -> Random) (methodsTest)" << std::endl;
    TestNumOfRowsOfMatrixY(smcfz_rndm.X, Y, "SMACOFZEIDEL_rand");
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (SMACOFZEIDEL) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMatrixYDimmension (SMACOFZEIDEL -> Random) (methodsTest)" << std::endl;
    TestMatrixYDimmension(Y, d, "SMACOFZEIDEL_rand");
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (SMACOFZEIDEL) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMethodConvergence (SMACOFZEIDEL -> Random) (methodsTest)" << std::endl;
    TestMethodConvergence(smcfz_rndm.getStressErrors(), "SMACOFZEIDEL_rand");
    std::cout << "%TEST_FINISHED% time=0 TestMethodConvergence (SMACOFZEIDEL) (methodsTest)" << std::endl;
    
    smcfz_rndm = SMACOFZEIDEL (epsilon, 1, d, RANDOM, X, 1);
    Y = smcfz_rndm.getProjection();
    std::cout << "%TEST_STARTED% TestMethodWithLargeXMatrix (SMACOFZEIDEL -> Random) (methodsTest)" << std::endl;
    TestMethodWithLargeXMatrix(X, Y, d, "SMACOFZEIDEL_rand");
    std::cout << "%TEST_FINISHED% time=0 TestMethodWithLargeXMatrix (SMACOFZEIDEL -> Random) (methodsTest)" << std::endl;
    
    Y = som.getProjection();
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (SOM) (methodsTest)" << std::endl;
    TestNumOfRowsOfMatrixY_SOM(som.X, Y, "SOM");
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (SOM) (methodsTest)" << std::endl;
    
    n = som.X.getObjectAt(0).getFeatureCount();
    std::cout << "%TEST_STARTED% TestMatrixYDimmension (SOM) (methodsTest)" << std::endl;
    TestMatrixYDimmension(Y, n, "SOM");
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (SOM) (methodsTest)" << std::endl;
    
    Y = sommds.getProjection();
    std::cout << "%TEST_STARTED% TestNumOfRowsOfMatrixY (SOMMDS) (methodsTest)" << std::endl;
    TestNumOfRowsOfMatrixY(sommds.getX(), Y, "SOMMDS");
    std::cout << "%TEST_FINISHED% time=0 TestNumOfRowsOfMatrixY (SOMMDS) (methodsTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% TestMatrixYDimmension (SOMMDS) (methodsTest)" << std::endl;
    TestMatrixYDimmension(Y, d, "SOMMDS");
    std::cout << "%TEST_FINISHED% time=0 TestMatrixYDimmension (SOMMDS) (methodsTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

