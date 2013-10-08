///////////////////////////////////////////////////////////
//  PSMACOF.h
//  Implementation of the Class PSMACOF
//  Created on:      07-Lie-2013 20:07:31
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_05B547C4_C175_49d0_BEF9_0686DFEC3A0F__INCLUDED_)
#define EA_05B547C4_C175_49d0_BEF9_0686DFEC3A0F__INCLUDED_

#include "ObjectMatrix.h"
#include "SMACOF.h"

/**
 * Class for parallel SMACOF
 */
class PSMACOF : public SMACOF
{

public:
	PSMACOF();
	virtual ~PSMACOF();

	PSMACOF(float eps, int maxIter, int d, int p);
        double** getProjectionInDoubles();

//protected:
	virtual ObjectMatrix getProjection();

private:
	int p;
        double** ObjectMatrixToDouble(ObjectMatrix);

};
#endif // !defined(EA_05B547C4_C175_49d0_BEF9_0686DFEC3A0F__INCLUDED_)
