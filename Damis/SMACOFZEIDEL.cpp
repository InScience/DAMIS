///////////////////////////////////////////////////////////
//  SMACOFZEIDEL.cpp
//  Implementation of the Class SMACOFZEIDEL
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "SMACOFZEIDEL.h"
#include "ShufleObjects.h"


SMACOFZEIDEL::SMACOFZEIDEL(){

}

SMACOFZEIDEL::~SMACOFZEIDEL(){

}

/**
 * Constructor of the class
 */
SMACOFZEIDEL::SMACOFZEIDEL(float eps, int maxIter, int d, ShufleEnum shEnum):SMACOF(eps, maxIter, d){
    shufleEnum = shEnum;
}

/**
 * Our virtual method that calculates the projection
 */
ObjectMatrix SMACOFZEIDEL::getProjection(){

    int iteration = 0, i;
    int n = X.getObjectCount();
    double oldStressError = getStress();
    double newStressError = 0.0;
    double tmpStressError = oldStressError;
    double sum = 0.0;
    ObjectMatrix Gutman, Y_new;
    std::vector<int> shufledIndexes;
    shufledIndexes.reserve(n);
    Y_new = Y;
    Gutman = getGutman();
    while (iteration < getMaxIteration() && (oldStressError - newStressError) > getEpsilon())
    {
        shufledIndexes = ShufleObjects::shufleObjectMatrix(shufleEnum, Y);
        oldStressError = tmpStressError;
        
        for (int row=0; row < n; row++)
        {
            i = shufledIndexes.at(row);
            for (int j = 0; j < d; j++)
            {
                sum = 0.0;
                for (int k = 0; k < n; k++)
                        sum += Gutman.getObjectAt(i).getItems().at(k) * Y.getObjectAt(k).getItems().at(j);
                Y.getObjectAt(i).UpdateValue(j, sum / n);
                //Y.getObjectAt(i).getItems().at(j) = sum / n;
            }
            Gutman = getGutman();
        }
        newStressError = getStress();
        tmpStressError = newStressError;
        iteration++;
    }
    return Y;
}
