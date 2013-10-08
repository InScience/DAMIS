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
PCA::PCA(int dim){
    setProjectionDimension(dim);
    PCA::toDataType();
    Y = PCA::getProjection();
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
    X = objMatrix;
    PCA::toDataType();
    PCA::getProjection();
}

ObjectMatrix PCA::getProjection(){
    int m = X.getObjectCount();
    int n = X.getObjectAt(0).getItems().size();
    double X_vid[n];
    for (int i = 0; i < n; i++)
        X_vid[i] = Statistics::getAverage(X, i);
    alglib::ae_int_t info;
    alglib::real_1d_array eigValues;
    alglib::real_2d_array eigVectors;
    pcabuildbasis(alglibX, m, n, info, eigValues, eigVectors);
    initializeProjectionMatrix(m);
    std::vector<double> tmp(d);

    if (info == 1)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < d; j++)
            {
                tmp[j] = 0.0;
                for (int k = 0; k < n; k++)
                    tmp[j] += (alglibX(i,k) - X_vid[k]) * eigVectors[k][j];
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
    int m = X.getObjectCount();
    int n = X.getObjectAt(0).getItems().size();
    alglibX.setlength(m, n);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            alglibX(i,j) = X.getObjectAt(i).getItems().at(j);
}


/**
 * Converts to ObjectMatrix result that is provided by external library.
 */
void PCA::fromDataType(){
    

}
