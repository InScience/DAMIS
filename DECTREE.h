#ifndef DECTREE_H
#define DECTREE_H

#include "ClusterizationMethods.h"

    /*! \file DECTREE
     *  \brief Class that implements decision tree algorithm.
     */
class DECTREE : public ClusterizationMethods
{
    public:
    /*! \fn DECTREE();
     *  \brief A default constructor
     */
        DECTREE();
    /*! \fn  DECTREE(double dL, double dT, double toToNoise, int noOfTrees);
     *  \brief Returns the class label.
     *  \param double dL - relative quantity of the object used in learning.
     *  \param double dt - relative quantity of objects used in training.
     *  \param double toNoise - noise suppresion parameter.
     *  \param noOfTrees - number of trees in decision forest
     */
        DECTREE(double dL, double dT, double toToNoise, int noOfTrees);
    /*! \fn ~DECTREE();
     *  \brief A standard destructor.
     */
        virtual ~DECTREE();

    /*! \fn virtual ObjectMatrix getProjection();
     *  \brief Returns the projection matrix \a Y of matrix \a X.
     *  \return ObjectMatrix Y - the projection matrix.
     */
    virtual ObjectMatrix getProjection();
    /** \fn virtual ObjectMatrix getProjection();
     *  \brief eans average relative error when estimating posterior probability of belonging to the correct class
     *  \return double posteriori probability.
     */
    double getStress();

    protected:

    private:
    /*! \var double r;
    *  \brief nois suppresion parameter
    */
        double r;
    /*! \var int nTree
    *  \brief number of trees in the forest
    */
        int nTree;
    /*! \var alglib::ae_int_t info;
    *  \brief Holds return code, if -2 - vrong class, -1 passed incorrect prameters, 1 OK
    */
        alglib::ae_int_t info;
    /*! \var alglib::decisionforest df;
    *  \brief Decision forest
    */
        alglib::decisionforest df;
    /*! \var alglib::dfreport rep;
    *  \brief Training report structure (gen erro and etc.)
    */
        alglib::dfreport rep;

};

#endif // DECTREE_H
