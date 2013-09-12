///////////////////////////////////////////////////////////
//  ExternalMethods.h
//  Implementation of the Interface ExternalMethods
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_0CF9EC4B_D778_4484_AEDE_6B5BF3207ECC__INCLUDED_)
#define EA_0CF9EC4B_D778_4484_AEDE_6B5BF3207ECC__INCLUDED_

class ExternalMethods
{

public:
	ExternalMethods() {

	}

	virtual ~ExternalMethods() {

	}

	virtual void fromDataType() =0;
	virtual void toDataType() =0;

};
#endif // !defined(EA_0CF9EC4B_D778_4484_AEDE_6B5BF3207ECC__INCLUDED_)
