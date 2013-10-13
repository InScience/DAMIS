///////////////////////////////////////////////////////////
//  HPCMethod.cpp
//  Implementation of the Class HPCMethod
//  Created on:      07-Lie-2013 20:07:30
//  Original author: Povilas
///////////////////////////////////////////////////////////

#include "HPCMethod.h"


HPCMethod::HPCMethod(){
    std::string file_name = "/home/mindaugas/cpu.arff";
    X = ObjectMatrix(file_name);
    X.loadDataMatrix();
}


HPCMethod::~HPCMethod(){

}

/**
 * Sends SOAP message. The message must include such data about each completed
 * algorithm: algorithm stress error, computation time
 */
void HPCMethod::sendMessage(){

}
