///////////////////////////////////////////////////////////
//  ShufleObjects.cpp
//  Implementation of the Class ShufleObjects
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "ShufleObjects.h"
#include "DataObject.h"
#include "Statistics.h"
#include <time.h>
#include <stdlib.h>
#include <list>


ShufleObjects::ShufleObjects(){

}



ShufleObjects::~ShufleObjects(){

}





ObjectMatrix ShufleObjects::byBubleSort(ObjectMatrix objectMatrix){

	return  NULL;
}


ObjectMatrix ShufleObjects::byDispersion(ObjectMatrix objectMatrix){

	return  NULL;
}


ObjectMatrix ShufleObjects::byPCA(ObjectMatrix objectMatrix){

	return  NULL;
}


std::vector<int> ShufleObjects::byRand(ObjectMatrix objectMatrix){

    int n = objectMatrix.getObjectCount();
    std::vector<int> currentIndexes;
    std::vector<int> shufledIndexes;
    shufledIndexes.reserve(n);
    currentIndexes.reserve(n);
    for (int i = 0; i < n; i++)
        currentIndexes.push_back(i);
    double r = 0.0;
    int index = 0;
    
    do
    {
        r = Statistics::getRandom(0, n, index);
        index = static_cast<int>(r);
        while (currentIndexes.at(index) == -1)
            index = (index + 1) % n;
        
        shufledIndexes.push_back(index);
        currentIndexes.at(index) = -1;
       
    } while (shufledIndexes.size() < n);
    
    return  shufledIndexes;
}


std::vector<int> ShufleObjects::shufleObjectMatrix(ShufleEnum shufleEnum, ObjectMatrix objectMatrix){
    std::vector<int> shufled;
    
    if (shufleEnum == Random)
        shufled = ShufleObjects::byRand(objectMatrix);
    
    return  shufled;
}
