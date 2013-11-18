///////////////////////////////////////////////////////////
//  SMACOFZEIDEL.cpp
//  Implementation of the Class SMACOFZEIDEL
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "SMACOFZEIDEL.h"
#include "ShufleObjects.h"
#include <float.h>


SMACOFZEIDEL::SMACOFZEIDEL(){

}

SMACOFZEIDEL::~SMACOFZEIDEL(){

}

/**
 * Constructor of the class
 */
SMACOFZEIDEL::SMACOFZEIDEL(float eps, int maxIter, int d, ShufleEnum shEnum):SMACOF(eps, maxIter, d){
    shufleEnum = shEnum;
    initializeProjectionMatrix();
}

SMACOFZEIDEL::SMACOFZEIDEL(float eps, int maxIter, int d, ShufleEnum shEnum, ObjectMatrix initProjection):SMACOF(eps, maxIter, d)
{
    shufleEnum = shEnum;
    Y = initProjection;
}

/**
 * Our virtual method that calculates the projection
 */
ObjectMatrix SMACOFZEIDEL::getProjection(){

    stressErrors.reserve(maxIteration);
    int i;
    int n = X.getObjectCount();
    stressErrors.push_back(getStress());
    double sum = 0.0;
    double Epsilon = DBL_MAX;
    ObjectMatrix Gutman, Y_new(n);
    std::vector<int> shufledIndexes;
    shufledIndexes.reserve(n);
    Y_new = Y;
    Gutman = getGutman();
    int iteration = 0;
    
    while (iteration < maxIteration && Epsilon > epsilon)
    {
        shufledIndexes = ShufleObjects::shufleObjectMatrix(shufleEnum, Y);
        
        for (int row=0; row < n; row++)
        {
            i = shufledIndexes.at(row);
            for (int j = 0; j < d; j++)
            {
                sum = 0.0;
                for (int k = 0; k < n; k++)
                        sum += Gutman.getObjectAt(i).getFeatureAt(k) * Y.getObjectAt(k).getFeatureAt(j);
                Y_new.updateDataObject(i, j, (sum / n));
            }
            Gutman = getGutman(Y_new);
        }
        Y = Y_new;
        
        iteration++;    
        stressErrors.push_back(getStress());        
        Epsilon = stressErrors.at(iteration - 1) - stressErrors.at(iteration);
    }

    return Y;
}

double SMACOFZEIDEL::getStress()
{
    return MDS::getStress();
}

std::vector<double> SMACOFZEIDEL::getStressErrors()
{
    return stressErrors;
}
