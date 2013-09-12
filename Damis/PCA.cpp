///////////////////////////////////////////////////////////
//  PCA.cpp
//  Implementation of the Class PCA
//  Created on:      07-Lie-2013 20:07:31
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "PCA.h"


PCA::PCA(){

}



PCA::~PCA(){

}





/**
 * Constructor that sets desired projection d
 */
PCA::PCA(int d){

}


/**
 * Overloaded constructor when the part of retaining dispersion is passed to PCA
 * object
 */
PCA::PCA(float disp){

}


/**
 * Overloaded constructor that accept object matrix that must be projected to d
 * dimension
 */
PCA::PCA(ObjectMatrix objMatrix, int d){

    n = objMatrix.DataObjects.size();
    m = objMatrix.DataObjects[0].getFeatureCount();
    double tmp[n * m];
    std::vector<double> tmp_values;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            tmp_values = objMatrix.DataObjects[i].getItems();
            tmp[m * i + j] = tmp_values[j];
        }
    }
    
    arr.setcontent(n, m, tmp);
}


ObjectMatrix PCA::getProjection(){

	return  NULL;
}


/**
 * Converts data object to datatype required by external method
 */
void PCA::toDataType(){

}


/**
 * Converts to ObjectMatrix result that is provided by external library.
 */
void PCA::fromDataType(){

}