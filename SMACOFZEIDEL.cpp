///////////////////////////////////////////////////////////
//  SMACOFZEIDEL.cpp
//  Implementation of the Class SMACOFZEIDEL
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \class SMACOFZEIDEL
    \brief A class of methods and attributes for SMACOFZEIDEL algorithm.
 */
#include "SMACOFZEIDEL.h"
#include "ShufleObjects.h"
#include <float.h>
#include <iostream>
#include <cmath>


SMACOFZEIDEL::SMACOFZEIDEL(){

}

SMACOFZEIDEL::~SMACOFZEIDEL(){

}

SMACOFZEIDEL::SMACOFZEIDEL(double eps, int maxIter, int d, ShufleEnum shEnum):SMACOF(eps, maxIter, d){
    shufleEnum = shEnum;
    initializeProjectionMatrix();
}

/*SMACOFZEIDEL::SMACOFZEIDEL(ObjectMatrix initProjection, double eps, int maxIter, int d, ShufleEnum shEnum):SMACOF(eps, maxIter, d)
{
    shufleEnum = shEnum;
    Y = initProjection;
}

SMACOFZEIDEL::SMACOFZEIDEL(double eps, int maxIter, int d, ShufleEnum shEnum, ObjectMatrix initialX):SMACOF(eps, maxIter, d, initialX)
{
    shufleEnum = shEnum;
}*/

ObjectMatrix SMACOFZEIDEL::getProjection(){

    stressErrors.reserve(maxIteration);
    int i;
    int m = X.getObjectCount();
    double sum = 0.0;
   // str = getStress();
    stressErrors.push_back(getStress());

    double Epsilon = DBL_MAX;
    ObjectMatrix Gutman, Y_new(m);
    std::vector<unsigned int> shufledIndexes;
    shufledIndexes.reserve(m);
    Y_new = Y;
    Gutman = getGutman();
    int iteration = 0;
    DataObject objGutmani;

    while (iteration < maxIteration && Epsilon > epsilon)
    {
        shufledIndexes = ShufleObjects::shufleObjectMatrix(shufleEnum, Y);

        for (int row = 0; row < m; row++)
        {
            i = shufledIndexes.at(row);
            objGutmani = Gutman.getObjectAt(i);
            for (int j = 0; j < d; j++)
            {
                sum = 0.0;
                for (int k = 0; k < m; k++)
                        sum += objGutmani.getFeatureAt(k) * Y.getObjectAt(k).getFeatureAt(j);
                Y_new.updateDataObject(i, j, (sum / (float) m));
            }
            Gutman = getGutman(Y_new, i); //change ith row
        }
        Y = Y_new;

        iteration++;
       // str = getStress();
        stressErrors.push_back(getStress());
        Epsilon = std::fabs((stressErrors.at(iteration - 1) - stressErrors.at(iteration)));
      //  std::cout <<iteration << " " << Epsilon << " " << str <<  std::endl;
    }
    return Y;
}

/*double SMACOFZEIDEL::getStress()
{
    return DimReductionMethod::getStress();
}*/
