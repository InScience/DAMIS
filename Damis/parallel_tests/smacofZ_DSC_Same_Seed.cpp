/* 
 * File:   main.cpp
 * Author: mindaugas
 *
 * Created on August 28, 2013, 9:57 PM
 */

#include <cstdlib>
#include <vector>
#include "../ARFF.h"
#include "../Statistics.h"
#include "../ShufleEnum.h"
#include <iostream>
#include "../DistanceMetrics.h"
#include "../ObjectMatrix.h"
#include "../MDS.h"
#include "../HPCMethod.h"
#include "../DimReductionMethod.h"
#include "../SMACOF.h"
#include "../SAMANN.h"
#include "../SMACOFZEIDEL.h"
#include "mpi.h"
#include "../Projection.h"
#include "../AdditionalMethods.h"
#include <sstream>
#include <fstream>
using namespace std;

int AdditionalMethods::PID;

void TestMessagePassing(int n, int k, const char* method)
{
	cout << method << ": testing if CPU No. 0 can receive messages from other CPUs" << endl;
	if (n == k + 1)
		cout << method << ": test passed." << endl;
	else
		cout << method << ": test FAILED!!!" <<endl;
}

void TestMessageSendingToDie(vector<int> cpu, vector<int> ans, const char* method)
{
	int n = cpu.size();
	bool answer = true;
	cout << method << ": testing if CPUs: ";
	for (int i = 0; i < n - 1; i++)
		cout << cpu.at(i) << ", ";
	cout << cpu.at(n - 1) << " received a message from CPU No. 0 to die." << endl;
	
	for (int i = 0; i < n; i++)
	{
		if (ans.at(i) != 1)
		{
			answer = false;
			break;
		}
	}

	if (answer == true)
		cout<< method << ": test passed." << endl;
	else
		cout<< method << ": test FAILED!!!" << endl;
} 

void TestMessageSendingToSendMatrix (int cpu, int ans, const char* method)
{
	cout << method << ": testing if CPU No. " << cpu << " received a message to send back matrix Y." << endl;

	if (ans == 1)
		cout<< method << ": test passed." << endl;
	else
		cout<< method << ": test FAILED!!!" << endl;
} 

void TestTheSendOfMatrix (ObjectMatrix X, ObjectMatrix Y, int cpu, const char* method)
{
	cout << method << ": testing if CPU No. 0 succesfully received matrix from CPU No. " << cpu << endl;
	if (X.getObjectCount() == Y.getObjectCount())
		cout << method << ": test passed." << endl;
	else
		cout << method << ": test FAILED!!!" << endl;
} 

void TestProjectionMatrixDimmensions(ObjectMatrix X, ObjectMatrix Y, int d, int CPU, const char* method)
{
	bool answer = true;
	int mx = X.getObjectCount();
	int my = Y.getObjectCount();
	cout << method << ": testing if the projection matrix Y is a [" << mx << "x" << d << "] matrix." << endl;
	if (mx == my)
	{
		for (int i = 0; i < my; i++)
		{
			if (Y.getObjectAt(i).getFeatureCount() != d)
			{
				answer = false;
				break;
			}
		}
		if (answer == true)
			cout << method << ": test passed." << endl;
		else
			cout << method << ": test FAILED (the number of columns does not match the preffered one)." << endl;
	}
	else
		cout << method << ": test FAILED (the number of rows in matrix Y received from CPU No. " << CPU
                     << " does not match the number of rows in matrix X)." << endl;
}

void TestProjectionMatrix(ObjectMatrix Y[], int k, const char* method)
{
	bool answer = true;
	cout << method << ": testing if the projection matrixes Y are identical." << endl;
	int m = Y[0].getObjectCount();
	int n = Y[0].getObjectAt(0).getFeatureCount();
	for (int i = 1; i < k; i++)
	{
		if (Y[i].getObjectCount() != m)
		{
			answer = false;
			break;
		}
	}
	if (answer == false)
		cout << method << ": test FAILED (mismatch of the number of rows in matrixes Y). " << endl;
	else
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int l = 0; l < k - 1; l++)
				{
					if (Y[l].getObjectAt(i).getFeatureAt(j) - Y[l + 1].getObjectAt(i).getFeatureAt(j) > 0.01)
					{
						answer = false;
						break;
					}
				}
				if (answer == false)
					break;
			}
			if (answer == false)
				break;
		}
		if (answer == true)
			cout << method << ": test passed." << endl;
		else
			cout << method << ": test FAILED!!!" << endl;
	}	
}


int main(int argc, char** argv) {
    //ofstream file ("parallelMethodsTestingReport.txt");
    int numOfProcs, pid; 
                                                // (pid) proceso ID
                                                // (send) pranesimas del Y siuntimo / nesiuntimo
                                                // (min_rank) proceso ID, apskaiciavusio maziausia paklaida
    ObjectMatrix Y;                             // projekcijos matrica
    double **receiveArray, **sendArray;         // gaunama ir siunciama Y matricos
    double epsilon;                             // skaiciavimu tikslumas
    int maxIter, d;                             // (maxIter) leistinas iteraciju kiekis, (d) mazinimo dimensija
    
    epsilon = 0.001;
    maxIter = 100;
    d = 2;
    
    MPI::Init(argc, argv);
    pid = MPI::COMM_WORLD.Get_rank();
    AdditionalMethods::PID = 0;
    numOfProcs = MPI::COMM_WORLD.Get_size();
    MPI_Status status;

    const char* method = "SMACOFZEIDEL_BUBLESORTDSC";
    
    //SMACOF mthd (epsilon, maxIter, d);   
    SMACOFZEIDEL mthd (epsilon, maxIter, d, BUBLESORTDSC);
    //SMACOFZEIDEL mthd (epsilon, maxIter, d, BUBLESORTASC);
    //SMACOFZEIDEL mthd (epsilon, maxIter, d, RANDOM);
    //SAMANN mthd(50, 10, 1.0, 1);

    if (pid == 0)
    { 
        if (numOfProcs == 1)
        {                    
            Y = mthd.getProjection(); 
            TestProjectionMatrixDimmensions(mthd.X, Y, d, 0, method);
        }
        else
        {
	    ObjectMatrix YY[numOfProcs];     
            Y = mthd.getProjection();
	    int n = Y.getObjectCount();
	    int m = Y.getObjectAt(0).getFeatureCount();
	    YY[0] = Y;
            
            for (int i = 1; i < numOfProcs; i++)
            {
                receiveArray = AdditionalMethods::Array2D(n, m);
                MPI_Recv(&(receiveArray[0][0]), m * n, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);   // priimama Y
                Y = AdditionalMethods::DoubleToObjectMatrix(receiveArray, n, m);
		YY[i] = Y;
            }
            TestProjectionMatrix(YY, numOfProcs, method);
        }
    }
    else
    {
        Y = mthd.getProjection();
	int n = Y.getObjectCount();
	int m = Y.getObjectAt(0).getFeatureCount();
	sendArray = AdditionalMethods::Array2D(n, m);
	sendArray = AdditionalMethods::ObjectMatrixToDouble(Y);
	MPI_Send(&(sendArray[0][0]), m * n, MPI_DOUBLE, 0, pid, MPI_COMM_WORLD);  // siunciama Y  
    }    
    
    MPI_Finalize();    
    
    return 0;
}

