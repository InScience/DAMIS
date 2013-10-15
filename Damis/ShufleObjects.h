///////////////////////////////////////////////////////////
//  ShufleObjects.h
//  Implementation of the Class ShufleObjects
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_02DD92AD_FC82_4feb_8A22_24C00CD534BA__INCLUDED_)
#define EA_02DD92AD_FC82_4feb_8A22_24C00CD534BA__INCLUDED_

#include "ObjectMatrix.h"
#include "ShufleEnum.h"

class ShufleObjects
{

public:
	ShufleObjects();
	virtual ~ShufleObjects();

	static std::vector<int> shufleObjectMatrix(ShufleEnum shufleEnum, ObjectMatrix objectMatrix);

private:
	static std::vector<int> byBubleSort(ObjectMatrix objectMatrix);
        static std::vector<int> byBubleSortDsc(ObjectMatrix objectMatrix);
	static std::vector<int> byRand(ObjectMatrix objectMatrix);

};
#endif // !defined(EA_02DD92AD_FC82_4feb_8A22_24C00CD534BA__INCLUDED_)
