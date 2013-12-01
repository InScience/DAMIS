///////////////////////////////////////////////////////////
//  SDS.h
//  Implementation of the Class SDS
//  Created on:      07-Lie-2013 20:07:31
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_BD1F1D91_A491_4a5e_9B31_E250CAE201D5__INCLUDED_)
#define EA_BD1F1D91_A491_4a5e_9B31_E250CAE201D5__INCLUDED_

#include "ObjectMatrix.h"
#include "PCA.h"
#include "SMACOF.h"
#include "MDS.h"
#include "DistanceMetricsEnum.h"
#include "ProjectionEnum.h"



class SDS : public MDS
{

public:
	SDS();
	virtual ~SDS();
	//PCA *m_PCA;
	//SMACOF *m_SMACOF;

	SDS(double eps, int maxIter, int d, ProjectionEnum baseVectInitt, int nofBaseVect, DistanceMetricsEnum distMetrics);


	virtual ObjectMatrix getProjection();
	virtual double getStress();        
        //tatic ObjectMatrix Y_base;
private:
	/**
	 * Base vector initialization method
	 */
	ProjectionEnum initMethod;
	ObjectMatrix Y_new;
        
        DistanceMetricsEnum distMethod;
	/**
	 * Number of base vectors
	 */
	int nb;
	//static ObjectMatrix X_base;
	//static ObjectMatrix X_new;
        
	void getQN();
        void Initialize();
        static void E_SDS(const alglib::real_1d_array &x, double &func, alglib::real_1d_array &grad, void *ptr);
        
};
#endif // !defined(EA_BD1F1D91_A491_4a5e_9B31_E250CAE201D5__INCLUDED_)
