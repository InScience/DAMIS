///////////////////////////////////////////////////////////
//  Projection.cpp
//  Implementation of the Class Projection
//  Created on:      15-Spa-2013 09:54:17
//  Original author: Mindaugas
///////////////////////////////////////////////////////////

/*! \class Projection
    \brief A class of static methods for projecting the initial projection matrix.
 */

#include "DataObject.h"
#include "Statistics.h"
#include "ObjectMatrix.h"
#include "Projection.h"
#include "ProjectionEnum.h"
#include "PCA.h"
#include <cmath>

Projection::Projection()
{

}

Projection::~Projection()
{

}

ObjectMatrix Projection::byRand(ObjectMatrix objectMatrix)
{

    int n = objectMatrix.getObjectCount();
    unsigned int max = objectMatrix.getObjectAt(0).getFeatureCount();
    unsigned int min = 0;
    std::vector<double> feature;

    ObjectMatrix projection(n);

    int x, randMax = RAND_MAX - RAND_MAX % max;
    int p = RAND_MAX+1;
    while(p > randMax)
        p = rand();
    x = min + p % (max - min);

    for (int i = 0; i < n; i++)
    {
        feature.push_back(objectMatrix.getObjectAt(i).getFeatureAt(x));
        projection.addObject(DataObject(feature));
        feature.clear();
    }
    return  projection;
}

ObjectMatrix Projection::byDispersion(ObjectMatrix objectMatrix)
{
    int n = objectMatrix.getObjectCount();
    int m = objectMatrix.getObjectAt(0).getFeatureCount();
    int maxDispersionCol = 0;
    double tmp = 0.0, maxDispersion = 0.0, tmpDiff;
    ObjectMatrix projection(n);
    std::vector<double> dispersion;
    std::vector<double> average;
    std::vector<double> feature;
    dispersion.reserve(m);
    average.reserve(m);

    /*  for (int j = 0; j < m; j++)
          average.push_back(Statistics::getAverage(objectMatrix, j));*/

    average = Statistics::getAverageColumns(objectMatrix);

    for (int j = 0; j < m; j++)
    {
        tmp = 0.0;
        for (int i = 0; i < n; i++)
        {
            tmpDiff = objectMatrix.getObjectAt(i).getFeatureAt(j) - average.at(j);
            tmp += tmpDiff;
        }
        dispersion.push_back(std::sqrt(tmp)); //got rid of the 1/n multiplier
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


ObjectMatrix Projection::byPCA(ObjectMatrix objectMatrix)
{
    int n = objectMatrix.getObjectCount();
    ObjectMatrix projection(n);
    PCA_ pca(objectMatrix, 1);
    projection = pca.getProjection();
    return  projection;
}

ObjectMatrix Projection::projectMatrix(ProjectionEnum projEnum, ObjectMatrix objectMatrix)
{
    ObjectMatrix projection;

    switch (projEnum)
    {
    case 1:
        projection = Projection::byRand(objectMatrix);
        break;
    case 2:
        projection = Projection::byPCA(objectMatrix);
        break;
    case 3:
        projection = Projection::byDispersion(objectMatrix);
        break;
    default:
        projection = Projection::byDispersion(objectMatrix);
        break;
    }

    return  projection;
}

