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
    initializeProjectionMatrix();
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
    ObjectMatrix Gutman;
    ObjectMatrix Y_new(m);
    Gutman = ObjectMatrix(m);
    vMatrix = ObjectMatrix(m);    
    std::vector<int> shufledIndexes;
    shufledIndexes.reserve(m);
    std::vector<double> vMatrixObject;
    Y_new = Y;
    getV();
      
    while (iteration < getMaxIteration() && (oldStressError - newStressError) > getEpsilon())
    {
        iteration = iteration + 1;
        shufledIndexes = ShufleObjects::shufleObjectMatrix(RANDOM, Y);
        oldStressError = tmpStressError;
        Gutman = getGutman();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                Gutman.updateDataObject(i, j, Gutman.getObjectAt(i).getFeatureAt(j) - vMatrix.getObjectAt(i).getFeatureAt(j));
        
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < d; j++)
            {
                sum = 0.0;
                for (int k = (i - neighbourNumber); k < (i + neighbourNumber); k++)
                    if (k >= 0 && k < m)
                        sum += Gutman.getObjectAt(i).getFeatureAt(k) * Y.getObjectAt(k).getFeatureAt(j);
                Y_new.updateDataObject(i, j, Y.getObjectAt(i).getFeatureAt(j) + 0.5 * sum / vMatrix.getObjectAt(i).getFeatureAt(i));
            }
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
    int m = X.getObjectCount();
    std::vector<double> vMatrixObject;
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
                    vMatrix.updateDataObject(i, k, -1.0);
                else if (i <= neighbourNumber)
                    vMatrix.updateDataObject(i, i, neighbourNumber + i);
                else if (i > neighbourNumber)
                    vMatrix.updateDataObject(i, i, 2 * neighbourNumber - (m - i));
                else
                    vMatrix.updateDataObject(i, i, 2 * neighbourNumber);
            }
        }
    }
    
}

/**
 * Sets neighbour quantity
 */
void DMA::setNeighbours(int neighbours){
    neighbourNumber = neighbours;
}
