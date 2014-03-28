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
#include <time.h>
#include <stdlib.h>
#include <list>


ShufleObjects::ShufleObjects(){

}

ShufleObjects::~ShufleObjects(){

}
/*! \brief Bubble sort shuffling 
 * 
 * Shuffling of object in ascending order
 * \param objectMatrix is a 
 */
std::vector<int> ShufleObjects::byBubleSort(ObjectMatrix objectMatrix)
{
    int n = objectMatrix.getObjectCount();
    int tmp_index = 0;
    double tmp_disp = 0.0;
    bool shufled = false;
    std::vector<int> shufledIndexes;
    shufledIndexes.reserve(n);
    for (int i = 0; i < n; i++)
        shufledIndexes.push_back(i);
    
    for (int k = 0; k < n; k++)
    {
        shufled = false;
        for (int i = 0; i < n - 1; i++)
        {
            if (objectMatrix.getObjectAt(i).getFeatureAt(0) > objectMatrix.getObjectAt(i + 1).getFeatureAt(0))
            {
                tmp_disp = objectMatrix.getObjectAt(i).getFeatureAt(0);
                tmp_index = i;
                objectMatrix.updateDataObject(i, 0, objectMatrix.getObjectAt(i + 1).getFeatureAt(0));
                objectMatrix.updateDataObject(i + 1, 0, tmp_disp);
                shufledIndexes[i] = shufledIndexes.at(i + 1);
                shufledIndexes[i + 1] = tmp_index;
                shufled = true;
            }
        }
        if (shufled == false)
            break;
    }
    
    return  shufledIndexes;
}

/*! \brief Bubble sort shuffling 
 * 
 * Shuffling of object in descending order
 */
std::vector<int> ShufleObjects::byBubleSortDsc(ObjectMatrix objectMatrix)
{
    int n = objectMatrix.getObjectCount();
    int tmp_index = 0;
    double tmp_disp = 0.0;
    bool shufled = false;
    std::vector<int> shufledIndexes;
    shufledIndexes.reserve(n);
    for (int i = 0; i < n; i++)
        shufledIndexes.push_back(i);
    
    for (int k = 0; k < n; k++)
    {
        shufled = false;
        for (int i = 0; i < n - 1; i++)
        {
            if (objectMatrix.getObjectAt(i).getFeatureAt(0) < objectMatrix.getObjectAt(i + 1).getFeatureAt(0))
            {
                tmp_disp = objectMatrix.getObjectAt(i).getFeatureAt(0);
                tmp_index = i;
                objectMatrix.updateDataObject(i, 0, objectMatrix.getObjectAt(i + 1).getFeatureAt(0));
                objectMatrix.updateDataObject(i + 1, 0, tmp_disp);
                shufledIndexes[i] = shufledIndexes.at(i + 1);
                shufledIndexes[i + 1] = tmp_index;
                shufled = true;
            }
        }
        if (shufled == false)
            break;
    }
    
    return  shufledIndexes;
}

/*! \brief Random shuffling 
 * 
 * Shuffling of object in random order
 */
std::vector<int> ShufleObjects::byRand(ObjectMatrix objectMatrix){

    unsigned int n = objectMatrix.getObjectCount();
    std::vector<int> currentIndexes;
    std::vector<int> shufledIndexes;
    shufledIndexes.reserve(n);
    currentIndexes.reserve(n);
    for (unsigned int i = 0; i < n; i++)
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
