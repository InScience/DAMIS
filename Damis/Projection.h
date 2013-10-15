/* 
 * File:   Projection.h
 * Author: mindaugas
 *
 * Created on October 15, 2013, 9:48 AM
 */

#ifndef PROJECTION_H
#define	PROJECTION_H

#include "ObjectMatrix.h"
#include "ProjectionEnum.h"

class Projection
{

public:
	Projection();
	virtual ~Projection();

	static ObjectMatrix projectMatrix(ProjectionEnum projEnum, ObjectMatrix objectMatrix);

private:
	static ObjectMatrix byDispersion(ObjectMatrix objectMatrix);
	static ObjectMatrix byPCA(ObjectMatrix objectMatrix);
};

#endif	/* PROJECTION_H */

