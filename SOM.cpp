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


SOM::SOM(){

}

SOM::~SOM(){

}

SOM::SOM(int rows, int columns, int ehat){
    k_x = rows;
    k_y = columns;
    eHat = ehat;
}

SOM::SOM(int rows, int columns, int ehat, ObjectMatrix x){
    k_x = rows;
    k_y = columns;
    eHat = ehat;
    X = x;
}

ObjectMatrix SOM::getProjection(){
    int n = X.getObjectAt(0).getFeatureCount();
    int m = X.getObjectCount();
    ObjectMatrix *M  = new ObjectMatrix(k_x, k_y, n);
    ObjectMatrix M_w(m);
    std::vector<double> M_Matrix_Row;
    double alpha , win_dist, dist_ij, eta, h, tmp;
    int win_x, win_y;

    for (int i = 0; i < k_x; i++)
    {
        for (int j = 0; j < k_y; j++)
        {
            for (int k = 0; k < n; k++)
                M->updateDataObject(i, j, k, Statistics::getRandom(-1.0, 1.0, (i + j + 5 * k)));
        }
    }

    for (int e = 0; e < eHat; e++)
    {
        alpha = Max((double)(eHat + 1 - e) / eHat, 0.01);
        win_x = 0;
        win_y = 0;
        for (int l = 0; l < m; l++)
        {
            win_dist = DBL_MAX;
            for (int i = 0; i < k_x; i++)
            {
                for (int j = 0; j < k_y; j++)
                {
                    dist_ij = DistanceMetrics::getDistance(M->getObjectAt(i, j), X.getObjectAt(l), EUCLIDEAN);
                    if (dist_ij < win_dist)
                    {
                        win_dist = dist_ij;
                        win_x = i;
                        win_y = j;
                    }
                }
            }
            for (int i = 0; i < k_x; i++)
            {
                for (int j = 0; j < k_y; j++)
                {
                    for (int k = 0; k < n; k++) // k=1
                    {
                        eta = Max(abs(win_x - i), abs(win_y - i));
                        h = alpha / (alpha * eta + 1);
                        if (eta > Max(alpha * Max((double)k_x, (double)k_y), 1))
                            h = 0;
                        tmp = M->getObjectAt(i, j).getFeatureAt(k) + h * (X.getObjectAt(l).getFeatureAt(k) - M->getObjectAt(i, j).getFeatureAt(k));
                        M->updateDataObject(i, j, k, tmp);
                    }
                }
            }
        }
    }

    win_x = 0;
    win_y = 0;

    for (int l = 0; l < m; l++)
    {
        win_dist = DBL_MAX;
        for (int i = 0; i < k_x; i++)
        {
            for (int j = 0; j < k_y; j++)
            {
                dist_ij = DistanceMetrics::getDistance(M->getObjectAt(i, j), X.getObjectAt(l), EUCLIDEAN);
                if (dist_ij < win_dist)
                {
                    win_dist = dist_ij;
                    win_x = i;
                    win_y = j;
                }
            }
        }
        M_w.addObject(M->getObjectAt(win_x, win_y));
    }
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

double SOM::getQuantizationError(){
    int m = X.getObjectCount();
    int r = nWinner.getObjectCount();
    double som_qe = 0.0, dist_li = 0.0;

    for (int l = 0; l < m; l++)
    {
      //  dist_li =0.0;
        for (int i = 0; i < r; i++)
            som_qe = DistanceMetrics::getDistance(nWinner.getObjectAt(i), X.getObjectAt(l), EUCLIDEAN);
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
    int n = M_w.getObjectCount();
    int k = 0;
    for (int i = 0; i < n - 1; i++)
    {
        k = 0;
        for (int j = i + 1; j<n; j++)
        {
            if (M_w.getObjectAt(i).IsIdentical(M_w.getObjectAt(j)) == true)
                k++;
        }
        if (k == 0)
            M_ws.addObject(M_w.getObjectAt(i));
    }
    if (M_w.getObjectAt(n - 2).IsIdentical(M_w.getObjectAt(n - 1)) == true)
        M_ws.addObject(M_w.getObjectAt(n - 1));

    return M_ws;
}
