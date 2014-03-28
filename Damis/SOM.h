///////////////////////////////////////////////////////////
//  SOM.h
//  Implementation of the Class SOM
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file SOM class
    \brief A class of methods and attributes for SOM algorithm.
 */
#if !defined(EA_76781C63_E408_48bc_B775_E512B31E8D6B__INCLUDED_)
#define EA_76781C63_E408_48bc_B775_E512B31E8D6B__INCLUDED_

#include "ObjectMatrix.h"
#include "DimReductionMethod.h"

class SOM : public DimReductionMethod
{

public:
        /**
        * A default constructor.
        */
	SOM();
        /**
        * A destructor.
        */
	virtual ~SOM();
        /*
         * An overloaded constructor that accepts: number of rows, number of columns and hat value.
         */
	SOM(int rows, int columns, int eHat);
        /*
         * An overloaded constructor that accepts: number of rows, number of columns, hat value and initial matrix.
         */
	SOM(int rows, int columns, int eHat, ObjectMatrix X);
        /** \fn double getQuantizationError();
         *  \brief Returns the quantization error.
         *  \return error - the quantization error.
         */
	double getQuantizationError();
	        /** \fn double getStress();
         *  \brief Returns the quantization error.
         *  \return error - the quantization error.
         */
	double getStress();
        /** \fn virtual ObjectMatrix getProjection();
         *  \brief Returns the projection matrix \a Y of matrix \a X.
         *  \return Y - the projection matrix.
         */
	virtual ObjectMatrix getProjection();

private:
        /** \fn double Max(double number1, double number2);
         *  \brief Returns the bigger number.
         *  \param number1 - The first number.
         *  \param number2 - The second number.
         *  \return max
         */
        double Max(double number1, double number2);
        /** \fn ObjectMatrix Different(ObjectMatrix matrix);
         *  \brief Returns different DataObjects from the ObjectMatrix.
         *  \param matrix - The ObjectMatrix
         *  \return uniqeMatrix - The ObjectMatrix with unique DataObjects.
         */
        ObjectMatrix Different(ObjectMatrix matrix);
	/**
	 * Number of object features i.e. equals to object columns (k_y)
	 */
	int k_y;
	/**
	 * Number of learning epoch
	 */
	int eHat;
	/**
	 * Neuron winner matrix
	 */
	ObjectMatrix nWinner;
	/**
	 * Number or rows is equal to number of ObjectMatrix rows (k_x)
	 */
	int k_x;

};
#endif // !defined(EA_76781C63_E408_48bc_B775_E512B31E8D6B__INCLUDED_)
