///////////////////////////////////////////////////////////
//  SDS.cpp
//  Implementation of the Class SDS
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \class SDS
 *  \brief A class of methods and attributes for SDS algorithm.
 * 
 *  A relative MDS method realization
 */
#include "SDS.h"
#include "ShufleObjects.h"
#include "Projection.h"
#include "PCA.h"
#include "SMACOF.h"
#include "alglib/optimization.h"
#include "DistanceMetrics.h"
#include "AdditionalMethods.h"
#include "ObjectMatrix.h"
#include <float.h>
#include <fstream>
#include <cmath>

/** \class StaticData
 *  \brief A class of static attributes for passing data to alglib's static method.
 */
class StaticData {
public:
    static ObjectMatrix X_base;
    static ObjectMatrix Y_base;
    static ObjectMatrix X_new;
};

ObjectMatrix StaticData::X_base;
ObjectMatrix StaticData::Y_base;
ObjectMatrix StaticData::X_new;

SDS::SDS(){

}

SDS::~SDS(){

}

/*! \brief A default constructor
 * 
 * \param eps a smallest change of error in last iteration
 * \param maxIter a maximal number of iterations
 * \param dim a dimension of projection
 * \param baseVectInit a base vector initialization method
 * \param nOfBaseVect a number of basic vector for MDS projection
 * \param distMetrics a used distance metric (EUCLIDIAN is recommended)
 * 
 */
SDS::SDS(double eps, int maxIter, int dim, ProjectionEnum baseVectInit, int nOfBaseVect, DistanceMetricsEnum distMetrics){
    epsilon = eps;
    maxIteration = maxIter;
    d = dim;
    initMethod = baseVectInit;
    nb = nOfBaseVect;
    distMethod = distMetrics;
}

ObjectMatrix SDS::getProjection(){
    int m = X.getObjectCount();
    int step = 0, rest = 0;
    StaticData::X_base = ObjectMatrix(nb);
    StaticData::X_new = ObjectMatrix(m - nb);
    StaticData::Y_base = ObjectMatrix(nb);
    Y_new = ObjectMatrix(m - nb);
    ObjectMatrix proj(m);
    std::vector<int> index;
    index.reserve(m);

    switch (initMethod)
    {
        case 1: proj = Projection::projectMatrix(RAND, X);
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
        case 3: proj = Projection::projectMatrix(DISPERSION, X);
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
            StaticData::X_base.addObject(X.getObjectAt(index.at(i)));
        else
            StaticData::X_new.addObject(X.getObjectAt(index.at(i)));
    }

    PCA_ pca(StaticData::X_base, d);
    StaticData::Y_base = pca.getProjection();
    SMACOF smcf(epsilon, maxIteration, d, StaticData::X_base, StaticData::Y_base);
    StaticData::Y_base = smcf.getProjection();

    Initialize();

    getQN();

    Y.clearDataObjects();

    for (int i = 0; i < nb; i++)
        Y.addObject(StaticData::Y_base.getObjectAt(i));

    for (int i = 0; i < m - nb; i++)
        Y.addObject(Y_new.getObjectAt(i));

    return  Y;
}

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

    alglib::minlbfgscreate(m, Ynew, state);
    alglib::minlbfgssetcond(state, epsg, epsf, epsx, maxits);
    alglib::minlbfgsoptimize(state,  E_SDS, NULL, NULL);
    alglib::minlbfgsresults(state, Ynew, rep);

    Y_new = AdditionalMethods::alglib1DArrayToObjectMatrix(Ynew, d);
}

double SDS::getStress(){
    return MDS::getStress();

   /* int m = X.getObjectCount();
    double dist1 = 0.0, dist2 = 0.0;
    double distX = 0.0, distY = 0.0;

    for (int i = 0; i < m - nb - 1; i++)
        for (int j = i + 1; j < m - nb; j++)
        {
            distX = DistanceMetrics::getDistance(StaticData::X_new.getObjectAt(i), StaticData::X_new.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(Y_new.getObjectAt(i), Y_new.getObjectAt(j), EUCLIDEAN);
            dist1 += pow(distX - distY, 2);
        }

    for (int i = 0; i < nb - 1; i++)
        for (int j = 0; j < m - nb; j++)
        {
            distX = DistanceMetrics::getDistance(StaticData::X_base.getObjectAt(i), StaticData::X_new.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(StaticData::Y_base.getObjectAt(i), Y_new.getObjectAt(j), EUCLIDEAN);
            dist2 += pow(distX - distY, 2);
        }

    return dist1 + dist2;*/
}

void SDS::E_SDS(const alglib::real_1d_array &Ynew, double &func, alglib::real_1d_array &grad, void *ptr)
{
    double f1 = 0.0, f2 = 0.0, distX = 0.0, distY = 0.0;
    int d = StaticData::Y_base.getObjectAt(0).getFeatureCount();
    int sm = StaticData::X_new.getObjectCount();
    int nb = StaticData::X_base.getObjectCount();
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
            distX = DistanceMetrics::getDistance(StaticData::X_new.getObjectAt(i), StaticData::X_new.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(dd[i], dd[j], EUCLIDEAN);
            f1 += std::pow(distX - distY, 2);
        }
    }

    for (int i = 0; i < nb; i++)
    {
        for (int j = 0; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(StaticData::X_base.getObjectAt(i), StaticData::X_new.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(StaticData::Y_base.getObjectAt(i), dd[j], EUCLIDEAN);
            f2 += std::pow(distX - distY, 2);
        }
    }

    func = f1 + f2;

    for (int i = 0; i < sm - 1; i++)
    {
        grad[i] = 0.0;
        for (int j = i + 1; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(StaticData::X_new.getObjectAt(i), StaticData::X_new.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(dd[i], dd[j], EUCLIDEAN);
            if (distY != 0)
                grad[i] += (distX - distY) / distY;
        }
    }

    for (int i = 0; i < nb; i++)
    {
        for (int j = 0; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(StaticData::X_base.getObjectAt(i), StaticData::X_new.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(StaticData::Y_base.getObjectAt(i), dd[j], EUCLIDEAN);
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
            dist_ij = DistanceMetrics::getDistance(StaticData::X_base.getObjectAt(j), StaticData::X_new.getObjectAt(i), EUCLIDEAN);
            if (dist_ij < min_dist)
            {
                min_dist = dist_ij;
                closest_base = j;
            }
        }
        Y_new.addObject(StaticData::Y_base.getObjectAt(closest_base));
    }
}
