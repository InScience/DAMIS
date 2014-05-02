///////////////////////////////////////////////////////////
//  WebInterface.h
//  Implementation of the Interface WebInterface
//  Created on:      07-Lie-2013 20:07:32
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_708FAA0D_9033_4bbe_8F5F_F9D38B70F1A2__INCLUDED_)
#define EA_708FAA0D_9033_4bbe_8F5F_F9D38B70F1A2__INCLUDED_

/**
 * Class responsible for sending SOAP message to WebServer
 */
class WebInterface
{

public:
	WebInterface() {

	}

	virtual ~WebInterface() {

	}

	virtual void sendMessage() =0;

};
#endif // !defined(EA_708FAA0D_9033_4bbe_8F5F_F9D38B70F1A2__INCLUDED_)
