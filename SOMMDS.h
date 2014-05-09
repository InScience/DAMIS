///////////////////////////////////////////////////////////
//  SOMMDS.h
//  Implementation of the Class SOMMDS
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file SOMMDS class
    \brief A class of methods and attributes for SOMMDS algorithm.
 */
#if !defined(SOMMDS_H)
#define SOMMDS_H

#include "ObjectMatrix.h"
#include "SMACOF.h"
#include "SOM.h"

class SOMMDS : public SMACOF, public SOM
{

public:
        /**
        * A default constructor.
        */
	SOMMDS();
        /**
        * A destructor.
        */
	virtual ~SOMMDS();
        /**
         * An overloaded constructor that accepts: epsilon, maximum number of iterations,
         * projection dimension, number of SOM rows, number of SOM columns and hat value.
         */
	SOMMDS(double eps, int max_iter, int d, int kx, int ky, int e_hat);
        /** \fn double getSOMQuantizationError();
         *  \brief Returns the SOM quantization error.
         *  \return som_qe - SOM quantization error.
         */
        double getSOMQuantizationError();
        /** \fn double getMDSStressError();
         *  \brief Returns the MDS stress error.
         *  \return mds_error - MDS stress error.
         */
       // double getMDSStressError();

        /** \fn double getStress();
         *  \brief Returns the MDS stress error.
         *  \return mds_error - MDS stress error.
         */
        double getStress();
        /** \fn ObjectMatrix getX();
         *  \brief Returns the matrix X.
         *  \return X - The initial data matrix.
         */
        ObjectMatrix getX();
        /** \fn virtual ObjectMatrix getProjection();
         *  \brief Returns the projection matrix \a Y of matrix \a X.
         *  \return Y - the projection matrix.
         */
	virtual ObjectMatrix getProjection();
private:
        /** \var double som_qe;
         *  \brief SOM quantization error.
         */
        double som_qe;
        /** \var double eps;
         *  \brief Difference between SMACOF errors.
         */
        double eps;
        /** \var double eps;
         *  \brief Difference between SMACOF errors.
         */
        int maxIter;
        /** \var int maxIter
         *  \brief Number of SMACOF iterations.
         */
        double d;
        /** \var double mds_error;
         *  \brief MDS error.
         */
        double mds_error;
        /** \var SMACOF smcf;
         *  \brief POinter to SMACOF object.
         */
        SMACOF *smcf;
};
#endif // !defined(SOMMDS_H)
