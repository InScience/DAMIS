/*
 * File:   arff.h
 * Author: mindaugas
 *
 * Created on August 28, 2013, 10:01 PM
 */

/*! \file ARFF class
 *  \brief A class for reading data from or writing data to an arff file.

 */

#ifndef ARFF_H
#define	ARFF_H

#include <vector>
#include <string>
#include "DataObject.h"
    /*!
    * Class that represents ARFF file object
    */
class ARFF
{
public:
    /*!
     * A default constructor.
     */
    ARFF();
    /*!
     * An overloaded constructor that accepts the path of an arff file.
     */
    ARFF(const char* path);
    /*!
     * A destructor.
     */
    ~ARFF();

    /*! \fn vector<string> getAttributes();
     *  \brief A method that returns the titles of the features.
     *  \return attributes - the vector of features titles.
     */
    std::vector<std::string> getAttributes();
    /*! \fn vector<string> getAttributesTypes();
     *  \brief A method that returns the data types of the features.
     *  \return attributesTypes - the vector of data type titles.
     */
    std::vector<std::string> getAttributesTypes();
    /*! \fn vector<vector<double> > getData();
     *  \brief A method that reads data from an arff file.
     *  \return data - the vector of vectors of doubles.
     */
    std::vector<std::vector<double> > getData();
    /*! \fn void writeData(const char* file, vector<DataObject> dataObject);
     *  \brief A method that writes data to an arff file.
     *  \param file - the path of a file.
     *  \param dataObject - the vector of DataObjects to write to a file \a file.
     *  \param wClass - the vector of class labels to write to a file \a file.
     */
    void writeData(const char* file, std::vector<std::string> comments, std::vector<DataObject> dataObject, std::vector<std::string> wClass, std::vector<std::string> attributeLabels);
    /*! \brief Returns attribute section list of classes as int enumerated values
    *   \return std::vector<int>
    */
    std::vector<int> getAttributeClasses ();
    /*! \brief Returns attribute section list of classes
    *   \return std::vector<std::string>
    */
    std::vector <std::string> getAttributeStringClasses();

    /*! \fn string getFailReason();
     *  \brief A method that returns the reason of unsuccessful read of an arff file.
     *  \return failReason - the message of type \a string.
     */
    std::string getFailReason();
    /*! \fn bool isSuccessfullyRead();
     *  \brief A method that returns the indicator value of successful file reading.
     *  \return readSuccess - boolean value.
     */
    bool isSuccessfullyRead();
    /*! \fn bool isClassFound();
    *  \brief Indicates if class is found in arff file.
    *  \return isClassFound - boolean value.
    */
    bool isClassFound();
    /*! \fn std::vector<int> getIntClass();
    *  \brief Returns classes as int values.
    *  \return std::vector<int> - vector of int's.
    */
    std::vector<int> getIntClass();
    /*! \fn int getObjectClass(int i);
    *  \brief Returns class class of the i-th object.
    * \param int i-th object
    *  \return int - class value in int mapping.
    */
    int getObjectClass(int i);
    /*! \fn static void writeStatData(std::string statFile, double err, double calcTime);
    *  \brief Writes satistical data to a file.
    * \param std::string path to file.
    * \param double algorithm error
    * \param double calculation time in seconds
    *  \return void.
    */
    static void writeStatData(std::string statFile, double err, double calcTime);
    /*! \var std::vector<int> objIntClass;
     *  \brief ector holds data section object classes mapped into int type.
     */
    std::vector<int> objIntClass;

private:
    /*! \var vector<vector<double> > data;
     *  \brief The actual data read from an arff file.
     */
    std::vector<std::vector<double>> data;
    /*! \var vector<string> attributes;
     *  \brief The titles of the features.
     */
    std::vector<std::string> attributes;
    /*! \var vector<string> attributesTypes;
     *  \brief The titles of the features data types.
     */
    std::vector<std::string> attributesTypes;
    /*! \var string failReason;
     *  \brief The reason of the unsuccessful read of the file.
     */
    std::string failReason;
    /*! \var bool readSuccess;
     *  \brief The indicator of the successful file read.
     * If it's value is \a true, the file is successfully read, if \a false, the file is not successfully read.
     */
    bool readSuccess;
    /*! \var const char *fileToRead;
     *  \brief Input data file.
     */
    const char *fileToRead;
    /*! \var bool classFound
     *  \brief Indicates if calss attribute is found.
     */
    bool classFound;// = false;
    /*! \var int classAttributeIndex
     *  \brief Holds index of the class attribute.
     */
    int classAttributeIndex;
    /*! \var std::vector<int> attributeIntClass;
     *  \brief Vector of int class attributes.
     */
    std::vector<int> attributeIntClass;
    /*! \var std::vector<std::string> attributeStringClass;
     *  \brief Vector of std::string class attributes.
     */
    std::vector<std::string>attributeStringClass;
    /*! \fn  void readArffFile();
    *  \brief Reads the arff file.
    *  \return void.
    */
    void readArffFile();
};

#endif	/* ARFF_H */

