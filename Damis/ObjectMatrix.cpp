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
    DataObjects.reserve(5);    
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
ObjectMatrix::ObjectMatrix(int m, int n){
    DataObjects.reserve(m);
    objectCount = 0;
}


/**
 * Constructor that creates m by n matrix that holds k features i.e. cube. Needed
 * by SOM algorithm.
 */
ObjectMatrix::ObjectMatrix(int m, int n, int k){
    
}


/**
 * Adds data object to ObjectMatrix
 */
void ObjectMatrix::addObject(DataObject object){
    DataObjects.push_back(object);
    objectCount = DataObjects.size();
}


/**
 * Gets object at position
 */
DataObject ObjectMatrix::getObjectAt(int index){
    return  DataObjects.at(index);
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
    if (file.ReadSuccess == true)
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
    {
        objectCount = 0;
        ErrorMessage = "gaidys";
    }
}


void ObjectMatrix::saveDataMatrix(const char* path){
    ARFF file;
    file.WriteData(path, this->DataObjects);
}
