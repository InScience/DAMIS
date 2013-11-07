
#include <cstdlib>
#include "AdditionalMethods.h"
#include "ObjectMatrix.h"

///////////////////////////////////////////////////////////
//  Projection.cpp
//  Implementation of the Class Projection
//  Created on:      24-Spa-2013 12:20:33
//  Original author: Mindaugas
///////////////////////////////////////////////////////////

AdditionalMethods::AdditionalMethods(){
    
}

AdditionalMethods::~AdditionalMethods(){
    
}

double** AdditionalMethods::ObjectMatrixToDouble(ObjectMatrix matrix){
    int numOfObjects = matrix.getObjectCount();
    int numOfFeatures = matrix.getObjectAt(0).getFeatureCount();
    double **matrixToReturn;
    matrixToReturn = Array2D(numOfObjects, numOfFeatures);
    
    
    for (int i = 0; i < numOfObjects; i++)
        for (int j = 0; j < numOfFeatures; j++)
            matrixToReturn[i][j] = matrix.getObjectAt(i).getFeatureAt(j);
        
    return matrixToReturn;
}

ObjectMatrix AdditionalMethods::DoubleToObjectMatrix(double** matrix, int rows, int cols){
    std::vector<double> v;
    v.reserve(cols);
    ObjectMatrix toReturn(rows);
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            v.push_back(matrix[i][j]);
        toReturn.addObject(DataObject(v));
        v.clear();
    }
    
    return toReturn;
}

double** AdditionalMethods::Array2D(int rows, int cols)      
{
    double *data = (double *)malloc(rows*cols*sizeof(double));
    double **array= (double **)malloc(rows*sizeof(double*));
    for (int i=0; i<rows; i++)
        array[i] = &(data[cols*i]);
    return array;
}

alglib::real_1d_array AdditionalMethods::ObjectMatrixTo1DArray(ObjectMatrix matrix)
{
    alglib::real_1d_array toReturn;
    int m = matrix.getObjectCount();
    int n = matrix.getObjectAt(0).getFeatureCount();
    toReturn.setlength(m * n);
    
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            toReturn(n * i + j) = matrix.getObjectAt(i).getFeatureAt(j);
    
    return toReturn;    
}
