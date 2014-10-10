///////////////////////////////////////////////////////////
//  SAMANN.cpp
//  Implementation of the Class SAMANN
//  Created on:      07-Lie-2013 20:07:31
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \class SAMANN
    \brief A class of methods and attributes for SAMANN algorithm.
 */
#include "SAMANN.h"
#include "Statistics.h"
#include "DistanceMetrics.h"
#include "math.h"
#include "AdditionalMethods.h"
//#include <fstream>
//#include <iomanip>
#include <float.h>
#include <iostream>

SAMANN::SAMANN()
{

}

SAMANN::~SAMANN()
{

}

SAMANN::SAMANN(int m1, int nl, double e, int maxIter)
{
    X = ObjectMatrix(AdditionalMethods::inputDataFile);
    X.loadDataMatrix();
    this->tmpX = X;

    mTrain = m1;
    nNeurons = nl;
    eta = e;
    maxIteration = maxIter;
    d = 2;
    initializeProjectionMatrix();
    stressErrors.reserve(maxIter);
}

double SAMANN::getLambda()
{

    double temp = 0.0;
    int m = X.getObjectCount();
    DataObject objXi;
    for (int i = 0; i < m - 1; i++)
    {
        objXi =  X.getObjectAt(i);
        for (int j = i + 1; j < m; j++)
            temp += DistanceMetrics::getDistance(objXi, X.getObjectAt(j), EUCLIDEAN);
    }
    return 1.0 / temp;
}

ObjectMatrix SAMANN::getProjection()
{

    int n = X.getObjectAt(0).getFeatureCount();
    int m = X.getObjectCount();
    double ddelta_L[mTrain][d + 1];
    double delta_tarp[mTrain];
    double ddelta_tarp[mTrain];
    double tarp = 0.0, tarp2 = 0.0, lambda, tmp, distXp, distYis, bestStress = 0.0, currStress = 0.0;
    std::vector<std::vector<double> > best_w1;
    std::vector<std::vector<double> > best_w2;
    initializeWeights();   // w1, w2
    NormalizeX();
    initializeExitMatrixes();   // Y_pasl, Y_is
    initializeDeltaL();    // delta_L

    std::vector<double> w1Row, w2Row;
    w1Row.reserve(n + 1);
    w2Row.reserve(nNeurons + 1);
    for (int i = 0; i < nNeurons + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
            w1Row.push_back(0.0);
        best_w1.push_back(w1Row);
        w1Row.clear();
    }

    for (int i = 0; i < d + 1; i++)
    {
        for (int j = 0; j < nNeurons + 1; j++)
            w2Row.push_back(0.0);
        best_w2.push_back(w2Row);
        w2Row.clear();
    }

    lambda = getLambda();

    for (int i = 0; i < mTrain; i++)
    {
        for (int j = 0; j < d + 1; j++)
            ddelta_L[i][j] = 0.0;
        delta_tarp[i] = 0.0;
        ddelta_tarp[i] = 0.0;
    }

    bestStress = getStress();

    DataObject objXMiu, objXpMiu, objXpNiu, objY_paslMiu, objY_paslNiu, objY_isMiu, objY_isNiu, objXNiuu, objY_paslNiuu;

    for (int iter = 0; iter < maxIteration; iter++)
    {
        getXp();
        for (int miu = 0; miu < mTrain - 1; miu++)
        {
            objXpMiu = Xp.getObjectAt(miu);
            objY_paslMiu = Y_pasl.getObjectAt(miu);
            objY_isMiu = Y_is.getObjectAt(miu);

            for (int niu = miu + 1; niu < mTrain; niu++)
            {
                objXpNiu = Xp.getObjectAt(niu);
                objY_paslNiu = Y_pasl.getObjectAt(niu);
                objY_isNiu = Y_is.getObjectAt(niu);

                for (int j = 1; j <= nNeurons; j++)
                {
                    tarp = 0.0;
                    tarp2 = 0.0;
                    for (int k = 0; k < n + 1; k++)
                    {
                        tarp += w1[j].at(k) * objXpMiu.getFeatureAt(k);
                        tarp2 += w1[j].at(k) * objXpNiu.getFeatureAt(k);
                    }

                    Y_pasl.updateDataObject(miu, j, 1.0 / (1 + exp(-1 * tarp)));
                    Y_pasl.updateDataObject(niu, j, 1.0 / (1 + exp(-1 * tarp2)));
                }

                for (int j = 1; j <= d; j++)
                {
                    tarp = 0.0;
                    tarp2 = 0.0;
                    for (int k = 0; k <= nNeurons; k++)
                    {
                        tarp += w2[j].at(k) * objY_paslMiu.getFeatureAt(k);
                        tarp2 += w2[j].at(k) * objY_paslNiu.getFeatureAt(k);
                    }
                    Y_is.updateDataObject(miu, j, 1.0 / (1 + exp(-1 * tarp)));
                    Y_is.updateDataObject(niu, j, 1.0 / (1 + exp(-1 * tarp2)));
                }

                distXp = DistanceMetrics::getDistance(objXpMiu, objXpNiu, EUCLIDEAN);
                distYis = DistanceMetrics::getDistance(objY_isMiu, objY_isNiu, EUCLIDEAN);

                if (distXp == 0)
                    distXp = 0.000001;
                if (distYis == 0)
                    distYis = 0.000001;

                for (int k = 1; k <= d; k++)
                {
                    tmp = -2 * lambda * ((distXp - distYis) / (distXp * distYis)) * (objY_isMiu.getFeatureAt(k) - objY_isNiu.getFeatureAt(k));
                    delta_L.updateDataObject(miu, niu, tmp);
                    ddelta_L[miu][k] = delta_L.getObjectAt(miu).getFeatureAt(niu) * (1 - objY_isMiu.getFeatureAt(k)) * objY_isMiu.getFeatureAt(k);
                    ddelta_L[niu][k] = delta_L.getObjectAt(miu).getFeatureAt(niu) * (1 - objY_isNiu.getFeatureAt(k)) * objY_isNiu.getFeatureAt(k);
                    for (int j = 1; j <= nNeurons; j++)
                        w2[k][j] = -1. * eta * (ddelta_L[miu][k] * objY_paslMiu.getFeatureAt(j) - ddelta_L[niu][k] * objY_paslNiu.getFeatureAt(j)) + w2[k][j];
                }

                for (int j = 1; j <= nNeurons; j++)
                {
                    delta_tarp[miu] = 0;
                    delta_tarp[niu] = 0;

                    for (int k = 1; k <= d; k++)
                    {
                        delta_tarp[miu] += ddelta_L[miu][k] * w2[k][j];
                        delta_tarp[niu] += ddelta_L[niu][k] * w2[k][j];
                    }

                    ddelta_tarp[miu] = delta_tarp[miu] * (1. - objY_paslMiu.getFeatureAt(j)) * objY_paslMiu.getFeatureAt(j);
                    ddelta_tarp[niu] = delta_tarp[niu] * (1. - objY_paslNiu.getFeatureAt(j)) * objY_paslNiu.getFeatureAt(j);

                    for (int k = 1; k < n + 1; k++)
                        w1[j][k] = -1. * eta * (ddelta_tarp[miu] * objXpMiu.getFeatureAt(k) - ddelta_tarp[niu] * objXpNiu.getFeatureAt(k)) + w1[j][k];
                }
            }
        }

        //  DataObject objXNiuu, objY_paslNiuu;

        for (int niuu = 0; niuu < m; niuu++)
        {
            objXNiuu = X.getObjectAt(niuu);
            objY_paslNiuu = Y_pasl.getObjectAt(niuu);

            for (int j = 1; j <= nNeurons; j++)
            {
                tarp = 0.0;
                for (int k = 0; k < n + 1; k++)
                    tarp += w1[j].at(k) * objXNiuu.getFeatureAt(k);
                Y_pasl.updateDataObject(niuu, j, 1.0 / (1 + exp(-1 * tarp)));
            }

            for (int j = 1; j <= d; j++)
            {
                tarp2 = 0.0;
                for (int k = 0; k <= nNeurons; k++)
                    tarp2 += w2[j].at(k) * objY_paslNiuu.getFeatureAt(k);
                Y_is.updateDataObject(niuu, j, 1.0 / (1 + exp(-1 * tarp2)));
            }
        }

        currStress = getStress();
        if (currStress < bestStress)
        {
            for (int i = 1; i <= nNeurons; i++)
                for (int j = 0; j < n + 1; j++)
                    best_w1[i][j] = w1.at(i).at(j);

            for (int i = 0; i < d + 1; i++)
                for (int j = 0; j < nNeurons + 1; j++)
                    best_w2[i][j] = w2.at(i).at(j);

            bestStress = currStress;
        }
        stressErrors.push_back(currStress);
    }  // iteraciju pabaiga

    for (int miu = 0; miu < m; miu++)
    {
        objXMiu = X.getObjectAt(miu);
        objY_paslMiu = Y_pasl.getObjectAt(miu);
        for (int j = 1; j < nNeurons + 1; j++)
        {
            tarp = 0.0;
            for (int k = 0; k < n + 1; k++)
                tarp += best_w1[j].at(k) * objXMiu.getFeatureAt(k);
            Y_pasl.updateDataObject(miu, j, 1.0 / (1 + exp(-1 * tarp)));
        }
        for (int j = 1; j <= d; j++)
        {
            tarp = 0.0;
            for (int k = 0; k <= nNeurons; k++)
                tarp += best_w2[j].at(k) * objY_paslMiu.getFeatureAt(k);
            Y_is.updateDataObject(miu, j, 1.0 / (1 + exp(-1 * tarp)));
        }
    }

    Y = ObjectMatrix(m);
    std::vector<double> Yrow;
    Yrow.reserve(d);
    for (int i = 0; i < m; i++)
    {
        objY_isNiu = Y_is.getObjectAt(i);
        for (int j = 1; j <= d; j++)
            Yrow.push_back(objY_isNiu.getFeatureAt(j));
        Y.addObject(DataObject(Yrow), tmpX.getObjectAt(i).getClassLabel());
       // std::cout << tmpX.getObjectAt(i).getClassLabel() << std::endl;
        Yrow.clear();
    }

    Y.setPrintClass(tmpX.getStringClassAttributes());

    return Y;
}

double SAMANN::getMax()
{
    int m = X.getObjectCount();
    double max = DBL_MIN, dist;
    DataObject objXi;
    for (int i = 0; i < m - 1; i++)
    {
        objXi = X.getObjectAt(i);
        for (int j = i + 1; j < m; j++)
        {
            dist = DistanceMetrics::getDistance(objXi, X.getObjectAt(j), EUCLIDEAN);
            if (dist > max)
                max = dist;
        }
    }
    return max;
}

void SAMANN::NormalizeX()
{
    double max = getMax();
    double value;
    int m = X.getObjectCount();
    int n = X.getObjectAt(0).getFeatureCount();
    std::vector<double> Xrow;
    Xrow.reserve(n + 1);
    ObjectMatrix Xtmp(m);
    DataObject objXi;

    for (int i = 0; i < m; i++)
    {
        Xrow.push_back(1.0);
        objXi = X.getObjectAt(i);
        for (int j = 0; j < n; j++)
        {
            value = objXi.getFeatureAt(j) / max;
            Xrow.push_back(value);
        }
        Xtmp.addObject(DataObject(Xrow));
        Xrow.clear();
    }
    X = Xtmp;
}

void SAMANN::getXp()
{
    int m = X.getObjectCount(), i = 0, k = 0, index = 0;
    Xp = ObjectMatrix(mTrain);
    double r = Statistics::getRandom(1, m);
    DataObject dObject;
    index = static_cast<int>(r);
    while (k < m)
    {
        dObject = X.getObjectAt(index);
        if (isIdentical(dObject) == false)
        {
            Xp.addObject(dObject);
            i++;
            if (i >= mTrain)
                break;
        }
        index = (index + 1) % m;
        k++;
    }

    if (i < mTrain)
    {
        index = 0;
        while (i < mTrain)
        {
            dObject = X.getObjectAt(index);
            Xp.addObject(dObject);
            i++;
            index = (index + 1) % m;
        }
    }
}

bool SAMANN::isIdentical(DataObject obj)
{
    bool ats = false;
    int n = Xp.getObjectCount();
    int m = obj.getFeatureCount();
    int k = 0;

    DataObject objXi;

    for (int i = 0; i < n; i++)
    {
        k = 0;
        objXi = Xp.getObjectAt(i);
        for (int j = 0; j < m; j++)
            if (obj.getFeatureAt(j) == objXi.getFeatureAt(j))
                k++;
        if (k == m)
        {
            ats = true;
            break;
        }
    }
    return ats;
}

double SAMANN::getStress()
{
    double tarp1 = 0.0, tarp2 = 0.0, distX, distY, tmp;
    int m = X.getObjectCount();
    DataObject objXMiu, objY_isMiu;

    for (int miu = 0; miu < m - 1; miu++)
    {
        objXMiu = X.getObjectAt(miu);
        objY_isMiu = Y_is.getObjectAt(miu);
        for (int niu = miu + 1; niu < m; niu++)
        {
            distX = DistanceMetrics::getDistance(objXMiu, X.getObjectAt(niu), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(objY_isMiu, Y_is.getObjectAt(niu), EUCLIDEAN);
            tarp1 += distX;
            if (distX == 0)
                distX = 0.000001;

            tmp = distX - distY;
            tarp2 += tmp * tmp / distX;
        }
    }
    return (1.0 / tarp1) * tarp2;
}

void SAMANN::initializeWeights()
{
    int n = X.getObjectAt(0).getFeatureCount();
    std::vector<double> w1Row, w2Row;
    w1Row.reserve(n + 1);
    w2Row.reserve(nNeurons + 1);

    for (int i = 0; i < nNeurons + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
            w1Row.push_back(Statistics::getRandom(-1, 1));
        w1.push_back(w1Row);
        w1Row.clear();
    }

    for (int i = 0; i < d + 1; i++)
    {
        for (int j = 0; j < nNeurons + 1; j++)
            w2Row.push_back(Statistics::getRandom(-1, 1));
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
    YisRow.reserve(d + 1);
    YpaslRow.reserve(nNeurons + 1);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < d + 1; j++)
            YisRow.push_back(1.0);
        Y_is.addObject(DataObject(YisRow));

        for (int j = 0; j < nNeurons + 1; j++)
            YpaslRow.push_back(1.0);
        Y_pasl.addObject(DataObject(YpaslRow));

        YisRow.clear();
        YpaslRow.clear();
    }
}

void SAMANN::initializeDeltaL()
{
    delta_L = ObjectMatrix(mTrain);

    std::vector<double> deltaLRow;
    deltaLRow.reserve(mTrain);

    for (int i = 0; i < mTrain; i++)
    {
        for (int j = 0; j < mTrain; j++)
            deltaLRow.push_back(0.1);
        delta_L.addObject(DataObject(deltaLRow));
        deltaLRow.clear();
    }
}

std::vector<double> SAMANN::getStressErrors()
{
    return stressErrors;
}
