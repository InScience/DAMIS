/*
 * File:   pcatestclass.cpp
 * Author: mindaugas
 *
 * Created on Sep 17, 2013, 3:14:47 PM
 */

#include "pcatestclass.h"


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
    
    CPPUNIT_ASSERT(true);
}

void pcatestclass::testFailedMethod() {
    CPPUNIT_ASSERT(true);
}

