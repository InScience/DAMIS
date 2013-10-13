///////////////////////////////////////////////////////////
//  SOM.cpp
//  Implementation of the Class SOM
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "SOM.h"
#include "Statistics.h"
#include "DistanceMetrics.h"
#include <float.h>
#include <cstdlib>


SOM::SOM(){

}

SOM::~SOM(){

}

/**
 * Constructs SOM object. Passed are k_x, k_y, e_hat
 */
SOM::SOM(int rows, int columns, int ehat){
    k_x = rows;
    k_y = columns;
    eHat = ehat;
}

/**
 * Constructor called from SOMMDS
 */
SOM::SOM(int rows, int columns, int eHat, ObjectMatrix X){

}

/**
 * Pure virtual method that calculates the projection
 */
ObjectMatrix SOM::getProjection(){
    int n = X.getObjectAt(0).getFeatureCount();
    int m = X.getObjectCount();
    ObjectMatrix M(k_x, k_y, n);
    ObjectMatrix M_w(m);
    std::vector<double> M_Matrix_Row;
    double alpha , win_dist, dist_ij, eta, h, tmp;
    int win_x, win_y;
    
    for (int i = 0; i < k_x; i++)
    {
        for (int j = 0; j < k_y; j++)
        {
            for (int k = 0; k < n; k++)
                M_Matrix_Row.push_back(Statistics::getRandom(-1.0, 1.0, (i + j + 5 * k)));
            M.addObjectTo(i, DataObject(M_Matrix_Row));
            M_Matrix_Row.clear();
        }
    }

    for (int e = 0; e < eHat; e++)
    {
        alpha = Max((double)(eHat + 1 - e) / eHat, 0.01);
        win_x = 0;
        win_y = 0;
        for (int l = 0; l < n; l++)
        {
            win_dist = DBL_MAX;
            for (int i = 0; i < k_x; i++)
            {
                for (int j = 0; j < k_y; j++)
                {
                    dist_ij = DistanceMetrics::getDistance(M.getObjectAt(i, j), X.getObjectAt(l), Euclidean);
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
                    for (int k = 1; k < n; k++)
                    {
                        eta = Max(abs(win_x - i), abs(win_x - i));
                        h = alpha / (alpha * eta + 1);
                        if (eta > Max(alpha * Max((double)k_x, (double)k_y), 1))
                            h = 0;
                        tmp = M.getObjectAt(i, j).getItems().at(k) + h * (X.getObjectAt(l).getItems().at(k) - M.getObjectAt(i, j).getItems().at(k));
                        M.getObjectAt(i, j).UpdateValue(k, tmp);
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
                dist_ij = DistanceMetrics::getDistance(M.getObjectAt(i, j), X.getObjectAt(l), Euclidean);
                if (dist_ij < win_dist)
                {
                    win_dist = dist_ij;
                    win_x = i;
                    win_y = j;
                }
            }
        }
        M_w.addObject(M.getObjectAt(win_x, win_y));
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

/**
 * Calculates SOM quantization error. Passed parameters are initial ObjectMAtrix
 * and neuron winner object matrix
 */
double SOM::getQuantizationError(){
    int m = X.getObjectCount();
    int r = nWinner.getObjectCount();
    double som_qe = 0.0, dist_li;
    
    for (int l = 0; l < m; l++)
    {
        for (int i = 0; i < r; i++)
            dist_li = DistanceMetrics::getDistance(nWinner.getObjectAt(i), X.getObjectAt(l), Euclidean);
        som_qe += dist_li;          
    }
    
    return som_qe;
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