///////////////////////////////////////////////////////////
//  PSMACOF.cpp
//  Implementation of the Class PSMACOF
//  Created on:      07-Lie-2013 20:07:31
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include <string.h>

#include "PSMACOF.h"
#include "Statistics.h"
#include <sstream>
#include <string>

PSMACOF::PSMACOF(){

}

PSMACOF::~PSMACOF(){

}

/**
 * Constructor for parallel algorithm object. Add number of processors (p)
 */
PSMACOF::PSMACOF(float eps, int maxIter, int d, int numOfProcs):SMACOF(eps, maxIter, d){
    p = numOfProcs;
}


/**
 * Pure virtual method that calculates the projection
 */

ObjectMatrix PSMACOF::getProjection(){
    
    Y = SMACOF::getProjection();    
    return Y;
}

double** PSMACOF::getProjectionInDoubles()
{
    double **projectionMatrix;
    projectionMatrix = ObjectMatrixToDouble(Y);
    
    return projectionMatrix;
}

double** PSMACOF::ObjectMatrixToDouble(ObjectMatrix matrix)
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

double PSMACOF::getStress()
{
    return getStress();
}
