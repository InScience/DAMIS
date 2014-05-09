///////////////////////////////////////////////////////////
//  ObjectMatrix.cpp
//  Implementation of the Class ObjectMatrix
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

/*! \class ObjectMatrix
    \brief A class of methods and attributes for manipulating matrices.
 */
#include "ObjectMatrix.h"
#include "AdditionalMethods.h"
#include "ARFF.h"
#include "DataObject.h"
#include <vector>
#include <cmath>
#include <iostream>

//double ObjectMatrix::_weight = 0;

ObjectMatrix::ObjectMatrix(){
    DataObjects.reserve(0);   //1
    objectCount = 0;
}

ObjectMatrix::~ObjectMatrix(){
}

ObjectMatrix::ObjectMatrix(std::string file){
    fileName.assign(file);
    objectCount = 0;
}

ObjectMatrix::ObjectMatrix(int cnt){
    DataObjects.reserve(cnt);
    objectCount = 0;
}

ObjectMatrix::ObjectMatrix(int n, int m){
    DataObjects.reserve(n);
    for (int i = 0; i < n; i++)
        DataObjects[i].setNumOfFeatures(m);
    objectCount = 0;
}

ObjectMatrix::ObjectMatrix(int m, int n, int k){
    std::vector<double> initialFeatures;
    initialFeatures.resize(k, 1.0);
    DataObject initial(initialFeatures);
    DataObjects2D.resize(m, std::vector<DataObject>(n, initial));
    objectCount = 0;
}

void ObjectMatrix::addObject(DataObject object){
    DataObjects.push_back(object);
    objectCount++;
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

DataObject ObjectMatrix::getObjectAt(int index){
    return  DataObjects.at(index);
}

DataObject ObjectMatrix::getObjectAt(int row_index, int col_index){
    return  DataObjects2D[row_index].at(col_index);
}

int ObjectMatrix::getObjectCount(){
    return objectCount;
}

std::vector<std::string> ObjectMatrix::getFeaturesTitle(){
    return featureTitles;
}

void ObjectMatrix::loadDataMatrix(){
    const char* path = fileName.c_str();
    ARFF file(path);

    ObjectMatrix::_weight = 0;

    if (file.isSuccessfullyRead() == true)   // successful read
    {
        std::vector< std::vector<double>> data = file.getData();
        featureTitles = file.getAttributes();

        std::vector< std::vector<double>> ::iterator dataObjectIterator;

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

        //Calculate matrix X distances between vectors

        //ObjectMatrix::_weight = 0;
        int i, j, z;
        int n =  data.at(0).size(); //features
        double diff, sRow, tmpVal;

        FILE *distFile;
        distFile = fopen(AdditionalMethods::tempFileSavePath.c_str(), "wb");

        for (i = 0; i < objectCount - 1; i++)
        {
            for (j = i + 1; j < objectCount; j++)
            {
                sRow = 0.0;
                for (z = 0; z < n; z++)
                {
                    diff  = data.at(i).at(z) - data.at(j).at(z);
                    sRow += diff * diff;
                }
                tmpVal = std::sqrt(sRow);
                fwrite(&tmpVal, sizeof(double), 1, distFile);
                ObjectMatrix::_weight += sRow;
            }
        }
    fclose(distFile);
    // end distance matrix calculation
    }
    else
        {
            //_weight = 0;
            objectCount = 0;
        }
}

void ObjectMatrix::saveDataMatrix(const char* path){
    ARFF file;
    file.writeData(path, this->DataObjects);
}

void ObjectMatrix::clearDataObjects()
{
    DataObjects.clear();
   /* int c = DataObjects.size();
    c++;*/
    objectCount = 0;
}

 /*double ObjectMatrix::getDistanceBetween(int i, int j)
 {
    FILE *distFile;
    distFile = fopen("D:\\dist.txt", "rb");
//   std::ifstream distFile;
//    distFile.open("D:\\dist.txt", std::ios::binary);
    double retVal;
    int noOfBytes = sizeof(double);

    fseek(distFile, (noOfBytes * i) + noOfBytes * (j - i - 1), SEEK_SET);
  //  fseek(distFile, 1, SEEK_SET);
    fread(&retVal, noOfBytes, 1, distFile);
  //  distFile>>retVal;

   // std::cout << retVal << std::endl;
    fclose(distFile);
 // distFile.close();
    return retVal;
    //return *(*(distances + i) + j - i - 1);
 }*/

 double ObjectMatrix::getWeight()
 {
    return ObjectMatrix::_weight;
 }
