///////////////////////////////////////////////////////////
//  SMACOFZEIDEL.h
//  Implementation of the Class SMACOFZEIDEL
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_34DB7616_0626_448c_8715_73AF0B10FB46__INCLUDED_)
#define EA_34DB7616_0626_448c_8715_73AF0B10FB46__INCLUDED_

#include "ObjectMatrix.h"
#include "SMACOF.h"
#include "ShufleEnum.h"

class SMACOFZEIDEL : public SMACOF
{

public:
	SMACOFZEIDEL();
	virtual ~SMACOFZEIDEL();

	SMACOFZEIDEL(float eps, int maxIter, int d, ShufleEnum shEnum);
        SMACOFZEIDEL(float eps, int maxIter, int d, ShufleEnum shEnum, ObjectMatrix initProjection);

//protected:
	virtual ObjectMatrix getProjection();
        double getStress();
private:
        ShufleEnum shufleEnum;

};
#endif // !defined(EA_34DB7616_0626_448c_8715_73AF0B10FB46__INCLUDED_)
