///////////////////////////////////////////////////////////
//  ClusterizationMethods.cpp
//  Implementation of the Class ClusterizationMethod
//  Created on:      27-Kov-2014 12:52:15
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "ClusterizationMethods.h"
#include "AdditionalMethods.h"
#include "Statistics.h"
#include <vector>

ClusterizationMethods::ClusterizationMethods()
{
        testObjQtty = 0;
        learnObjQtty = 0;
        uknownClassObjQtty = 0;    
initializeXMatrix();
    noOfClusters = X.getClassCount();
    objectIndex.reserve(0);
   /* for (int i = 0; i < X.getObjectCount(); i++)
        objectIndex.push_back(i);*/
}

ClusterizationMethods::ClusterizationMethods(int clNo)
{
        testObjQtty = 0;
        learnObjQtty = 0;
        uknownClassObjQtty = 0;
    noOfClusters = clNo;
    initializeXMatrix();
}
ClusterizationMethods::~ClusterizationMethods()
{

}
//overloaded constructor that accepts no of clusters and no of features
/*ClusterizationMethods::ClusterizationMethods(int noOfClusters, int noOfFeatures)
{
        testObjQtty = 0;
        learnObjQtty = 0;
        uknownClassObjQtty = 0;
    this->noOfClusters = noOfClusters;
    this->noOfFeatures = noOfFeatures;
   // this->initializeXMatrix();
}*/

//initializes X matrix
void ClusterizationMethods::initializeXMatrix()
{
    X = ObjectMatrix(AdditionalMethods::inputDataFile);
    X.loadDataMatrix();
}

//returns number of clusters
int ClusterizationMethods::getNoOfClusters()
{
    //int m = noOfClusters;
    return noOfClusters;
}
/**
 * Returns number of clusters (Y matrix rows)
 */
int ClusterizationMethods::getNoOfReturnRows()
{
    return noOfRows;
}
/**
 * Returns number of Y matrix row features
 */
int ClusterizationMethods::getNoOfReturnRowFeatures()
{
    return noOfFeatures;
}

void ClusterizationMethods::initializeYMatrix()
{
    int r = getNoOfReturnRows(), c = getNoOfReturnRowFeatures();
    Y = ObjectMatrix(r);
    std::vector<double> dataObjectItem;
    dataObjectItem.reserve(0);
    //int r = getNoOfReturnRows(), c = getNoOfReturnRowFeatures();

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            dataObjectItem.push_back(Statistics::getRandom(-5, 5));

        if (X.getClassCount() > 0)
            Y.addObject(DataObject(dataObjectItem, X.getObjectAt(i).getClassLabel()));
        else
            Y.addObject(DataObject(dataObjectItem));

        //Y.addObject(DataObject(dataObjectItem));
        dataObjectItem.clear();
    }
}


void ClusterizationMethods::initializeYMatrix(int rows, int cols)
{
    setYMatrixDimensions(rows, cols);
    initializeYMatrix();
}
/**
 * Sets the number of found classes (used by kmeans ger_k)
 */
void ClusterizationMethods::setNoOfReturnRows(int r)
{
    noOfRows = r;
}

void ClusterizationMethods::setNoOfReturnRowFeatures(int f)
{
    noOfFeatures = f;
}

void ClusterizationMethods::setYMatrixDimensions(int rows, int cols)
{
    ClusterizationMethods::setNoOfReturnRows(rows);
    ClusterizationMethods::setNoOfReturnRowFeatures(cols);
}

void ClusterizationMethods::initializeData(double dL, double dT)
{
    int objCount = X.getObjectCount();
    int n = X.getObjectAt(0).getFeatureCount();
    int i, j;
    //count how many we have unknown classes
    for (i = 0; i < objCount; i++ )
        if (X.getObjectAt(i).getClassLabel() == -1)
        uknownClassObjQtty++;

    int available = objCount -  uknownClassObjQtty; //set the number of available objects for learning and testing

    learnObjQtty = ceil(available * (dL / 100.));
    testObjQtty = ceil(available * (dT / 100.));

    while (learnObjQtty + testObjQtty > available)
        if (testObjQtty >= 2)
            testObjQtty--;
        else
            learnObjQtty--;

    //set dimmensions of the array n+1 = last element points to class
    this->learnSet.setlength(learnObjQtty, n + 1);
    this->testSet.setlength(testObjQtty, n + 1);

    DataObject tmp;
    int tmpL = 0, tmpT = 0;

    for (i = 0; i < objCount; i++)
    {
        tmp = X.getObjectAt(i);
        if ( tmpL < learnObjQtty && tmp.getClassLabel() != -1)
        {
            for (j = 0; j < n; j++)
                learnSet(tmpL,j) = tmp.getFeatureAt(j);
            learnSet(tmpL,j) = tmp.getClassLabel();
            tmpL++;
        }
        else if ( tmpT < testObjQtty && tmp.getClassLabel() != -1)
        {
            for (j = 0; j < n; j++)
                testSet(tmpT,j) = tmp.getFeatureAt(j);
            testSet(tmpT,j) = tmp.getClassLabel();
            tmpT++;
        }
    }
}

void ClusterizationMethods::initializeData()
{
    int objCount = X.getObjectCount();
    int n = X.getObjectAt(0).getFeatureCount();
    int i, j;
    //count how many we have unknown classes

// TODO (Povilas#1#): move to Object matrix

    for (i = 0; i < objCount; i++ )
        if (X.getObjectAt(i).getClassLabel() == -1)
        uknownClassObjQtty++;

    learnObjQtty = objCount - uknownClassObjQtty; //set the number of available objects for learning and testing

    //set dimmensions of the array n+1 = last element points to class
    this->learnSet.setlength(learnObjQtty, n + 1);

    DataObject tmp;
    int tmpL = 0;

    for (i = 0; i < objCount; i++)
    {
        tmp = X.getObjectAt(i);
        if ( tmpL < learnObjQtty && tmp.getClassLabel() != -1)
        {
            for (j = 0; j < n; j++)
                learnSet(tmpL,j) = tmp.getFeatureAt(j);
            learnSet(tmpL,j) = tmp.getClassLabel();
            tmpL++;
        }
    }
}

