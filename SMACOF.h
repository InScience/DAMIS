///////////////////////////////////////////////////////////
//  SMACOF.h
//  Implementation of the Class SMACOF
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file SMACOF class
    \brief A class of methods and attributes for SMACOF algorithm.
 */
#if !defined(SMACOF_H)
#define SMACOF_H

#include "ObjectMatrix.h"
#include "MDS.h"

class SMACOF : public MDS
{

public:
        /**
        * A default constructor.
        */
	SMACOF();
        /**
        * A destructor.
        */
	virtual ~SMACOF();
        /**
         * An overloaded constructor that accepts: epsilon, the maximum number of iterations and
         * projection dimension.
         */
	SMACOF(double eps, int maxIter, int d);
        /**
         * An overloaded constructor that accepts: epsilon, the maximum number of iterations,
         * projection dimension, initial data matrix and initial projection matrix.
         */
	SMACOF(double eps, int maxIter, int d, ObjectMatrix X, ObjectMatrix Y);
        /**
         * An overloaded constructor that accepts: initial projection matrix, epsilon,
         * the maximum number of iterations and projection dimension.
         */
 //       SMACOF(ObjectMatrix initialY, double eps, int maxIter, int d);
        /**
         * An overloaded constructor that accepts: epsilon, the maximum number of iterations,
         * projection dimension, shuffling strategy and initial data matrix.
         */
        SMACOF(double eps, int maxIter, int d, ObjectMatrix initialMatrix);
        /** \fn virtual ObjectMatrix getProjection();
         *  \brief Returns the projection matrix \a Y of matrix \a X.
         *  \return Y - the projection matrix.
         */
	virtual ObjectMatrix getProjection();
        /** \fn double getStress();
         *  \brief Returns the stress error value.
         *  \return error - Stress error value.
         */
    double getStress();
        /** \fn ObjectMatrix getGutmanMatrix();
         *  \brief Returns the Guttman matrix.
         *  \return gutmanMatrix - The Guttman Matrix
         */
  //      ObjectMatrix getGutmanMatrix();
private:
        /** \var bool readFile;
         *  \brief Shows how stress should be calculated either read from file o  calc on the fly X distances.
         */
    bool readFile;
};
#endif // !defined(SMACOF_H)
