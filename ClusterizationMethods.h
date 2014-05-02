///////////////////////////////////////////////////////////
//  ClusterizationMethods.h
//  Implementation of the Class ClusterizationMethod
//  Created on:      27-Kov-2014 12:52:15
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(CLUSTERIZATIONMETHODS_H)
#define CLUSTERIZATIONMETHODS_H

#include "HPCMethod.h"

/**
 * Class that combines clasterization methods. Class provides the number of found
 * classes method and the pure virtual function get Classterization
 */
class ClusterizationMethods : public HPCMethod
{

public:
	ClusterizationMethods();
	virtual ~ClusterizationMethods();

protected:
	virtual ObjectMatrix getProjection() =0;
	void getNoOfClases();
	void setNoOfClases(int k);

private:
	/**
	 * Holds numeber of clases
	 */
	int noOfClases;

};
#endif // !defined(CLUSTERIZATIONMETHODS_H)
