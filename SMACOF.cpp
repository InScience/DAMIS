///////////////////////////////////////////////////////////
//  SMACOF.cpp
//  Implementation of the Class SMACOF
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \class SMACOF
    \brief A class of methods and attributes for SMACOF algorithm.
 */
#include "SMACOF.h"
#include "ShufleObjects.h"
#include <string>
#include <sstream>
#include <vector>
#include "DataObject.h"
#include <float.h>

SMACOF::SMACOF(){

}

SMACOF::~SMACOF(){

}

SMACOF::SMACOF(double eps, int maxIter, int d):MDS(eps, maxIter, d){
    initializeProjectionMatrix();
}

SMACOF::SMACOF(double eps, int maxIter, int d, ObjectMatrix X_base, ObjectMatrix Y_base):MDS(eps, maxIter, d){
    X = X_base;
    Y = Y_base;
}

SMACOF::SMACOF(ObjectMatrix initialY, double eps, int maxIter, int d):MDS(eps, maxIter, d){
    Y = initialY;
}

SMACOF::SMACOF(double eps, int maxIter, int d, ObjectMatrix initialX):MDS(eps, maxIter, d, initialX){
    initializeProjectionMatrix();
}

ObjectMatrix SMACOF::getProjection(){
    stressErrors.reserve(maxIteration);
    int iteration = 0;
    int n = X.getObjectCount();
    stressErrors.push_back(SMACOF::getStress());
    double sum = 0.0;
    double Epsilon = DBL_MAX;
    ObjectMatrix Gutman;
    ObjectMatrix Y_new(n);
    std::vector<double> Y_newRow;
    Y_newRow.reserve(d);

    while (iteration < maxIteration && Epsilon > epsilon)
    {
        Y_new.clearDataObjects();
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

        stressErrors.push_back(getStress());
        iteration++;
        Epsilon = stressErrors.at(iteration - 1) - stressErrors.at(iteration);
    }
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
