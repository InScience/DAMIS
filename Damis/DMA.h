///////////////////////////////////////////////////////////
//  DMA.h
//  Implementation of the Class DMA
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_3155AA55_4FD7_44fa_8149_A99119949EDB__INCLUDED_)
#define EA_3155AA55_4FD7_44fa_8149_A99119949EDB__INCLUDED_

#include "ObjectMatrix.h"
#include "MDS.h"

class DMA : public MDS
{

public:
        /**
        * A default constructor.
        */
	DMA();
	virtual ~DMA();
        /**
        * An overloaded constructor that accepts epsilon (\a eps), number of iterations (\a maxIter), dimension (\a d), number of neighbors (\a neighbors) and initial ObjectMatrix (\a initialX) that needs to be projected.
        */
        DMA(double eps, int maxIter, int d, int neighbors, ObjectMatrix initialX);
        /**
        * An overloaded constructor that accepts epsilon (\a eps), number of iterations (\a maxIter), dimension (\a d), number of neighbors (\a neighbors).
        */
	DMA(double eps, int maxIter, int d, int neighbours);
        /** \fn int getNeighbours();
         *  \brief Returns the number of neighbours.
         *  \return neighbourNumber - the number of neighbours.
        */  
	int getNeighbours();
        /** \fn setNeighbours(int neighbours);
         *  \brief Sets the number of neighbours.
         *  \param neighbours - the number of neighbours.
        */ 
	void setNeighbours(int neighbours);

//protected:
        /** \fn virtual ObjectMatrix getProjection();
         *  \brief Returns the projection Y of matrix X.
         *  \return ObjectMatrix - an object of projected matrix.
         */
	virtual ObjectMatrix getProjection();

private:
        /** \var int neighbourNumber;
         *  \brief A number of neighbours.
         */
	int neighbourNumber;
        /** \var ObjectMatrix vMatrix;
         *  \brief An object of matrix V.
         */
	ObjectMatrix vMatrix;
        /** \fn getV();
         *  \brief Initializes and calculates the matrix V.
         */
	void getV();
        /** \fn void shuffle();
         *  \brief Shuffles the initial matrix X and projection matrix Y.
         */
        void shuffle();
};
#endif // !defined(EA_3155AA55_4FD7_44fa_8149_A99119949EDB__INCLUDED_)
