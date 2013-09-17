///////////////////////////////////////////////////////////
//  PCA.cpp
//  Implementation of the Class PCA
//  Created on:      07-Lie-2013 20:07:31
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "PCA.h"
#include "Statistics.h"
#include "alglib/dataanalysis.h"

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
PCA::PCA(ObjectMatrix objMatrix, int dim){
 
    setProjectionDimension(dim);
    initialMatrix = objMatrix;
    n = initialMatrix.DataObjects.size();
    m = initialMatrix.DataObjects.at(0).getFeatureCount();
    PCA::toDataType();
    PCA::getProjection();
}


ObjectMatrix PCA::getProjection(){

    alglib::ae_int_t info;
    alglib::real_1d_array eigValues;
    alglib::real_2d_array eigVectors;
    pcabuildbasis(arr, n, m, info, eigValues, eigVectors);
    initializeProjectionMatrix(m);
    std::vector<double> tmp(d);

    if (info == 1)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < d; j++)
            {
                tmp[j] = 0.0;
                for (int k = 0; k < m; k++)
                    tmp[j] += arr[i][k] * eigVectors[k][j];
            }
            DataObject dd(tmp);
            Y.addObject(dd);
        }
        
    }
    return Y;
}

ObjectMatrix PCA::getY(){
    return Y;
}

/**
 * Converts data object to datatype required by external method
 */
void PCA::toDataType(){
 
    double tmp[n * m];
    std::vector<double> tmp_values;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            tmp_values = initialMatrix.DataObjects[i].getItems();
            tmp[m * i + j] = tmp_values[j];
        }  
    arr.setcontent(n, m, tmp);
}


/**
 * Converts to ObjectMatrix result that is provided by external library.
 */
void PCA::fromDataType(){
    

}