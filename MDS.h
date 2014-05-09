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
        /**
        * A default constructor.
        */
	MDS();
        /**
        * A destructor.
        */
	virtual ~MDS();
        /**
        * An overloaded constructor that accepts the epsilon, number of iterations and dimension.
        */
	MDS(double eps, int maxIter, int d);
        /**
        * An overloaded constructor that accepts: epsilon, the number of iterations,
         * projection dimension and the initial data matrix.
        */
    MDS(double eps, int maxIter, int d, ObjectMatrix initialMatrix);
        /** \fn int getIteration();
         *  \brief Returns the number of iterations performed.
         * \return iteration - the number of iterations performed.
         */
 //   int getIteration();
        /** \fn vector<double> getStressErrors();
         *  \brief Returns the list of stress errors.
         * \return stressErrors - the list of the stress errors.
         */
 //       std::vector<double> getStressErrors();
protected:
        /** \fn double getEpsilon();
         *  \brief Returns the value of the \a epsilon.
         *  \return epsilon
         */
//	double getEpsilon();
        /** \fn ObjectMatrix getGutman();
         *  \brief Calculates the matrix of the Guttman.
         *  \return gutman - an object of the class \a ObjectMatrix.
         */
	ObjectMatrix getGutman();
        /** \fn ObjectMatrix getGutman(int neighbour);
         *  \brief Calculates the matrix of the Guttman.
         *  \param neighbour - the amount of the neighbours
         *  \return gutman - an object of the class \a ObjectMatrix.
         */
	ObjectMatrix getGutman(int neighbour);
        /** \fn ObjectMatrix getGutman(ObjectMatrix Y_new);
         *  \brief Calculates the matrix of the Guttman.
         *  \param Y_new - projection matrix.
         *  \return gutman - an object of the class \a ObjectMatrix.
         */
    ObjectMatrix getGutman(ObjectMatrix Y_new);
        /** \fn ObjectMatrix getGutman(ObjectMatrix Y_new, int j);
         *  \brief Recalculates jth row and column of the matrix of the Guttman.
         *  \param Y_new - projection matrix.
         *  \param j - columns/row to recalculate.
         *  \return gutman - an object of the class \a ObjectMatrix.
         */
    ObjectMatrix getGutman(ObjectMatrix Y_new, int j);
        /** \fn int getMaxIteration();
         *  \brief Returns the maximum number of iterations.
         * \return maxIteration - the maximum number of iterations.
         */
///	int getMaxIteration();
        /** \fn virtual double getStress();
         *  \brief Returns the stress error value.
         *  \return error - the stress error value.
         */
	//virtual double getStress();
        /** \fn void setEpsilon(double eps);
         *  \brief Sets the value of epsilon.
         *  \param eps - the epsilon value.
         */
	//void setEpsilon(double eps);
        /** \fn void setMaxIteration(int maxIter);
         *  \brief Sets the maximum number of iterations.
         *  \param maxIter - the number of iterations.
         */
	//void setMaxIteration(int maxIter);
        /** \var double epsilon;
         *  \brief Epsilon value.
         */
	double epsilon;
        /** \var int maxIteration;
         *  \brief Maximum value of iterations.
         */
	int maxIteration;
        /** \var vector<double> stressErrors;
         *  \brief The list of stress errors.
         */
        std::vector<double> stressErrors;

        /** \var ObjectMatrix gutman;
         *  \brief Gutman matrix.
         */
        ObjectMatrix gutman;


        //void initGutmanMatrix(int mSize);

private:
        /** \fn double getWeight(int i, int j);
         *  \brief Calculates the weight of the \a i-th and the \a j-th DataObjects.
         *  \param i - the \a i-th DataObject in the ObjectMatrix X.
         *  \param j - the \a j-th DataObject in the ObjectMatrix X.
         *  \return weight - the weight of the \a i-th and the \a j-th DataObjects.
         */
       // double getWeight(int i, int j);

       	        /** \fn double getStressWeight();
         *  \brief Calculates the weight of the upper left matrix triangle.
         *  \param weightType - indicates which weight should be returned according to MDS error
         *  \return weight - the weight of the upper left matrix triangle.
         */
//        virtual double getStressWeight(int weightType = 1);

};
#endif // !defined(MDS_H)
