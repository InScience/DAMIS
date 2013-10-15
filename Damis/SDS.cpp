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
    ObjectMatrix Y_base(nb, d);
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
    
    return  Y;
}


/**
 * Computes Quasi Newton in external method library
 */
void SDS::getQN(){

}


/**
 * Computes MDS stress function
 */
double SDS::getStress(){

	return 0;
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
