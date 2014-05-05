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
#include <unistd.h>
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
#include "mpi_x86\mpi.h"
#include "Projection.h"
#include "PCA.h"
#include "AdditionalMethods.h"
#include "cmdLineParser\CommandLineParser.h"

#include <sstream>
#include <algorithm>

int AdditionalMethods::PID;    //  seed for random numbers generator
std::string AdditionalMethods::inputDataFile = ""; // input data file that will be passed to the HPC method constructor

void PrintMatrix(ObjectMatrix);                                                 // Y atvaizdavimas ekrane (testavimui)
double strToDouble(std::string);                                                // command line parameter to double type
int strToInt(std::string cmdParam);

template <typename T>                                             // command line parameter to int type
void paralelCompute(int pid, int numOfProcs, T *mthd, std::string resultFile, std::string statFile); // call functiopn

int main(int argc, char** argv)
{
    std::string inputFile = "", resultFile="", statFile="";     // pradiniu duomenu, rezultatų ir paklaidų failai
    std::string tmp ="";                                        //temp parameter for call method selection

    int numOfProcs, pid; // (numOfProcs) procesu kiekis

    // MPI::Init(argc, argv);
    MPI_Init(&argc, &argv);
    //pid = MPI::COMM_WORLD.Get_rank();
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    AdditionalMethods::PID = pid;

    //numOfProcs = MPI::COMM_WORLD.Get_size();
    MPI_Comm_size(MPI_COMM_WORLD, &numOfProcs);

   // MPI_Status status;

    CommandLineParser cmdLine(argc,argv,true);

    //extract command line arguments

    inputFile = cmdLine.get_arg("-i");
    resultFile = cmdLine.get_arg("-o");
    statFile = cmdLine.get_arg("-s");

    if (!inputFile.empty() || !resultFile.empty() || !statFile.empty())
    {
        /*std::cout <<"Input file: " << inputFile << std::endl;
        std::cout <<"Result file: " << resultFile << std::endl;
        std::cout <<"Stat file: " << statFile << std::endl;*/

        AdditionalMethods::inputDataFile.assign(inputFile);

            //generate file name for X distance matrix
        if (pid == 0)
        {
            AdditionalMethods::tempFileSavePath = AdditionalMethods::generateFileName();
            if (AdditionalMethods::tempFileSavePath.empty())
                {
                    MPI_Finalize();
                    printf("Unable to generate file name for X distance matrix");
                    return 0;
                }
        }

        tmp = cmdLine.get_arg("-al");
        std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);

        Statistics::intSeed();

        if (tmp == "PCA")
        {
            tmp = cmdLine.get_arg("-projType");
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);

            if (tmp == "0" || tmp == "FALSE" )
            {
                PCA_ *method = new PCA_(strToInt(cmdLine.get_arg("-d")), false);
                paralelCompute(pid, numOfProcs, method, resultFile, statFile);
            }
            else
            {
                PCA_ *method = new PCA_(strToDouble(cmdLine.get_arg("-d")), true);

                paralelCompute(pid, numOfProcs, method, resultFile, statFile);
            }
        }
        else if (tmp =="DMA")
        {
            DMA *method = new DMA(strToDouble(cmdLine.get_arg("-eps")), strToInt(cmdLine.get_arg("-maxIter")), strToInt(cmdLine.get_arg("-d")), strToInt(cmdLine.get_arg("-neighbour")));
            //std::cout << strToDouble(cmdLine.get_arg("-eps")) << strToInt(cmdLine.get_arg("-maxIter")) << strToInt(cmdLine.get_arg("-d")) << strToInt(cmdLine.get_arg("-neighbour"));
            paralelCompute(pid, numOfProcs, method, resultFile, statFile);
        }
        else if (tmp =="RELATIVEMDS")
        {
            int pEnum = strToInt(cmdLine.get_arg("-selStrategy"));
            //SDS(double eps, int maxIter, int d, ProjectionEnum baseVectInitt, int nofBaseVect, DistanceMetricsEnum distMetrics);
            SDS *method;

            if (pEnum == 1)
                method = new SDS(strToDouble(cmdLine.get_arg("-eps")), strToInt(cmdLine.get_arg("-maxIter")), strToInt(cmdLine.get_arg("-d")), ProjectionEnum::RAND, strToInt(cmdLine.get_arg("-noOfBaseVectors")), EUCLIDEAN); //may be manhatan or chebyshew
            else if (pEnum == 2)
                method = new SDS(strToDouble(cmdLine.get_arg("-eps")), strToInt(cmdLine.get_arg("-maxIter")), strToInt(cmdLine.get_arg("-d")), ProjectionEnum::PCA, strToInt(cmdLine.get_arg("-noOfBaseVectors")), EUCLIDEAN); //may be manhatan or chebyshew
            else
                method = new SDS(strToDouble(cmdLine.get_arg("-eps")), strToInt(cmdLine.get_arg("-maxIter")), strToInt(cmdLine.get_arg("-d")), ProjectionEnum::DISPERSION, strToInt(cmdLine.get_arg("-noOfBaseVectors")), EUCLIDEAN); //may be manhatan or chebyshew

            //std::cout << strToDouble(cmdLine.get_arg("-eps")) <<" "<< strToInt(cmdLine.get_arg("-maxIter")) <<" "<< strToInt(cmdLine.get_arg("-d")) <<" "<< strToInt(cmdLine.get_arg("-selStrategy")) <<" "<< strToInt(cmdLine.get_arg("-noOfBaseVectors")) <<" "<< EUCLIDEAN;
            paralelCompute(pid, numOfProcs, method, resultFile, statFile);
        }
        else if (tmp == "SMACOFMDS")
        {
            tmp = cmdLine.get_arg("-zeidel");
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
            if (tmp == "0" || tmp == "FALSE")
            {
                //	SMACOF(double eps, int maxIter, int d);
                double eps = strToDouble(cmdLine.get_arg("-eps"));
                int maxIter = strToInt(cmdLine.get_arg("-maxIter"));
                int d = strToInt(cmdLine.get_arg("-d"));

                SMACOF *method = new SMACOF(eps, maxIter, d);
                //std::cout << strToDouble(cmdLine.get_arg("-eps")) << strToInt(cmdLine.get_arg("-maxIter")) << strToInt(cmdLine.get_arg("-d")) << cmdLine.get_arg("-zeidel");
                paralelCompute(pid, numOfProcs, method, resultFile, statFile);
            }
            else
            {
                //SMACOFZEIDEL(double eps, int maxIter, int d, ShufleEnum shEnum);
                SMACOFZEIDEL *method = new SMACOFZEIDEL(strToDouble(cmdLine.get_arg("-eps")), strToInt(cmdLine.get_arg("-maxIter")), strToInt(cmdLine.get_arg("-d")), BUBLESORTDSC); // sorting method may be other
                //std::cout << strToDouble(cmdLine.get_arg("-eps")) << strToInt(cmdLine.get_arg("-maxIter")) << strToInt(cmdLine.get_arg("-d")) << BUBLESORTDSC << (cmdLine.get_arg("-zeidel"));
                paralelCompute(pid, numOfProcs, method, resultFile, statFile);
            }
        }
        else if (tmp == "SAMANN")
        {
            //SAMANN(int m1, int nl, double eta, int maxIter);
            SAMANN *method = new SAMANN(strToInt(cmdLine.get_arg("-mTrain")), strToInt(cmdLine.get_arg("-nNeurons")), strToDouble(cmdLine.get_arg("-eta")), strToInt(cmdLine.get_arg("-maxIter")));
            //std::cout << strToInt(cmdLine.get_arg("-mTrain")) << strToInt(cmdLine.get_arg("-nNeurons")) << strToDouble(cmdLine.get_arg("-eta")) << strToInt(cmdLine.get_arg("-maxIter"));
            paralelCompute(pid, numOfProcs, method, resultFile, statFile);
        }
        else if (tmp == "SOMMDS")
        {
            //SOMMDS(double eps, int max_iter, int d, int kx, int ky, int e_hat);
            //SOMMDS mthd11(epsilon, maxIter, d, 100, 3, 5);
            SOMMDS *method = new SOMMDS(strToDouble(cmdLine.get_arg("-eps")), strToInt(cmdLine.get_arg("-maxIter")), strToInt(cmdLine.get_arg("-mdsProjection")),strToInt(cmdLine.get_arg("-rows")),strToInt(cmdLine.get_arg("-columns")), strToInt(cmdLine.get_arg("-eHat")));
            //method.
            std::cout << strToDouble(cmdLine.get_arg("-eps")) << strToInt(cmdLine.get_arg("-maxIter")) << strToInt(cmdLine.get_arg("-mdsProjection")) << strToInt(cmdLine.get_arg("-rows")) << strToInt(cmdLine.get_arg("-columns")) << strToInt(cmdLine.get_arg("-eHat"));
            paralelCompute(pid, numOfProcs, method, resultFile, statFile);
        }
        else if (tmp == "SOM")
        {
            SOM *method = new SOM(strToInt(cmdLine.get_arg("-rows")),strToInt(cmdLine.get_arg("-columns")), strToInt(cmdLine.get_arg("-eHat")));
           // std::cout << strToInt(cmdLine.get_arg("-rows")) << "-rows" <<  strToInt(cmdLine.get_arg("-columns")) <<"-columns" << strToInt(cmdLine.get_arg("-eHat")) << "-eHat";
            paralelCompute(pid, numOfProcs, method, resultFile, statFile);
        }
        else
        {
            std::cout << "Unknown algorithm call";
        }
    }
    else
    {
        std::cout << "Input/output file parameter(s) not found";
    }

    /*PCA_ mthd1(d);
    PCA_ mthd2(80.0, true);*/
    //PCA mthd1((int)2);
    //PCA mthd2((double)10.0);
    //SDS mthd3(epsilon, maxIter, d, DISPERSION, 50, EUCLIDEAN);
    /*SMACOFZEIDEL mthd4 (epsilon, maxIter, d, BUBLESORTDSC);
    SMACOFZEIDEL mthd5 (epsilon, maxIter, d, BUBLESORTASC);
    SMACOFZEIDEL mthd6 (epsilon, maxIter, d, RANDOM);
    SMACOF mthd7 (epsilon, maxIter, d);*/
    //SAMANN mthd8(70, 10, 10.0, 50);
    //DMA mthd9(epsilon, 10, d, 15);
    //SOM mthd10(100, 3, 5);
    //mthd10.getProjection();
    //SOMMDS mthd11(epsilon, maxIter, d, 100, 3, 5);


    MPI_Finalize();
    return 0;
}

template <typename T>
void paralelCompute(int pid, int numOfProcs, T *mthd, std::string resultFile, std::string statFile)
{
    double t_start, t_end;                      // skaiciavimu pradzia ir pabaiga
    ObjectMatrix Y;                             // projekcijos matrica
    double *stressErrors;                       // surinktu is procesu paklaidu aibe (testavimui)
    double receivedStress, min_stress = 0.0;    // gaunama ir maziausia paklaidos
    double **receiveArray, **sendArray;         // gaunama ir siunciama Y matricos

    MPI_Status status;

    int send, min_rank = 0;

    if (pid == 0)
    {
        t_start = MPI_Wtime();
        if (numOfProcs == 1)
        {
            Y = mthd->getProjection();
            /* Y = mthd2.getProjection();
             Y = mthd3.getProjection();
             Y = mthd4.getProjection();
             Y = mthd5.getProjection();
             Y = mthd6.getProjection();
             Y = mthd7.getProjection();
             Y = mthd8.getProjection();
             Y = mthd9.getProjection();
             Y = mthd10.getProjection();
             Y = mthd11.getProjection();*/
                Y.saveDataMatrix(resultFile.c_str());
                ARFF::writeStatData(statFile, mthd->getStress(), MPI_Wtime() - t_start);
        }
        else
        {
            stressErrors = new double[numOfProcs];     // surinktu paklaidu masyvas (testavimui)
            //Y = mthd7.getProjection();
            Y = mthd->getProjection();
            int n = Y.getObjectCount();
            int m = Y.getObjectAt(0).getFeatureCount();

             stressErrors[0] = mthd->getStress();
            //stressErrors[0] = method.getQuantizationError(); // SOM does not have get stress

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

                Y.saveDataMatrix(resultFile.c_str());
                ARFF::writeStatData(statFile, mthd->getStress(), MPI_Wtime() - t_start);
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

                Y.saveDataMatrix(resultFile.c_str());
                ARFF::writeStatData(statFile, mthd->getStress(), MPI_Wtime() - t_start);

            }
        }
        //std::cout<<"Calculation time: "<<t_end - t_start<<" s."<<std::endl;
    }
    else
    {
        Y = mthd->getProjection();

        double stress = mthd->getStress();
        //double stress = method.getQuantizationError(); // SOM does not have get stress
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
/*
* Method that converts string command line parameter to double
*/
double strToDouble(std::string cmdParam)
{
    const char *str = cmdParam.c_str();
    char *err;
    double x = strtod(str, &err);
    if (*err == 0 && cmdParam !="")
    {
        //return x; //atof(cmdParam.c_str());
        return atof(cmdParam.c_str());
    }
}

int strToInt(std::string cmdParam)
{
    const char *str = cmdParam.c_str();
    char *err;
    double x = strtod(str, &err);
    if (*err == 0 && cmdParam !="")
    {
        //return x; //atof(cmdParam.c_str());
        return atoi(cmdParam.c_str());
    }
}
