///////////////////////////////////////////////////////////
//  ShufleObjects.cpp
//  Implementation of the Class ShufleObjects
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \class ShufleObjects
    \brief A class of static methods for shuffling the DataObjects in ObjectMatrix.
 */
#include "ShufleObjects.h"
#include "DataObject.h"
#include "Statistics.h"
//#include <time.h>
//#include <stdlib.h>
//#include <list>
#include <iostream>


ShufleObjects::ShufleObjects(){

}

ShufleObjects::~ShufleObjects(){

}

std::vector<unsigned int> ShufleObjects::byBubleSort(ObjectMatrix objectMatrix)   // didejimo tvarka
{
    int n = objectMatrix.getObjectCount();
    int tmp_index = 0;
    double tmp_disp = 0.0;
    bool shufled = false;
    std::vector<unsigned int> shufledIndexes;
    shufledIndexes.reserve(n);
    for (int i = 0; i < n; i++)
        shufledIndexes.push_back(i);

   int l = 1;
    do
    {
        shufled = true;
        for (int i = 0; i < n - l; i++)
        {
            if (objectMatrix.getObjectAt(shufledIndexes.at(i)).getFeatureAt(0) > objectMatrix.getObjectAt(shufledIndexes.at(i + 1)).getFeatureAt(0))
            {
                tmp_index = shufledIndexes.at(i);
                shufledIndexes.at(i) = shufledIndexes.at(i + 1);
                shufledIndexes.at(i + 1) = tmp_index;
                shufled = false;
            }
        }
        l++;
    }
    while (!shufled);

    return  shufledIndexes;
}

std::vector<unsigned int> ShufleObjects::byBubleSortDsc(ObjectMatrix objectMatrix)  // mazejimo tvarka
{
    int n = objectMatrix.getObjectCount();
    int tmp_index = 0;
    double tmp_disp = 0.0;
    bool shufled = false;
    std::vector<unsigned int> shufledIndexes;
    shufledIndexes.reserve(n);
    for (int i = 0; i < n; i++)
        shufledIndexes.push_back(i);

    int l = 1;
    do
    {
        shufled = true;
        for (int i = 0; i < n - l; i++)
        {
            if (objectMatrix.getObjectAt(shufledIndexes.at(i)).getFeatureAt(0) < objectMatrix.getObjectAt(shufledIndexes.at(i + 1)).getFeatureAt(0))
            {
                tmp_index = shufledIndexes.at(i);
                shufledIndexes.at(i) = shufledIndexes.at(i + 1);
                shufledIndexes.at(i + 1) = tmp_index;
                shufled = false;
            }
        }
        l++;
    }
    while (!shufled);

  /*  for (int i = 0; i < n; i++)
        std::cout << objectMatrix.getObjectAt(shufledIndexes.at(i)).getFeatureAt(0) << std::endl;*/

    return  shufledIndexes;
}

std::vector<unsigned int> ShufleObjects::byRand(ObjectMatrix objectMatrix){

    unsigned int n = objectMatrix.getObjectCount();
    std::vector<unsigned int> currentIndexes;
    std::vector<unsigned int> shufledIndexes;
    shufledIndexes.reserve(n);
    currentIndexes.reserve(n);

    for (unsigned int i = 0; i < n; i++)
        currentIndexes.push_back(i);

    double r = 0.0;
    int index = 0;

    do
    {
        r = Statistics::getRandom(0, n - 1); //-1 since 0 is included
        index = static_cast<int>(r);
        while (currentIndexes.at(index) == -1)
            index = (index + 1) % n;

        shufledIndexes.push_back(index);
        currentIndexes.at(index) = -1;

    } while (shufledIndexes.size() < n);

    return  shufledIndexes;
}


std::vector<unsigned int> ShufleObjects::shufleObjectMatrix(ShufleEnum shufleEnum, ObjectMatrix objectMatrix){
    std::vector<unsigned int> shufled;

    switch (shufleEnum)
    {
        case 1: shufled = ShufleObjects::byRand(objectMatrix);
                break;
        case 2: shufled = ShufleObjects::byBubleSort(objectMatrix);
                break;
        case 3: shufled = ShufleObjects::byBubleSortDsc(objectMatrix);
                break;
        default: shufled = ShufleObjects::byRand(objectMatrix);
                break;
    }

    return  shufled;
}
