///////////////////////////////////////////////////////////
//  SOM.cpp
//  Implementation of the Class SOM
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \class SOM
    \brief A class of methods and attributes for SOM algorithm.
 */
#include "SOM.h"
#include "Statistics.h"
#include "DistanceMetrics.h"
#include <float.h>
#include <cstdlib>
#include <iostream>
#include "stdio.h"
#include "AdditionalMethods.h"
#include <algorithm>


SOM::SOM()
{

}

SOM::~SOM()
{

}

SOM::SOM(int rows, int columns, int ehat)
{
    k_x = rows;
    k_y = columns;
    eHat = ehat;
    X = ObjectMatrix(AdditionalMethods::inputDataFile);
    X.loadDataMatrix();
    returnWinners = false;
}

SOM::SOM(int rows, int columns, int ehat, ObjectMatrix x)
{
    k_x = rows;
    k_y = columns;
    eHat = ehat;
    X = x;
    returnWinners = true;
}

ObjectMatrix SOM::getProjection()
{
    int n = X.getObjectAt(0).getFeatureCount();
    int m = X.getObjectCount();
    ObjectMatrix *M  = new ObjectMatrix(k_x, k_y, n);
    ObjectMatrix M_w(m);
    std::vector<double> M_Matrix_Row;
    double alpha , win_dist, dist_ij, eta, h, tmp;
    int win_x, win_y;
    std::vector<std::string> possClasses;


    DataObject objXtmp, objMtmp;

    for (int i = 0; i < k_x; i++)
    {
        for (int j = 0; j < k_y; j++)
        {
            double dist = 0.0;
            double rnd;

            for (int k = 0; k < n; k++)
            {
                rnd = Statistics::getRandom(-10.0, 1.0);
                M->updateDataObject(i, j, k, rnd);
                dist += rnd*rnd;
            }

            double rootDist = sqrt(dist);
            objMtmp = M->getObjectAt(i, j);

            for (int k = 0; k < n; k++) //norm data in M matrix
                M->updateDataObject(i, j, k, float(objMtmp.getFeatureAt(k) / rootDist));
        }
    }

    for (int e = 0; e < eHat; e++)
    {
        alpha =  Max((double)(eHat + 1.0 - e) / (float) eHat, 0.01);

        for (int l = 0; l < m; l++)
        {
            win_dist = DBL_MAX;
            win_x = 0;
            win_y = 0;
            objXtmp = X.getObjectAt(l);

            for (int i = 0; i < k_x; i++)
            {
                for (int j = 0; j < k_y; j++)
                {
                    dist_ij = DistanceMetrics::getDistance(M->getObjectAt(i, j), objXtmp, EUCLIDEAN);
                    if (dist_ij < win_dist)
                    {
                        win_dist = dist_ij;
                        win_x = i;
                        win_y = j;
                    }
                }
            }
            for (int i = 0; i < k_x ; i++)
            {
                for (int j = 0 ; j < k_y ; j++)
                {
                    objMtmp = M->getObjectAt(i, j);
                    for (int k = 0; k < n; k++) // k=1
                    {
                        eta = Max(abs(win_x - i), abs(win_y - j));
                        h = (float)alpha / (alpha * eta + 1.);
                        if (eta > Max(alpha * Max((double)k_x, (double)k_y), 1.0))
                            h = 0.0;
                        tmp = objMtmp.getFeatureAt(k) + h * (objXtmp.getFeatureAt(k) - objMtmp.getFeatureAt(k));
                        M->updateDataObject(i, j, k, tmp);
                    }
                }

            }
        }
    }

    if (returnWinners == false)
        nWinner = X;

    std::vector<std::string> objClass;
    for (int l = 0; l < m; l++)
    {
        win_dist = DBL_MAX;
        win_x = 0;
        win_y = 0;
        objXtmp = X.getObjectAt(l);
        for (int i = 0; i < k_x; i++)
        {
            for (int j = 0; j < k_y; j++)
            {
                dist_ij = DistanceMetrics::getDistance(M->getObjectAt(i, j), objXtmp, EUCLIDEAN);

                if (dist_ij < win_dist)
                {
                    win_dist = dist_ij;
                    win_x = i;
                    win_y = j;
                }
            }
        }
        // std::string cls = std::to_string(win_x) + "-" + std::to_string(win_y);

        if (returnWinners == false)
            objClass.push_back(std::to_string(static_cast<long long>(win_x)) + "-" + std::to_string(static_cast<long long>(win_y)));
        else
            M_w.addObject(M->getObjectAt(win_x, win_y));
    }
    std::vector<std::string> diffObjClaseses;
    if (returnWinners == false)
    {
        diffObjClaseses = objClass;
        //remove dublicates
        std::sort(diffObjClaseses.begin(), diffObjClaseses.end());
        auto last = std::unique(diffObjClaseses.begin(), diffObjClaseses.end());
        diffObjClaseses.erase(last, diffObjClaseses.end());
        nWinner.setPrintClass(diffObjClaseses);


        for (int i = 0; i < m; i++) //setting object classes
        {
            for (int j = 0; j < diffObjClaseses.size(); j++)
            {
                if (objClass.at(i) == diffObjClaseses.at(j) )
                {
                    nWinner.updateDataObjectClass(i, j);
                    break;
                }
            }
        }
    }
    else
        nWinner = Different(M_w);

    return  nWinner;
}

double SOM::Max(double d1, double d2)
{
    if (d1 > d2)
        return d1;
    else
        return d2;
}

double SOM::getQuantizationError()
{
    int m = X.getObjectCount();
    int r = nWinner.getObjectCount();
    double som_qe = 0.0; //, dist_li = 0.0;

    DataObject objXtmp;

    for (int l = 0; l < m; l++)
    {
        //  dist_li =0.0;
        objXtmp = X.getObjectAt(l);
        for (int i = 0; i < r; i++)
            som_qe += DistanceMetrics::getDistance(nWinner.getObjectAt(i), objXtmp, EUCLIDEAN);
        // som_qe += dist_li;
    }

    return som_qe / m; //dalyba is m
}

double SOM::getStress()
{
    return SOM::getQuantizationError();
}

ObjectMatrix SOM::Different(ObjectMatrix M_w)
{
    ObjectMatrix M_ws;
    DataObject objTmp;
    int n = M_w.getObjectCount();
    int k = 0;
    for (int i = 0; i < n - 1; i++)
    {
        k = 0;
        objTmp = M_w.getObjectAt(i);
        for (int j = i + 1; j < n; j++)
        {
            if (objTmp.IsIdentical(M_w.getObjectAt(j)) == true)
                k++;
        }
        if (k == 0)
            M_ws.addObject(objTmp);
    }
    if (M_w.getObjectAt(n - 2).IsIdentical(M_w.getObjectAt(n - 1)) == true)
        M_ws.addObject(M_w.getObjectAt(n - 1));

    return M_ws;
}
