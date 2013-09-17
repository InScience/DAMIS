///////////////////////////////////////////////////////////
//  DimReductionMethod.h
//  Implementation of the Class DimReductionMethod
//  Created on:      07-Lie-2013 20:07:29
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_DC369997_8613_4bb3_AA07_8B266375AA92__INCLUDED_)
#define EA_DC369997_8613_4bb3_AA07_8B266375AA92__INCLUDED_

#include "ObjectMatrix.h"
#include "HPCMethod.h"

class DimReductionMethod : public HPCMethod
{

public:
	DimReductionMethod();
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

	virtual ObjectMatrix getProjection() =0;
	int getProjectionDimension();
	void initializeProjectionMatrix(int n);
	void setProjectionDimension(int dimension);

};
#endif // !defined(EA_DC369997_8613_4bb3_AA07_8B266375AA92__INCLUDED_)
