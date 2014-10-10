#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "ClusterizationMethods.h"


class DECISIONTREE : public ClusterizationMethods
{
    public:
        DECISIONTREE();
        virtual ~DECISIONTREE();

        DECISIONTREE(double dL, double dT, double tolToNoiseRatio, int noOfTrees);

    /** \fn virtual ObjectMatrix getProjection();
     *  \brief Returns the projection matrix \a Y of matrix \a X.
     *  \return Y - the projection matrix.
     */
    virtual ObjectMatrix getProjection();

    double getStress();

    protected:

    private:
        //no of trees
        int nTree = 0;
        //tolerance to noise ratio std 0.66 ranges 0-1
        double r = 0.0;
};

#endif // DECISIONTREE_H
