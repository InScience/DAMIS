///////////////////////////////////////////////////////////
//  DataMatrix.h
//  Implementation of the Interface DataMatrix
//  Created on:      07-Lie-2013 20:07:29
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_0D61ACEF_288D_4949_AB18_4545C1E57302__INCLUDED_)
#define EA_0D61ACEF_288D_4949_AB18_4545C1E57302__INCLUDED_

#include "ObjectMatrix.h"

class DataMatrix
{

public:
	DataMatrix() {

	}

	virtual ~DataMatrix() {

	}
        
	virtual void loadDataMatrix() =0;
	//virtual void saveDataMatrix(ObjectMatrix, char) =0;

};
#endif // !defined(EA_0D61ACEF_288D_4949_AB18_4545C1E57302__INCLUDED_)
