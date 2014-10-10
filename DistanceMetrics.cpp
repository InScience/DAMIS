/*! \class DistanceMetrics
    \brief A class of static methods for calculating distance between DataObjects.
 */
#include <cstdlib>

#include "DistanceMetrics.h"
#include "DistanceMetricsEnum.h"
#include "ObjectMatrix.h"
#include <cmath>
#include <algorithm>    // std::transform
#include <numeric>


double DistanceMetrics::getDistance(DataObject obj1, DataObject obj2, DistanceMetricsEnum dme)
{
    double to_return = 0.0;
    if (dme == MANHATTAN)
        to_return = DistanceMetrics::getManhattan(obj1, obj2);
    else if (dme == EUCLIDEAN)
        to_return = DistanceMetrics::getEuclidean(obj1, obj2);
    else if (dme == CHEBYSHEV)
        to_return = DistanceMetrics::getChebyshev(obj1, obj2);

    return to_return;
}


double DistanceMetrics::getManhattan(DataObject obj1, DataObject obj2)
{
    double to_return = 0.0;
    int n = obj1.getFeatureCount();

    for (int i = 0; i < n; i++)
        to_return += fabs(obj1.getFeatureAt(i) - obj2.getFeatureAt(i));

    return to_return;
}


double DistanceMetrics::getEuclidean(DataObject obj1, DataObject obj2)
{
    double s = 0.0;
    int n = obj1.getFeatureCount(), i;
    double diff = 0;
    for (i = 0; i < n; i++)
    {
        diff = obj1.getFeatureAt(i) - obj2.getFeatureAt(i);
        s += diff * diff;
    }
    double to_return = std::sqrt(s);//0.0;
    return to_return;
}

double DistanceMetrics::getChebyshev(DataObject obj1, DataObject obj2)
{
    double to_return = -1.0;
    int n = obj1.getFeatureCount();

    for (int i = 0; i < n; i++)
    {
        if (fabs(obj1.getFeatureAt(i) - obj2.getFeatureAt(i)) > to_return)
            to_return = fabs(obj1.getFeatureAt(i) - obj2.getFeatureAt(i));
    }

    return to_return;
}


