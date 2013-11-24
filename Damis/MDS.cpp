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

MDS::MDS(double eps, int maxIter, int dimension, ObjectMatrix x){
    epsilon = eps;
    maxIteration = maxIter;
    d = dimension;
    X = x;
}

/**
 * Gets eps value
 */
double MDS::getEpsilon(){
    return epsilon;
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
            distYij = DistanceMetrics::getDistance(Y.getObjectAt(i), Y.getObjectAt(j), EUCLIDEAN);
            if (i != j &&  distYij != 0)
            {
                distXij = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN);
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
            distYij = DistanceMetrics::getDistance(Y_new.getObjectAt(i), Y_new.getObjectAt(j), EUCLIDEAN);
            if (i != j &&  distYij != 0)
            {
                distXij = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN);
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

/**
 * Computes MDS stress function
 */
double MDS::getStress(){
    double stress = 0.0;
    int n = X.getObjectCount();
    double distX = 0.0;
    double distY = 0.0;
    
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            distX = DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(Y.getObjectAt(i), Y.getObjectAt(j), EUCLIDEAN);
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
        weight += std::pow(DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN), 2);
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

std::vector<double> MDS::getStressErrors()
{
    return stressErrors;
}
