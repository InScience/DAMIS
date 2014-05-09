/*
 * File:   Statistics.h
 * Author: mindaugas
 *
 * Created on August 30, 2013, 10:58 AM
 */
/*! \file Statistics class
    \brief A class of static methods for calculating statistical information.
 */
#ifndef STATISTICS_H
#define	STATISTICS_H

#include "DataObject.h"
#include "ObjectMatrix.h"

class Statistics{
public:
    /** \fn static double getAverage(ObjectMatrix matrix, int col);
     *  \brief Calculates the average value of the specified features.
     *  \param matrix - The ObjectMatrix.
     *  \param col - The column number.
     *  \return average - The average of the features in a \a col column.
     */
    static double getAverage(ObjectMatrix matrix, int col);
        /** \fn static double getAverage(ObjectMatrix matrix);
     *  \brief Calculates the average value of each feature (column) of whole object matrix.
     *  \param matrix - The ObjectMatrix.
     *  \return vector average - The average of the features in a all columns.
     */
    static std::vector<double> getAverageColumns(ObjectMatrix matrix);
    /** \fn static double getCorrCoef(ObjectMatrix matrix, int i, int j);
     *  \brief Calculates the correlation coefficient between the \a i-th and the \a j-th DataObjects.
     *  \param matrix - The ObjectMatrix.
     *  \param i - The \a i-th DataObject.
     *  \param j - The \a j-th DataObject.
     *  \return coefficient - The correlation coefficient.
     */
    static double getCorrCoef(ObjectMatrix matrix, int i, int j);
    /** \fn static double getCovCoef(ObjectMatrix matrix, int i, int j);
     *  \brief Calculates the covariation coefficient between the \a i-th and the \a j-th DataObjects.
     *  \param matrix - The ObjectMatrix.
     *  \param i - The \a i-th DataObject.
     *  \param j - The \a j-th DataObject.
     *  \return coefficient - The covariation coefficient.
     */
    static double getCovCoef(ObjectMatrix matrix, int i, int j);
    /** \fn static ObjectMatrix getCovMatrix(ObjectMatrix matrix);
     *  \brief Returns the covariation matrix.
     *  \param matrix - The data matrix.
     *  \return covMatrix - The covariation matrix.
     */
    static ObjectMatrix getCovMatrix(ObjectMatrix matrix);
    /** \fn static double getRandom(double min, double max, int k);
     *  \brief Returns the randomly generated number in interval \a [min,max].
     *  \param min - The lower bound of the interval.
     *  \param max - The higher bound of the interval.
     *  \return number - The randomly generated number.
     */
    static double getRandom(double min, double max);
    /** \fn static double getRandom(int k);
     *  \brief Returns the randomly generated number in interval \a [0,1].
     *  \return number - The randomly generated number.
     */
    static double getRandom();

    /** \fn static double initSeed();
     *  \brief Initiates seed for each processor.
     */
    static void initSeed();
    //static double getDispersion(ObjectMatrix , int);
    //static double getSum(ObjectMatrix, int);
};

#endif	/* STATISTICS_H */

