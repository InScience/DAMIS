///////////////////////////////////////////////////////////
//  HPCMethod.h
//  Implementation of the Class HPCMethod
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(HPCMETHOD_H)
#define HPCMETHOD_H

#include "ObjectMatrix.h"
#include "WebInterface.h"

/*! \file HPCMethod class
 *   \brief Abstract class that aggregates ObjectMatrix X and ability to send  SOAP message
 * with data about stress error value and method computation time.
 */

class HPCMethod : public WebInterface
{

public:
    /*! \fn HPCMethod();
    * \brief A default constructor.
    */
    HPCMethod();
    /*! \fn virtual ~HPCMethod();
    * \brief A destructor.
    */
    virtual ~HPCMethod();
    /*! \var ObjectMatrix X
     *  \brief Initial input data matrix.
     */
    ObjectMatrix X;
    /*! \fn virtual void sendMessage();
     *  \brief Sends a message to Web interface.
     */
    virtual void sendMessage();

};
#endif // !defined(HPCMETHOD_H)
