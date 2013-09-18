/*
 * File:   ReadARFFtestclass.h
 * Author: mindaugas
 *
 * Created on Sep 18, 2013, 9:05:52 AM
 */

#ifndef READARFFTESTCLASS_H
#define	READARFFTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class ReadARFFtestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ReadARFFtestclass);

    CPPUNIT_TEST(ReadFileCorrect);  // korektiski duomenys
    CPPUNIT_TEST(ReadFileNoSuchFile); // nera tokio failo
    CPPUNIT_TEST(ReadFileMissingFeature); // truksta duomenu: ? arba is vis nera

    CPPUNIT_TEST_SUITE_END();

public:
    ReadARFFtestclass();
    virtual ~ReadARFFtestclass();
    void setUp();
    void tearDown();

private:
    void ReadFileCorrect();
    void ReadFileNoSuchFile();
    void ReadFileMissingFeature();
};

#endif	/* READARFFTESTCLASS_H */

