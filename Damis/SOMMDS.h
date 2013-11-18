///////////////////////////////////////////////////////////
//  SOMMDS.h
//  Implementation of the Class SOMMDS
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_7E809A89_6ED7_4e3d_A371_330C18909791__INCLUDED_)
#define EA_7E809A89_6ED7_4e3d_A371_330C18909791__INCLUDED_

#include "ObjectMatrix.h"
#include "SMACOF.h"
#include "SOM.h"

class SOMMDS : public SMACOF, public SOM
{

public:
	SOMMDS();
	virtual ~SOMMDS();

	SOMMDS(float eps, int max_iter, int d, int kx, int ky, int e_hat);
        double getSOMQuantizationError();
        double getMDSStressError();

//protected:
	virtual ObjectMatrix getProjection();
private:
        double som_qe;
        double mds_error;
};
#endif // !defined(EA_7E809A89_6ED7_4e3d_A371_330C18909791__INCLUDED_)
