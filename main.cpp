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
#include <mpi.h>
#include "Projection.h"
#include "PCA.h"
#include "AdditionalMethods.h"
#include "KMEANS.h"
#include "MLP.h"
#include "DECTREE.h"
#include "cmdLineParser/CommandLineParser.h"
#include <time.h>

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
    std::string tmp ="";
    const char* send;                                        //temp parameter for call method selection
    int tmpPathSize;

    int numOfProcs, pid; // (numOfProcs) procesu kiekis

//    MPI::Init(argc, argv);
    MPI_Init(&argc, &argv);
        //numOfProcs = MPI::COMM_WORLD.Get_size();
    MPI_Comm_size(MPI_COMM_WORLD, &numOfProcs);
    //pid = MPI::COMM_WORLD.Get_rank();
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    // MPI_Status status;

    if (pid == 0)
        time(&AdditionalMethods::startTime);

    AdditionalMethods::PID = pid;

    //std::cout <<AdditionalMethods::PID << " " << numOfProcs << std::endl;
   // MPI_Finalize();
   // return 0;

    CommandLineParser cmdLine(argc,argv,true);

    //extract command line arguments

    inputFile = cmdLine.get_arg("-i");
    resultFile = cmdLine.get_arg("-o");
    statFile = cmdLine.get_arg("-s");

    if (!inputFile.empty() || !resultFile.empty() || !statFile.empty())
    {
        AdditionalMethods::inputDataFile.assign(inputFile);

        //generate file name for X distance matrix
        //if (pid == 0) // if it is master then generate and brodcast the distance matrix file name
       // {
            AdditionalMethods::tempFileSavePath = strdup(AdditionalMethods::generateFileName().c_str());

            if (AdditionalMethods::tempFileSavePath == "")
            {
                MPI_Finalize();
                std::cout <<"Unable to generate file name for X distance matrix";
                return 0;
            }

        //     tmpPathSize = strlen(AdditionalMethods::tempFileSavePath) + 2; //get size of the generated file path + 2 adds space to '\0' symbols
       // }

      //  MPI_Bcast(&tmpPathSize, 1, MPI_INT, 0, MPI_COMM_WORLD); //broad cast the size

     //   if (pid != 0) // if it is not root process then allocate the plase that will store the passed path to the file
     //       AdditionalMethods::tempFileSavePath = (char*)malloc(tmpPathSize* sizeof(char));
//
     //   MPI_Bcast(AdditionalMethods::tempFileSavePath, tmpPathSize, MPI_CHAR, 0, MPI_COMM_WORLD); //bradcast the path to other processes

      //  std::cout << AdditionalMethods::PID << " " <<tmpPathSize <<" " << AdditionalMethods::tempFileSavePath <<std::endl;

        tmp = cmdLine.get_arg("-al");
        std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);

        Statistics::initSeed();

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
                //paralelCompute(pid, 5, method, resultFile, statFile);
            }
            else
            {
                //SMACOFZEIDEL(double eps, int maxIter, int d, ShufleEnum shEnum);
                SMACOFZEIDEL *method = new SMACOFZEIDEL(strToDouble(cmdLine.get_arg("-eps")), strToInt(cmdLine.get_arg("-maxIter")), strToInt(cmdLine.get_arg("-d")), RANDOM); // sorting method may be other
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
//            std::cout << strToDouble(cmdLine.get_arg("-eps")) << strToInt(cmdLine.get_arg("-maxIter")) << strToInt(cmdLine.get_arg("-mdsProjection")) << strToInt(cmdLine.get_arg("-rows")) << strToInt(cmdLine.get_arg("-columns")) << strToInt(cmdLine.get_arg("-eHat"));
            paralelCompute(pid, numOfProcs, method, resultFile, statFile);
        }
        else if (tmp == "SOM")
        {
            SOM *method = new SOM(strToInt(cmdLine.get_arg("-rows")),strToInt(cmdLine.get_arg("-columns")), strToInt(cmdLine.get_arg("-eHat")));
            // std::cout << strToInt(cmdLine.get_arg("-rows")) << "-rows" <<  strToInt(cmdLine.get_arg("-columns")) <<"-columns" << strToInt(cmdLine.get_arg("-eHat")) << "-eHat";
            paralelCompute(pid, numOfProcs, method, resultFile, statFile);
        }
        else if (tmp == "KMEANS")
        {
                  KMEANS *method = new KMEANS(strToInt(cmdLine.get_arg("-noOfClust")),strToInt(cmdLine.get_arg("-maxIter")));
            // std::cout << strToInt(cmdLine.get_arg("-rows")) << "-rows" <<  strToInt(cmdLine.get_arg("-columns")) <<"-columns" << strToInt(cmdLine.get_arg("-eHat")) << "-eHat";
                  paralelCompute(pid, numOfProcs, method, resultFile, statFile);
        }
         else if (tmp == "MLP")
        {
            tmp = cmdLine.get_arg("-kFoldVal");
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
            bool kFoldValidation = true;
            if (tmp == "0" || tmp == "FALSE")
            {
                kFoldValidation =false;
            }
            //  KMEANS *method = new KMEANS(strToInt(cmdLine.get_arg("-noOfClust")),strToInt(cmdLine.get_arg("-maxIter")));
                MLP *method = new MLP(strToInt(cmdLine.get_arg("-h1pNo")), strToInt(cmdLine.get_arg("-h2pNo")), strToDouble(cmdLine.get_arg("-qty")), strToInt(cmdLine.get_arg("-maxIter")), kFoldValidation);
            // std::cout << strToInt(cmdLine.get_arg("-rows")) << "-rows" <<  strToInt(cmdLine.get_arg("-columns")) <<"-columns" << strToInt(cmdLine.get_arg("-eHat")) << "-eHat";
                paralelCompute(pid, numOfProcs, method, resultFile, statFile);
            }
         else if (tmp == "DECTREE")
        {
                //  KMEANS *method = new KMEANS(strToInt(cmdLine.get_arg("-noOfClust")),strToInt(cmdLine.get_arg("-maxIter")));
                DECTREE *method = new DECTREE(strToDouble(cmdLine.get_arg("-dL")), strToDouble(cmdLine.get_arg("-dT")), strToDouble(cmdLine.get_arg("-r")), strToInt(cmdLine.get_arg("-nTree")));
            // std::cout << strToInt(cmdLine.get_arg("-rows")) << "-rows" <<  strToInt(cmdLine.get_arg("-columns")) <<"-columns" << strToInt(cmdLine.get_arg("-eHat")) << "-eHat";
                paralelCompute(pid, numOfProcs, method, resultFile, statFile);
        }
        else
        {
            std::cout << "Unknown algorithm call" << std::endl;
        }
    }
    else
    {
        std::cout << "Input/output file parameter(s) not found" << std::endl;
    }


//std::cout <<"aaa " <<AdditionalMethods::PID << std::endl;

    MPI_Finalize();
//AdditionalMethods::deleteFile();//
    return 0;
}

template <typename T>
void paralelCompute(int pid, int numOfProcs, T *mthd, std::string resultFile, std::string statFile)
{
    time_t t_end;                      // skaiciavimu pradzia ir pabaiga
    ObjectMatrix Y;                             // projekcijos matrica
    double *stressErrors;                       // surinktu is procesu paklaidu aibe (testavimui)
    double receivedStress, min_stress = 0.0;    // gaunama ir maziausia paklaidos
    double **receiveArray, **sendArray;         // gaunama ir siunciama Y matricos

    MPI_Status status;

    int send, min_rank = 0;

// time(&t_start);

    if (pid == 0)
    {
        if (numOfProcs == 1)
        {
            Y = mthd->getProjection();
            Y.saveDataMatrix(resultFile.c_str());
           // time(&t_end);
            ARFF::writeStatData(statFile, mthd->getStress(), difftime(time(&t_end), AdditionalMethods::startTime));
//std::cout << " laikas  " << difftime(time(&t_end), AdditionalMethods::startTime) <<  std::endl;
        }
        else
        {
            stressErrors = new double[numOfProcs];     // surinktu paklaidu masyvas (testavimui)
            Y = mthd->getProjection();
            int n ;//= Y.getObjectCount();
            int m ;//= Y.getObjectAt(0).getFeatureCount();

            stressErrors[0] = mthd->getStress()+1;
//std::cout << "0 turi paklaida " << stressErrors[0] << std::endl;
            for (int i = 1; i < numOfProcs; i++)
            {
                MPI_Recv(&receivedStress, 1, MPI_DOUBLE, i, i, MPI_COMM_WORLD, &status);  // priimama paklaida is kiekvieno proceso
//std::cout << "gauna is " <<i << " projekcijos paklaida " << receivedStress << std::endl;
                stressErrors[i] = receivedStress;
            }

          //  time(&t_end);

            min_stress = stressErrors[0];
            for (int i = 1; i < numOfProcs; i++)
               {
                   if (stressErrors[i] < min_stress)
                {
                    min_stress = stressErrors[i];
                    min_rank = i;

                }
//std::cout << "rankas: " <<min_rank << " err: " << stressErrors[i] << std::endl;
               }
//std::cout << "rankas is " <<min_rank << " maziausias" << std::endl;
            if (min_rank == 0)  // jei maziausia paklaida tevinio proceso siunciamas pranesimas likusiems, kad savo Y nesiustu
            {
                send = 0;

                for (int i = 1; i < numOfProcs; i++)
                    MPI_Send(&send, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
//std::cout << "ssiusta visiems 0 " << std::endl;
                Y.saveDataMatrix(resultFile.c_str());
              //  time(&t_end);
                ARFF::writeStatData(statFile, stressErrors[min_rank], difftime(time(&t_end), AdditionalMethods::startTime));
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

                 //   int nn, mm; //kintamieji nusako kokie dyd=io matrica bus gaunama

                    MPI_Recv(&n, 1, MPI_INT, min_rank, min_rank, MPI_COMM_WORLD, &status);
                    MPI_Recv(&m, 1, MPI_INT, min_rank, min_rank, MPI_COMM_WORLD, &status);
//std::cout << "gaunama n ir m " << n << " " << m << std::endl;

                /*if (nn!=n || mm!m) //will have to receive the whole Y data since matrices of the parent and child do not match
                {
                    n = mm;
                    m = mm;
                }*/
 //std::cout << "Procesorius  " << pid  << " gavo matrica" << std::endl;
               // Y = AdditionalMethods::DoubleToObjectMatrix(receiveArray, n, m); // gra=ianams tik skai2iai realiai priskirti negalima kadangi dingsta kals4s
                receiveArray = AdditionalMethods::Array2D(n, m);
                MPI_Recv(&(receiveArray[0][0]), n * m, MPI_DOUBLE, min_rank, min_rank, MPI_COMM_WORLD, &status);   // priimama Y data dali
                Y = AdditionalMethods::DoubleToObjectMatrix(receiveArray, n, m);
//std::cout << "Y sukurta  "<< std::endl;
                //update the Y matrix data that was received from the another process
                for (int i = 0; i < n; i++)
                        for (int j = 0; j < m; j++)
                            Y.updateDataObject(i,j,receiveArray[i][j]);
                int classQty = 0;
                MPI_Recv(&classQty, 1, MPI_INT, min_rank, min_rank, MPI_COMM_WORLD, &status); // receive the different class qty

 //std::cout << "gaunamas klasiu kiekis  " << classQty  << std::endl;

                if (classQty !=0 )
                {
                    std::vector<std::string> receivedAtrrClasses;
                    int clNameLenght;
                    for (int cl = 0; cl < classQty; cl++)
                    {
                        MPI_Recv(&clNameLenght, 1, MPI_INT, min_rank, min_rank, MPI_COMM_WORLD, &status); // must send +1
                        char buffer[clNameLenght];
                        MPI_Recv(buffer, clNameLenght, MPI_CHAR, min_rank, min_rank, MPI_COMM_WORLD, &status);
                        receivedAtrrClasses.push_back(std::string(buffer));
//std::cout << buffer << std::endl;
                    }
                //set class present yra kazkas neaisku keli tokie patys metodai :!!!!
                    Y.setPrintClass(receivedAtrrClasses);

                    int classLabelBuffer[n];
                    MPI_Recv(&classLabelBuffer, n, MPI_INT, min_rank, min_rank, MPI_COMM_WORLD, &status);
                    for (int i = 0; i < n; i++)
                        {
                            Y.updateDataObjectClass(i,classLabelBuffer[i]);
//std::cout << classLabelBuffer[i] << " ";
                        }
                }
                Y.saveDataMatrix(resultFile.c_str());
                //time(&t_end);
                ARFF::writeStatData(statFile, stressErrors[min_rank], difftime(time(&t_end), AdditionalMethods::startTime));
//std::cout << " laikas  " << difftime(time(&t_end), AdditionalMethods::startTime) <<  std::endl;
            }
        }
    }
    else
    {
        Y = mthd->getProjection();

        double stress = mthd->getStress();
        MPI_Send(&stress, 1, MPI_DOUBLE, 0, pid, MPI_COMM_WORLD);  // siunciama paklaida teviniam procesui
//std::cout << "Procesorius  " << pid  << " issiunte pakalaida" << std::endl;
        MPI_Recv(&send, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);  // priimamas pranesimas ar siusti Y


        if (send == 1)          // siusti, jei send = 1, nesiusti, jei send = 0
        {
            int n = Y.getObjectCount();
            int m = Y.getObjectAt(0).getFeatureCount();
            //siisiunciam busimos matricos dydi //SOM atveju nugal4toj7 kiekis gali ir nesutapti su tevinio porceso turimu
            MPI_Send(&n, 1, MPI_INT, 0, pid, MPI_COMM_WORLD);
            MPI_Send(&m, 1, MPI_INT, 0, pid, MPI_COMM_WORLD);

            sendArray = AdditionalMethods::Array2D(n, m);
            sendArray = AdditionalMethods::ObjectMatrixToDouble(Y);
            MPI_Send(&(sendArray[0][0]), m * n, MPI_DOUBLE, 0, pid, MPI_COMM_WORLD);  // siunciama Y

            int classQty = Y.getClassCount();
            MPI_Send(&classQty, 1, MPI_INT, 0, pid, MPI_COMM_WORLD); //siunciam kiek  yra skirtingu klasiu atributu sekcijoje
            if (classQty != 0 )
            {
                std::vector<std::string> possClasses = Y.getStringClassAttributes();
                for (int i = 0 ; i < classQty; i ++)
                {
                   //  std::string cls = possClasses.at(i);
                   // const char* cString = cls.c_str();
//std::cout << cls << " ";
                    int clsSize = possClasses.at(i).size()+1;
                    MPI_Send(&clsSize, 1, MPI_INT, 0, pid, MPI_COMM_WORLD); //siunciam charo dydi
                    MPI_Send((void*)possClasses.at(i).c_str(), clsSize, MPI_CHAR, 0, pid, MPI_COMM_WORLD); //siunciam patį stringą
                }
                //kadangi yra ir pačios klases siunciam ir objekto klasių masyvą
                int classLabelBuffer[n];
                for (int i = 0; i < n; i++)
                    classLabelBuffer[i] = Y.getObjectAt(i).getClassLabel();

                MPI_Send(&classLabelBuffer, n, MPI_INT, 0, pid, MPI_COMM_WORLD); //send buffer
            }

//std::cout << "Procesorius  " << pid  << " issiunte matrica" << std::endl;
        }

    }
   // MPI_Barrier(MPI_COMM_WORLD);
}

void PrintMatrix(ObjectMatrix matrix)
{
    int numOfObjects = matrix.getObjectCount();
    int numOfFeatures = matrix.getObjectAt(0).getFeatureCount();

//    std::cout<<"******* Projekcijos matrica *******"<<std::endl;
    for (int i = 0; i < numOfObjects; i++)
    {
        for (int j = 0; j < numOfFeatures; j++);
 //           std::cout<<matrix.getObjectAt(i).getFeatureAt(j)<<" ";
 //       std::cout<<std::endl;
    }
}
/*
* Method that converts string command line parameter to doublel
*/
double strToDouble(std::string cmdParam)
{
    const char *str = cmdParam.c_str();
    char *err;
    double x = strtod(str, &err);
    if (*err == 0 && cmdParam !="")
    {
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
        return atoi(cmdParam.c_str());
    }
}
