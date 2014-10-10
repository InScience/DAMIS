///////////////////////////////////////////////////////////
//  SMACOF.h
//  Implementation of the Class SMACOF
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file SMACOF class
    \brief A class of methods and attributes for SMACOF algorithm.
 */
#if !defined(SMACOF_H)
#define SMACOF_H

#include "ObjectMatrix.h"
#include "MDS.h"

class SMACOF : public MDS
{

public:
    /*! \fn SMACOF();
    * \brief A default constructor.
    */
    SMACOF();
    /*! \fn  virtual ~SMACOF();
    * \brief A destructor.
    */
    virtual ~SMACOF();
    /*! \fn SMACOF(double eps, int maxIter, int d);
     * \brief An overloaded constructor that accepts: epsilon, the maximum number of iterations and
     * projection dimension.
     * \param double eps - difference betwenn two errors
     * \param int maxIter - number of maximum iterations
     * \param int d - projection dimmension
     */
    SMACOF(double eps, int maxIter, int d);
    /*! \fn  SMACOF(double eps, int maxIter, int d, ObjectMatrix X, ObjectMatrix Y);
     * \brief An overloaded constructor that accepts: epsilon, the maximum number of iterations,
     * projection dimension, initial data matrix and initial projection matrix.
    * \param double eps - difference betwenn two errors
     * \param int maxIter - number of maximum iterations
     * \param int d - projection dimmension
     * \param ObjectMatrix X - X matrix
     * \param ObjectMatrix Y - initial Y matrix
     */
    SMACOF(double eps, int maxIter, int d, ObjectMatrix X, ObjectMatrix Y);
    /*! \fn SMACOF(double eps, int maxIter, int d, ObjectMatrix initialMatrix);
     * \brief An overloaded constructor that accepts: epsilon, the maximum number of iterations,
     * projection dimension, shuffling strategy and initial data matrix.
     * \param double eps - difference betwenn two errors
     * \param int maxIter - number of maximum iterations
     * \param int d - projection dimmension
     * \param ObjectMatrix initialMatrix - initial matrix
     */
    SMACOF(double eps, int maxIter, int d, ObjectMatrix initialMatrix);
    /*! \fn virtual ObjectMatrix getProjection();
     *  \brief Returns the projection matrix \a Y of matrix \a X.
     *  \return Y - the projection matrix.
     */
    virtual ObjectMatrix getProjection();
    /*! \fn double getStress();
     *  \brief Returns the stress error value.
     *  \return error - Stress error value.
     */
    double getStress();

private:
    /*! \var bool readFile;
     *  \brief Shows how stress should be calculated either read from file o  calc on the fly X distances.
     */
    bool readFile;
};
#endif // !defined(SMACOF_H)
