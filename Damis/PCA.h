///////////////////////////////////////////////////////////
//  PCA.h
//  Implementation of the Class PCA
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_137C79B9_5330_4edc_A6BF_D6D076823555__INCLUDED_)
#define EA_137C79B9_5330_4edc_A6BF_D6D076823555__INCLUDED_

#include "ObjectMatrix.h"
#include "ExternalMethods.h"
#include "DimReductionMethod.h"
#include "alglib/ap.h"

class PCA : public DimReductionMethod, public ExternalMethods
{

public:
	PCA();
	virtual ~PCA();

	PCA(int d);
	PCA(float disp);
	PCA(ObjectMatrix objMatrix, int d);
	virtual void toDataType();
	virtual void fromDataType();

//protected:
	virtual ObjectMatrix getProjection();

private:
	/**
	 * Dispersion part to retain in resulting projection
	 */
	float dispPart;
        alglib::real_2d_array alglibX;

};
#endif // !defined(EA_137C79B9_5330_4edc_A6BF_D6D076823555__INCLUDED_)
