/* 
 * File:   DistanceMetrics.h
 * Author: mindaugas
 *
 * Created on September 1, 2013, 11:15 PM
 */

#ifndef DISTANCEMETRICS_H
#define	DISTANCEMETRICS_H

#include "DataObject.h"
#include "ObjectMatrix.h"
#include "DistanceMetricsEnum.h"

class DistanceMetrics{
public:
    static double getDistance(DataObject, DataObject, DistanceMetricsEnum);
    static double getDistance(DistanceMetricsEnum, ObjectMatrix&, DataObject);
private:
    static double getChebyshev(DataObject, DataObject);
    static double getEuclidean(DataObject, DataObject);
    static double getManhattan(DataObject, DataObject);
};

#endif	/* DISTANCEMETRICS_H */

