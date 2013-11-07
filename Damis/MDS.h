///////////////////////////////////////////////////////////
//  MDS.h
//  Implementation of the Class MDS
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_CDF28449_1ACC_4a74_A6EB_47124922ACEA__INCLUDED_)
#define EA_CDF28449_1ACC_4a74_A6EB_47124922ACEA__INCLUDED_

#include "ObjectMatrix.h"
#include "DimReductionMethod.h"

class MDS : public DimReductionMethod
{

public:
	MDS();
	virtual ~MDS();

	MDS(double eps, int maxIter, int d);
        double getFinalEpsilon();
        int getIteration();
protected:
	double getEpsilon();
	ObjectMatrix getGutman();
        ObjectMatrix getGutman(ObjectMatrix Y_new);
	int getMaxIteration();
	virtual double getStress();
	void setEpsilon(double eps);
	void setMaxIteration(int maxIter);

        double finalEpsilon;
	double epsilon;
        int iteration;
	int maxIteration;
private:
        double getWeight(int, int);
};
#endif // !defined(EA_CDF28449_1ACC_4a74_A6EB_47124922ACEA__INCLUDED_)
