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
    getProjection();
    Y.saveDataMatrix("tests/smacofZeidel.txt");
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
    ObjectMatrix Gutman;
    std::vector<int> shufledIndexes;
    shufledIndexes.reserve(n);
    
    while (iteration < getMaxIteration() && (oldStressError - newStressError) > getEpsilon())
    {
        shufledIndexes = ShufleObjects::shufleObjectMatrix(shufleEnum, Y);
        oldStressError = tmpStressError;
        Gutman = getGutman();
        for (int row=0; row < n; row++)
        {
            i = shufledIndexes.at(row);
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
