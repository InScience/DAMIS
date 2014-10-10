///////////////////////////////////////////////////////////
//  PCA.h
//  Implementation of the Class PCA
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file PCA class
    \brief A class of methods and attributes for PCA algorithm.
 */
#if !defined PCA_H
#define PCA_H

#include "ObjectMatrix.h"
#include "DimReductionMethod.h"
#include "alglib/ap.h"

class PCA_ : public DimReductionMethod
{

public:
    /*! \fn PCA_();
    * \brief A default constructor.
    */
    PCA_();
    /*! \fn virtual ~PCA_();
    * \brief A destructor.
    */
    virtual ~PCA_();

    /*! \fn PCA_(double d, bool disp = true);
     * \brief An overloaded constructor that accepts the dimension or dispersion part (if disp = true).
     * \param double d - dimension or relative disperrsion
     * \param bool disp true if d mean relative dispersion false if d mean dimmension
     */
    PCA_(double d, bool disp = true);
    /*! \fn PCA_(ObjectMatrix objMatrix, int d);
     * \brief An overloaded constructor that accepts the ObjectMatrix and dimension.
     * \param ObjectMatrix objMatrix - matrix of objects
     * \param int d projection dimmension
     */
    PCA_(ObjectMatrix objMatrix, int d);
    /*! \fn virtual void toDataType();
     *  \brief Converts the ObjectMatrix to alglib's real_2d_array.
     */
    virtual void toDataType();
    /*! \fn virtual void fromDataType();
     *  \brief Converts alglib's real_2d_array to an ObjectMatrix.
     */
    virtual void fromDataType();
    /** \fn alglib::real_1d_array getEigenValues();
     *  \brief Returns the eigenvalues of the projection.
     *  \return eigValues - the eigenvalues of the projection.
     */
    alglib::real_1d_array getEigenValues();
    /** \fn virtual ObjectMatrix getProjection();
     *  \brief Returns the projection matrix.
     *  \return Y - the projection matrix.
     */
    virtual ObjectMatrix getProjection();

private:
    /*! \var double d;
     * \brief Dispersion part to retain in resulting projection
     */
    double d;
    /*! \var bool disp;
     * \brief Indicates whether dispersion part must be returned
     */
    bool disp;
    /*! \var alglib::real_2d_array alglibX;
     *  \brief The 2D alglib type matrix.
     */
    alglib::real_2d_array alglibX;
    /*! \fn void ProjectXMatrix();
     *  \brief Calculates the projection of matrix X.
     */
    void ProjectXMatrix();
    /*! \var alglib::real_1d_array eigValues;
     *  \brief The array of eigenvalues.
     */
    alglib::real_1d_array eigValues;
};
#endif
