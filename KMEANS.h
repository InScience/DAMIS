#ifndef KMEANS_H
#define KMEANS_H

#include "ClusterizationMethods.h"

/*! \file KEMEANS class
 *   \brief Class implements kmeans clustering algorithm
 */

class KMEANS : public ClusterizationMethods
{
    public:
     /*! \fn KMEANS();
     *  \brief Default constructor
     */
        KMEANS();
     /*! \fn KMEANS(int noOfClusters, int maxIter);
     *  \brief Overloaded constructor.
     * \param int noOfClusters - quantity of clusters
     * \param maxIter - macimum number of iterations.
     */
        KMEANS( int noOfClusters, int maxIter);
     /*! \fn virtual ~KMEANS();
     *   \brief default destructor.
     */
        virtual ~KMEANS();

    /*! \fn virtual ObjectMatrix getProjection();
     *  \brief Returns the projection matrix \a Y of matrix \a X.
     *  \return ObjectMatrix Y - the projection matrix.
     */
    virtual ObjectMatrix getProjection();

    /*! \fn int getNoOfClusters();
     *  \brief Returns number of clusters.
     *  \return int  - Stress error value.
     */
     int getNoOfClusters();
    /*! \fn double getStress();
     *  \brief Returns the stress error value.
     *  \return error - Stress error value.
     */
    double getStress();

    protected:

    private:
    /*! \var  int maxIter;
     *  \brief Holds maximum iteration value.
     */
        int maxIter;
     /*! \var  int noOfClusters
     *  \brief Holds number of clusters.
     */
        int noOfClusters;
};

#endif // KMEANS_H
