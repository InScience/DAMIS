///////////////////////////////////////////////////////////
//  SAMANN.h
//  Implementation of the Class SAMANN
//  Created on:      07-Lie-2013 20:07:31
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_F0DCD72D_78A3_4631_BA37_85170CEDA2B0__INCLUDED_)
#define EA_F0DCD72D_78A3_4631_BA37_85170CEDA2B0__INCLUDED_

#include "ObjectMatrix.h"
#include "DimReductionMethod.h"

class SAMANN : public DimReductionMethod
{

public:
	SAMANN();
	virtual ~SAMANN();

	SAMANN(int m1, int nl, double eta, int maxIter);
	void train();

//protected:
	virtual ObjectMatrix getProjection();

private:
	/**
	 * Learning speed value
	 */
	double eta;
	/**
	 * SAMAN lambda value
	 */
	double lambda;
	/**
	 * Number of maximum Iterations
	 */
	int maxIteration;
	/**
	 * Number of training elements
	 */
	int mTrain;
	/**
	 * Number of neurons in hidden layer
	 */
	int nNeurons;
	/**
	 * Matrix represents SAMAN algorithm training set.
	 */
	ObjectMatrix Xp;
        ObjectMatrix Y_pasl;
        ObjectMatrix Y_is;
        ObjectMatrix delta_L;
        std::vector<std::vector<double> > w1;
        std::vector<std::vector<double> > w2;

	double getLambda();
	double getStress();
	virtual void getTrainingSet();
	void updateWeights();
        void initializeWeights();         // initializes w1 and w2
        void initializeExitMatrixes();    // initializes Y_is and Y_pasl
        void initializeDeltaL();          // initialize delta_L
        double getMax();
        void NormalizeX();
        void getXp();
        bool isIdentical(DataObject);
};
#endif // !defined(EA_F0DCD72D_78A3_4631_BA37_85170CEDA2B0__INCLUDED_)
