/*
 * File:   MDStestclass.h
 * Author: mindaugas
 *
 * Created on Sep 23, 2013, 2:59:39 AM
 */

#ifndef MDSTESTCLASS_H
#define	MDSTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class MDStestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(MDStestclass);

    CPPUNIT_TEST(GutmanMatrixDim);
    CPPUNIT_TEST(GutmanMatrixDistIsZero);
    CPPUNIT_TEST(GutmanMatrixDistNonZero);

    CPPUNIT_TEST_SUITE_END();

public:
    MDStestclass();
    virtual ~MDStestclass();
    void setUp();
    void tearDown();

private:
    void GutmanMatrixDim();
    void GutmanMatrixDistIsZero();
    void GutmanMatrixDistNonZero();
};

#endif	/* MDSTESTCLASS_H */

