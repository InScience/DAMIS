///////////////////////////////////////////////////////////
//  SMACOF.cpp
//  Implementation of the Class SMACOF
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \class SMACOF
    \brief A class of methods and attributes for SMACOF algorithm.
 */
#include "SMACOF.h"
#include "ShufleObjects.h"
#include <string>
#include <sstream>
#include <vector>
#include "DataObject.h"
#include <float.h>
#include <cmath>
#include <iostream>
#include "AdditionalMethods.h"
#include "DistanceMetrics.h"

SMACOF::SMACOF(){

}

SMACOF::~SMACOF(){

}

SMACOF::SMACOF(double eps, int maxIter, int d):MDS(eps, maxIter, d){
    X = ObjectMatrix(AdditionalMethods::inputDataFile);
    X.loadDataMatrix();
    readFile = true;
    int m = X.getObjectCount();
    gutman = ObjectMatrix(m);
    std::vector<double> gutmanRow;
    gutmanRow.resize(m, 0);

    for (int i = 0; i < m; i++)
        gutman.addObject(DataObject(gutmanRow));

    initializeProjectionMatrix();
}

SMACOF::SMACOF(double eps, int maxIter, int d, ObjectMatrix X_base, ObjectMatrix Y_base):MDS(eps, maxIter, d){
    X = X_base;
    readFile = false;

    int m = X.getObjectCount();
    gutman = ObjectMatrix(m);
    std::vector<double> gutmanRow;
    gutmanRow.resize(m, 0);

    for (int i = 0; i < m; i++)
        gutman.addObject(DataObject(gutmanRow));
    Y = Y_base;
}

/*SMACOF::SMACOF(ObjectMatrix initialY, double eps, int maxIter, int d):MDS(eps, maxIter, d){
    Y = initialY;
}*/

SMACOF::SMACOF(double eps, int maxIter, int d, ObjectMatrix initialX):MDS(eps, maxIter, d){
    X = initialX;
    readFile = false;

    int m = X.getObjectCount();
    gutman = ObjectMatrix(m);
    std::vector<double> gutmanRow;
    gutmanRow.resize(m, 0);

    for (int i = 0; i < m; i++)
        gutman.addObject(DataObject(gutmanRow));
   // Y = Y_base;
    initializeProjectionMatrix();
}

ObjectMatrix SMACOF::getProjection(){
    stressErrors.reserve(maxIteration);
    int iteration = 0;
    int m = X.getObjectCount();
    //double str = getStress();
    stressErrors.push_back(getStress());
    double sum = 0.0;
    double Epsilon = DBL_MAX;
  //  ObjectMatrix Gutman;
    ObjectMatrix Y_new(m);

    ObjectMatrix Y_loc = Y; // runs faster if have local copy of Y matrix

    std::vector<double> Y_newRow;
    Y_newRow.reserve(d);
    DataObject obj1;

    while (iteration < maxIteration && Epsilon > epsilon)
    {
        Y_new.clearDataObjects();
        gutman = getGutman();

        for (int i = 0; i < m; i++)
        {
            Y_newRow.clear();
            obj1 = gutman.getObjectAt(i);
            for (int j = 0; j < d; j++)
            {
                sum = 0.0;
                for (int k = 0; k < m; k++)
                        sum += obj1.getFeatureAt(k) * Y_loc.getObjectAt(k).getFeatureAt(j); //get from local copy
                Y_newRow.push_back(sum / (float) m);
            }
            Y_new.addObject(DataObject(Y_newRow));
        }
        Y = Y_new;
        Y_loc = Y;
        //str = getStress();
        stressErrors.push_back(getStress());
        iteration++;
        Epsilon = std::fabs(stressErrors.at(iteration - 1) - stressErrors.at(iteration));
    //    std::cout << iteration << " " << Epsilon << " " << str << std::endl;
    }
    return Y;
}

double SMACOF::getStress()
{
    if (readFile) //depends if it was standalone run or was called from relative MDS method
        return DimReductionMethod::getStress();
    else
    {
        double stress = 0.0, weight= 0.0;
        int m = X.getObjectCount();
        double distX = 0.0;
        double distY = 0.0;
        double tmp;
        DataObject objXi, objYi;
        for (int i = 0; i < m - 1; i++)
        {
            objXi = X.getObjectAt(i);
            objYi = Y.getObjectAt(i);
            for (int j = i + 1; j < m; j++)
            {
                distX = DistanceMetrics::getDistance(objXi, X.getObjectAt(j), EUCLIDEAN);
                distY = DistanceMetrics::getDistance(objYi, Y.getObjectAt(j), EUCLIDEAN);
                tmp = distX - distY;
                stress += tmp * tmp;

                weight += distX * distX;
            }
        }
        return  stress / weight;
    }
}

/*ObjectMatrix SMACOF::getGutmanMatrix()
{
    return MDS::getGutman();
}*/
