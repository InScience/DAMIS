/* 
 * File:   DistanceMetrics.h
 * Author: mindaugas
 *
 * Created on September 1, 2013, 11:15 PM
 */
/*! \file DistanceMetrics class
    \brief A class of static methods for calculating distance between DataObjects.
 */
#ifndef DISTANCEMETRICS_H
#define	DISTANCEMETRICS_H

#include "DataObject.h"
#include "ObjectMatrix.h"
#include "DistanceMetricsEnum.h"

class DistanceMetrics{
public:
    /** \fn static double getDistance(DataObject object1, DataObject object2, DistanceMetricsEnum);
     *  \brief Calculates the distance between two DataObjects.
     * @param object1 - a DataObject.
     * @param object2 - a DataObject.
     * @param metricsEnum - enumeration type of the distance calculation metrics.
     * @return distance - the distance between two DataObjects.
     */
    static double getDistance(DataObject object1, DataObject object2, DistanceMetricsEnum metricsEnum);
private:
    /** \fn static double getChebyshev(DataObject object1, DataObject object2);
     *  \brief Calculates the distance between two DataObjects using \a Chebyshev metrics. 
     * @param object1 - a DataObject.
     * @param object2 - a DataObject.
     * @return distance - the distance between two DataObjects.
     */
    static double getChebyshev(DataObject object1, DataObject object2);
    /** \fn static double getEuclidean(DataObject object1, DataObject object2);
     *  \brief Calculates the distance between two DataObjects using \a Euclidean metrics. 
     * @param object1 - a DataObject.
     * @param object2 - a DataObject.
     * @return distance - the distance between two DataObjects.
     */
    static double getEuclidean(DataObject object1, DataObject object2);
    /** \fn static double getManhattan(DataObject object1, DataObject object2);
     *  \brief Calculates the distance between two DataObjects using \a Manhattan metrics. 
     * @param object1 - a DataObject.
     * @param object2 - a DataObject.
     * @return distance - the distance between two DataObjects.
     */
    static double getManhattan(DataObject object1, DataObject object2);
};

#endif	/* DISTANCEMETRICS_H */

