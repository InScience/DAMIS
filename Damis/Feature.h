///////////////////////////////////////////////////////////
//  Feature.h
//  Implementation of the Class Feature
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#if !defined(EA_EE2D36D2_3B93_478e_A088_CEF5667699A9__INCLUDED_)
#define EA_EE2D36D2_3B93_478e_A088_CEF5667699A9__INCLUDED_

class Feature
{

public:
	Feature();
	virtual ~Feature();

	Feature(float feature);
	float getFeature();

private:
	float feature;

};
#endif // !defined(EA_EE2D36D2_3B93_478e_A088_CEF5667699A9__INCLUDED_)
