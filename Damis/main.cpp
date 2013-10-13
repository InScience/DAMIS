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
#include "ShufleEnum.h"
#include <iostream>
#include "DistanceMetrics.h"
#include "ObjectMatrix.h"
#include "PCA.h"
#include "MDS.h"
#include "HPCMethod.h"
#include "DimReductionMethod.h"
#include "SMACOF.h"
#include "SAMANN.h"
#include "SMACOFZEIDEL.h"
#include "SOM.h"
#include "mpi.h"
#include <sstream>

using namespace std;

double** ObjectMatrixToDouble(ObjectMatrix);

int main(int argc, char** argv) {
    
    int numOfProcs, pid, bufferSize;
    double t_start, t_end;   // skaiciavimu pradzia ir pabaiga
    ObjectMatrix Y;
    double **sendBuffer;
    double ***receiveBuffer;
    double stress;

    MPI::Init(argc, argv);
    pid = MPI::COMM_WORLD.Get_rank();
    numOfProcs = MPI::COMM_WORLD.Get_size();
    //MPI_Comm_size(MPI_COMM_WORLD,&numOfProcs);
    //MPI_Comm_rank(MPI_COMM_WORLD,&pid);
    
    //ARFF file("/home/Dimis/cpu.arff");
    //    bool t = file.ReadSuccess;
    //    cout<<"aaa"<<endl;
    
    if (pid == 0)
    {
        //ARFF file("/home/Damis/cpu.arff");
        //bool t = file.ReadSuccess;
        //cout<<t<<endl;
        //t_start = MPI_Wtime();
        if (numOfProcs == 1)
        {
            ARFF file("/home/mindaugas/cpu.arff");
            bool t = file.ReadSuccess;
            cout<<t<<endl;
            //SMACOFZEIDEL smcf (0.001, 5, 2, Random);
            SMACOF smcf (0.001, 5, 2);
            Y = smcf.getProjection();
            int n = Y.getObjectCount();
            cout<<"Y obj. count: "<<n<<endl;
            int m = smcf.getX().getObjectCount();
            cout<<"X obj. count: "<<m<<endl;
            cout<<"Iterations: "<<smcf.iteration<<endl;
            cout<<"Error: "<<smcf.stress<<endl;
            //Y.saveDataMatrix("tests/new_test7.txt");           
        }
        else
        {
            // send X to other processors
            SMACOF smcf (0.0001, 5, 2);
            Y = smcf.getProjection();
            int n = Y.getObjectCount();
            cout<<n<<endl;
            int m = smcf.getX().getObjectCount();
            cout<<m;
            //receive Y from other processors
            // palyginti paklaidas
            //t_end = MPI_Wtime();
            //cout<<"Calculation time: "<<t_end - t_start<<" s."<<endl;
            //bufferSize = Y.getObjectCount() * Y.getObjectAt(0).getFeatureCount();
            //receiveBuffer = new double**[numOfProcs];   //   kiekvieno proceso Y matrica 
            //for (int i = 0; i < numOfProcs; i++)        
            //{
            //    receiveBuffer[i] = new double *[Y.getObjectCount()];  // eilute
            //    for (int j = 0; j< Y.getObjectCount(); j++)
            //        receiveBuffer[i][j] = new double[Y.getObjectAt(0).getFeatureCount()];   //  stulpelis
            //}
            //sendBuffer = psmcf.getProjectionInDoubles();
            //MPI_Allgather( sendBuffer, bufferSize, MPI_DOUBLE, receiveBuffer, bufferSize, MPI_DOUBLE, MPI_COMM_WORLD);
        }
    }
    else
    {
        //receive X from root processor
        SMACOF smcf (0.0001, 5, 2);
        Y = smcf.getProjection();
        int n = Y.getObjectCount();
        cout<<n<<endl;
        int m = smcf.getX().getObjectCount();
        cout<<m;
        //send Y to root processor    
    }    
    
    MPI_Finalize();    
    
    return 0;
}

double** ObjectMatrixToDouble(ObjectMatrix matrix)
{
    int numOfObjects = matrix.getObjectCount();
    int numOfFeatures = matrix.getObjectAt(0).getFeatureCount();
    double **matrixToReturn = 0;
    
    matrixToReturn = new double *[numOfObjects];
    for (int i = 0; i < numOfObjects; i++)
        matrixToReturn[i] = new double [numOfFeatures];
    
    for (int i = 0; i < numOfObjects; i++)
        for (int j = 0; j < numOfFeatures; j++)
            matrixToReturn[i][j] = matrix.getObjectAt(i).getItems().at(j);
    
    return matrixToReturn;
}
