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
#include "DistanceMetrics.h"
#include "DistanceMetricsEnum.h"
#include <cmath>

/*! \class DMA
    \brief A class of methods and attributes for DMA algorithm.
 */

DMA::DMA(){

}

DMA::~DMA(){

}

DMA::DMA(double eps, int maxIter, int d, int neighbours):MDS(eps, maxIter, d){
    neighbourNumber = neighbours;
    initializeProjectionMatrix();
}

DMA::DMA(double eps, int maxIter, int d, int neighbours, ObjectMatrix x):MDS(eps, maxIter, d){
    neighbourNumber = neighbours;
    X = x;
    initializeProjectionMatrix();
}

int DMA::getNeighbours(){
    return neighbourNumber;
}

ObjectMatrix DMA::getProjection(){
    stressErrors.reserve(maxIteration);
    m = X.getObjectCount();
    int iteration = 0;
    stressErrors.push_back(getStress());
    double Epsilon = DBL_MAX;
    double sum = 0.0;
    ObjectMatrix Y_new(m);
    ObjectMatrix gutman;
    Y_new = Y;

    while (iteration < maxIteration && Epsilon > epsilon)
    {
        shuffle();
        gutman = getGutman(neighbourNumber);

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < d; j++)
            {
                sum = 0.0;
                for (int k = (i - neighbourNumber); k <= (i + neighbourNumber); k++)
                    if (k >= 0 && k < m)
                        if (k !=i)
                            sum += gutman.getObjectAt(i).getFeatureAt(k) * Y.getObjectAt(k).getFeatureAt(j); // +1 pridedamas formuojant gutmano matrica
                        else
                            sum += (gutman.getObjectAt(i).getFeatureAt(k) - getV(i)) * Y.getObjectAt(k).getFeatureAt(j);
                Y_new.updateDataObject(i, j, Y.getObjectAt(i).getFeatureAt(j) + 0.5 * sum / getV(i));
            }
        }
        Y = Y_new;
        iteration++;
        stressErrors.push_back(getStress());
        Epsilon = stressErrors.at(iteration - 1) - stressErrors.at(iteration);
    }
    return  Y;
}

int DMA::getV(int i)
{
    int k1 = i - neighbourNumber;
    int k2 = i + neighbourNumber;
    if (k1 < 0)
        k1 = 0;
    if (k2 >= m)
        k2 = m - 1;
    return k2 - k1;
}

void DMA::setNeighbours(int neighbours){
    neighbourNumber = neighbours;
}

void DMA::shuffle()
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

double DMA::getStress(){
    /*double sum1 = 0.0, sum2 = 0.0, stress = 0.0;
    int m = X.getObjectCount();
    double distX = 0.0;
    double distY = 0.0;

    for (int i = 0; i < m - 1; i++)
    {
        for (int j = i + 1; j < m; j++)
        {
            distX = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(Y.getObjectAt(i), Y.getObjectAt(j), EUCLIDEAN);
            sum1 += std::pow(distX - distY, 2);
            sum2 += std::pow(distX, 2);
        }
    }
    stress = std::sqrt(sum1 / sum2);
    return stress;*/
    return MDS::getStress();
}
