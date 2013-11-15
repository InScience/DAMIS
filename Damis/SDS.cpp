///////////////////////////////////////////////////////////
//  SDS.cpp
//  Implementation of the Class SDS
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "SDS.h"
#include "ShufleObjects.h"
#include "Projection.h"
#include "PCA.h"
#include "SMACOF.h"
#include "alglib/optimization.h"
#include "DistanceMetrics.h"
#include "AdditionalMethods.h"
#include <float.h>
#include <fstream>
#include <cmath>

SDS::SDS(){

}

SDS::~SDS(){

}

/**
 * Constructor
 */
SDS::SDS(double eps, int maxIter, int dim, ProjectionEnum baseVectInitt, int nofBaseVect, DistanceMetricsEnum distMetrics){
    epsilon = eps;
    maxIteration = maxIter;
    d = dim;
    initMethod = baseVectInitt;
    nb = nofBaseVect;
    distMethod = distMetrics;
}


/**
 * Pure virtual method that calculates the projection
 */
ObjectMatrix SDS::getProjection(){
    int m = X.getObjectCount();
    int step = 0, rest = 0;
    X_base = ObjectMatrix(nb);
    X_new = ObjectMatrix(m - nb);
    Y_base = ObjectMatrix(nb);
    Y_new = ObjectMatrix(m - nb);
    ObjectMatrix proj(m);
    std::vector<int> index;
    index.reserve(m);
    
    switch (initMethod)
    {
        case 1: proj = Projection::projectMatrix(DISPERSION, X);
                index = ShufleObjects::shufleObjectMatrix(BUBLESORTDSC, proj);
                step = m / nb;
                for (int i = 0; i < nb; i++)
                {
                    rest = index.at(i);
                    index[i] = index.at(i * step);
                    index[i * step] = rest;
                }
                break;
        case 2: proj = Projection::projectMatrix(PCA, X);
                index = ShufleObjects::shufleObjectMatrix(BUBLESORTDSC, proj);
                step = m / nb;
                for (int i = 0; i < nb; i++)
                {
                    rest = index.at(i);
                    index[i] = index.at(i * step);
                    index[i * step] = rest;
                }
                break;
        default: proj = Projection::projectMatrix(DISPERSION, X);
                index = ShufleObjects::shufleObjectMatrix(RANDOM, proj);
                break;
    }
    
    for (int i = 0; i < m; i++)
    {
        if (i < nb)
            X_base.addObject(X.getObjectAt(index.at(i)));
        else
            X_new.addObject(X.getObjectAt(index.at(i)));
    }
    
    PCA::PCA pca(X_base, d);
    Y_base = pca.getProjection();
    SMACOF smcf(epsilon, maxIteration, d, X_base, Y_base);
    Y_base = smcf.getProjection();
    
    Initialize();
    
    getQN();
    
    Y.clearDataObjects();
    
    for (int i = 0; i < nb; i++)
        Y.addObject(Y_base.getObjectAt(i));
        
    for (int i = 0; i < m - nb; i++)
        Y.addObject(Y_new.getObjectAt(i));
    
    return  Y;
}

/**
 * Computes Quasi Newton in external method library
 */
void SDS::getQN(){
    int m = Y_new.getObjectCount();
    alglib::minlbfgsstate state;
    alglib::minlbfgsreport rep;
    double epsg = epsilon;
    double epsf = 0;
    double epsx = 0;
    alglib::ae_int_t maxits = maxIteration;
    alglib::real_1d_array Ynew;
    Ynew = AdditionalMethods::ObjectMatrixTo1DArray(Y_new);
      
    X_new.saveDataMatrix("xnew.arff");
    X_base.saveDataMatrix("xbase.arff");
    Y_base.saveDataMatrix("ybase.arff");
    Y_new.saveDataMatrix("ynew.arff");
    
    alglib::minlbfgscreate(m, Ynew, state);
    alglib::minlbfgssetcond(state, epsg, epsf, epsx, maxits);
    alglib::minlbfgsoptimize(state,  E_SDS, NULL, NULL);
    alglib::minlbfgsresults(state, Ynew, rep);
    
    std::ofstream f("test.txt");
    f<<Ynew(0)<< " "<<Ynew(1)<<std::endl;    
    f.close();
    
    Y_new = AdditionalMethods::alglib1DArrayToObjectMatrix(Ynew, d);
}

/**
 * Computes MDS stress function
 */
double SDS::getStress(){
    int m = X.getObjectCount();
    double dist1 = 0.0, dist2 = 0.0; 
    double distX = 0.0, distY = 0.0;
       
    for (int i = 0; i < m - nb; i++)
        for (int j = i + 1; j < m - nb; j++)
        {
            distX = DistanceMetrics::getDistance(X_new.getObjectAt(i), X_new.getObjectAt(j), Euclidean);
            distY = DistanceMetrics::getDistance(Y_new.getObjectAt(i), Y_new.getObjectAt(j), Euclidean);
            dist1 += pow(distX - distY, 2);
        }
    
    for (int i = 0; i < nb; i++)
        for (int j = 0; j < m - nb; j++)
        {
            distX = DistanceMetrics::getDistance(X_base.getObjectAt(i), X_new.getObjectAt(j), Euclidean);
            distY = DistanceMetrics::getDistance(Y_base.getObjectAt(i), Y_new.getObjectAt(j), Euclidean);
            dist2 += pow(distX - distY, 2);
        }
    
    return dist1 + dist2;
}

void SDS::E_SDS(const alglib::real_1d_array &Ynew, double &func, alglib::real_1d_array &grad, void *ptr)
{
    double f1 = 0.0, f2 = 0.0, distX = 0.0, distY = 0.0;
    ObjectMatrix Xnew("xnew.arff");
    Xnew.loadDataMatrix();
    ObjectMatrix Xbase("xbase.arff");
    Xbase.loadDataMatrix();
    ObjectMatrix Ybase("ybase.arff");
    Ybase.loadDataMatrix();
    int d = Ybase.getObjectAt(0).getFeatureCount();
    int sm = Xnew.getObjectCount();
    int nb = Xbase.getObjectCount();
    std::vector<double> items;
    items.reserve(d);
    DataObject dd[sm];
    
    for (int i = 0; i < sm; i++)
    {
        for (int j = 0; j < d; j++)
            items.push_back(Ynew[d * i + j]);
        dd[i] = DataObject(items);
        items.clear();
    }
    
    for (int i = 0; i < sm - 1; i++)
    {   
        for (int j = i + 1; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(Xnew.getObjectAt(i), Xnew.getObjectAt(j), Euclidean);
            distY = DistanceMetrics::getDistance(dd[i], dd[j], Euclidean);
            f1 += std::pow(distX - distY, 2);
        }
    }    
    
    for (int i = 0; i < nb; i++)
    {
        for (int j = 0; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(Xbase.getObjectAt(i), Xnew.getObjectAt(j), Euclidean);
            distY = DistanceMetrics::getDistance(Ybase.getObjectAt(i), dd[j], Euclidean);
            f2 += std::pow(distX - distY, 2);
        }
    }
    
    func = f1 + f2;
    
    for (int i = 0; i < sm - 1; i++)
    {
        grad[i] = 0.0;
        for (int j = i + 1; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(Xnew.getObjectAt(i), Xnew.getObjectAt(j), Euclidean);
            distY = DistanceMetrics::getDistance(dd[i], dd[j], Euclidean);
            if (distY != 0)
                grad[i] += (distX - distY) / distY;
        }
    }
    
    for (int i = 0; i < nb; i++)
    {
        for (int j = 0; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(Xbase.getObjectAt(i), Xnew.getObjectAt(j), Euclidean);
            distY = DistanceMetrics::getDistance(Ybase.getObjectAt(i), dd[j], Euclidean);
            if (distY != 0)
                grad[j] += (distX - distY) / distY;
        }
    }
}

void SDS::Initialize()
{
    int m = X.getObjectCount();
    int closest_base = 0;
    double min_dist = DBL_MAX;
    double dist_ij;
    
    for (int i = 0; i < m - nb; i++)
    {
        min_dist = DBL_MAX;
        closest_base = 0;
        for (int j = 0; j < nb; j++)
        {
            dist_ij = DistanceMetrics::getDistance(X_base.getObjectAt(j), X_new.getObjectAt(i), Euclidean);
            if (dist_ij < min_dist)
            {
                min_dist = dist_ij;
                closest_base = j;
            }
        }
        Y_new.addObject(Y_base.getObjectAt(closest_base));
    }
}
