///////////////////////////////////////////////////////////
//  DataObject.h
//  Implementation of the Class DataObject
//  Created on:      07-Lie-2013 20:07:29
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_2E0FA64E_418E_4162_A9CF_9091C3861ED8__INCLUDED_)
#define EA_2E0FA64E_418E_4162_A9CF_9091C3861ED8__INCLUDED_

#include "Feature.h"
#include <vector>

class DataObject
{

public:
	DataObject();
	virtual ~DataObject();       
	DataObject(int featureCount);
	DataObject(int featureCount, int classLabel);
        DataObject(std::vector<double> v);
	int getClassLabel();
	int getFeatureCount();
	void setClassLabel(int classLabel);
        std::vector<double> features;
        void setNumOfFeatures(int);
        bool IsIdentical(DataObject);

private:
	int classLabel;
	int featureCount;
	int index;
};
#endif // !defined(EA_2E0FA64E_418E_4162_A9CF_9091C3861ED8__INCLUDED_)
