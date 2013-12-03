///////////////////////////////////////////////////////////
//  SOMMDS.cpp
//  Implementation of the Class SOMMDS
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \class SOMMDS
    \brief A class of methods and attributes for SOMMDS algorithm.
 */
#include "SOMMDS.h"
#include "SOM.h"

SOMMDS::SOMMDS(){

}

SOMMDS::~SOMMDS(){

}

SOMMDS::SOMMDS(double eps, int max_iter, int d, int kx, int ky, int e_hat):SMACOF(eps, max_iter, d), SOM(kx, ky, e_hat){
 
}

ObjectMatrix SOMMDS::getProjection(){
    ObjectMatrix M_ws;
    M_ws = SOM::getProjection();
    som_qe = SOM::getQuantizationError();
    SMACOF::X = M_ws;
    mds_error = SMACOF::getStress();
    return  SMACOF::getProjection();
}

double SOMMDS::getSOMQuantizationError()
{
    return som_qe;
}

double SOMMDS::getMDSStressError()
{
    return mds_error;
}

ObjectMatrix SOMMDS::getX()
{
    return SMACOF::X;
}
