///////////////////////////////////////////////////////////
//  HPCMethod.cpp
//  Implementation of the Class HPCMethod
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

/*! \class HPCMethod
 *   \brief Abstract class that aggregates ObjectMatrix X and ability to send  SOAP message
 * with data about stress error value and method computation time.
 */

#include "HPCMethod.h"


HPCMethod::HPCMethod(){
    std::string file_name = "arff_files/iris.arff";
    X = ObjectMatrix(file_name);
    X.loadDataMatrix();
}


HPCMethod::~HPCMethod(){

}

void HPCMethod::sendMessage(){

}
