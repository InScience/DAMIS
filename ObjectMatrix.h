///////////////////////////////////////////////////////////
//  ObjectMatrix.h
//  Implementation of the Class ObjectMatrix
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file ObjectMatrix class
    \brief A class of methods and attributes for manipulating matrices.
 */
#if !defined(OBJECTMATIRX_H)
#define OBJECTMATIRX_H

#include "DataObject.h"
#include "DataMatrix.h"
#include <vector>
#include <string>


class ObjectMatrix : public DataMatrix
{

public:
        /**
        * A default constructor.
        */
	ObjectMatrix();
        /**
        * A destructor.
        */
	virtual ~ObjectMatrix();
        /**
        * An overloaded constructor that accepts the arff file name to read data from.
        */
	ObjectMatrix(std::string fileName);
        /**
        * An overloaded constructor that accepts the integer number as the amount of DataObjects in an ObjectMatrix.
        */
	ObjectMatrix(int count);
        /**
        * An overloaded constructor that accepts the integer numbers \a m and \a n as the size dimensions of the an ObjectMatrix.
        */
	ObjectMatrix(int m, int n);
        /**
        * An overloaded constructor that accepts the integer numbers \a m, \a n and \a k as the size dimensions of the an ObjectMatrix.
        */
	ObjectMatrix(int m, int n, int k);
        /** \fn void addObject(DataObject object);
         *  \brief Adds the DataObject to the set of DataObjects.
         *  \param dataObject - the DataObject that needs to be added to the DataObjects list.
         */
	void addObject(DataObject dataObject);
        /** \fn void addObjectTo(int index, DataObject dataObject);
         *  \brief Adds the DataObject to the set of DataObjects.
         *  \param index - the index of the row.
         *  \param dataObject - the DataObject that needs to be added to the DataObjects list.
         */
        void addObjectTo(int index, DataObject dataObject);
        /** \fn DataObject getObjectAt(int i);
         *  \brief Returns the \a i-th DataObject from the set of the DataObjects.
         *  \param i - the index of the DataObject that needs to be returned from the DataObjects list.
         *  \return dataObject - the \a i-th DataObject from the set of the DataObjects.
         */
	DataObject getObjectAt(int i);
        /** \fn DataObject getObjectAt(int i, int j);
         *  \brief Returns the DataObject at index \a i and \a j from the set of the DataObjects.
         *  \param i - the row number of the DataObject that needs to be returned from the DataObjects list.
         *  \param j - the column number of the DataObject that needs to be returned from the DataObjects list.
         *  \return dataObject - the DataObject at the \a i-th row and the \a j-th column from the set of the DataObjects.
         */
        DataObject getObjectAt(int i, int j);
        /** \fn double getDataAt(int i, int j);
         *  \brief Returns the j-th feature of i-th data DataObject.
         *  \return dataItem - the amount of DataObjects in the set of DataObjects.
         */
         //double getDataAt(int i, int j);
        /** \fn int getObjectCount();
         *  \brief Returns the number of DataObjects in the set of DataObjects.
         *  \return dataObject - the DataObject at the \a i-th row and the \a j-th column from the set of the DataObjects.
         */
	int getObjectCount();
        /** \fn void loadDataMatrix();
         *  \brief Loads the data to ObjectMatrix from an arff file.
         */
	void loadDataMatrix();
        /** \fn vector<string> getFeaturesTitle();
         *  \brief Returns the titles of the features.
         *  \return featureTitles - the titles of the features
         */
        std::vector<std::string> getFeaturesTitle();
        /** \fn void saveDataMatrix(const char*);
         *  \brief Saves the ObjectMatrix data to an arff file.
         *  \param fileName - the name of the file to save data to.
         */
        void saveDataMatrix(const char*);
        /** \fn void clearDataObjects();
         *  \brief Clears the items from the DataObjects set.         *
         */
        void clearDataObjects();
        /** \fn void updateDataObject(int objectIndex, int featureIndex, double newValue);
         *  \brief Updates the feature value.
         *  \param objectIndex - the index of the DataObject.
         *  \param featureIndex - the index of the feature in the DataObject.
         *  \param newValue - the new value of a feature.
         */
        void updateDataObject(int objectIndex, int featureIndex, double newValue);
        /** \fn void updateDataObject(int rowIndex, int colIndex, int featureIndex, double newValue);
         *  \brief Updates the feature value.
         *  \param rowIndex - the row index of the DataObject.
         *  \param colIndex - the column index of the DataObject.
         *  \param featureIndex - the index of the feature in the DataObject.
         *  \param newValue - the new value of a feature.
         */
        void updateDataObject(int rowIndex, int colIndex, int featureIndex, double newValue);
        /** \fn void getWeight();
         *  \brief Returns weight of X matrix (for stress calculation)
         */
        double getWeight();

private:
        /** \var vector<DataObject> DataObjects;
         *  \brief The set of DataObjects.
         */
        std::vector<DataObject> DataObjects;
        /** \var vector<vector<DataObject> > DataObjects2D;
         *  \brief The set of the sets of DataObjects.
         */
        std::vector<std::vector<DataObject>> DataObjects2D;
        /** \var int objectCount;
         *  \brief The number of DataObjects in the set of the DataObjects.
         */
        int objectCount;
        /** \var double weight;
         *  \brief weight of the distances in X matrix.
         */
        double weight;
        /** \var vector<string> featureTitles;
         *  \brief The set of feature titles.
         */
        std::vector<std::string> featureTitles;
        /** \var string fileName;
         *  \brief The file name to read the data from.
         */
        std::string fileName;

};
#endif // !defined(OBJECTMATIRX_H)
