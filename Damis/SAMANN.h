///////////////////////////////////////////////////////////
//  SAMANN.h
//  Implementation of the Class SAMANN
//  Created on:      07-Lie-2013 20:07:31
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file SAMANN class
    \brief A class of methods and attributes for SAMANN algorithm.
 */
#if !defined(EA_F0DCD72D_78A3_4631_BA37_85170CEDA2B0__INCLUDED_)
#define EA_F0DCD72D_78A3_4631_BA37_85170CEDA2B0__INCLUDED_

#include "ObjectMatrix.h"
#include "DimReductionMethod.h"

class SAMANN : public DimReductionMethod
{

public:
        /**
        * A default constructor.
        */
	SAMANN();
        /**
        * A destructor.
        */
	virtual ~SAMANN();
        /**
        * Constructor that takes, no of learning elements, no of neurons in hidden layer,
        * learning speed value, and number of max training iterations.
 */
	SAMANN(int m1, int nl, double eta, int maxIter);
        /** \fn vector<double> getStressErrors();
         *  \brief Returns the stress errors calculated after each iteration.
         *  \return list - the list of stress errors.
         */
        std::vector<double> getStressErrors();
        /** \fn virtual ObjectMatrix getProjection();
         *  \brief Returns the projection matrix \a Y of matrix \a X.
         *  \return Y - the projection matrix.
         */
	virtual ObjectMatrix getProjection();
        /** \fn double getStress();
         *  \brief Returns the stress error value
         *  \return stressError - The stress error value.
         */
	double getStress();
private:
	/**
	 * Learning speed value
	 */
	double eta;
	/**
	 * SAMAN lambda value
	 */
	double lambda;
	/**
	 * Number of maximum Iterations
	 */
	int maxIteration;
	/**
	 * Number of training elements
	 */
	int mTrain;
	/**
	 * Number of neurons in hidden layer
	 */
	int nNeurons;
	/**
	 * Matrix represents SAMAN algorithm training set.
	 */
	ObjectMatrix Xp;
        /** \var ObjectMatrix Y_pasl;
         *  \brief Hidden layer matrix.
         */
        ObjectMatrix Y_pasl;
        /** \var ObjectMatrix Y_is;
         *  \brief Exit layer matrix.
         */
        ObjectMatrix Y_is;
        /** \var ObjectMatrix delta_L;
         *  \brief Exit layer matrix.
         */
        ObjectMatrix delta_L;
        /** \var vector<vector<double> > w1;
         *  \brief The weights of the first hidden layer.
         */
        std::vector<std::vector<double> > w1;
        /** \var vector<vector<double> > w2;
         *  \brief The weights of the second hidden layer.
         */
        std::vector<std::vector<double> > w2;
        /** \var vector<double> stressErrors;
         *  \brief The list of stress errors calculated after each iteration.
         */
        std::vector<double> stressErrors;
        /** \fn double getLambda();
         *  \brief Returns the lambda value.
         *  \return lambda 
         */
	double getLambda();
        /** \fn void initializeWeights();
         *  \brief Initializes weights \a w1 and \a w2.
         */
        void initializeWeights(); 
        /** \fn void initializeExitMatrixes();
         *  \brief Initializes matrices \a Y_is and \a Y_pasl.
         */
        void initializeExitMatrixes();
        /** \fn void initializeDeltaL(); 
         *  \brief Initializes \a delta_L matrix.
         */
        void initializeDeltaL();
        /** \fn double getMax();
         *  \brief Returns the maximum Euclidean distance between DataObjects.
         *  \return dist - The maximum Euclidean distance between DataObjects
         */
        double getMax();
        /** \fn void NormalizeX();
         *  \brief Normalizes matrix \a X.
         */
        void NormalizeX();
        /** \fn void getXp();
         *  \brief Forms the matrix \a Xp.
         */
        void getXp();
        /** \fn bool isIdentical(DataObject dataObject);
         *  \brief Checks if there are identical DataObjects to \a dataObject in an \a Xp matrix.
         *  \param dataObject - The DataObject that needs to be checked out.
         *  \return answer - The boolean value, i.e. if \a true - it means that there are already such DataObject,
         *  \a false - otherwise.
         */
        bool isIdentical(DataObject dataObject);
};
#endif // !defined(EA_F0DCD72D_78A3_4631_BA37_85170CEDA2B0__INCLUDED_)
