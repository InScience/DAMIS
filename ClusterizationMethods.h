///////////////////////////////////////////////////////////
//  ClusterizationMethods.h
//  Implementation of the Class ClusterizationMethod
//  Created on:      27-Kov-2014 12:52:15
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(CLUSTERIZATIONMETHODS_H)
#define CLUSTERIZATIONMETHODS_H

#include "DimReductionMethod.h"
#include "alglib/dataanalysis.h"

/*! \file Clusterization
 * \brief that combines clusterization methods. Class provides the number of found
 * classes method and the pure virtual function get Clusterization
 */
class ClusterizationMethods : public DimReductionMethod
{

public:
    /*! \fn ClusterizationMethods();
    *  \brief A standard constructor
    */
    ClusterizationMethods();

    /*! \fn ClusterizationMethods(int noOfClusters);
    *  \brief Overloaded constructor that accepts and initializes the number of clusters.
    * \param int noOfClusters
    */
    ClusterizationMethods(int noOfClusters);
    /*! \fn ~ClusterizationMethods();
    *  \brief A standard destructor
    */
    virtual ~ClusterizationMethods();

protected:
// TODO (Povilas#1#): Change all getProjectipon to run, since claserization methods does not have meaning of getProjection

    /*! \fn int getNoOfReturnRows();
    *  \brief Returns number of rows of the input data.
    *  \return int - number of data rows .
    */
    int getNoOfReturnRows();
    /*! \fn int getNoOfClusters();
    *  \brief Returns number of clusters
    *  \return int - number of clusters.
    */
    int getNoOfClusters();
    /*! \fn void setNoOfReturnRows(int k);
    *  \brief Sets number of retrun rows.
    * \param int k - number of rows.
    *  \return void.
    */
    void setNoOfReturnRows(int k);
    /*! \fn int getNoOfReturnRowFeatures();
    *  \brief Returns row feature quantity.
    *  \return int - feature count.
    */
    int getNoOfReturnRowFeatures();
    /*! \fn void setNoOfReturnRowFeatures(int f);
    *  \brief Sets number of features in the return data.
    * \param int f number of features of one row in output data
    *  \return void.
    */
    void setNoOfReturnRowFeatures(int f);
    /*! \fn void initializeYMatrix();
    *  \brief Initializes return data structure
    *  \return void.
    */
    void initializeYMatrix();
    /*! \fn initializeYMatrix(int rows, int cols);
    *  \brief Initializes return data structure (rows and columns provided)
    * \param int rows - with number of rows
    * \param int cols - with number of cols
    *  \return void.
    */
    void initializeYMatrix(int rows, int cols);
    /*! \fn void setYMatrixDimensions(int rows, int cols);
    *  \brief Set output Y matrix dimensions
    * \param int rows - Rows of the matrix
    * \param int cols - Columns of the matrix
    *  \return void.
    */
    void setYMatrixDimensions(int rows, int cols);
    //matrix that holds the return data
        /*! \fn static void writeStatData(std::string statFile, double err, double calcTime);
    *  \brief Writes satistical data to a file.
    * \param std::string path to file.
    * \param double algorithm error
    * \param double calculation time in seconds
    *  \return void.
    */
    ObjectMatrix Y;
    //initialize input data
        /*! \fn static void writeStatData(std::string statFile, double err, double calcTime);
    *  \brief Writes satistical data to a file.
    * \param std::string path to file.
    * \param double algorithm error
    * \param double calculation time in seconds
    *  \return void.
    */
    void initializeData(double dL, double dT);
    //initialize dL + dT matrix
        /*! \fn static void writeStatData(std::string statFile, double err, double calcTime);
    *  \brief Writes satistical data to a file.
    * \param std::string path to file.
    * \param double algorithm error
    * \param double calculation time in seconds
    *  \return void.
    */
    void initializeData();

    /*!
     * Holds size of test object set
     */
        int testObjQtty ;//= 0;
    /*!
     * Holds size of learning object set
     */
        int learnObjQtty ;// = 0;
    /*!
     * Holds quantty of object with uknown class
     */
        int uknownClassObjQtty ;//= 0;
    /*!
     * Alglib data structure for learn set
     */
        alglib::real_2d_array learnSet;
    /*!
     * Alglib data structure for test set
     */
        alglib::real_2d_array testSet;
    /*!
     * Holds object indexes
     */
        std::vector <int> objectIndex;

private:
    /*! \fn void initializeXMatrix();
     *  \brief A method that initializes X matrix.
     *  \return void.
     */
    void initializeXMatrix();
    /*! \var int noOfClusters;
     * \brief Holds number of clusters (Y matrix rows)
     */
    int noOfClusters;
    /*! \var int noOfFeatures;
     *  \brief Holds number of row features (Y row feature count)
     */
    int noOfFeatures;
    /*! \var int noOfRows;
     * \brief Holds number of rows (Y row count)
     */
    int noOfRows;
};
#endif //!defined(CLUSTERIZATIONMETHODS_H)
