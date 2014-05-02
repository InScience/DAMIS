///////////////////////////////////////////////////////////
//  DimReductionMethod.h
//  Implementation of the Class DimReductionMethod
//  Created on:      07-Lie-2013 20:07:29
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file DimReductionMethod class
    \brief A class of methods and attributes for initialization of projection matrix.
 */
#if !defined(DIMREDUCTIONMETHOD_H)
#define DIMREDUCTIONMETHOD_H

#include "ObjectMatrix.h"
#include "HPCMethod.h"

class DimReductionMethod : public HPCMethod
{

public:
        /**
        * A default constructor.
        */
	DimReductionMethod();
        /**
        * A destructor.
        */
	virtual ~DimReductionMethod();

protected:
	/**
	 * Projection Dimmension
	 */
	int d;
    /**
	 * Stress weight of the X matrix
	 */
	double weight;
	/**
	 * Projection Matrix
	 */
	ObjectMatrix Y;
        /** \fn ObjectMatrix getProjection();
         *  \brief A pure virtual function that returns the projection matrix.
         *  \return Y - an object of ObjectMatrix class.
         */
	virtual ObjectMatrix getProjection() =0;
        /** \fn int getProjectionDimension();
         *  \brief Returns the dimension of the projection.
         *  \return d - a dimension projection.
         */
	int getProjectionDimension();
        /** \fn void initializeProjectionMatrix();
         *  \brief Initializes the projection matrix.
         */
	void initializeProjectionMatrix();
        /** \fn void setProjectionDimension(int dimension);
         *  \brief Sets the projection dimension.
         *  \param dimension - a value assigned to \a d.
         *
         */
	void setProjectionDimension(int dimension);
        /** \fn virtual double getStress();
         *  \brief Returns the stress error value.
         *  \return error - The stress error value.
         */
    virtual double getStress();



};
#endif // !defined(DIMREDUCTIONMETHOD_H)
