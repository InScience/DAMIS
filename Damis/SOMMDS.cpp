///////////////////////////////////////////////////////////
//  SOMMDS.cpp
//  Implementation of the Class SOMMDS
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "SOMMDS.h"
#include "SOM.h"

SOMMDS::SOMMDS(){

}

SOMMDS::~SOMMDS(){

}

/**
 * Constructor
 */
SOMMDS::SOMMDS(float eps, int max_iter, int d, int kx, int ky, int e_hat):SMACOF(eps, max_iter, d), SOM(kx, ky, e_hat){
 
}

/**
 * Pure virtual method that calculates the projection
 */
ObjectMatrix SOMMDS::getProjection(){
    ObjectMatrix M_ws;
    //SOM som(k_x, k_y, eHat);
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
