///////////////////////////////////////////////////////////
//  SMACOFZEIDEL.h
//  Implementation of the Class SMACOFZEIDEL
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file SMACOFZEIDEL class
    \brief A class of methods and attributes for SMACOFZEIDEL algorithm.
 */
#if !defined(SMACOFZEIDEL_H)
#define SMACOFZEIDEL_H

#include "ObjectMatrix.h"
#include "SMACOF.h"
#include "ShufleEnum.h"

class SMACOFZEIDEL : public SMACOF
{

public:
    /*! \fn SMACOFZEIDEL();
    * \brief A default constructor.
    */
    SMACOFZEIDEL();
    /*! \fn virtual ~SMACOFZEIDEL();
    * \brief A destructor.
    */
    virtual ~SMACOFZEIDEL();
    /*! \fn SMACOFZEIDEL(double eps, int maxIter, int d, ShufleEnum shEnum);
     * \brief An overloaded constructor that accepts: epsilon, the maximum number of iterations,
     * projection dimension and shuffling strategy.
     * \param double eps - difference betwenn two errors
     * \param int maxIter - number of maximum iterations
     * \param int d - projection dimmension
     * \param ShufleEnum shEnum - object shufling strategy
     */
    SMACOFZEIDEL(double eps, int maxIter, int d, ShufleEnum shEnum);
    /*! \fn virtual ObjectMatrix getProjection();
     *  \brief Returns the projection matrix \a Y of matrix \a X.
     *  \return Y - the projection matrix.
     */
    virtual ObjectMatrix getProjection();
private:
    /*! \var ShufleEnum shufleEnum;
     *  \brief Shuffle enum.
     */
    ShufleEnum shufleEnum;
};
#endif // !defined(SMACOFZEIDEL_H)
