#include <cstdlib>
#include <sstream>
#include <iostream>
#include <time.h>
#include "AdditionalMethods.h"
#include "ObjectMatrix.h"
#include "DataObject.h"
#include "alglib/dataanalysis.h"

///////////////////////////////////////////////////////////
//  Projection.cpp
//  Implementation of the Class Projection
//  Created on:      24-Spa-2013 12:20:33
//  Original author: Mindaugas
///////////////////////////////////////////////////////////

/*! \file AdditionalMethods
    \brief A class of static methods for data conversion and static members.
 */

const char* AdditionalMethods::alphanum= "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
std::string AdditionalMethods::tempFileSavePath = "";
std::string AdditionalMethods::tempPath = "";
FILE *AdditionalMethods::distFile = NULL;

AdditionalMethods::AdditionalMethods()
{

}

AdditionalMethods::~AdditionalMethods()
{

}

/**
 * Method generates random file name and adds to the prefix
 */
std::string AdditionalMethods::generateFileName()
{
    time_t t;
    time(&t);
    srand((unsigned int)(t+rand()));

    std::string catString, path;
    path.assign(AdditionalMethods::inputDataFile);

    std::string::size_type tt = path.find_last_of("/");
    path = path.substr(0,tt) + "/";
    AdditionalMethods::tempPath.assign(path);
    catString.assign(AdditionalMethods::tempPath);

    int i;
    int qty = 20;

    for ( i = 0; i < qty; ++i)
        catString += (AdditionalMethods::alphanum[rand() % (strlen(AdditionalMethods::alphanum) - 1)]);
    catString +=".bin";

    return  catString;
}


double** AdditionalMethods::ObjectMatrixToDouble(ObjectMatrix matrix)
{
    int numOfObjects = matrix.getObjectCount();
    int numOfFeatures = matrix.getObjectAt(0).getFeatureCount();
    double **matrixToReturn;
    matrixToReturn = Array2D(numOfObjects, numOfFeatures);

    for (int i = 0; i < numOfObjects; i++)
        for (int j = 0; j < numOfFeatures; j++)
            matrixToReturn[i][j] = matrix.getObjectAt(i).getFeatureAt(j);

    return matrixToReturn;
}

ObjectMatrix AdditionalMethods::DoubleToObjectMatrix(double** matrix, int rows, int cols)
{
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

alglib::real_1d_array AdditionalMethods::DataObjectTo1DArray(DataObject dataObject)
{
    alglib::real_1d_array toReturn;
//    int m = matrix.getObjectCount();
    int n = dataObject.getFeatureCount();
    toReturn.setlength(n);

    // for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
        toReturn(j) = dataObject.getFeatureAt(j);

    return toReturn;
}

ObjectMatrix AdditionalMethods::alglib1DArrayToObjectMatrix(alglib::real_1d_array array, int featureCount)
{
    int m = array.length() / featureCount;
    ObjectMatrix toReturn(m);
    std::vector<double> dataObjectFeatures;
    dataObjectFeatures.reserve(featureCount);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < featureCount; j++)
            dataObjectFeatures.push_back(array(featureCount * i + j));
        toReturn.addObject(DataObject(dataObjectFeatures));
        dataObjectFeatures.clear();
    }
    return toReturn;
}

DataObject AdditionalMethods::alglib1DArrayToDataObject(alglib::real_1d_array array)
{
    int m = array.length();// / featureCount;
    DataObject toReturn;
    std::vector<double> dataObjectFeatures;
    dataObjectFeatures.reserve(m);

    /*   for (int i = 0; i < m; i++)
       {*/
    for (int j = 0; j < m; j++)
        dataObjectFeatures.push_back(array(j));
    /*toReturn.addObject(DataObject(dataObjectFeatures));
    dataObjectFeatures.clear();*/
    toReturn = DataObject(dataObjectFeatures);
    //}
    return toReturn;
}

std::vector<std::string> AdditionalMethods::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> AdditionalMethods::split(const std::string& s, char delim)
{
    std::vector<std::string> elems;
    AdditionalMethods::split(s, delim, elems);
    return elems;
}
