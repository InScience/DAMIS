///////////////////////////////////////////////////////////
//  ObjectMatrix.h
//  Implementation of the Class ObjectMatrix
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_EAE79B7B_5151_41cf_A08C_CE61651B7393__INCLUDED_)
#define EA_EAE79B7B_5151_41cf_A08C_CE61651B7393__INCLUDED_

#include "DataObject.h"
#include "DataMatrix.h"
#include <vector>
#include <string>


class ObjectMatrix : public DataMatrix
{

public:
	ObjectMatrix();
	virtual ~ObjectMatrix();
        std::vector<DataObject> DataObjects;
        std::vector<std::vector<DataObject> > DataObjects2D;
	ObjectMatrix(std::string);
	ObjectMatrix(int count);
	ObjectMatrix(int m, int n);
	ObjectMatrix(int m, int n, int k);
	void addObject(DataObject object);
        void addObjectTo(int index, DataObject object);
	DataObject getObjectAt(int index);
        DataObject getObjectAt(int, int);
	int getObjectCount();
	void loadDataMatrix();
        std::vector<std::string> getFeaturesTitle();
	void saveDataMatrix(const char*);
        std::string ErrorMessage;
private:
	int objectCount;
        std::vector<std::string> featureTitles;
        std::string fileName;
};
#endif // !defined(EA_EAE79B7B_5151_41cf_A08C_CE61651B7393__INCLUDED_)
