///////////////////////////////////////////////////////////
//  DataObject.cpp
//  Implementation of the Class DataObject
//  Created on:      07-Lie-2013 20:07:29
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "DataObject.h"


DataObject::DataObject(){

    classLabel = -1;
}

DataObject::~DataObject(){

}


/**
 * Constructor that constructs an object and sets object feature count
 */
DataObject::DataObject(int feature_count){

    classLabel = -1;
    featureCount = feature_count;
}

DataObject::DataObject(std::vector<double> vector){
    items = vector;
    featureCount = items.size();
}

/**
 * Constructor that sets feature count and class label
 */
DataObject::DataObject(int feature_count, int class_label){
    
    featureCount = feature_count;
    classLabel = class_label;
}


int DataObject::getClassLabel(){

	return classLabel;
}

std::vector<double> DataObject::getItems(){
    return items;
}

/**
 * Returns feature count
 */
int DataObject::getFeatureCount(){

    return featureCount;
}


void DataObject::setClassLabel(int class_Label){
    classLabel = class_Label;
}