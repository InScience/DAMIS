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
    static double getRandom(double, double, int);
    static double getRandom(int);
    static double getRandom(double, double);   // testavimui, vienodu matricu generavimui
    static double getDispersion(ObjectMatrix, int);
    static double getSum(ObjectMatrix, int);
};

#endif	/* STATISTICS_H */

