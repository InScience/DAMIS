///////////////////////////////////////////////////////////
//  MDS.cpp
//  Implementation of the Class MDS
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

/*! \class MDS
    \brief A class of methods and attributes for MDS algorithms.
 */

#include "MDS.h"
#include "ARFF.h"
#include "string"
#include "DistanceMetrics.h"
#include <cstdlib>
#include "DataObject.h"
#include "PCA.h"
#include <vector>
#include <cmath>

MDS::MDS(){

}

MDS::~MDS(){

}

MDS::MDS(double eps, int maxIter, int dimension){
    epsilon = eps;
    maxIteration = maxIter;
    d = dimension;
    int m = X.getObjectCount();
    gutman = ObjectMatrix(m);
    std::vector<double> gutmanRow;
    gutmanRow.reserve(m);

   /* for (int i = 0; i < m; i++)
        gutmanRow.push_back(0.0);*/

    for (int i = 0; i < m; i++)
        gutman.addObject(DataObject(gutmanRow));
}

MDS::MDS(double eps, int maxIter, int dimension, ObjectMatrix initialMatrix){
    epsilon = eps;
    maxIteration = maxIter;
    d = dimension;
    X = initialMatrix;
}

double MDS::getEpsilon(){
    return epsilon;
}

ObjectMatrix MDS::getGutman(){
    int m = X.getObjectCount();
    double distXij;
    double distYij;
    double sum = 0.0;

    for (int i = 0; i < m; i++)
    {
        sum = 0.0;
        for (int j = 0; j < i; j++)
        {
            distYij = DistanceMetrics::getDistance(Y.getObjectAt(i), Y.getObjectAt(j), EUCLIDEAN);
            if (distYij > 0)
            {
                distXij = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN);
                gutman.updateDataObject(i, j,  -1 * distXij/distYij);
            }
            else
                gutman.updateDataObject(i, j, 0.0);
            sum += gutman.getObjectAt(i).getFeatureAt(j);
        }

        for (int j = i + 1; j < m; j++)
        {
            distYij = DistanceMetrics::getDistance(Y.getObjectAt(i), Y.getObjectAt(j), EUCLIDEAN);
            if (distYij > 0)
            {
                distXij = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN);
                gutman.updateDataObject(i, j,  -1 * distXij/distYij);
            }
            else
                gutman.updateDataObject(i, j, 0.0);
            sum += gutman.getObjectAt(i).getFeatureAt(j);
        }
        gutman.updateDataObject(i, i, -1 * sum);
    }
    return  gutman;
}

ObjectMatrix MDS::getGutman(int neighbour){
    int m = X.getObjectCount();
    double distXij;
    double distYij;
    double sum = 0.0;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
            gutman.updateDataObject(i, j, 0.0);

        for (int j = (i - neighbour); j <= (i + neighbour); j++)
        {
            if (j >= 0 && j != i && j < m)
            {
                distYij = DistanceMetrics::getDistance(Y.getObjectAt(i), Y.getObjectAt(j), EUCLIDEAN);
                if (distYij > 0)
                {
                    distXij = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN);
                    gutman.updateDataObject(i, j, -1.0 * distXij/distYij + 1.0);
                }
                else
                    gutman.updateDataObject(i, j, 1.0);
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        sum = 0.0;
        for (int j = 0; j < i; j++)
            sum += gutman.getObjectAt(i).getFeatureAt(j);

        for (int j = i + 1; j < m; j++)
            sum += gutman.getObjectAt(i).getFeatureAt(j);

        gutman.updateDataObject(i, i, -1 * sum);
    }

    return  gutman;
}

ObjectMatrix MDS::getGutman(ObjectMatrix Ynew){
    int m = X.getObjectCount();
    double distXij;
    double distYij;
    double sum = 0.0;

    for (int i = 0; i < m; i++)
    {
        sum = 0.0;
        for (int j = 0; j < i; j++)
        {
            distYij = DistanceMetrics::getDistance(Ynew.getObjectAt(i), Ynew.getObjectAt(j), EUCLIDEAN);
            if (distYij > 0)
            {
                distXij = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN);
                gutman.updateDataObject(i, j,  -1 * distXij/distYij);
            }
            else
                gutman.updateDataObject(i, j, 0.0);
            sum += gutman.getObjectAt(i).getFeatureAt(j);
        }

        for (int j = i + 1; j < m; j++)
        {
            distYij = DistanceMetrics::getDistance(Ynew.getObjectAt(i), Ynew.getObjectAt(j), EUCLIDEAN);
            if (distYij > 0)
            {
                distXij = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN);
                gutman.updateDataObject(i, j,  -1 * distXij/distYij);
            }
            else
                gutman.updateDataObject(i, j, 0.0);
            sum += gutman.getObjectAt(i).getFeatureAt(j);
        }
        gutman.updateDataObject(i, i, -1 * sum);
    }
    return  gutman;
}

int MDS::getMaxIteration(){
    return maxIteration;
}

double MDS::getStress(){
   /* double stress = 0.0;
    int m = X.getObjectCount();
    double distX = 0.0;
    double distY = 0.0;

    for (int i = 0; i < m - 1; i++)
    {
        for (int j = i + 1; j < m; j++)
        {
            distX = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(Y.getObjectAt(i), Y.getObjectAt(j), EUCLIDEAN);
            stress += std::pow(distX - distY, 2);
        }
    }

    return stress * MDS::getStressWeight();*/
    return DimReductionMethod::getStress();
}

/*double MDS::getWeight(int i, int j)
{
    double weight = 0.0;
    int m = X.getObjectCount();

    for (int k = i; k < j; k++)
        for (int k = j; k < m; k++)
            weight += std::pow(DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(k), EUCLIDEAN),2);
    return 1 / weight;
    //return 1.0;
}*/

void MDS::setEpsilon(double eps){
    epsilon = eps;
}

void MDS::setMaxIteration(int maxIter){
    maxIteration = maxIter;
}

double MDS::getStressWeight(int weightType)
{
    double weight = 0.0;
    int m = X.getObjectCount();

    if (weightType == 1)
        {
        for (int i = 0; i < m - 1; i++)
            for (int j = i + 1; j < m; j++)
                weight += std::pow(DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN),2);
        }
    if (weight)
        return 1./weight;
    else
         return 0;
}

std::vector<double> MDS::getStressErrors()
{
    return stressErrors;
}
