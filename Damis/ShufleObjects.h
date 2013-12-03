///////////////////////////////////////////////////////////
//  ShufleObjects.h
//  Implementation of the Class ShufleObjects
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file ShufleObjects class
    \brief A class of static methods for shuffling the DataObjects in ObjectMatrix.
 */
#if !defined(EA_02DD92AD_FC82_4feb_8A22_24C00CD534BA__INCLUDED_)
#define EA_02DD92AD_FC82_4feb_8A22_24C00CD534BA__INCLUDED_

#include "ObjectMatrix.h"
#include "ShufleEnum.h"

class ShufleObjects
{

public:
	ShufleObjects();
	virtual ~ShufleObjects();
        /** \fn static vector<int> shufleObjectMatrix(ShufleEnum shufleEnum, ObjectMatrix objectMatrix);
         *  \brief Returns the list of shuffled indexes of the matrix \a objectMatrix DataObjects.
         *  \param shufleEnum - The shuffle strategy.
         *  \param objectMatrix - The matrix that DataObjects needs to be shuffled.
         *  \return shuffledIndexes - The list of shuffled indexes. 
         */
	static std::vector<int> shufleObjectMatrix(ShufleEnum shufleEnum, ObjectMatrix matrix);

private:
        /** \fn static vector<int> byBubleSort(ObjectMatrix objectMatrix);
         *  \brief Returns the list of indexes shuffled by ascending bubble sort.
         *  \param objectMatrix - The matrix that DataObjects needs to be shuffled.
         *  \return shuffledIndexes - The list of shuffled indexes.
         */
	static std::vector<int> byBubleSort(ObjectMatrix objectMatrix);
        /** \fn static vector<int> byBubleSortDsc(ObjectMatrix objectMatrix);
         *  \brief Returns the list of indexes shuffled by descending bubble sort.
         *  \param objectMatrix - The matrix that DataObjects needs to be shuffled.
         *  \return shuffledIndexes - The list of shuffled indexes.
         */
        static std::vector<int> byBubleSortDsc(ObjectMatrix objectMatrix);
        /** \fn static vector<int> byRand(ObjectMatrix objectMatrix);
         *  \brief Returns the list of indexes shuffled randomly.
         *  \param objectMatrix - The matrix that DataObjects needs to be shuffled.
         *  \return shuffledIndexes - The list of shuffled indexes.
         */
	static std::vector<int> byRand(ObjectMatrix objectMatrix);

};
#endif // !defined(EA_02DD92AD_FC82_4feb_8A22_24C00CD534BA__INCLUDED_)
