///////////////////////////////////////////////////////////
//  DMA.h
//  Implementation of the Class DMA
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////
/*! \file DMA class
    \brief A class of methods and attributes for DMA algorithm.
 */
#if !defined(DMA_H)
#define DMA_H

#include "ObjectMatrix.h"
#include "MDS.h"

class DMA : public MDS
{

public:
    /*! \fn DMA();
    * \brief A default constructor.
    */
    DMA();
    /*! \fn ~DMA();
    * \brief A default destructor.
    */
    virtual ~DMA();
    /*! \fn DMA(double eps, int maxIter, int d, int neighbours);
     *  \brief An overloaded constructor.
     *  \param double eps - erro between two subsequent projections
     * \param int maxIter - maximum iterations to perform.
     * \param int d - projection dimmension.
     * \param int neighbours - quantity of neighbours to rely on.
    */
    DMA(double eps, int maxIter, int d, int neighbours);
    /*! \fn int getNeighbours();
     *  \brief Returns the number of neighbours.
     *  \return neighbourNumber - the number of neighbours.
    */
    int getNeighbours();
    /*! \fn setNeighbours(int neighbours);
     *  \brief Sets the number of neighbours.
     *  \param neighbours - the number of neighbours.
    */
    void setNeighbours(int neighbours);
    /*! \fn virtual ObjectMatrix getProjection();
     *  \brief Returns the projection Y of matrix X.
     *  \return ObjectMatrix - an object of projected matrix.
     */
    virtual ObjectMatrix getProjection();

private:
    /*! \var int neighbourNumber;
     *  \brief A number of neighbours.
     */
    int neighbourNumber;
    /*! \fn void shuffle();
     *  \brief Shuffles the initial matrix X and projection matrix Y.
     */
    void shuffle();
    /*! \fn int getV(int i);
     *  \brief Calculates the number of neighbours around a point [i][i].
     *  \param int i - The diagonal point index.
     *  \return neighbours - The number of neighbours.
     */
    int getV(int i);
    /*! \var int m;
     *  \brief The number of DataObjects in matrix X.
     */
    int m;
    /*! \var  std::vector<unsigned int>;
     *  \brief Holds shuffling indices of an object matrix.
     */
    std::vector<unsigned int> shufledIndexes;
};
#endif // !defined(DMA_H)
