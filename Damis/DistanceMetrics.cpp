#include <cstdlib>

#include "DistanceMetrics.h"
#include "DistanceMetricsEnum.h"
#include <cmath>

double DistanceMetrics::getDistance(DataObject obj1, DataObject obj2, DistanceMetricsEnum dme){
    double to_return = 0.0;
    if (dme == Manhattan)
        to_return = DistanceMetrics::getManhattan(obj1, obj2);
    else if (dme == Euclidean)
        to_return = DistanceMetrics::getEuclidean(obj1, obj2);
    else if (dme == Chebyshev)
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
    double to_return = 0.0;
    double s = 0.0;
    int n = obj1.getFeatureCount();
    
    for (int i = 0; i < n; i++)
        s += std::pow((obj1.getFeatureAt(i) - obj2.getFeatureAt(i)), 2);
    
    to_return = std::sqrt(s);
    
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
