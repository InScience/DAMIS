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
#include "Projection.h"
#include <sstream>

using namespace std;

double** ObjectMatrixToDouble(ObjectMatrix);            // konvertavimas is ObjectMatrix i 2D double masyva
ObjectMatrix DoubleToObjectMatrix(double**, int, int);  // konvertavimas is 2D double masyvo i ObjectMatrix
void PrintY(ObjectMatrix);                              // Y atvaizdavimas ekrane (testavimui)

double **Array2D(int rows, int cols)                    // 2D double istisines matricos kurimas
{
    double *data = (double *)malloc(rows*cols*sizeof(double));
    double **array= (double **)malloc(rows*sizeof(double*));
    for (int i=0; i<rows; i++)
        array[i] = &(data[cols*i]);
    return array;
}

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
    
    epsilon = 0.01;
    maxIter = 10;
    d = 2;
    
    MPI::Init(argc, argv);
    pid = MPI::COMM_WORLD.Get_rank();
    numOfProcs = MPI::COMM_WORLD.Get_size();
    MPI_Status status;
    
    if (pid == 0)
    { 
        t_start = MPI_Wtime();
        if (numOfProcs == 1)
        {
            //SMACOFZEIDEL smcf (0.001, 5, 2, Random);
            SMACOF smcf (epsilon, maxIter, d);
            Y = smcf.getProjection();
            PrintY(Y);
            //Y.saveDataMatrix("tests/new_test7.txt");           
        }
        else
        {
            stressErrors = new double[numOfProcs];     // surinktu paklaidu masyvas (testavimui)       
            SMACOF smcf (epsilon, maxIter, d);
            Y = smcf.getProjection();
            int n = Y.getObjectCount();
            int m = Y.getObjectAt(0).getFeatureCount();
            stressErrors[0] = smcf.stress;
            for (int i = 1; i < numOfProcs; i++)
            {
                MPI_Recv(&receivedStress, 1, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);  // priimama paklaida is kiekvieno proceso
                stressErrors[i] = receivedStress;
            }
            
            t_end = MPI_Wtime();
            
            for (int i = 0; i < numOfProcs; i++)
                cout<<"Stress error received from process No. " <<i<<" is "<<stressErrors[i]<<endl;
                        
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
                PrintY(Y);
                //Y.saveDataMatrix("result.arff");
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
                
                receiveArray = Array2D(n, m);

                MPI_Recv(&(receiveArray[0][0]), m * n, MPI_DOUBLE, min_rank, MPI_ANY_TAG, MPI_COMM_WORLD, &status);   // priimama Y
                Y = DoubleToObjectMatrix(receiveArray, n, m);
                PrintY(Y);
                //Y.saveDataMatrix("result.arff");
            }         
            
            cout<<"Calculation time: "<<t_end - t_start<<" s."<<endl;
        }
    }
    else
    {
        SMACOF smcf (epsilon, maxIter, d);
        Y = smcf.getProjection();
        
        MPI_Send(&smcf.stress, 1, MPI_DOUBLE, 0, pid, MPI_COMM_WORLD);  // siunciama paklaida teviniam procesui
        MPI_Recv(&send, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);  // priimamas pranesimas ar siusti Y
        
        if (send == 1)          // siusti, jei send = 1, nesiusti, jei send = 0
        {
            int n = Y.getObjectCount();
            int m = Y.getObjectAt(0).getFeatureCount();
            sendArray = Array2D(n, m);
            sendArray = ObjectMatrixToDouble(Y);
            MPI_Send(&(sendArray[0][0]), m * n, MPI_DOUBLE, 0, pid, MPI_COMM_WORLD);  // siunciama Y
        }    
    }    
    
    MPI_Finalize();    
    
    return 0;
}

double** ObjectMatrixToDouble(ObjectMatrix matrix)
{
    int numOfObjects = matrix.getObjectCount();
    int numOfFeatures = matrix.getObjectAt(0).getFeatureCount();
    double **matrixToReturn;
    matrixToReturn = Array2D(numOfObjects, numOfFeatures);
    
    
    for (int i = 0; i < numOfObjects; i++)
        for (int j = 0; j < numOfFeatures; j++)
            matrixToReturn[i][j] = matrix.getObjectAt(i).features.at(j);
    
    return matrixToReturn;
}

ObjectMatrix DoubleToObjectMatrix(double** matrix, int rows, int cols)
{
    std::vector<double> v;
    v.reserve(cols);
    ObjectMatrix toReturn(rows);
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            v.push_back(matrix[i][j]);
        toReturn.addObject(DataObject(v));
        v.clear();
    }
    
    return toReturn;
}

void PrintY(ObjectMatrix matrix)
{
    int numOfObjects = matrix.getObjectCount();
    int numOfFeatures = matrix.getObjectAt(0).getFeatureCount();
    
    cout<<"******* Projekcijos matrica *******"<<endl;
    for (int i = 0; i < numOfObjects; i++)
    {
        for (int j = 0; j < numOfFeatures; j++)
            cout<<matrix.getObjectAt(i).features.at(j)<<" ";
        cout<<endl;
    }
}
