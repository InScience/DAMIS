/* 
 * File:   main.cpp
 * Author: mindaugas
 *
 * Created on August 28, 2013, 9:57 PM
 */

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include "ARFF.h"
#include "Statistics.h"
#include "ShufleEnum.h"
#include "DistanceMetrics.h"
#include "ObjectMatrix.h"
#include "MDS.h"
#include "HPCMethod.h"
#include "DimReductionMethod.h"
#include "SMACOF.h"
#include "SAMANN.h"
#include "SMACOFZEIDEL.h"
#include "SDS.h"
#include "SOM.h"
#include "SOMMDS.h"
#include "DMA.h"
#include "mpi.h"
#include "Projection.h"
#include "PCA.h"
#include "AdditionalMethods.h"
#include <sstream>

int AdditionalMethods::PID;    //  seed for random numbers generator

void PrintMatrix(ObjectMatrix);                      // Y atvaizdavimas ekrane (testavimui)

int main(int argc, char** argv) {
    
    int numOfProcs, pid, send, min_rank = 0;    // (numOfProcs) procesu kiekis
                                                // (pid) proceso ID
                                                // (send) pranesimas del Y siuntimo / nesiuntimo
                                                // (min_rank) proceso ID, apskaiciavusio maziausia paklaida
    double t_start, t_end;                      // skaiciavimu pradzia ir pabaiga
    ObjectMatrix Y;                             // projekcijos matrica
    double *stressErrors;                       // surinktu is procesu paklaidu aibe (testavimui)
    double receivedStress, min_stress = 0.0;    // gaunama ir maziausia paklaidos
    double **receiveArray, **sendArray;         // gaunama ir siunciama Y matricos
    double epsilon;                             // skaiciavimu tikslumas
    int maxIter, d;                             // (maxIter) leistinas iteraciju kiekis, (d) mazinimo dimensija
    
    epsilon = 0.001;
    maxIter = 10;
    d = 2;
    
    MPI::Init(argc, argv);
    pid = MPI::COMM_WORLD.Get_rank();
    AdditionalMethods::PID = pid;
    numOfProcs = MPI::COMM_WORLD.Get_size();
    MPI_Status status;
    
    PCA_::PCA_ mthd1(d);
    PCA_::PCA_ mthd2(1.0);
    SDS mthd3(epsilon, maxIter, d, DISPERSION, 50, EUCLIDEAN);
    SMACOFZEIDEL mthd4 (epsilon, maxIter, d, BUBLESORTDSC);
    SMACOFZEIDEL mthd5 (epsilon, maxIter, d, BUBLESORTASC);
    SMACOFZEIDEL mthd6 (epsilon, maxIter, d, RANDOM);
    SMACOF mthd7 (epsilon, maxIter, d);
    SAMANN mthd8(70, 10, 10.0, 50);
    DMA mthd9(epsilon, 10, d, 15);
    SOM mthd10(100, 3, 5);
    SOMMDS mthd11(epsilon, maxIter, d, 100, 3, 5);
    
    if (pid == 0)
    { 
        t_start = MPI_Wtime();
        if (numOfProcs == 1)
        {               
            Y = mthd1.getProjection();
            Y = mthd2.getProjection();
            Y = mthd3.getProjection();
            Y = mthd4.getProjection();
            Y = mthd5.getProjection();
            Y = mthd6.getProjection();
            Y = mthd7.getProjection();
            Y = mthd8.getProjection();
            Y = mthd9.getProjection();
            Y = mthd10.getProjection();
            Y = mthd11.getProjection();
            t_end = MPI_Wtime();
            //PrintMatrix(Y);    
        }
        else
        {
            stressErrors = new double[numOfProcs];     // surinktu paklaidu masyvas (testavimui)       
            Y = mthd7.getProjection();
            int n = Y.getObjectCount();
            int m = Y.getObjectAt(0).getFeatureCount();
            stressErrors[0] = mthd7.getStress();
            for (int i = 1; i < numOfProcs; i++)
            {
                MPI_Recv(&receivedStress, 1, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);  // priimama paklaida is kiekvieno proceso
                stressErrors[i] = receivedStress;
            }
            
            t_end = MPI_Wtime();
                        
            min_stress = stressErrors[0];
            for (int i = 1; i < numOfProcs; i++)
                if (stressErrors[i] < min_stress)
                {
                    min_stress = stressErrors[i];
                    min_rank = i;
                }
            
            if (min_rank == 0)  // jei maziausia paklaida tevinio proceso siunciamas pranesimas likusiems, kad savo Y nesiustu
            {
                send = 0;
                for (int i = 1; i < numOfProcs; i++)
                    MPI_Send(&send, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                PrintMatrix(Y);
            }
            else
            {
                for (int i = 1; i < numOfProcs; i++)
                    if (i == min_rank)
                    {
                        send = 1;
                        MPI_Send(&send, 1, MPI_INT, i, 0, MPI_COMM_WORLD);  // siunciamas pranesimas, kad atsiustu Y
                    }
                    else
                    {
                        send = 0;
                        MPI_Send(&send, 1, MPI_INT, i, 0, MPI_COMM_WORLD);  // siunciamas pranesimas, kad nesiustu Y
                    }
                
                receiveArray = AdditionalMethods::Array2D(n, m);

                MPI_Recv(&(receiveArray[0][0]), m * n, MPI_DOUBLE, min_rank, MPI_ANY_TAG, MPI_COMM_WORLD, &status);   // priimama Y
                Y = AdditionalMethods::DoubleToObjectMatrix(receiveArray, n, m);
                PrintMatrix(Y);
            }                    
        }
        std::cout<<"Calculation time: "<<t_end - t_start<<" s."<<std::endl;
    }
    else
    {
        Y = mthd7.getProjection();
        double stress = mthd7.getStress();
        MPI_Send(&stress, 1, MPI_DOUBLE, 0, pid, MPI_COMM_WORLD);  // siunciama paklaida teviniam procesui
        MPI_Recv(&send, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);  // priimamas pranesimas ar siusti Y
        
        if (send == 1)          // siusti, jei send = 1, nesiusti, jei send = 0
        {
            int n = Y.getObjectCount();
            int m = Y.getObjectAt(0).getFeatureCount();
            sendArray = AdditionalMethods::Array2D(n, m);
            sendArray = AdditionalMethods::ObjectMatrixToDouble(Y);
            MPI_Send(&(sendArray[0][0]), m * n, MPI_DOUBLE, 0, pid, MPI_COMM_WORLD);  // siunciama Y
        }    
    }    
    
    MPI_Finalize();    
    
    return 0;
}

void PrintMatrix(ObjectMatrix matrix)
{
    int numOfObjects = matrix.getObjectCount();
    int numOfFeatures = matrix.getObjectAt(0).getFeatureCount();
    
    std::cout<<"******* Projekcijos matrica *******"<<std::endl;
    for (int i = 0; i < numOfObjects; i++)
    {
        for (int j = 0; j < numOfFeatures; j++)
            std::cout<<matrix.getObjectAt(i).getFeatureAt(j)<<" ";
        std::cout<<std::endl;
    }
}
