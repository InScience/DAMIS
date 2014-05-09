///////////////////////////////////////////////////////////
//  SDS.cpp
//  Implementation of the Class SDS
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \class SDS
    \brief A class of methods and attributes for SDS algorithm.
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
//#include <fstream>
#include <cmath>
#include <iostream>

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

SDS::SDS(double eps, int maxIter, int dim, ProjectionEnum baseVectInit, int nofBaseVect, DistanceMetricsEnum distMetrics):MDS(eps, maxIter, dim){
    X = ObjectMatrix(AdditionalMethods::inputDataFile);
    X.loadDataMatrix();
    epsilon = eps;
    maxIteration = maxIter;
  //  d = dim;
    initMethod = baseVectInit;
    nb = nofBaseVect;
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
    std::vector<unsigned int> index;
    index.reserve(m);

    switch (initMethod)
    {
        case 1: proj = Projection::projectMatrix(RAND, X);
                break;
        case 2: proj = Projection::projectMatrix(PCA, X);
                break;
        case 3: proj = Projection::projectMatrix(DISPERSION, X);
                break;
        default: proj = Projection::projectMatrix(DISPERSION, X);
                break;
    }

    index = ShufleObjects::shufleObjectMatrix(BUBLESORTDSC, proj); //works slow
    step = m / nb;
    for (int i = 0; i < nb; i++)
    {
        rest = index.at(i);
        index.at(i) = index.at(i * step);
        index.at(i * step) = rest;
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

    Initialize(); // get the nearest

    Y.clearDataObjects();

    for (int i = 0; i < nb; i++)
        Y.addObject(StaticData::Y_base.getObjectAt(i));

//sudedam tai kas grazinama is QN
ObjectMatrix tmpX;
//ObjectMatrix retMat;
    for (int i = 0; i < m - nb; i++) //redo slow call and much more
        {
            //StaticData::X_new.clearDataObjects();
            tmpX.addObject(X.getObjectAt(index.at(nb + i)));
            StaticData::X_new = tmpX;

           // StaticData::X_new.addObject(X.getObjectAt(index.at(nb + i)));
           // tmpY.addObject(Y_new.getObjectAt(i));
            //std::cout << tmpY.getObjectAt(0).getFeatureAt(0) <<" " << tmpY.getObjectAt(0).getFeatureAt(1) << std::endl;
            //std::cout << i << std::endl;
           // retMat = getQN(tmpY);
            Y.addObject(getQN(Y_new.getObjectAt(i))) ;//retMat.getObjectAt(0));
         //   tmpY.clearDataObjects();
            tmpX.clearDataObjects();
        }
    return  Y;
}

DataObject SDS::getQN(DataObject Yqn)
{
    int m = 1; // number of objects that will be passed to Newton
    alglib::minlbfgsstate state;
    alglib::minlbfgsreport rep;
    double epsg = epsilon;
    double epsf = 0;
    double epsx = 0;
    alglib::ae_int_t maxits = maxIteration;
    alglib::real_1d_array Ynew;
    Ynew = AdditionalMethods::DataObjectTo1DArray(Yqn);

    alglib::minlbfgscreate(m, Ynew, state);
    alglib::minlbfgssetcond(state, epsg, epsf, epsx, maxits);
    alglib::minlbfgsoptimize(state,  E_SDS, NULL, NULL);
    alglib::minlbfgsresults(state, Ynew, rep);

    return AdditionalMethods::alglib1DArrayToDataObject(Ynew);
}

/*double SDS::getStress(){
    return DimReductionMethod::getStress();

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

    return dist1 + dist2;
}*/

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

    double tmp;

    for (int i = 0; i < d * sm; i++)
        grad[i] = 0.0;

    for (int i = 0; i < sm ; i++)
    {
        for (int j = 0; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(StaticData::X_new.getObjectAt(i), StaticData::X_new.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(dd[i], dd[j], EUCLIDEAN);
            tmp = distX - distY;
            f1 += tmp * tmp;
            if (distY != 0)
            {
                for (int  k = 0; k < d; k++)
                {
                    grad[j + k] += 2 * (distX - distY) / distY * (Ynew[d * i + k] - Ynew[d * j + k]);
                }
            }
        }
    }

    for (int i = 0; i < nb; i++)
    {
        for (int j = 0; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(StaticData::X_base.getObjectAt(i), StaticData::X_new.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(StaticData::Y_base.getObjectAt(i), dd[j], EUCLIDEAN);
            tmp = distX - distY;
            f2 += tmp * tmp;
            if (distY != 0)
            {
                for (int  k = 0; k < d; k++)
                {
                    grad[j + k] += 2 * (distX - distY) / distY * (StaticData::Y_base.getObjectAt(i).getFeatureAt(k) - Ynew[d * j + k]);
                }
            }
        }
    }

    func = f1 + f2;


    /*for (int i = 0; i < sm; i++)
    {
        for (int j = 0; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(StaticData::X_new.getObjectAt(i), StaticData::X_new.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(dd[i], dd[j], EUCLIDEAN);
            if (distY != 0)
                for (int  k = 0; k < d; k++)
                    {
                        grad[j + k] += 2 * (distX - distY) / distY * (Ynew[d * i + k] - Ynew[d * j + k]);
                    }
        }
    }
    for (int i = 0; i < nb; i++)
    {
        for (int j = 0; j < sm; j++)
        {
            distX = DistanceMetrics::getDistance(StaticData::X_base.getObjectAt(i), StaticData::X_new.getObjectAt(j), EUCLIDEAN);
            distY = DistanceMetrics::getDistance(StaticData::Y_base.getObjectAt(i), dd[j], EUCLIDEAN);

        }
    }*/
}

void SDS::Initialize()
{
    int m = X.getObjectCount();
    int closest_base;
    double min_dist;
    double dist_ij;
    DataObject objXi;



    for (int i = 0; i < m - nb; i++)
    {
        min_dist = DBL_MAX;
        closest_base = 0;

        objXi = StaticData::X_new.getObjectAt(i);
        for (int j = 0; j < nb; j++)
        {
            dist_ij = DistanceMetrics::getDistance(StaticData::X_base.getObjectAt(j), objXi, EUCLIDEAN);
            if (dist_ij < min_dist)
            {
                min_dist = dist_ij;
                closest_base = j;
            }
        }
        Y_new.addObject(StaticData::Y_base.getObjectAt(closest_base));
    }
}
