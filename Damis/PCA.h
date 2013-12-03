///////////////////////////////////////////////////////////
//  PCA.h
//  Implementation of the Class PCA
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file PCA class
    \brief A class of methods and attributes for PCA algorithm.
 */
#if !defined(EA_137C79B9_5330_4edc_A6BF_D6D076823555__INCLUDED_)
#define EA_137C79B9_5330_4edc_A6BF_D6D076823555__INCLUDED_

#include "ObjectMatrix.h"
#include "DimReductionMethod.h"
#include "alglib/ap.h"

class PCA : public DimReductionMethod
{

public:
        /**
        * A default constructor.
        */
	PCA();
        /**
        * A destructor.
        */
	virtual ~PCA();
        /**
         * An overloaded constructor that accepts the dimension.
         */
	PCA(int d);
        /**
         * An overloaded constructor that accepts the dispersion part.
         */
	PCA(double disp);
        /**
         * An overloaded constructor that accepts the ObjectMatrix and dispersion part.
         */
        PCA(ObjectMatrix objMatrix, double disp);
        /**
         * An overloaded constructor that accepts the ObjectMatrix and dimension.
         */
	PCA(ObjectMatrix objMatrix, int d);
        /** \fn virtual void toDataType();
         *  \brief Converts the ObjectMatrix to alglib's real_2d_array. 
         */
	virtual void toDataType();
        /** \fn virtual void fromDataType();
         *  \brief Converts alglib's real_2d_array to an ObjectMatrix. 
         */
	virtual void fromDataType();
        /** \fn int getDimension();
         *  \brief Returns the dimension.
         *  \return d - the dimension. 
         */
        int getDimension();
        /** \fn double getDispersionPart();
         *  \brief Returns the dispersion part.
         *  \return dispPart - the dispersion part. 
         */
        double getDispersionPart();
        /** \fn alglib::real_1d_array getEigenValues();
         *  \brief Returns the eigenvalues of the projection.
         *  \return eigValues - the eigenvalues of the projection.
         */
        alglib::real_1d_array getEigenValues();
        /** \fn virtual ObjectMatrix getProjection();
         *  \brief Returns the projection matrix.
         *  \return Y - the projection matrix.
         */
	virtual ObjectMatrix getProjection();

private:
	/**
	 * Dispersion part to retain in resulting projection
	 */
	double dispPart;
        /** \var alglib::real_2d_array alglibX;
         *  \brief The 2D alglib type matrix.
         */
        alglib::real_2d_array alglibX;
        /** \fn void ProjectXMatrix();
         *  \brief Calculates the projection of matrix X.
         * 
         */
        void ProjectXMatrix();
        /** \var alglib::real_1d_array eigValues;
         *  \brief The array of eigenvalues.
         */
        alglib::real_1d_array eigValues;
};
#endif // !defined(EA_137C79B9_5330_4edc_A6BF_D6D076823555__INCLUDED_)
