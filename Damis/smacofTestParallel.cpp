/* 
 * File:   smacofTestParallel.cpp
 * Author: mindaugas
 *
 * Created on Oct 24, 2013, 10:22:59 AM
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "../SMACOF.h"
#include "../ObjectMatrix.h"
#include "mpi.h"
/*
 * Simple C++ Test Suite
 */

std::ofstream file ("test_results.txt", std::ios::app);

void ReceiveErrorsTest(int numOfProcs, MPI_Status status) {
    double receivedStress;
    int k = 1;
    std::cout << "-- Checking if all slave processors returns stress error to master processor" << std::endl;
    file << "\tTesting if all slave processors returns stress error to master processor -> ";
    for (int i = 1; i < numOfProcs; i++)
    {
        MPI_Recv(&receivedStress, 1, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if (status.MPI_ERROR == 0)
            k++;
    }
    if (k == numOfProcs)
    {
        std::cout << "Test passed." << std::endl;
        file << "Passed." << std::endl;
    }
    else
    {
        std::cout << "%TEST_FAILED% time=0 testname=ReceiveErrorsTest (smacofTestParallel) message=Test Failed!!!" << std::endl;
        file << "Failed!!!" << std::endl;
    }
}

void test2() {
    std::cout << "smacofTestParallel test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (smacofTestParallel) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    
    int numOfProcs, pid, send, min_rank = 0;
    double epsilon = 0.001;
    int maxIter = 5, d = 2;
    double *stressErrors;
    ObjectMatrix Y;
    
    MPI::Init(argc, argv);
    pid = MPI::COMM_WORLD.Get_rank();
    numOfProcs = MPI::COMM_WORLD.Get_size();
    MPI_Status status;
    
    std::cout << "%SUITE_STARTING% smacofTestParallel" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;
    
    if (pid == 0)
    {
        if (numOfProcs == 1)
            SMACOF smf(epsilon, maxIter, d);           
        else
        {
            std::cout << "%TEST_STARTED% ReceiveErrorsTest (smacofTestParallel)" << std::endl;
            ReceiveErrorsTest(numOfProcs, status);
            std::cout << "%TEST_FINISHED% time=0 test1 (smacofTestParallel)" << std::endl;
        }
    }
    

    std::cout << "%TEST_STARTED% test2 (smacofTestParallel)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (smacofTestParallel)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

