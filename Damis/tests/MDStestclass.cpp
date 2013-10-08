/*
 * File:   MDStestclass.cpp
 * Author: mindaugas
 *
 * Created on Sep 23, 2013, 2:59:39 AM
 */

#include "MDStestclass.h"
#include "../ObjectMatrix.h"
#include "../DataObject.h"


CPPUNIT_TEST_SUITE_REGISTRATION(MDStestclass);

MDStestclass::MDStestclass() {
}

MDStestclass::~MDStestclass() {
}

void MDStestclass::setUp() {
}

void MDStestclass::tearDown() {
}

void MDStestclass::GutmanMatrixDim() {
    ObjectMatrix m(2);
    std::vector<double> v1;
    std::vector<double> v2;
    v1.push_back(1); v1.push_back(2); v1.push_back(3);
    v2.push_back(1.1); v2.push_back(2.1); v2.push_back(3.2);
    m.addObject(DataObject(v1));
    m.addObject(DataObject(v2));
    CPPUNIT_ASSERT(true);
}

void MDStestclass::GutmanMatrixDistIsZero() {
    CPPUNIT_ASSERT(true);
}

void MDStestclass::GutmanMatrixDistNonZero() {
    CPPUNIT_ASSERT(true);
}

