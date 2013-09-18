/* 
 * File:   main.cpp
 * Author: mindaugas
 *
 * Created on August 28, 2013, 9:57 PM
 */

#include <cstdlib>
#include <vector>
#include "arff.h"
#include "Statistics.h"
#include <iostream>
#include "DistanceMetrics.h"
#include "ObjectMatrix.h"
#include "PCA.h"

using namespace std;

void PrintToScreen(ObjectMatrix);

int main(int argc, char** argv) {
    
    ObjectMatrix omx("cpu.arff");
    
    std::vector <std::string> attr;
    std::vector <std::vector<double> > duom;
    
    for (int i = 0; i < omx.getFeaturesTitle().size(); i++)
        cout<<omx.getFeaturesTitle().at(i)<< " ";
    cout<<endl;
    
    PrintToScreen(omx);
    
    if (omx.getObjectCount() > 0)
    {
        ObjectMatrix cov = Statistics::getCovMatrix(omx);    
        PrintToScreen(cov);
        PCA pca_test(omx, 2);
        pca_test.toDataType();
        ObjectMatrix Y = pca_test.getY();
        PrintToScreen(Y);
    }
    
    
    return 0;
}

void PrintToScreen(ObjectMatrix omx)
{
    for (int i = 0; i < omx.getObjectCount(); i++)
    {
        DataObject obj = omx.DataObjects[i];
        for (int j = 0; j < obj.getFeatureCount(); j++)
            cout<<obj.getItems().at(j)<< " ";
        cout<<endl;
    }
}