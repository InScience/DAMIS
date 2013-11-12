///////////////////////////////////////////////////////////
//  MDS.cpp
//  Implementation of the Class MDS
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "MDS.h"
#include "arff.h"
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

/**
 * Constructor for MDS type object
 */
MDS::MDS(double eps, int maxIter, int dimension){
    epsilon = eps;
    maxIteration = maxIter;
    d = dimension;
}

/**
 * Gets eps value
 */
double MDS::getEpsilon(){
    return epsilon;
}

double MDS::getFinalEpsilon(){
    return finalEpsilon;
}

ObjectMatrix MDS::getGutman(){
    int n = X.getObjectCount();
    ObjectMatrix GutmanMatrix(n);
    double distXij;
    double distYij;
    
    std::vector<double> GutmanMatrixRow;
    GutmanMatrixRow.reserve(n);
    for (int i = 0; i < n; i++)
        GutmanMatrixRow.push_back(0);
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            distYij = DistanceMetrics::getDistance(Y.getObjectAt(i), Y.getObjectAt(j), Euclidean);
            if (i != j &&  distYij != 0)
            {
                distXij = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), Euclidean);
                GutmanMatrixRow.at(j) = -1 * distXij/distYij;
            }
            else if (i != j && distYij == 0)
                GutmanMatrixRow.at(j) = 0;
        }
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                GutmanMatrixRow.at(i) = 0;
                for (int k = 0; k < n; k++)
                    if (i != k)
                        GutmanMatrixRow.at(i) += GutmanMatrixRow.at(k);
                GutmanMatrixRow.at(i) = -1 * GutmanMatrixRow.at(i);
                break;
            }
                
        }
        GutmanMatrix.addObject(DataObject(GutmanMatrixRow));
    }
    
    return  GutmanMatrix;
}

ObjectMatrix MDS::getGutman(ObjectMatrix Y_new){
    int n = X.getObjectCount();
    ObjectMatrix GutmanMatrix(n);
    double distXij;
    double distYij;
    
    std::vector<double> GutmanMatrixRow;
    GutmanMatrixRow.reserve(n);
    for (int i = 0; i < n; i++)
        GutmanMatrixRow.push_back(0);
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            distYij = DistanceMetrics::getDistance(Y_new.getObjectAt(i), Y_new.getObjectAt(j), Euclidean);
            if (i != j &&  distYij != 0)
            {
                distXij = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), Euclidean);
                GutmanMatrixRow.at(j) = -1 * distXij/distYij;
            }
            else if (i != j && distYij == 0)
                GutmanMatrixRow.at(j) = 0;
        }
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                GutmanMatrixRow.at(i) = 0;
                for (int k = 0; k < n; k++)
                    if (i != k)
                        GutmanMatrixRow.at(i) += GutmanMatrixRow.at(k);
                GutmanMatrixRow.at(i) = -1 * GutmanMatrixRow.at(i);
                break;
            }
                
        }
        GutmanMatrix.addObject(DataObject(GutmanMatrixRow));
    }
    
    return  GutmanMatrix;
}

/**
 * Gets max iteration
 */
int MDS::getMaxIteration(){
    return maxIteration;
}

int MDS::getIteration(){
    return iteration;
}

/**
 * Computes MDS stress function
 */
double MDS::getStress(){
    double stress = 0.0;
    int n = X.getObjectCount();
    int m = Y.getObjectCount();
    double distX = 0.0;
    double distY = 0.0;
    
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            distX = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), Euclidean);
            distY = DistanceMetrics::getDistance(Y.getObjectAt(i), Y.getObjectAt(j), Euclidean);
            stress += getWeight(i, j) * std::pow(distX - distY, 2);
        }
    }
    
    return stress;
}

double MDS::getWeight(int i, int j)
{
    double weight = 0.0;
    int n = X.getObjectCount();
    
    for (int j = i + 1; j < n; j++)
        weight += std::pow(DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), Euclidean), 2);
    return 1 / weight;
}

/**
 * Sets epsilon
 */
void MDS::setEpsilon(double eps){
    epsilon = eps;
}


void MDS::setMaxIteration(int maxIter){
    maxIteration = maxIter;
}
