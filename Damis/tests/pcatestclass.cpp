/*
 * File:   pcatestclass.cpp
 * Author: mindaugas
 *
 * Created on Sep 17, 2013, 3:14:47 PM
 */

#include "pcatestclass.h"
#include "../ObjectMatrix.h"
#include "../PCA.h"

CPPUNIT_TEST_SUITE_REGISTRATION(pcatestclass);

pcatestclass::pcatestclass() {
}

pcatestclass::~pcatestclass() {
}

void pcatestclass::setUp() {
}

void pcatestclass::tearDown() {
}

void pcatestclass::testMethod() {
    ObjectMatrix omx("cpu.arff");
    int n = omx.getObjectCount();
    int d = 2;
    bool ats = false;
    PCA pca_test(omx, d);
    pca_test.toDataType();
    ObjectMatrix Y = pca_test.getY();
    if (Y.getObjectCount() == n && Y.getObjectAt(0).getItems().size() == d)
        ats = true;
    CPPUNIT_ASSERT(ats);
}

void pcatestclass::testFailedMethod() {
    CPPUNIT_ASSERT(true);
}

