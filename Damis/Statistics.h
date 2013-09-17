/* 
 * File:   Statistics.h
 * Author: mindaugas
 *
 * Created on August 30, 2013, 10:58 AM
 */

#ifndef STATISTICS_H
#define	STATISTICS_H

#include "DataObject.h"
#include "ObjectMatrix.h"

class Statistics{
public:
    static double getAverage(ObjectMatrix, int);
    static double getCorrCoef(ObjectMatrix, int, int);
    static double getCovCoef(ObjectMatrix, int, int);
    static ObjectMatrix getCovMatrix(ObjectMatrix);
    static double getRandom(double, double);
    static double getRandom();
};

#endif	/* STATISTICS_H */

