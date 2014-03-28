///////////////////////////////////////////////////////////
//  DimReductionMethod.h
//  Implementation of the Class DimReductionMethod
//  Created on:      07-Lie-2013 20:07:29
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file DimReductionMethod class
    \brief A class of methods and attributes for initialization of projection matrix.
 */
#if !defined(EA_DC369997_8613_4bb3_AA07_8B266375AA92__INCLUDED_)
#define EA_DC369997_8613_4bb3_AA07_8B266375AA92__INCLUDED_

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

	        /** \fn double getStressWeight();
         *  \brief Calculates the weight of the upper left matrix triangle.
         *  \param weightType - indicates whitch weight should be returned according to MDS error
         *  \return weight - the weight of the upper left matrix triangle.
         */
    virtual double getStressWeight(int weightType = 1);


};
#endif // !defined(EA_DC369997_8613_4bb3_AA07_8B266375AA92__INCLUDED_)
