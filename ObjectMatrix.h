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
    /*! \fn ObjectMatrix();
    *  \brief A default constructor.
    */
    ObjectMatrix();
    /*! \fn virtual ~ObjectMatrix();
    * \brief A destructor.
    */
    virtual ~ObjectMatrix();
    /*! \fn ObjectMatrix(std::string fileName);
    * \brief  An overloaded constructor that accepts the arff file name to read data from.
    * \param std::string fileName - path to a file
    */
    ObjectMatrix(std::string fileName);
    /*! \fn ObjectMatrix(int count);
    * \brief An overloaded constructor that accepts the integer number as the amount of DataObjects in an ObjectMatrix.
    * \param int count - quantity of data objects in object matrix
    */
    ObjectMatrix(int count);
    /*! \fn ObjectMatrix(int m, int n);
    * \brief An overloaded constructor that accepts the integer numbers \a m and \a n as the size dimensions of the an ObjectMatrix.
    * \param int m - number of rows
    * \param int n - number of columns
    */
    ObjectMatrix(int m, int n);
    /*! \fn ObjectMatrix(int m, int n, int k);
    * \brief An overloaded constructor that accepts the integer numbers \a m, \a n and \a k as the size dimensions of the an ObjectMatrix.
    * \param int m - number of rows
    * \param int n - number of columns
    * \param int k - depth of the Object matrix used by SOM algorithm
    */
    ObjectMatrix(int m, int n, int k);
    /*! \fn void addObject(DataObject object);
     *  \brief Adds the DataObject to the set of DataObjects.
     *  \param dataObject - the DataObject that needs to be added to the DataObjects list.
     */
    void addObject(DataObject dataObject);
    /*! \fn void addObject(DataObject object, int cls);
     *  \brief Adds the DataObject to the set of DataObjects.
     *  \param dataObject - the DataObject that needs to be added to the DataObjects list.
     * \param int cls - class that data object belongs to.
     */
    void addObject(DataObject object, int cls);
    /*! \fn void addObjectTo(int index, DataObject dataObject);
     *  \brief Adds the DataObject to the set of DataObjects.
     *  \param index - the index of the row.
     *  \param dataObject - the DataObject that needs to be added to the DataObjects list.
     */
    void addObjectTo(int index, DataObject dataObject);
    /*! \fn DataObject getObjectAt(int i);
     *  \brief Returns the \a i-th DataObject from the set of the DataObjects.
     *  \param i - the index of the DataObject that needs to be returned from the DataObjects list.
     *  \return dataObject - the \a i-th DataObject from the set of the DataObjects.
     */
    DataObject getObjectAt(int i);
    /*! \fn DataObject getObjectAt(int i, int j);
     *  \brief Returns the DataObject at index \a i and \a j from the set of the DataObjects.
     *  \param i - the row number of the DataObject that needs to be returned from the DataObjects list.
     *  \param j - the column number of the DataObject that needs to be returned from the DataObjects list.
     *  \return dataObject - the DataObject at the \a i-th row and the \a j-th column from the set of the DataObjects.
     */
    DataObject getObjectAt(int i, int j);
    /*! \fn int getObjectCount();
     *  \brief Returns the number of DataObjects in the set of DataObjects.
     *  \return dataObject - the DataObject at the \a i-th row and the \a j-th column from the set of the DataObjects.
     */
    int getObjectCount();
    /*! \fn void loadDataMatrix();
     *  \brief Loads the data to ObjectMatrix from an arff file.
     */
    void loadDataMatrix();
    /*! \fn vector<string> getFeaturesTitle();
     *  \brief Returns the titles of the features.
     *  \return featureTitles - the titles of the features
     */
    std::vector<std::string> getFeaturesTitle();
    /*! \fn void saveDataMatrix(const char*);
     *  \brief Saves the ObjectMatrix data to an arff file.
     *  \param fileName - the name of the file to save data to.
     */
    void saveDataMatrix(const char*);
    /*! \fn void clearDataObjects();
     *  \brief Clears the items from the DataObjects set.         *
     */
    void clearDataObjects();
    /*! \fn void updateDataObject(int objectIndex, int featureIndex, double newValue);
     *  \brief Updates the feature value.
     *  \param objectIndex - the index of the DataObject.
     *  \param featureIndex - the index of the feature in the DataObject.
     *  \param newValue - the new value of a feature.
     */
    void updateDataObject(int objectIndex, int featureIndex, double newValue);
    /*! \fn void updateDataObjectClass(int objectIndex, int newClass);
     *  \brief Updates the class value.
     *  \param objectIndex - the index of the DataObject.
     *  \param newClass - the new value of a class.
     */
    void updateDataObjectClass(int objectIndex, int newClass);
    /*! \fn void updateDataObject(int rowIndex, int colIndex, int featureIndex, double newValue);
     *  \brief Updates the feature value.
     *  \param rowIndex - the row index of the DataObject.
     *  \param colIndex - the column index of the DataObject.
     *  \param featureIndex - the index of the feature in the DataObject.
     *  \param newValue - the new value of a feature.
     */
    void updateDataObject(int rowIndex, int colIndex, int featureIndex, double newValue);
    /*! \fn void getWeight();
     *  \brief Returns weight of X matrix (for stress calculation)
     */
    double getWeight();
    /*! \fn bool getPrintClass();
     *  \brief shows if classes must be printed to file
     * \return if clases must be printed to file
     */
    bool getPrintClass();
    /*! \fn bool getPrintClass();
     *  \brief shows if classes must be printed to file
     * \return if clases must be printed to file
     */
    void setPrintClass(std::vector <std::string> printClass);
    /*! \fn int getClassCount();
     *  \brief returns quantity of different classes
     * \return int no of different classes
     */
    int getClassCount();

    /*! \fn void addAtributes(std::vector <std::string> addAttr);
     *  \brief Sets class attribute names
     * \param std::vector <std::string> addAttr vector of strings of class names
     */
    void addAtributes(std::vector <std::string> addAttr);
    /*! \fn std::vector <std::string> getStringClassAttributes();
     *  \brief Returns class atrribute names
     * \return std::vector <std::string> class names
     */
    std::vector <std::string> getStringClassAttributes();
    /*! \fn  void addComment(std::string comment);
     *  \brief Adds comment in arff file
     * \param std::string comment - comment
     */
    void addComment(std::string comment);
    /*! \fn bool getIsClassPresent();
     *  \brief returns the presence of the class
     * \return bool
     */
    bool getIsClassPresent();
    /*! \fn void setIsClassPresent();
     *  \brief sets the presence of classes
     */
    void setIsClassPresent();
    /*! \fn std::vector<int>getIntObjectClasses();
     *  \brief returns data section object classes in int.
     * int is the class index of the attribute class section class
     * \return std::vector<int> object classes.
     */
   // std::vector<int> getIntObjectClasses();



private:
    /*! \var vector<DataObject> DataObjects;
     *  \brief The set of DataObjects.
     */
    std::vector<DataObject> DataObjects;
    /*! \var vector<vector<DataObject> > DataObjects2D;
     *  \brief The set of the sets of DataObjects.
     */
    std::vector<std::vector<DataObject>> DataObjects2D;
    /*! \var int objectCount;
     *  \brief The number of DataObjects in the set of the DataObjects.
     */
    int objectCount;
    /*! \var double weight;
     *  \brief weight of the distances in X matrix.
     */
    double _weight;
    /*! \var vector<string> featureTitles;
     *  \brief The set of feature titles.
     */
    std::vector<std::string> featureTitles;
    /*! \var std::vector<int> objClasses
     *  \brief Holds int object class vector
     */
    std::vector<int> objClasses;
    /*! \var std::vector<std::string> additionalAttributes;
     *  \brief Holds additional attribute info
     */
    std::vector<std::string> additionalAttributes;
    /*! \var std::vector<std::string>attributeStringClasses;
     *  \brief Possible classes found in attribute section
     */
    std::vector<std::string>attributeStringClasses;
    /*! \var string fileName;
     *  \brief The file name to read the data from.
     */
    std::string fileName;
    /*! \var bool isClassPresent;
     *  \brief Indicates if the class is present in arff file.
     */
    bool isClassPresent ;
    /*! \var std::vector<std::string> comments;
     *  \brief Hols commens of the arff file.
     */
    std::vector<std::string> comments;

};
#endif // !defined(OBJECTMATIRX_H)
