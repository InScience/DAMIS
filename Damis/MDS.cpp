///////////////////////////////////////////////////////////
//  MDS.cpp
//  Implementation of the Class MDS
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

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

/**
 * Constructor for MDS type object
 */
MDS::MDS(double eps, int maxIter, int dimension){
    epsilon = eps;
    maxIteration = maxIter;
    d = dimension;
    int m = X.getObjectCount();
    gutman = ObjectMatrix(m);
    std::vector<double> gutmanRow;
    gutmanRow.reserve(m);
    
    for (int i = 0; i < m; i++)
        gutmanRow.push_back(0.0);
    
    for (int i = 0; i < m; i++)       
        gutman.addObject(DataObject(gutmanRow));
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
    int m = X.getObjectCount();
    double distXij;
    double distYij;
    double sum = 0.0;
       
    for (int i = 0; i < m; i++)
    {
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
        }
        
        sum = 0.0;
        for (int j = 0; j < i; j++)
            sum += gutman.getObjectAt(i).getFeatureAt(j);
            
        for (int j = i + 1; j < m; j++)
            sum += gutman.getObjectAt(i).getFeatureAt(j);
        
        gutman.updateDataObject(i, i, -1 * sum);
    }
    return  gutman;
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
    int m = X.getObjectCount();
    double distX = 0.0;
    double distY = 0.0;
    
    for (int i = 0; i < m - 1; i++)
    {
        for (int j = i + 1; j < m; j++)
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
    //double weight = 0.0;
    //int m = X.getObjectCount();
    
    //for (int k = i; k < j; k++)
    //for (int k = j; k < m; k++)
    //    weight += std::pow(DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(k), EUCLIDEAN), 2);
    //return 1 / weight;
    return 1.0;
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
