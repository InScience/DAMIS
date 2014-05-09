///////////////////////////////////////////////////////////
//  SMACOFZEIDEL.h
//  Implementation of the Class SMACOFZEIDEL
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file SMACOFZEIDEL class
    \brief A class of methods and attributes for SMACOFZEIDEL algorithm.
 */
#if !defined(SMACOFZEIDEL_H)
#define SMACOFZEIDEL_H

#include "ObjectMatrix.h"
#include "SMACOF.h"
#include "ShufleEnum.h"

class SMACOFZEIDEL : public SMACOF
{

public:
        /**
        * A default constructor.
        */
	SMACOFZEIDEL();
        /**
        * A destructor.
        */
	virtual ~SMACOFZEIDEL();
        /**
         * An overloaded constructor that accepts: epsilon, the maximum number of iterations,
         * projection dimension and shuffling strategy.
         */
	SMACOFZEIDEL(double eps, int maxIter, int d, ShufleEnum shEnum);
        /**
         * An overloaded constructor that accepts: initial projection matrix, epsilon, the maximum number of iterations,
         * projection dimension and shuffling strategy.
         */
      //  SMACOFZEIDEL(ObjectMatrix initProjection, double eps, int maxIter, int d, ShufleEnum shEnum);
        /**
         * An overloaded constructor that accepts: epsilon, the maximum number of iterations,
         * projection dimension, shuffling strategy and initial data matrix.
         */
    //    SMACOFZEIDEL(double eps, int maxIter, int d, ShufleEnum shEnum, ObjectMatrix initialX);
        /** \fn virtual ObjectMatrix getProjection();
         *  \brief Returns the projection matrix \a Y of matrix \a X.
         *  \return Y - the projection matrix.
         */
	virtual ObjectMatrix getProjection();
        /** \fn double getStress();
         *  \brief Returns the stress error value.
         *  \return error - Stress error value.
         */
 //       double getStress();
private:
        /** \var ShufleEnum shufleEnum;
         *  \brief Shuffle enum.
         */
        ShufleEnum shufleEnum;
};
#endif // !defined(SMACOFZEIDEL_H)
