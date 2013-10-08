/* 
 * File:   main.cpp
 * Author: mindaugas
 *
 * Created on August 28, 2013, 9:57 PM
 */

#include <cstdlib>
#include <vector>
#include "arff.h"
#include "Statistics.h"
#include <iostream>
#include "DistanceMetrics.h"
#include "ObjectMatrix.h"
#include "PCA.h"
#include "MDS.h"
#include "HPCMethod.h"
#include "DimReductionMethod.h"
#include "SMACOF.h"
#include "PSMACOF.h"
#include "mpi.h"
#include <sstream>

using namespace std;

int main(int argc, char** argv) {
    
    int numOfProcs, pid, bufferSize;
    PSMACOF psmcf;
    ObjectMatrix Y;
    double **sendBuffer;
    double ***receiveBuffer;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numOfProcs);
    MPI_Comm_rank(MPI_COMM_WORLD,&pid);
    
    if (pid == 0)
    {
        if (numOfProcs == 1)
        {
            SMACOF smcf (0.1, 2, 2);
            Y = smcf.getProjection();
            Y.saveDataMatrix("tests/new_test.txt");           
        }
        else
        {
            psmcf = PSMACOF(0.1, 2, 2, numOfProcs);
            Y = psmcf.getProjection();
            bufferSize = Y.getObjectCount() * Y.getObjectAt(0).getFeatureCount();
            receiveBuffer = new double**[numOfProcs];   //   kiekvieno proceso Y matrica 
            for (int i = 0; i < numOfProcs; i++)        
            {
                receiveBuffer[i] = new double *[Y.getObjectCount()];  // eilute
                for (int j = 0; j< Y.getObjectCount(); j++)
                    receiveBuffer[i][j] = new double[Y.getObjectAt(0).getFeatureCount()];   //  stulpelis
            }
            sendBuffer = psmcf.getProjectionInDoubles();
            //MPI_Allgather( sendBuffer, bufferSize, MPI_DOUBLE, receiveBuffer, bufferSize, MPI_DOUBLE, MPI_COMM_WORLD);
        }
    }
    else
    {
        psmcf = PSMACOF(0.1, 2, 2, numOfProcs);
        Y = psmcf.getProjection();
        sendBuffer = psmcf.getProjectionInDoubles();
        //Y.saveDataMatrix("/home/mindaugas/new_test1.txt");
    }    
    
    MPI_Finalize();
    /*
    int size, p_id;
    SMACOF smcf;
    ObjectMatrix Y;
    int initialized, finalized;

    MPI_Initialized(&initialized);
    if (!initialized)
        MPI_Init(NULL, NULL);
    
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&p_id);
    //if (size > 0)
    //{
    cout<<"Creating object in: "<<p_id<<endl;
        smcf = SMACOF(0.1, 2, 2);
        cout<<"Created object in: "<<p_id<<endl;
        Y = smcf.getProjection();
        int k = Y.getObjectCount();

        std::stringstream ss;
        ss << p_id;
        std::string str = ss.str();
        std::string c = std::string("tests/p.txt") + str;
        
        const char *cstr = c.c_str();
        //cout<<cstr<<" "<<endl;
        cout<<k<<endl;
        Y.saveDataMatrix(Y, cstr);
    //}
    
    MPI_Finalized(&finalized);
    if (!finalized)
        MPI_Finalize();
    
    */
    
    return 0;
}
