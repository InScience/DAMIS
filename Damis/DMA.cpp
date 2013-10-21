///////////////////////////////////////////////////////////
//  DMA.cpp
//  Implementation of the Class DMA
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "DMA.h"
#include "ShufleEnum.h"
#include "ShufleObjects.h"

DMA::DMA(){

}



DMA::~DMA(){

}





/**
 * Constructor for DMA object
 */
DMA::DMA(float eps, int maxIter, int d, int neighbours):MDS(eps, maxIter, d){
    neighbourNumber = neighbours;
}


/**
 * Gets neighbour
 * neighbour
 * Gets neighbour quantity
 */
int DMA::getNeighbours(){

	return neighbourNumber;
}


/**
 * Pure virtual method that calculates the projection
 */
ObjectMatrix DMA::getProjection(){
    int m = X.getObjectCount();
    int iteration = 0;
    double oldStressError = getStress();
    double newStressError = 0.0, sum = 0.0;
    double tmpStressError = oldStressError;
    vMatrix = ObjectMatrix(m, m);
    ObjectMatrix Gutman;
    ObjectMatrix Y_new(m, d);
    Gutman = ObjectMatrix(m, m);
    std::vector<double> vMatrixObject;
    std::vector<int> shufledIndexes;
    shufledIndexes.reserve(m);
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
            vMatrixObject.push_back(0.0);
        vMatrix.addObject(DataObject(vMatrixObject));    
        vMatrixObject.clear();
    }
    
    for (int i = 0; i < m; i++)
    {
        for (int k = (i - neighbourNumber); k < (i + neighbourNumber); k++)
        {
            if (k > 0 && k < m)
            {
                if (k != i)
                    vMatrix.getObjectAt(i).features[k] = -1.0;
                else if (i <= neighbourNumber)
                    vMatrix.getObjectAt(i).features[i] = neighbourNumber + i;
                else if (i > neighbourNumber)
                    vMatrix.getObjectAt(i).features[i] = 2 * neighbourNumber - (m - i);
                else
                    vMatrix.getObjectAt(i).features[i] = 2 * neighbourNumber;
            }
        }
    }
    
    while (iteration < getMaxIteration() && (oldStressError - newStressError) > getEpsilon())
    {
        iteration = iteration + 1;
        shufledIndexes = ShufleObjects::shufleObjectMatrix(RANDOM, Y);
        oldStressError = tmpStressError;
        Gutman = getGutman();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                Gutman.getObjectAt(i).features[j] = Gutman.getObjectAt(i).features.at(j) - vMatrix.getObjectAt(i).features.at(j);
        
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < d; j++)
            {
                sum = 0.0;
                for (int k = (i - neighbourNumber); k < (i + neighbourNumber); k++)
                    if (k > 0 && k < m)
                        sum = sum + Gutman.getObjectAt(i).features.at(k) * Y.getObjectAt(k).features.at(j);
                vMatrixObject.push_back(Y.getObjectAt(i).features.at(j) + 0.5 * sum / vMatrix.getObjectAt(i).features.at(i));
            }
            Y_new.addObject(DataObject(vMatrixObject));
            vMatrixObject.clear();
        }
        Y = Y_new;
        newStressError = getStress();
        tmpStressError = newStressError;
    }
    
    return  Y;
}

/**
 * Calculates V matrix
 */
void DMA::getV(){

}

/**
 * Sets neighbour quantity
 */
void DMA::setNeighbours(int neighbours){
    neighbourNumber = neighbours;
}