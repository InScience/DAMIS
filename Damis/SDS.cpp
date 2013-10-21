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
#include <float.h>

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
    int n = X.getObjectAt(0).getFeatureCount();
    int step = 0, rest = 0;
    X_base = ObjectMatrix(nb, n);
    X_new = ObjectMatrix(m - nb, n);
    Y_base = ObjectMatrix(nb, d);
    Y_new = ObjectMatrix(m - nb, d);
    ObjectMatrix proj(m, 1);
    std::vector<int> index;
    index.reserve(m);
    
    switch (initMethod)
    {
        case 1: proj = Projection::projectMatrix(DISPERSION, X);
                index = ShufleObjects::shufleObjectMatrix(BUBLESORTDSC, proj);
                step = m % nb;
                for (int i = 0; i < nb; i++)
                {
                    rest = index.at(i);
                    index[i] = index.at(i * step);
                    index[i * step] = rest;
                }
                break;
        case 2: proj = Projection::projectMatrix(PCA, X);
                index = ShufleObjects::shufleObjectMatrix(BUBLESORTDSC, proj);
                step = m % nb;
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
        if (i <= nb)
            X_base.addObject(X.getObjectAt(index.at(i)));
        else
            X_new.addObject(X.getObjectAt(index.at(i)));
    }
    
    PCA::PCA pca(X_base, d);
    Y_base = pca.getProjection();
    SMACOF smcf(epsilon, maxIteration, d, X_base, Y_base);
    Y_base = smcf.getProjection();
    
    Initialize();
    
    for (int i = 0; i < m - nb; i++)
    {
        
        
    }
    
    return  Y;
}


/**
 * Computes Quasi Newton in external method library
 */
void SDS::getQN(){
    int m = Y_new.getObjectCount();
    alglib::minlbfgsstate state;
    alglib::minlbfgsreport rep;
    double epsg = 0.0000000001;
    double epsf = 0;
    double epsx = 0;
    alglib::ae_int_t maxits = 10;
    alglib::real_1d_array Ynew;
    Ynew.setlength(d);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < d; j++)
            Ynew[j] = Y_new.getObjectAt(i).features.at(j);
        alglib::minlbfgscreate(1, Ynew, state);
        alglib::minlbfgssetcond(state, epsg, epsf, epsx, maxits);
        //alglib::minlbfgsoptimize(state, E_SDS);
        alglib::minlbfgsresults(state, Ynew, rep);
    }

}

/**
 * Computes MDS stress function
 */
double SDS::getStress(){
    int m = X.getObjectCount();
    int sm = m - nb;  // new
    int sf = nb;      // baziniai
    double dist1 = 0.0, dist2 = 0.0; 
    double distX = 0.0, distY = 0.0;
       
    for (int i = 0; i < sm - 1; i++)
        for (int j = i + 1; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(X_new.getObjectAt(i), X_new.getObjectAt(j), Euclidean);
            distY = DistanceMetrics::getDistance(Y_new.getObjectAt(i), Y_new.getObjectAt(j), Euclidean);
            dist1 += pow(distX - distY, 2);
        }
    
    for (int i = 0; i < sf; i++)
    {
        for (int j = 0; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(X_base.getObjectAt(i), X_new.getObjectAt(j), Euclidean);
            distY = DistanceMetrics::getDistance(Y_base.getObjectAt(i), Y_new.getObjectAt(j), Euclidean);
            dist2 += pow(distX - distY, 2);
        }
    }
    
    return dist1 + dist2;
}

void SDS::E_SDS(const alglib::real_1d_array &Ynew, double &func, alglib::real_1d_array &grad, void *ptr)
{
    func = 100*pow(Ynew[0]+3,4) + pow(Ynew[1]-3,4);
    grad[0] = 400*pow(Ynew[0]+3,3);
    grad[1] = 4*pow(Ynew[1]-3,3);
}

/**
 * Converts data object to datatype required by external method
 */
void SDS::toDataType(){
    

}


/**
 * Converts to ObjectMatrix result that is provided by external library.
 */
void SDS::fromDataType(){

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
        for (int j = 0; j < nb; j++)
        {
            dist_ij = DistanceMetrics::getDistance(X_base.getObjectAt(j), X_new.getObjectAt(i), Euclidean);
            if (dist_ij < min_dist)
            {
                min_dist = dist_ij;
                closest_base = j;
            }
        }
        Y_new.addObject(X_base.getObjectAt(closest_base));
    }
}
