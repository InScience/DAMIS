/* 
 * File:   arffTest.cpp
 * Author: mindaugas
 *
 * Created on Nov 18, 2013, 5:59:44 PM
 */

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "../arff.h"
#include "../ObjectMatrix.h"
#include "../DataObject.h"

/*
 * Simple C++ Test Suite
 */

void ReadCorrectFile(ARFF file) {
    
    std::cout<<"-- Testing the read of existing correctly formated data file --"<< std::endl;
    
    if (file.getFileReadStatus() == 1)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=ReadCorrectFile (arffTest) message=Test Failed." << std::endl;
}

void ReadUncorrectFile(ARFF file) {
    std::cout<<"-- Testing the read of existing uncorrectly formated data file --"<< std::endl;
    
    if (file.getFileReadStatus() == 0)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=ReadUncorrectFile (arffTest) message=Test Failed." << std::endl;
}

void ReadNonExistingFile(ARFF file) {
    std::cout<<"-- Testing the case of trying to read the non existing file --"<<std::endl;
    if (file.getFileReadStatus() == 0)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=ReadNonExistingFile (arffTest) message=Test Failed." << std::endl;
}

void ReadLargeFile(ARFF file) {
    std::cout<<"-- Testing the capability to read large file --"<<std::endl;
    if (file.getFileReadStatus() == 1)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=ReadLargeFile (arffTest) message=Test Failed." << std::endl;
}

void ReadMediumLargeFile(ARFF file) {
    std::cout<<"-- Testing the capability to read medium large file --"<<std::endl;
    if (file.getFileReadStatus() == 1)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=ReadMediumLargeFile (arffTest) message=Test Failed." << std::endl;
}

void ReadVeryLargeFile(ARFF file) {
    std::cout<<"-- Testing the capability to read very large file --"<<std::endl;
    if (file.getFileReadStatus() == 1)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=ReadVeryLargeFile (arffTest) message=Test Failed." << std::endl;
}

void WriteObjectMatrixToARFF(ObjectMatrix X) {
    std::cout << "-- Testing write data to arff file --" << std::endl;
    X.saveDataMatrix("arff_files/test.arff");
    ARFF arff("arff_files/test.arff");
    if (arff.getFileReadStatus() == 1)
        std::cout << "Test passed." << std::endl;
    else
        std::cout << "%TEST_FAILED% time=0 testname=WriteObjectMatrixToARFF (arffTest) message=Test Failed." << std::endl;
}


int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% arffTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% ReadCorrectFile (arffTest)" << std::endl;
    ARFF arff("arff_files/cpu.arff");
    ReadCorrectFile(arff);
    std::cout << "%TEST_FINISHED% time=0 test1 (arffTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% ReadUncorrectFile (arffTest)\n" << std::endl;
    arff = ARFF("arff_files/cpu_.arff");
    ReadUncorrectFile(arff);
    std::cout << "%TEST_FINISHED% time=0 ReadUncorrectFile (arffTest)" << std::endl;

    std::cout << "%TEST_STARTED% ReadNonExistingFile (arffTest)\n" << std::endl;
    arff = ARFF("arff_files/cpuuu.arff");
    ReadNonExistingFile(arff);
    std::cout << "%TEST_FINISHED% time=0 ReadNonExistingFile (arffTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% ReadLargeFile (arffTest)\n" << std::endl;
    arff = ARFF("arff_files/random_10K.arff");
    ReadLargeFile(arff);
    std::cout << "%TEST_FINISHED% time=0 ReadLargeFile (arffTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% ReadMediumLargeFile (arffTest)\n" << std::endl;
    arff = ARFF("arff_files/random_100K.arff");
    ReadMediumLargeFile(arff);
    std::cout << "%TEST_FINISHED% time=0 ReadMediumLargeFile (arffTest)" << std::endl;
    
    std::cout << "%TEST_STARTED% ReadVeryLargeFile (arffTest)\n" << std::endl;
    arff = ARFF("arff_files/random_1M.arff");
    ReadVeryLargeFile(arff);
    std::cout << "%TEST_FINISHED% time=0 ReadVeryLargeFile (arffTest)" << std::endl;
    
    ObjectMatrix matrix(100);
    std::vector<double> features;
    features.reserve(20);
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 20; j++)
            features.push_back(i + 20.3 * j);
        matrix.addObject(DataObject(features));
        features.clear();
    }
    
    std::cout << "%TEST_STARTED% WriteObjectMatrixToARFF (arffTest)\n" << std::endl;
    WriteObjectMatrixToARFF(matrix);
    std::cout << "%TEST_FINISHED% time=0 WriteObjectMatrixToARFF (arffTest)" << std::endl;
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

