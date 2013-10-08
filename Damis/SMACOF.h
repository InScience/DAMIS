///////////////////////////////////////////////////////////
//  SMACOF.h
//  Implementation of the Class SMACOF
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_33C383A8_AABC_4498_9E97_8D153E43A6A7__INCLUDED_)
#define EA_33C383A8_AABC_4498_9E97_8D153E43A6A7__INCLUDED_

#include "ObjectMatrix.h"
#include "MDS.h"

class SMACOF : public MDS
{

public:
	SMACOF();
	virtual ~SMACOF();

	SMACOF(float eps, int maxIter, int d);
	SMACOF(float eps, int maxIter, int d, ObjectMatrix X, ObjectMatrix Y);
        ObjectMatrix ReturnY();

//protected:
	virtual ObjectMatrix getProjection();

};
#endif // !defined(EA_33C383A8_AABC_4498_9E97_8D153E43A6A7__INCLUDED_)
