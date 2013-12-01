///////////////////////////////////////////////////////////
//  MDS.h
//  Implementation of the Class MDS
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_CDF28449_1ACC_4a74_A6EB_47124922ACEA__INCLUDED_)
#define EA_CDF28449_1ACC_4a74_A6EB_47124922ACEA__INCLUDED_

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
        * An overloaded constructor that accepts the initial matrix, epsilon, number of iterations and dimension.
        */
        MDS(ObjectMatrix initialMatrix, double eps, int maxIter, int d);
        /** \fn int getIteration();
         *  \brief Returns the number of iterations performed.
         * \return iteration - the number of iterations performed.
         */
        int getIteration();
        /** \fn vector<double> getStressErrors();
         *  \brief Returns the list of stress errors.
         * \return stressErrors - the list of the stress errors.
         */
        std::vector<double> getStressErrors();
protected:
        /** \fn double getEpsilon();
         *  \brief Returns the value of the \a epsilon. 
         *  \return epsilon
         */
	double getEpsilon();
        /** \fn double getGutman();
         *  \brief Calculates the matrix of the Gutman. 
         *  \return gutman - an object of the class \a ObjectMatrix.
         */
	ObjectMatrix getGutman();
        /** \fn ObjectMatrix getGutman(ObjectMatrix Y_new);
         *  \brief Calculates the matrix of the Gutman.
         *  \param Y_new - projection matrix.
         *  \return gutman - an object of the class \a ObjectMatrix.
         */
        ObjectMatrix getGutman(ObjectMatrix Y_new);
        /** \fn int getMaxIteration();
         *  \brief Returns the maximum number of iterations.
         * \return maxIteration - the maximum number of iterations.
         */
	int getMaxIteration();
        /** \fn virtual double getStress();
         *  \brief Returns the stress error value.
         *  \return error - the stress error value.
         */
	virtual double getStress();
        
	void setEpsilon(double eps);
	void setMaxIteration(int maxIter);

	double epsilon;
	int maxIteration;
        std::vector<double> stressErrors;        
private:
        double getWeight(int, int);
        ObjectMatrix gutman;
};
#endif // !defined(EA_CDF28449_1ACC_4a74_A6EB_47124922ACEA__INCLUDED_)
