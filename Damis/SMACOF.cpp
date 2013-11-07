///////////////////////////////////////////////////////////
//  SMACOF.cpp
//  Implementation of the Class SMACOF
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "SMACOF.h"
#include "ShufleObjects.h"
#include <string>
#include <sstream>
#include <vector>
#include "DataObject.h"

SMACOF::SMACOF(){

}

SMACOF::~SMACOF(){

}

/**
 * Constructor for SMACOF object
 */
SMACOF::SMACOF(float eps, int maxIter, int d):MDS(eps, maxIter, d){
    initializeProjectionMatrix();
}

/**
 * Constructor called from SMACOF class
 */
SMACOF::SMACOF(float eps, int maxIter, int d, ObjectMatrix X_base, ObjectMatrix Y_base):MDS(eps, maxIter, d){
    X = X_base;
    Y = Y_base;
}

SMACOF::SMACOF(float eps, int maxIter, int d, ObjectMatrix initialY):MDS(eps, maxIter, d){
    Y = initialY;
}

/**
 * Pure virtual method that calculates the projection
 */
ObjectMatrix SMACOF::getProjection(){

    iteration = 0;
    int n = X.getObjectCount();
    double oldStressError = getStress();
    double newStressError = 0.0;
    double tmpStressError = oldStressError;
    double sum = 0.0;
    ObjectMatrix Gutman;
    ObjectMatrix Y_new(n);
    std::vector<double> Y_newRow;
    Y_newRow.reserve(d);

    while (iteration < getMaxIteration() && (oldStressError - newStressError) > getEpsilon())
    {
        Y_new.clearDataObjects();
        oldStressError = tmpStressError;
        Gutman = getGutman();

        for (int i=0; i < n; i++)
        {
            Y_newRow.clear();
            for (int j = 0; j < d; j++)
            {
                sum = 0.0;
                for (int k = 0; k < n; k++)
                        sum += Gutman.getObjectAt(i).getFeatureAt(k) * Y.getObjectAt(k).getFeatureAt(j);
                Y_newRow.push_back(sum / n);                
            }
            Y_new.addObject(DataObject(Y_newRow));
        }
        Y = Y_new;
        //std::stringstream ss;
        //ss << iteration;
        //std::string str = "test_ " + ss.str();
        //Y.saveDataMatrix(str.c_str());
        newStressError = getStress();
        tmpStressError = newStressError;
        iteration++;
    }
    finalEpsilon = oldStressError - newStressError;
    return Y;
}

double SMACOF::getStress()
{
    return MDS::getStress();
}

ObjectMatrix SMACOF::getGutmanMatrix()
{
    return MDS::getGutman();
}
