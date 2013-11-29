///////////////////////////////////////////////////////////
//  DMA.cpp
//  Implementation of the Class DMA
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "DMA.h"
#include "ShufleEnum.h"
#include "ShufleObjects.h"
#include <float.h>
#include <fstream>

DMA::DMA(){

}

DMA::~DMA(){

}

/**
 * Constructor for DMA object. Input: epsilon, no. of iterations, dimension, no. of neighbors
 */
DMA::DMA(double eps, int maxIter, int d, int neighbours):MDS(eps, maxIter, d){
    neighbourNumber = neighbours;
    initializeProjectionMatrix();
}

/**
 * Overloaded constructor for DMA object. Input: epsilon, no. of iterations, dimension, no. of neighbors, initial object matrix
 */
DMA::DMA(double eps, int maxIter, int d, int neighbours, ObjectMatrix x):MDS(eps, maxIter, d){
    neighbourNumber = neighbours;
    X = x;
    initializeProjectionMatrix();
}

/**
 * Returns neighbors quantity
 */
int DMA::getNeighbours(){
    return neighbourNumber;
}

/**
 * Pure virtual method that calculates the projection
 */
ObjectMatrix DMA::getProjection(){
    stressErrors.reserve(maxIteration);
    int m = X.getObjectCount();
    int iteration = 0;
    stressErrors.push_back(getStress());
    double Epsilon = DBL_MAX;
    double sum = 0.0;   
    ObjectMatrix Y_new(m);
    ObjectMatrix gutman;      
    Y_new = Y;
    getV();
    
    while (iteration < maxIteration) // && Epsilon > epsilon)
    {
        shuffleX();
        gutman = getGutman();

        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                gutman.updateDataObject(i, j, gutman.getObjectAt(i).getFeatureAt(j) - vMatrix.getObjectAt(i).getFeatureAt(j));

        for (int i = 0; i < m; i++)
        {            
            for (int j = 0; j < d; j++)
            {
                sum = 0.0;
                for (int k = (i - neighbourNumber); k <= (i + neighbourNumber); k++)
                    if (k >= 0 && k < m)
                        sum += gutman.getObjectAt(i).getFeatureAt(k) * Y.getObjectAt(k).getFeatureAt(j);
                Y_new.updateDataObject(i, j, Y.getObjectAt(i).getFeatureAt(j) + 0.5 * sum / vMatrix.getObjectAt(i).getFeatureAt(i));
            }
        }
        Y = Y_new;
        iteration++;        
        stressErrors.push_back(getStress());        
        Epsilon = stressErrors.at(iteration - 1) - stressErrors.at(iteration);
    }
    return  Y;
}

/**
 * Calculates V matrix
 */
void DMA::getV(){   
    int m = X.getObjectCount();
    vMatrix = ObjectMatrix(m); 
    std::vector<double> vMatrixObject;
    vMatrixObject.reserve(m);
            
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
            vMatrixObject.push_back(0.0);
        vMatrix.addObject(DataObject(vMatrixObject));    
        vMatrixObject.clear();
    }
    
    for (int i = 0; i < m; i++)
    {
        for (int k = (i - neighbourNumber); k <= (i + neighbourNumber); k++)
        {
            if (k >= 0 && k < m)
            {
                if (k != i)
                    vMatrix.updateDataObject(i, k, -1.0);
                else if (i <= neighbourNumber)
                    vMatrix.updateDataObject(i, i, neighbourNumber + i);
                else if (i >= (m - neighbourNumber))
                    vMatrix.updateDataObject(i, i, 2 * neighbourNumber - (neighbourNumber + 1 - (m - i)));
                else
                    vMatrix.updateDataObject(i, i, 2 * neighbourNumber);
            }
        }
    }
}

/**
 * Sets neighbors quantity
 */
void DMA::setNeighbours(int neighbours){
    neighbourNumber = neighbours;
}

void DMA::shuffleX()
{
    int m = X.getObjectCount();
    int j = 0;
    ObjectMatrix Xshuffled(m);
    ObjectMatrix Yshuffled(m);
    std::vector<int> shufledIndexes;
    shufledIndexes.reserve(m);
    shufledIndexes = ShufleObjects::shufleObjectMatrix(RANDOM, Y);
    for (int i = 0; i < m; i++)
    {
        j = shufledIndexes.at(i);
        Xshuffled.addObject(X.getObjectAt(j));
    }
    X = Xshuffled;
    
    for (int i = 0; i < m; i++)
    {
        j = shufledIndexes.at(i);
        Yshuffled.addObject(Y.getObjectAt(j));
    }
    Y = Yshuffled;
}
