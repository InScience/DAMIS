///////////////////////////////////////////////////////////
//  SOM.h
//  Implementation of the Class SOM
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_76781C63_E408_48bc_B775_E512B31E8D6B__INCLUDED_)
#define EA_76781C63_E408_48bc_B775_E512B31E8D6B__INCLUDED_

#include "ObjectMatrix.h"
#include "DimReductionMethod.h"

class SOM : public DimReductionMethod
{

public:
	SOM();
	virtual ~SOM();

	SOM(int rows, int columns, int eHat);
	SOM(int rows, int columns, int eHat, ObjectMatrix X);
	double getQuantizationError();

//protected:
	virtual ObjectMatrix getProjection();

private:
    double Max(double, double);
    ObjectMatrix Different(ObjectMatrix);
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
