///////////////////////////////////////////////////////////
//  DimReductionMethod.cpp
//  Implementation of the Class DimReductionMethod
//  Created on:      07-Lie-2013 20:07:29
//  Original author: Povilas
///////////////////////////////////////////////////////////

/*! \class DimReductionMethod
    \brief A class of methods and attributes for initialization of projection matrix.
 */

#include "DimReductionMethod.h"
#include "DistanceMetrics.h"
#include "PCA.h"
#include "Statistics.h"
#include <cmath>


DimReductionMethod::DimReductionMethod(){
    d = 2;
}

DimReductionMethod::~DimReductionMethod(){

}

int DimReductionMethod::getProjectionDimension(){
	return d;
}

void DimReductionMethod::initializeProjectionMatrix(){
    int n = X.getObjectCount();
    Y = ObjectMatrix(n);
    std::vector<double> DataObjectItem;
   // double r = 0.0;
   // for (int j = 0; j < d; j++)
        DataObjectItem.reserve(0);//push_back(0.0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < d; j++)
       // {
          //  r = ;
            DataObjectItem.push_back(Statistics::getRandom(-0.1, 0.1, (i + j * 5)));
     //   }
        Y.addObject(DataObject(DataObjectItem));
        DataObjectItem.clear();
    }
}

void DimReductionMethod::setProjectionDimension(int dimension){
    d = dimension;
}

/*double DimReductionMethod::getStress()
{
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
            stress += std::pow(distX - distY, 2);
        }
    }

    return stress;
}*/
double DimReductionMethod::getStressWeight(int weightType)
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

ObjectMatrix DimReductionMethod::getProjection(){
    return Y;
}
