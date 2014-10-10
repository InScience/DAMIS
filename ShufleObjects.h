///////////////////////////////////////////////////////////
//  ShufleObjects.h
//  Implementation of the Class ShufleObjects
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file ShufleObjects class
    \brief A class of static methods for shuffling the DataObjects in ObjectMatrix.
 */
#if !defined(SHUFLEOBJECTS_H)
#define SHUFLEOBJECTS_H

#include "ObjectMatrix.h"
#include "ShufleEnum.h"

class ShufleObjects
{

public:
    /*! \fn ShufleObjects();
    * \brief Standard constructor
    */
    ShufleObjects();
    /*! \fn virtual ~ShufleObjects();
    * \brief Standard destructor
    */
    virtual ~ShufleObjects();
    /*! \fn static vector<int> shufleObjectMatrix(ShufleEnum shufleEnum, ObjectMatrix objectMatrix);
     *  \brief Returns the list of shuffled indexes of the matrix \a objectMatrix DataObjects.
     *  \param shufleEnum - The shuffle strategy.
     *  \param objectMatrix - The matrix that DataObjects needs to be shuffled.
     *  \return shuffledIndexes - The list of shuffled indexes.
     */
    static std::vector<unsigned int> shufleObjectMatrix(ShufleEnum shufleEnum, ObjectMatrix matrix);

private:
    /*! \fn static vector<int> byBubleSort(ObjectMatrix objectMatrix);
     *  \brief Returns the list of indexes shuffled by ascending bubble sort.
     *  \param objectMatrix - The matrix that DataObjects needs to be shuffled.
     *  \return shuffledIndexes - The list of shuffled indexes.
     */
    static std::vector<unsigned int> byBubleSort(ObjectMatrix objectMatrix);
    /*! \fn static vector<int> byBubleSortDsc(ObjectMatrix objectMatrix);
     *  \brief Returns the list of indexes shuffled by descending bubble sort.
     *  \param objectMatrix - The matrix that DataObjects needs to be shuffled.
     *  \return shuffledIndexes - The list of shuffled indexes.
     */
    static std::vector<unsigned int> byBubleSortDsc(ObjectMatrix objectMatrix);
    /*! \fn static vector<int> byRand(ObjectMatrix objectMatrix);
     *  \brief Returns the list of indexes shuffled randomly.
     *  \param objectMatrix - The matrix that DataObjects needs to be shuffled.
     *  \return shuffledIndexes - The list of shuffled indexes.
     */
    static std::vector<unsigned int> byRand(ObjectMatrix objectMatrix);

};
#endif // !defined(SHUFLEOBJECTS_H)
