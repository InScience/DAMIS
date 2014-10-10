/*
 * File:   Projection.h
 * Author: mindaugas
 *
 * Created on October 15, 2013, 9:48 AM
 */
/*! \file Projection class
    \brief A class of static methods for projecting the initial projection matrix.
 */
#ifndef PROJECTION_H
#define	PROJECTION_H

#include "ObjectMatrix.h"
#include "ProjectionEnum.h"

class Projection
{

public:
    /*! \fn  Projection();
    * \brief Default constructor
    */
    Projection();
    /*! \fn  Projection();
    * \brief Default destructor
    */
    virtual ~Projection();
    /*! \fn static ObjectMatrix projectMatrix(ProjectionEnum projEnum, ObjectMatrix objectMatrix);
     *  \brief Orders
     *  \param projEnum - the Enum type of projection.
     *  \param objectMatrix - the ObjectMatrix to project.
     *  \return ObjectMatrix - the projection by \a projEnum.
     */
    static ObjectMatrix projectMatrix(ProjectionEnum projEnum, ObjectMatrix objectMatrix);

private:
    /*! \fn static ObjectMatrix byDispersion(ObjectMatrix objectMatrix);
     *  \brief Projects matrix by dispersion.
     *  \param objectMatrix - The matrix that needs to be projected.
     *  \return projectionMatrix - The projected matrix.
     */
    static ObjectMatrix byDispersion(ObjectMatrix objectMatrix);
    /*! \fn static ObjectMatrix byPCA(ObjectMatrix objectMatrix);
     *  \brief Projects matrix by PCA.
     *  \param objectMatrix - The matrix that needs to be projected.
     *  \return projectionMatrix - The projected matrix.
     */
    static ObjectMatrix byPCA(ObjectMatrix objectMatrix);
    /*! \fn static ObjectMatrix byRAND(ObjectMatrix objectMatrix);
     *  \brief Projects matrix by RAND.
     *  \param objectMatrix - The matrix that needs to be projected.
     *  \return projectionMatrix - The projected matrix.
     */
    static ObjectMatrix byRand(ObjectMatrix objectMAtrix);

};

#endif	/* PROJECTION_H */

