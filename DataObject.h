///////////////////////////////////////////////////////////
//  DataObject.h
//  Implementation of the Class DataObject
//  Created on:      07-Lie-2013 20:07:29
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file DataObject class
    \brief A class of methods and attributes for manipulating features in data vectors.
 */
#if !defined(EA_2E0FA64E_418E_4162_A9CF_9091C3861ED8__INCLUDED_)
#define EA_2E0FA64E_418E_4162_A9CF_9091C3861ED8__INCLUDED_

#include <vector>

class DataObject
{

public:
        /**
        * A default constructor.
        */
	DataObject();
        /**
        * A destructor.
        */
	virtual ~DataObject();
        /**
        * An overloaded constructor that accepts the number of the features.
        */
	DataObject(int featureCount);
        /**
        * An overloaded constructor that accepts the number of the features and a class label.
        */
	DataObject(int featureCount, int classLabel);
        /**
        * An overloaded constructor that accepts the vector of the features.
        */
    DataObject(std::vector<double> v);
        /** \fn int getClassLabel();
         *  \brief Returns the class label.
         *  \return classLabel - the class label.
         */
	int getClassLabel();
        /** \fn int getFeatureCount();
         *  \brief Returns the number of features.
         *  \return featureCount - the number of features.
         */
	int getFeatureCount();
        /** \fn void setClassLabel(int classLabel);
         *  \brief Sets the class label.
         *  \param classLabel - the class label.
         */
	void setClassLabel(int classLabel);
        /** \fn double getFeatureAt(int index);
         *  \brief Returns the feature at specified index.
         *  \param index - a zero-based index of the element in a features list.
         *  \return feature - a feature at index \a index.
         */
        double getFeatureAt(int index);
        /** \fn void setNumOfFeatures(int);
         *  \brief Sets the number of features.
         *  \param num - a number of features.
         */
        void setNumOfFeatures(int num);
        /** \fn bool IsIdentical(DataObject other);
         *  \brief Checks if current DataObject is identical to the given one.
         *  \param otherObject - a DataObject that needs to be compared with \this DataObject.
         *  \return answer - a boolean value, \a true if DataObjects are identical, \a false otherwise.
         */
        bool IsIdentical(DataObject otherObject);
        /** \fn void updateFeature(int featureIndex, double newValue);
         *  \brief Updates the feature value.
         *  \param featureIndex - a zero-based index of the feature in a list.
         *  \param newValue - a new value of a feature.
         */
        void updateFeature(int featureIndex, double newValue);
        std::vector<double> getFeatures();


private:
        /** \var int classLabel;
        *  \brief The label of the class.
        */
	int classLabel;
        /** \var int featureCount;
        *  \brief The number of the features.
        */
	int featureCount;
        /** \var int index;
        *  \brief The index of the feature.
        */
	int index;
        /** \var vector<double> features;
        *  \brief The set of the features.
        */
    std::vector<double> features;
};
#endif // !defined(EA_2E0FA64E_418E_4162_A9CF_9091C3861ED8__INCLUDED_)
