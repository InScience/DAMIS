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

void pcatestclass::CorrectFile() {
    ObjectMatrix omx("tests/cpu.arff");
    omx.loadDataMatrix();
    int n = omx.getObjectCount();
    int d = 2;
    bool ats = false;
    if (n > 0)
    {
        PCA pca_test(omx, d);
        ObjectMatrix Y = pca_test.getProjection();
        if (Y.getObjectCount() == n && Y.getObjectAt(0).features.size() == d)
                ats = true;
    }
    CPPUNIT_ASSERT(ats);
}
void pcatestclass::NonExistingFile() {
    ObjectMatrix omx("tests/cpuu.arff");
    omx.loadDataMatrix();
    bool ats = false;
    if (omx.getObjectCount() == 0)
        ats = true;
    
    CPPUNIT_ASSERT(ats);
}

void pcatestclass::InCorrectFile() {
    ObjectMatrix omx("tests/cpu_.arff");
    omx.loadDataMatrix();
    bool ats = false;
    if (omx.getObjectCount() == 0)
        ats = true;
    
    CPPUNIT_ASSERT(ats);
}

void pcatestclass::CorrectConversion(){
    ObjectMatrix X("tests/cpu.arff");
    X.loadDataMatrix();
    int m = X.getObjectCount();
    int n = X.getObjectAt(0).features.size();
    alglib::real_2d_array alglibX;
    alglibX.setlength(m, n);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            alglibX(i,j) = X.getObjectAt(i).features.at(j);
    
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (alglibX(i,j) - X.getObjectAt(i).features.at(j) > 0.001)
                CPPUNIT_ASSERT(false);
    CPPUNIT_ASSERT(true);
}