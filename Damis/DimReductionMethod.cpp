///////////////////////////////////////////////////////////
//  DimReductionMethod.cpp
//  Implementation of the Class DimReductionMethod
//  Created on:      07-Lie-2013 20:07:29
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "DimReductionMethod.h"
#include "PCA.h"
#include "Statistics.h"


DimReductionMethod::DimReductionMethod(){
    d = 2;
}

DimReductionMethod::~DimReductionMethod(){

}

/**
 * Returns d
 */
int DimReductionMethod::getProjectionDimension(){
	return d;
}

/**
 * Initializes Y matrix acording to dimension d and fills it with data.
 */
void DimReductionMethod::initializeProjectionMatrix(){
    int n = X.getObjectCount();
    Y = ObjectMatrix(n);
    std::vector<double> DataObjectItem;
    double r = 0.0;
    for (int j = 0; j < d; j++)
        DataObjectItem.push_back(0.0);
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < d; j++)
        {
            r = Statistics::getRandom(-0.1, 0.1, (i + j * 5));
            DataObjectItem[j] = r;
        }
        Y.addObject(DataObject(DataObjectItem));
    }
}

/**
 * Sets the desired projection dimension
 */
void DimReductionMethod::setProjectionDimension(int dimension){
    d = dimension;
}

ObjectMatrix DimReductionMethod::getProjection()
{
    return Y;
}
