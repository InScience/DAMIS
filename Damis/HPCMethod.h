///////////////////////////////////////////////////////////
//  HPCMethod.h
//  Implementation of the Class HPCMethod
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_C30BAF2D_F989_4624_9B14_AC72555B02B9__INCLUDED_)
#define EA_C30BAF2D_F989_4624_9B14_AC72555B02B9__INCLUDED_

#include "ObjectMatrix.h"
#include "WebInterface.h"

/**
 * Abstract class that aggregates ObjectMatrix X and ability to send  SOAP message
 * with data about stress error value and method computation time
 */
class HPCMethod : public WebInterface
{

public:
        /**
        * A default constructor.
        */
	HPCMethod();
        /**
        * A destructor.
        */
	virtual ~HPCMethod();
        /** \var ObjectMatrix X
         *  \brief Initial data matrix.
         */
	ObjectMatrix X;
        /** \fn virtual void sendMessage();
         *  \brief Sends a message to Web interface.
         */
	virtual void sendMessage();

};
#endif // !defined(EA_C30BAF2D_F989_4624_9B14_AC72555B02B9__INCLUDED_)
