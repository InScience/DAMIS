///////////////////////////////////////////////////////////
//  DimReductionMethod.h
//  Implementation of the Class DimReductionMethod
//  Created on:      07-Lie-2013 20:07:29
//  Original author: Povilas
///////////////////////////////////////////////////////////
#if !defined(DIMREDUCTIONMETHOD_H)
#define DIMREDUCTIONMETHOD_H

#include "ObjectMatrix.h"
#include "HPCMethod.h"
/*! \file DimReductionMethod class
    \brief A class of methods and attributes for initialization of projection matrix.
 */
class DimReductionMethod : public HPCMethod
{

public:
    /*! \fn DimReductionMethod();
    * \brief A default constructor.
    */
    DimReductionMethod();
    /*! \fn virtual ~DimReductionMethod();
    * \brief A destructor.
    */
    virtual ~DimReductionMethod();
    /*! \fn virtual double getStress();
     *  \brief Returns the stress error value.
     *  \return error - The stress error value.
     */
    virtual double getStress();

protected:
    /*! \var int d;
     * \brief Projection Dimmension
     */
    int d;
    /*! \var ObjectMatrix Y;
     * \brief result matrix.
     */
    ObjectMatrix Y;
    /*! \fn ObjectMatrix getProjection();
     *  \brief A pure virtual function that returns the projection matrix.
     *  \return Y - an object of ObjectMatrix class.
     */
    virtual ObjectMatrix getProjection() =0;
    /*! \fn int getProjectionDimension();
     *  \brief Returns the dimension of the projection.
     *  \return d - a dimension projection.
     */
    int getProjectionDimension();
    /*! \fn void initializeProjectionMatrix();
     *  \brief Initializes the projection matrix.
     * \return void.
     */
    void initializeProjectionMatrix();
    /*! \fn void setProjectionDimension(int dimension);
     *  \brief Sets the projection dimension.
     *  \param dimension - a value assigned to \a d.
     *  \return void.
     */
    void setProjectionDimension(int dimension);
};
#endif // !defined(DIMREDUCTIONMETHOD_H)
