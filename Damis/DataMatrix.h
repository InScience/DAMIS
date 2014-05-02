///////////////////////////////////////////////////////////
//  DataMatrix.h
//  Implementation of the Interface DataMatrix
//  Created on:      07-Lie-2013 20:07:29
//  Original author: Povilas
///////////////////////////////////////////////////////////

/** \class DataMatrix
 *  \brief A class of pure virtual methods for manipulating the Objectmatrix.
 */

#if !defined(EA_0D61ACEF_288D_4949_AB18_4545C1E57302__INCLUDED_)
#define EA_0D61ACEF_288D_4949_AB18_4545C1E57302__INCLUDED_

#include "ObjectMatrix.h"

class DataMatrix
{

public:
        /**
        * A default constructor.
        */
	DataMatrix() {
        }

        /**
        * A destructor.
        */
	virtual ~DataMatrix(){
        }
        /** \fn virtual void loadDataMatrix() =0;
         *  \brief A pure virtual method for loading data from an arff file.
         */
	virtual void loadDataMatrix() =0;
        /** \fn virtual void saveDataMatrix(const char*) =0;
         *  \brief A pure virtual method for saving data to an arff file.
         *  \param file - a name of the file to save data to.
         */
	virtual void saveDataMatrix(const char* file)  =0;

};
#endif // !defined(EA_0D61ACEF_288D_4949_AB18_4545C1E57302__INCLUDED_)
