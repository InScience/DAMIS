///////////////////////////////////////////////////////////
//  Projection.cpp
//  Implementation of the Class Projection
//  Created on:      15-Spa-2013 09:54:17
//  Original author: Mindaugas
///////////////////////////////////////////////////////////

#include "DataObject.h"
#include "Statistics.h"
#include "ObjectMatrix.h"
#include "Projection.h"
#include "ProjectionEnum.h"
#include "PCA.h"
#include <cmath>

Projection::Projection(){

}

Projection::~Projection(){

}

ObjectMatrix Projection::byDispersion(ObjectMatrix objectMatrix){
    int n = objectMatrix.getObjectCount();
    int m = objectMatrix.getObjectAt(0).getFeatureCount();
    int maxDispersionCol = 0;
    double tmp = 0.0, maxDispersion = 0.0;
    ObjectMatrix projection(n);
    std::vector<double> dispersion;
    std::vector<double> average;
    std::vector<double> feature;
    dispersion.reserve(m);
    average.reserve(m);
    
    for (int j = 0; j < m; j++)
        average.push_back(Statistics::getAverage(objectMatrix, j));
    
    for (int j = 0; j < m; j++)
    {
        tmp = 0.0;
        for (int i = 0; i < n; i++)
            tmp += std::pow((objectMatrix.getObjectAt(i).getFeatureAt(j) - average.at(j)), 2);
        dispersion.push_back(std::sqrt((1.0 / n) * tmp));
    }
        
    maxDispersion = dispersion.at(0);
    for (int j = 1; j < m; j++)
        if (dispersion.at(j) > maxDispersion)
        {
            maxDispersion = dispersion.at(j);
            maxDispersionCol = j;
        }
    
    for (int i = 0; i < n; i++)
    {
        feature.push_back(objectMatrix.getObjectAt(i).getFeatureAt(maxDispersionCol));
        projection.addObject(DataObject(feature));
        feature.clear();
    }
    
    return  projection;
}


ObjectMatrix Projection::byPCA(ObjectMatrix objectMatrix){
    int n = objectMatrix.getObjectCount();
    ObjectMatrix projection(n);

    PCA::PCA pca(objectMatrix, 1);
    projection = pca.getProjection();    
    return  projection;
}

ObjectMatrix Projection::projectMatrix(ProjectionEnum projEnum, ObjectMatrix objectMatrix){
    ObjectMatrix projection;
    
    switch (projEnum)
    {
        case 1: projection = Projection::byDispersion(objectMatrix);
                break;
        case 2: projection = Projection::byPCA(objectMatrix);
                break;
        default: projection = Projection::byDispersion(objectMatrix);
                break;
    }
         
    return  projection;
}

