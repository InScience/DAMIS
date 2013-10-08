///////////////////////////////////////////////////////////
//  SMACOF.cpp
//  Implementation of the Class SMACOF
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "SMACOF.h"
#include "ShufleObjects.h"

SMACOF::SMACOF(){

}

SMACOF::~SMACOF(){

}

/**
 * Constructor for SMACOF object
 */
SMACOF::SMACOF(float eps, int maxIter, int d):MDS(eps, maxIter, d){
    getProjection();
    //Y.saveDataMatrix(Y, "tests/smacof.txt");
}

/**
 * Constructor called from SMACOF class
 */
SMACOF::SMACOF(float eps, int maxIter, int d, ObjectMatrix X, ObjectMatrix Y):MDS(eps, maxIter, d){

}

/**
 * Pure virtual method that calculates the projection
 */
ObjectMatrix SMACOF::getProjection(){

    int iteration = 0;
    int n = X.getObjectCount();
    double oldStressError = getStress();
    double newStressError = 0.0;
    double tmpStressError = oldStressError;
    double sum = 0.0;
    ObjectMatrix Gutman;

    while (iteration < getMaxIteration() && (oldStressError - newStressError) > getEpsilon())
    {
        oldStressError = tmpStressError;
        Gutman = getGutman();
        for (int i=0; i < n; i++)
        {
            for (int j = 0; j < d; j++)
            {
                sum = 0.0;
                for (int k = 0; k < n; k++)
                        sum += Gutman.getObjectAt(i).getItems().at(k) * Y.getObjectAt(k).getItems().at(j);
                Y.getObjectAt(i).getItems().at(j) = sum / n;
            }
        }
        newStressError = getStress();
        tmpStressError = newStressError;
        iteration++;
    }
    
    return Y;
}

ObjectMatrix SMACOF::ReturnY()
{
    
    return Y;
}