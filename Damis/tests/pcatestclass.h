/*
 * File:   pcatestclass.h
 * Author: mindaugas
 *
 * Created on Sep 17, 2013, 3:14:47 PM
 */

#ifndef PCATESTCLASS_H
#define	PCATESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class pcatestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(pcatestclass);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    pcatestclass();
    virtual ~pcatestclass();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif	/* PCATESTCLASS_H */

