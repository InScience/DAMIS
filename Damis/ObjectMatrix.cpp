///////////////////////////////////////////////////////////
//  ObjectMatrix.cpp
//  Implementation of the Class ObjectMatrix
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "ObjectMatrix.h"
#include <vector>
#include "arff.h"
#include "DataObject.h"

ObjectMatrix::ObjectMatrix(){
    DataObjects.reserve(1);    
}

ObjectMatrix::~ObjectMatrix(){
    //DataObjects.clear();
}

/**
 * Constructor that reads object matrix from arff file
 */
ObjectMatrix::ObjectMatrix(std::string file){
    fileName = file;
    objectCount = 0;
}

/**
 * Constructor that creates ObjectMAtrix for n objects
 */
ObjectMatrix::ObjectMatrix(int count){
    DataObjects.reserve(count);
    objectCount = 0;
}

/**
 * Constructor that creates ObjectMAtrix for n objects, and m features
 */
ObjectMatrix::ObjectMatrix(int n, int m){
    DataObjects.reserve(n);
    for (int i = 0; i < n; i++)
        DataObjects[i].setNumOfFeatures(m);
    objectCount = 0;
}

/**
 * Constructor that creates m by n matrix that holds k features i.e. cube. Needed
 * by SOM algorithm.
 */
ObjectMatrix::ObjectMatrix(int m, int n, int k){
    std::vector<double> initialFeatures;
    initialFeatures.resize(k, 1.0);
    DataObject initial(initialFeatures);
    DataObjects2D.resize(m, std::vector<DataObject>( n, initial) );
    objectCount = 0;
}

/**
 * Adds data object to ObjectMatrix
 */
void ObjectMatrix::addObject(DataObject object){
    DataObjects.push_back(object);
    objectCount = DataObjects.size();
}

void ObjectMatrix::addObjectTo(int index, DataObject object){
    DataObjects2D[index].push_back(object);
    objectCount++;
}

void ObjectMatrix::updateDataObject(int objectIndex, int featureIndex, double newValue)
{
    this->DataObjects.at(objectIndex).updateFeature(featureIndex, newValue);
}

void ObjectMatrix::updateDataObject(int rowIndex, int colIndex, int featureIndex, double newValue)
{
    this->DataObjects2D[rowIndex].at(colIndex).updateFeature(featureIndex, newValue);
}

/**
 * Gets object at position
 */
DataObject ObjectMatrix::getObjectAt(int index){
    return  DataObjects.at(index);
}

DataObject ObjectMatrix::getObjectAt(int row_index, int col_index){
    return  DataObjects2D[row_index].at(col_index);
}

/**
 * Gets object count
 */
int ObjectMatrix::getObjectCount(){
    return objectCount;
}

std::vector<std::string> ObjectMatrix::getFeaturesTitle(){
    return featureTitles;
}

/**
 * Loads (deserializes) object matrix (reads arff file into an OdjectMatrix object)
 */
void ObjectMatrix::loadDataMatrix(){
    const char* path = fileName.c_str();
    ARFF file(path);
    if (file.getFileReadStatus() == 1)   // successful read
    {
        std::vector< std::vector<double> > data = file.GetData();  
        featureTitles = file.GetAttributes();
        std::vector< std::vector<double> >::iterator dataObjectIterator;
        std::vector<double>::iterator featureIterator;
        std::vector<double> dataObjectItems;

        for(dataObjectIterator = data.begin();dataObjectIterator!=data.end();++dataObjectIterator)
        {
            for(featureIterator = (*dataObjectIterator).begin();featureIterator!=(*dataObjectIterator).end();++featureIterator)
                dataObjectItems.push_back(*featureIterator);

            DataObject tmp(dataObjectItems);
            DataObjects.push_back(tmp);
            dataObjectItems.clear();
        }  
        objectCount = DataObjects.size();        
    }
    else
        objectCount = 0;
}


void ObjectMatrix::saveDataMatrix(const char* path){
    ARFF file;
    file.WriteData(path, this->DataObjects);
}

void ObjectMatrix::clearDataObjects()
{
    DataObjects.clear();
}
