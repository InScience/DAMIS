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
#include "AdditionalMethods.h"
#include <fstream>


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
    d = 2;
    initializeProjectionMatrix();
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
            temp = temp + 1.0 / DistanceMetrics::getDistance(X.getObjectAt(i), X.getObjectAt(j), EUCLIDEAN);
    }
    return 1.0 / temp;
}


/**
 * Pure virtual method that calculates the projection
 */
ObjectMatrix SAMANN::getProjection(){

    int n = X.getObjectAt(0).getFeatureCount();
    int m = X.getObjectCount();
    double ddelta_L[mTrain];
    double ddelta_suma[mTrain];
    double delta_tarp[mTrain];
    double ddelta_tarp[mTrain];
    double tarp = 0.0, tarp1 = 0.0, tarp2 = 0.0, lambda, tmp, distXp, distY;
    std::ofstream file("Y_is.txt");
    std::ofstream file2("Y_pasl.txt");
    
    initializeWeights();   // w1, w2
    initializeExitMatrixes();   // Y_pasl, Y_is
    initializeDeltaL();   // delta_L
    NormalizeX(); 
    
    for (int i = 0; i < m; i++)
        X.updateDataObject(i, 0, 1.0);
    
    double** Ypasl = AdditionalMethods::ObjectMatrixToDouble(Y_pasl);
    double** Yis = AdditionalMethods::ObjectMatrixToDouble(Y_is);
    
    getXp();
    lambda = getLambda();
    
    Xp.saveDataMatrix("xp.arff");
    
    for (int i = 0; i < mTrain; i++)
    {
        ddelta_L[i] = 0.0;
        ddelta_suma[i] = 0.0;
        delta_tarp[i] = 0.0;
        ddelta_tarp[i] = 0.0;
    }

    for (int iter = 0; iter < maxIteration; iter++)
    {
        for (int miu = 0; miu < mTrain - 1; miu++)
        {
            for (int niu = miu + 1; niu < mTrain; niu++)
            {
                for (int j = 0; j < nNeurons; j++)
                {
                    tarp = 0.0;
                    file2 <<"miu:" <<miu<<", niu: "<<niu <<", j: " << j << ", w1: ";
                    for (int k = 0; k < n; k++)
                    {
                        tarp += w1[j].at(k) * Xp.getObjectAt(miu).getFeatureAt(k);
                        file2 <<w1[j].at(k)<<", ";
                    }
                    file2<<std::endl;
                    Ypasl[miu][j] = 1.0 / (1 + exp(-1 * tarp));
                    //Y_pasl.updateDataObject(miu, j, 1.0 / (1 + exp(-1 * tarp)));
                }

                for (int j = 0; j < d; j++)
                {
                    tarp = 0.0;
                    file << "miu: " << miu <<", niu: "<< niu<< " Y_pasl: ";
                    for (int k = 0; k < nNeurons; k++)
                    {
                        //tarp = tarp + w2[j].at(k) * Y_pasl.getObjectAt(miu).getFeatureAt(k);
                        file <<Ypasl[miu][k]<<", ";
                        tarp += w2[j].at(k) * Ypasl[miu][k];
                    }
                    file << " tarp: " << tarp <<std::endl;
                    Yis[miu][j] = 1.0 / exp(-1 * tarp);
                    //Y_is.updateDataObject(miu, j, 1.0 / exp(-1 * tarp));
                }
                
                tarp1 = 0.0;
                tarp2 = 0.0;
                for (int k = 0; k < d; k++)
                {
                    distXp = DistanceMetrics::getDistance(Xp.getObjectAt(miu), Xp.getObjectAt(niu), EUCLIDEAN);
                    distY = DistanceMetrics::getDistance(Y.getObjectAt(miu), Y.getObjectAt(niu), EUCLIDEAN);
                    //tmp = -2 * lambda * ((distXp - distY) / (distXp * distY)) * (Y_is.getObjectAt(miu).getFeatureAt(k) - Y_is.getObjectAt(niu).getFeatureAt(k));
                    tmp = -2 * lambda * ((distXp - distY) / (distXp * distY)) * (Yis[miu][k] - Yis[niu][k]);
                    delta_L.updateDataObject(miu, niu, tmp);
                    //ddelta_L[miu] = delta_L.getObjectAt(miu).getFeatureAt(niu) * (1 - Y_is.getObjectAt(miu).getFeatureAt(k)) * Y_is.getObjectAt(miu).getFeatureAt(k);
                    ddelta_L[miu] = delta_L.getObjectAt(miu).getFeatureAt(niu) * (1 - Yis[miu][k]) * Yis[miu][k];
                    //ddelta_L[niu] = delta_L.getObjectAt(miu).getFeatureAt(niu) * (1 - Y_is.getObjectAt(niu).getFeatureAt(k)) * Y_is.getObjectAt(niu).getFeatureAt(k);//
                    ddelta_L[niu] = delta_L.getObjectAt(miu).getFeatureAt(niu) * (1 - Yis[niu][k]) * Yis[niu][k];
                    tarp1 = tarp1 + ddelta_L[miu];
                    tarp2 = tarp2 + ddelta_L[niu];
                    
                    for (int j = 0; j < nNeurons; j++)
                    {
                        if (iter == 0)
                           // w2[k][j] = -1 * eta * (ddelta_L[miu] * Y_pasl.getObjectAt(miu).getFeatureAt(j) - ddelta_L[niu] * Y_pasl.getObjectAt(niu).getFeatureAt(j));
                        w2[k][j] = -1 * eta * (ddelta_L[miu] * Ypasl[miu][j] - ddelta_L[niu] * Ypasl[niu][j]);
                        else
                            //w2[k][j] = -1 * eta * (ddelta_L[miu] * Y_pasl.getObjectAt(miu).getFeatureAt(j) - ddelta_L[niu] * Y_pasl.getObjectAt(niu).getFeatureAt(j)) - w2[k][j];
                        w2[k][j] = -1 * eta * (ddelta_L[miu] * Ypasl[miu][j] - ddelta_L[niu] * Ypasl[niu][j]) - w2[k][j];
                    }
                }
                ddelta_suma[miu] = tarp1;
                ddelta_suma[niu] = tarp2;
                
                for (int j = 0; j < nNeurons; j++)
                {
                    for (int k = 0; k < d; k++)
                    {
                        delta_tarp[miu] += ddelta_suma[miu] * w2[k][j];
                        delta_tarp[niu] += ddelta_suma[niu] * w2[k][j];
                    }
                    
                    for (int k = 0; k < n; k++)
                    {
                        //ddelta_tarp[miu] = delta_tarp[miu] * (1 - Y_pasl.getObjectAt(miu).getFeatureAt(j));
                        //ddelta_tarp[niu] = delta_tarp[niu] * (1 - Y_pasl.getObjectAt(niu).getFeatureAt(j));
                        ddelta_tarp[miu] = delta_tarp[miu] * (1 - Ypasl[miu][j]);
                        ddelta_tarp[niu] = delta_tarp[niu] * (1 - Ypasl[niu][j]);
                        if (iter == 0)
                            //w1[j][k] = -1 * eta * (ddelta_tarp[miu] * Y_pasl.getObjectAt(miu).getFeatureAt(j) - ddelta_tarp[niu] * Y_pasl.getObjectAt(niu).getFeatureAt(j));
                        w1[j][k] = -1 * eta * (ddelta_tarp[miu] * Ypasl[miu][j] - ddelta_tarp[niu] * Ypasl[niu][j]);
                        else
                           // w1[j][k] = -1 * eta * (ddelta_tarp[miu] * Y_pasl.getObjectAt(miu).getFeatureAt(j) - ddelta_tarp[niu] * Y_pasl.getObjectAt(niu).getFeatureAt(j)) -w1[j][k];
                        w1[j][k] = -1 * eta * (ddelta_tarp[miu] * Ypasl[miu][j] - ddelta_tarp[niu] * Ypasl[niu][j]) -w1[j][k];
                    }                       
                }
            } 
             
        }        
    }  // iteraciju pabaiga
    
    //Y_pasl.saveDataMatrix("ypasl.arff");
    
    for (int miu = 0; miu < m; miu++)
    {
        for (int j = 0; j < nNeurons; j++)
        {
            tarp = 0.0;
            for (int k = 0; k < n; k++)
                tarp += w1[j].at(k) * X.getObjectAt(miu).getFeatureAt(k);
           // Y_pasl.updateDataObject(miu, j, 1.0 / (1 + exp(-1 * tarp)));  
           Ypasl[miu][j] = 1.0 / (1 + exp(-1 * tarp));            
        }
        for (int j = 0; j < d; j++)
        {
            tarp = 0.0;
            for (int k = 0; k < nNeurons; k++)
                //tarp += w2[j].at(k) * Y_pasl.getObjectAt(miu).getFeatureAt(k);
            tarp += w2[j].at(k) * Ypasl[miu][k];
            //Y_is.updateDataObject(miu, j, 1.0 / (1 + exp(-1 * tarp)));
            Yis[miu][j] = 1.0 / (1 + exp(-1 * tarp));
        }
    }
    Y = AdditionalMethods::DoubleToObjectMatrix(Yis, m, 2);
    //return  Y_is;
    file.close();
    file2.close();
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
    Xp = ObjectMatrix(nNeurons);
    double r = 0.0;
    DataObject dObject;

    while (i < mTrain)
    //while (i < nNeurons)
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
            distX = DistanceMetrics::getDistance(X.getObjectAt(miu), X.getObjectAt(niu), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(Y.getObjectAt(miu), Y.getObjectAt(niu), EUCLIDEAN);
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

void SAMANN::initializeWeights()
{
    int n = X.getObjectAt(0).getFeatureCount();
    std::vector<double> w1Row, w2Row;
    w1Row.reserve(n);
    w2Row.reserve(nNeurons);
    
    for (int i = 0; i < nNeurons; i++)
    {
        for (int j = 0; j < n; j++)
            w1Row.push_back(Statistics::getRandom(-0.1, 0.1, (i + 5 * j)));
        w1.push_back(w1Row);
        w1Row.clear();
    }
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < nNeurons; j++)
            w2Row.push_back(Statistics::getRandom(-0.1, 0.1, (i + 5 * j)));
        w2.push_back(w2Row);
        w2Row.clear();
    }
}

void SAMANN::initializeExitMatrixes()
{
    int m = X.getObjectCount();
    Y_is = ObjectMatrix(m);
    Y_pasl = ObjectMatrix(m);
    std::vector<double> YisRow, YpaslRow;
    YisRow.reserve(d);
    YpaslRow.reserve(nNeurons);
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < d; j++)
            YisRow.push_back(1.0);
        Y_is.addObject(DataObject(YisRow));
        
        for (int j = 0; j < nNeurons; j++)
            YpaslRow.push_back(1.0);
        Y_pasl.addObject(DataObject(YpaslRow));   
        
        YisRow.clear();
        YpaslRow.clear();
    }   
}

void SAMANN::initializeDeltaL()
{
    delta_L = ObjectMatrix(mTrain - 1);

    std::vector<double> deltaLRow;
    deltaLRow.reserve(mTrain);
    
    for (int i = 0; i < mTrain - 1; i++)
    {
        for (int j = 0; j < mTrain; j++)
            deltaLRow.push_back(0.1);
        delta_L.addObject(DataObject(deltaLRow));        
        deltaLRow.clear();
    }   
}
