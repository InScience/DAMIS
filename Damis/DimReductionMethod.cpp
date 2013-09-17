///////////////////////////////////////////////////////////
//  DimReductionMethod.cpp
//  Implementation of the Class DimReductionMethod
//  Created on:      07-Lie-2013 20:07:29
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "DimReductionMethod.h"


DimReductionMethod::DimReductionMethod(){
    d = 2;
}

DimReductionMethod::~DimReductionMethod(){

}

/**
 * Returns d
 */
int DimReductionMethod::getProjectionDimension(){

	return d;
}

/**
 * Initializes Y matrix acording to dimension d and fills it with data.
 */
void DimReductionMethod::initializeProjectionMatrix(int n){
    Y = ObjectMatrix(n);
}

/**
 * Sets the desired projection dimension
 */
void DimReductionMethod::setProjectionDimension(int dimension){
    d = dimension;
}