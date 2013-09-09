///////////////////////////////////////////////////////////
//  ObjectMatrix.cpp
//  Implementation of the Class ObjectMatrix
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "ObjectMatrix.h"
#include <vector>

ObjectMatrix::ObjectMatrix(){
    DataObjects.reserve(5);
    
}



ObjectMatrix::~ObjectMatrix(){

    //DataObjects.~vector();
}

/**
 * Constructor that reads object matrix from arff file
 */
ObjectMatrix::ObjectMatrix(std::string fileName){

    
    
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


/**
 * Loads (deserializes) object matrix (reads arff file into an OdjectMatrix object)
 */
void ObjectMatrix::loadDataMatrix(){

}


void ObjectMatrix::saveDataMatrix(ObjectMatrix om, char path){

    char a = path;
}