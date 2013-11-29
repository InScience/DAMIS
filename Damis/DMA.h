///////////////////////////////////////////////////////////
//  DMA.h
//  Implementation of the Class DMA
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_3155AA55_4FD7_44fa_8149_A99119949EDB__INCLUDED_)
#define EA_3155AA55_4FD7_44fa_8149_A99119949EDB__INCLUDED_

#include "ObjectMatrix.h"
#include "MDS.h"

class DMA : public MDS
{

public:
	DMA();
	virtual ~DMA();

        DMA(double eps, int maxIter, int d, int neighbours, ObjectMatrix x);
	DMA(double eps, int maxIter, int d, int neighbours);
	int getNeighbours();
	void setNeighbours(int neighbours);

//protected:
	virtual ObjectMatrix getProjection();

private:
	int neighbourNumber;
	ObjectMatrix vMatrix;
	void getV();
        void shuffleX();
};
#endif // !defined(EA_3155AA55_4FD7_44fa_8149_A99119949EDB__INCLUDED_)
