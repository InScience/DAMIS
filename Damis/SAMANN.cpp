///////////////////////////////////////////////////////////
//  SAMANN.cpp
//  Implementation of the Class SAMANN
//  Created on:      07-Lie-2013 20:07:31
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "SAMANN.h"
#include "Statistics.h"
#include "DistanceMetrics.h"
#include "math.h"


SAMANN::SAMANN(){

}



SAMANN::~SAMANN(){

}

/**
 * Contructor that takes, no of learning elemnts, no oh neurons in hidden layer,
 * learning speed value, and numebr of max training iterations.
 */
SAMANN::SAMANN(int m1, int nl, double e, int maxIter){
    mTrain = m1;
    nNeurons = nl;
    eta = e;
    maxIteration = maxIter;
}


/**
 * Calculates Lambda value for SAMAN projection
 */
double SAMANN::getLambda(){

    double temp = 0.0;
    int n = X.getObjectCount();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
            temp = temp + 1 / DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), Euclidean);
    }
    return 1 / temp;
}


/**
 * Pure virtual method that calculates the projection
 */
ObjectMatrix SAMANN::getProjection(){

    int n = X.getObjectAt(0).getFeatureCount();
    int m = X.getObjectCount();
    std::vector<std::vector<double> > w1, w2;
    std::vector<double> matrixRow, ddelta_L(mTrain), ddelta_suma(mTrain), delta_tarp(mTrain), ddelta_tarp(mTrain);
    ObjectMatrix Y_pasl(m), Y_is(m), delta_L(mTrain - 1);    
    double tarp = 0.0, tarp1 = 0.0, tarp2 = 0.0, lambda, tmp, distXp, distY;
    
    for (int i = 0; i < mTrain - 1; i++)
    {
        ddelta_L.push_back(0.1);
        ddelta_suma.push_back(0.0);
        delta_tarp.push_back(0.0);
        ddelta_tarp.push_back(0.0);
        for (int j = 0; j < mTrain; j++)
            matrixRow.push_back(0.1);
        delta_L.addObject(DataObject(matrixRow));        
        matrixRow.clear();
    }
    ddelta_L.push_back(0.1);
    ddelta_suma.push_back(0.0);
    delta_tarp.push_back(0.0);
    ddelta_tarp.push_back(0.0);
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < d; j++)
            matrixRow.push_back(1.0);
        Y_is.addObject(DataObject(matrixRow));
        for (int j = d; j < nNeurons; j++)
            matrixRow.push_back(1.0);
        Y_pasl.addObject(DataObject(matrixRow));        
        matrixRow.clear();        
    }
    
    for (int i = 0; i < nNeurons; i++)
    {
        for (int j = 0; j < n; j++)
            matrixRow.push_back(Statistics::getRandom(-0.1, 0.1, (i + 5 * j)));
        w1.push_back(matrixRow);
        matrixRow.clear();
    }
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < nNeurons; j++)
            matrixRow.push_back(Statistics::getRandom(-0.1, 0.1, (i + 5 * j)));
        w2.push_back(matrixRow);
        matrixRow.clear();
    }
    
    NormalizeX();
    getXp();
    lambda = getLambda();
        
    for (int iter = 0; iter < maxIteration; iter++)
    {
        for (int miu = 1; miu < mTrain - 1; miu++)
        {
            for (int niu = miu + 1; niu < mTrain; niu++)
            {
                for (int j = 0; j < nNeurons; j++)
                {
                    tarp = 0.0;
                    for (int k = 0; k < n; k++)
                        tarp = tarp + w1[j].at(k) * Xp.getObjectAt(miu).getFeatureAt(k);
                    Y_pasl.updateDataObject(miu, j, 1.0 / (1 + exp(-1 * tarp)));
                }
                for (int j = 0; j < d; j++)
                {
                    tarp = 0.0;
                    for (int k = 0; k < nNeurons; k++)
                        tarp = tarp + w2[j].at(k) * Y_pasl.getObjectAt(miu).getFeatureAt(k);
                    Y_is.updateDataObject(miu, j, 1.0 / exp(-1 * tarp));
                }
            }
        }
        for (int miu = 1; miu < mTrain - 1; miu++)
        {
            for (int niu = miu + 1; niu < mTrain; niu++)
            {
                tarp1 = 0.0;
                tarp2 = 0.0;
                for (int k = 0; k < d; k++)
                {
                    distXp = DistanceMetrics::getDistance(Xp.getObjectAt(miu), Xp.getObjectAt(niu), Euclidean);
                    distY = DistanceMetrics::getDistance(Y.getObjectAt(miu), Y.getObjectAt(niu), Euclidean);
                    tmp = -2 * lambda * ((distXp - distY) / (distXp * distY)) * (Y_is.getObjectAt(miu).getFeatureAt(k) - Y_is.getObjectAt(niu).getFeatureAt(k));
                    delta_L.updateDataObject(miu, niu, tmp);
                    ddelta_L[miu] = delta_L.getObjectAt(miu).getFeatureAt(niu) * (1 - Y_is.getObjectAt(miu).getFeatureAt(k)) * Y_is.getObjectAt(miu).getFeatureAt(k);
                    ddelta_L[niu] = delta_L.getObjectAt(miu).getFeatureAt(niu) * (1 - Y_is.getObjectAt(niu).getFeatureAt(k)) * Y_is.getObjectAt(niu).getFeatureAt(k);
                    tarp1 = tarp1 + ddelta_L[miu];
                    tarp2 = tarp2 + ddelta_L[niu];
                    
                    for (int j = 0; j < nNeurons; j++)
                    {
                        if (iter == 1)
                            w2[j][k] = -1 * eta * (ddelta_L[miu] * Y_pasl.getObjectAt(miu).getFeatureAt(j) - ddelta_L[niu] * Y_pasl.getObjectAt(niu).getFeatureAt(j));
                        else
                            w2[j][k] = -1 * eta * (ddelta_L[miu] * Y_pasl.getObjectAt(miu).getFeatureAt(j) - ddelta_L[niu] * Y_pasl.getObjectAt(niu).getFeatureAt(j)) - w2[k][j];
                    }
                }
                ddelta_suma[miu] = tarp1;
                ddelta_suma[niu] = tarp2;
                for (int j = 0; j < nNeurons; j++)
                {
                    for (int k = 0; k < d; k++)
                    {
                        delta_tarp[miu] = ddelta_suma.at(miu) * w2[j][k];
                        delta_tarp[niu] = ddelta_suma.at(niu) * w2[j][k];
                    }
                    
                    for (int k = 0; k < n; k++)
                    {
                        ddelta_tarp[miu] = delta_tarp[miu] * (1 - Y_pasl.getObjectAt(miu).getFeatureAt(j));
                        ddelta_tarp[niu] = delta_tarp[niu] * (1 - Y_pasl.getObjectAt(niu).getFeatureAt(j));
                        if (iter == 1)
                            w1[j][k] = -1 * eta * (ddelta_tarp[miu] * Y_pasl.getObjectAt(miu).getFeatureAt(j) - ddelta_tarp[niu] * Y_pasl.getObjectAt(niu).getFeatureAt(j));
                        else
                            w1[j][k] = -1 * eta * (ddelta_tarp[miu] * Y_pasl.getObjectAt(miu).getFeatureAt(j) - ddelta_tarp[niu] * Y_pasl.getObjectAt(niu).getFeatureAt(j)) -w2[j][k];
                    }                    
                }
            }            
        }
    }  // iteraciju pabaiga
    
    for (int miu = 0; miu < m; miu++)
    {
        for (int j = 0; j < nNeurons; j++)
        {
            tarp = 0.0;
            for (int k = 0; k < n; k++)
                tarp += w1[j].at(k) * X.getObjectAt(miu).getFeatureAt(k);
            Y_pasl.updateDataObject(miu, j, 1.0 / (1 + exp(-1 * tarp)));              
        }
        for (int j = 0; j < d; j++)
        {
            tarp = 0.0;
            for (int k = 0; k < nNeurons; k++)
                tarp += w2[j].at(k) * Y_pasl.getObjectAt(miu).getFeatureAt(k);
            Y_is.updateDataObject(miu, j, 1.0 / (1 + exp(-1 * tarp)));
        }
    }
    Y = Y_is;
    return  Y;
}

double SAMANN::getMax()
{
    int n = X.getObjectCount();
    int m = X.getObjectAt(0).getFeatureCount();
    double max = -10000.0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (max < X.getObjectAt(i).getFeatureAt(j))
                max = X.getObjectAt(i).getFeatureAt(j);
    return max; 
}

void SAMANN::NormalizeX()
{
    double max = getMax();
    double value;
    int n = X.getObjectCount();
    int m = X.getObjectAt(0).getFeatureCount();
    //ObjectMatrix X_Norm(n);
    //std::vector<double> row;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            value = X.getObjectAt(i).getFeatureAt(j) / max;
            X.updateDataObject(i, j, value);
        }
            //row.push_back(X.getObjectAt(i).getItems().at(j) / max)
        //X_Norm.addObject(DataObject(row));
        //row.clear();
    }
    //X = X_Norm;
}

void SAMANN::getXp()
{
    int n = X.getObjectCount(), i = 0, k = 0, index = 0;
    double r = 0.0;
    DataObject dObject;

    while (i < nNeurons)
    {
        r = Statistics::getRandom(0, n, k);
        index = static_cast<int>(r);
        dObject = X.getObjectAt(index);
        if (isIdentical(dObject) == false)
        {
            Xp.addObject(dObject);
            i++;
        }
        k++;
    }
}

bool SAMANN::isIdentical(DataObject obj)
{
    bool ats = false;
    int n = Xp.getObjectCount();
    int m = obj.getFeatureCount();
    int k = 0;
    
    for (int i = 0; i < n; i++)
    {
        k = 0;
        for (int j = 0; j < m; j++)
            if (obj.getFeatureAt(j) == Xp.getObjectAt(i).getFeatureAt(j))
                k++;
        if (k == m)
        {
            ats = true;
            break;
        }
    }
    
    return ats;
}

/**
 * calculates SAMAN stress
 */
double SAMANN::getStress(){
    double tarp1 = 0.0, tarp2 = 0.0, distX, distY;
    int m = X.getObjectCount();
    for (int miu = 0; miu < m - 1; miu++)
    {
        for (int niu = miu + 1; niu < m; niu++)
        {
            distX = DistanceMetrics::getDistance(X.getObjectAt(miu), X.getObjectAt(niu), Euclidean);
            distY = DistanceMetrics::getDistance(Y.getObjectAt(miu), Y.getObjectAt(niu), Euclidean);
            tarp1 += 1 / distX;
            tarp2 += pow(distX - distY, 2) / distX;
        }
    }
    return tarp1 * tarp2;
}


/**
 * Function forms set of training objects (uses Preprocess class function)
 */
void SAMANN::getTrainingSet(){

}


/**
 * Public function trains SAMAN network
 */
void SAMANN::train(){

}


/**
 * Function updates last and hidden layer neuron weights
 */
void SAMANN::updateWeights(){

}
