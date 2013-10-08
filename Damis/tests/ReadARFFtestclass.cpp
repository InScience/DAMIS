/*
 * File:   ReadARFFtestclass.cpp
 * Author: mindaugas
 *
 * Created on Sep 18, 2013, 9:05:53 AM
 */

#include "ReadARFFtestclass.h"
#include "../arff.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ReadARFFtestclass);

ReadARFFtestclass::ReadARFFtestclass() {
}

ReadARFFtestclass::~ReadARFFtestclass() {
}

void ReadARFFtestclass::setUp() {
}

void ReadARFFtestclass::tearDown() {
}

void ReadARFFtestclass::ReadFileCorrect() {
    ARFF file("./tests/cpu.arff");
    CPPUNIT_ASSERT(file.ReadSuccess);
}

void ReadARFFtestclass::ReadFileNoSuchFile() {
    bool ats = false;
    ARFF file("cpuu.arff");
    if (file.ReadSuccess == false)
        ats = true;
    CPPUNIT_ASSERT(ats);
}

void ReadARFFtestclass::ReadFileMissingFeature()
{
    bool ats = false;
    ARFF file("./tests/cpu_.arff");
    if (file.ReadSuccess == false)
        ats = true;
    CPPUNIT_ASSERT(ats);
}