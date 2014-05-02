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

class ARFF
{
public:
    /**
     * A default constructor.
     */
    ARFF();
    /**
     * An overloaded constructor that accepts the path of an arff file.
     */
    ARFF(const char* path);
    /**
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
     */
    void writeData(const char* file, std::vector<DataObject> dataObject);
    /*! \fn string getFailReason();
     *  \brief A method that returns the reason of unsuccessful read of an arff file.
     *  \return failReason - the message of type \a string.
     */
    std::string getFailReason();
    /*! \fn bool isCorrectlyFormated();
     *  \brief A method that returns the indicator value of successful file reading.
     *  \return readSuccess - boolean value.
     */
    bool isSuccessfullyRead();
    /*! \fn void writeStatData(std::string statFile, double err, double calcTime);
    *  \brief Writes algorihtm erro and calculation time to file.
    *  \param statFile - file path to be written to.
    *  \param err - algorithm error.
    *\param calcTime - algorithm run time.
    *  \return array - a two-dimensional array of doubles.
    */
    static void writeStatData(std::string statFile, double err, double calcTime);

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
};

#endif	/* ARFF_H */

