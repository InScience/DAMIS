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


SMACOFZEIDEL::SMACOFZEIDEL(){

}

SMACOFZEIDEL::~SMACOFZEIDEL(){

}

SMACOFZEIDEL::SMACOFZEIDEL(double eps, int maxIter, int d, ShufleEnum shEnum):SMACOF(eps, maxIter, d){
    shufleEnum = shEnum;
    initializeProjectionMatrix();
}

SMACOFZEIDEL::SMACOFZEIDEL(ObjectMatrix initProjection, double eps, int maxIter, int d, ShufleEnum shEnum):SMACOF(eps, maxIter, d)
{
    shufleEnum = shEnum;
    Y = initProjection;
}

SMACOFZEIDEL::SMACOFZEIDEL(double eps, int maxIter, int d, ShufleEnum shEnum, ObjectMatrix initialX):SMACOF(eps, maxIter, d, initialX)
{
    shufleEnum = shEnum;
}

ObjectMatrix SMACOFZEIDEL::getProjection(){

    stressErrors.reserve(maxIteration);
    int i;
    int n = X.getObjectCount();
    stressErrors.push_back(getStress());
    double sum = 0.0;
    double Epsilon = DBL_MAX;
    ObjectMatrix Gutman, Y_new(n);
    std::vector<unsigned int> shufledIndexes;
    shufledIndexes.reserve(n);
    Y_new = Y;
    Gutman = getGutman();
    int iteration = 0;

    while (iteration < maxIteration && Epsilon > epsilon)
    {
        shufledIndexes = ShufleObjects::shufleObjectMatrix(shufleEnum, Y);

        for (int row=0; row < n; row++)
        {
            i = shufledIndexes.at(row);
            for (int j = 0; j < d; j++)
            {
                sum = 0.0;
                for (int k = 0; k < n; k++)
                        sum += Gutman.getObjectAt(i).getFeatureAt(k) * Y.getObjectAt(k).getFeatureAt(j);
                Y_new.updateDataObject(i, j, (sum / (double)n));
            }
            Gutman = getGutman(Y_new);
        }
        Y = Y_new;

        iteration++;
        stressErrors.push_back(getStress());
        Epsilon = stressErrors.at(iteration - 1) - stressErrors.at(iteration);
    }

    return Y;
}

double SMACOFZEIDEL::getStress()
{
    return MDS::getStress();
}