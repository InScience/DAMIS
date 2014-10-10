///////////////////////////////////////////////////////////
//  MDS.h
//  Implementation of the Class MDS
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file MDS class
    \brief A class of methods and attributes for MDS algorithms.
 */
#if !defined(MDS_H)
#define MDS_H

#include "ObjectMatrix.h"
#include "DimReductionMethod.h"

class MDS : public DimReductionMethod
{

public:
    /*! \fn MDS();
    * \brief A default constructor.
    */
    MDS();
    /*! \fn virtual ~MDS();
    * \brief A destructor.
    */
    virtual ~MDS();
    /*! \fn MDS(double eps, int maxIter, int d);
    * \brief An overloaded constructor.
    * \param  double eps - difference between two errors after two subsequent iterations
    * \param  int maxIter number of iterations
    * \param int d dimension.
    */
    MDS(double eps, int maxIter, int d);
    /*! \fn MDS(double eps, int maxIter, int d, ObjectMatrix initialMatrix);
    * \brief An overloaded constructor.
    * \param  double eps - difference between two errors after two subsequent iterations
    * \param  int maxIter number of iterations
    * \param int d dimension.
    * \param ObjectMatrix initialMatrix starting position of the projection
    */
    MDS(double eps, int maxIter, int d, ObjectMatrix initialMatrix);

protected:

    /*! \fn ObjectMatrix getGutman();
     *  \brief Calculates the matrix of the Guttman.
     *  \return gutman - an object of the class \a ObjectMatrix.
     */
    ObjectMatrix getGutman();
    /*! \fn ObjectMatrix getGutman(int neighbour);
     *  \brief Calculates the matrix of the Guttman.
     *  \param neighbour - the amount of the neighbours
     *  \return gutman - an object of the class \a ObjectMatrix.
     */
    ObjectMatrix getGutman(int neighbour);
    /*! \fn ObjectMatrix getGutman(ObjectMatrix Y_new);
     *  \brief Calculates the matrix of the Guttman.
     *  \param Y_new - projection matrix.
     *  \return gutman - an object of the class \a ObjectMatrix.
     */
    ObjectMatrix getGutman(ObjectMatrix Y_new);
    /*! \fn ObjectMatrix getGutman(ObjectMatrix Y_new, int j);
     *  \brief Recalculates jth row and column of the matrix of the Guttman.
     *  \param Y_new - projection matrix.
     *  \param j - columns/row to recalculate.
     *  \return gutman - an object of the class \a ObjectMatrix.
     */
    ObjectMatrix getGutman(ObjectMatrix Y_new, int j);
    /*! \var double epsilon;
     *  \brief Epsilon value.
     */
    double epsilon;
    /*! \var int maxIteration;
     *  \brief Maximum value of iterations.
     */
    int maxIteration;
    /*! \var vector<double> stressErrors;
     *  \brief The list of stress errors.
     */
    std::vector<double> stressErrors;
    /*! \var ObjectMatrix gutman;
     *  \brief Gutman matrix.
     */
    ObjectMatrix gutman;
};
#endif // !defined(MDS_H)
