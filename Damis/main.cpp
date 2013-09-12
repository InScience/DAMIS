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
#include "alglibinternal.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    /*
    vector <string> r;
    ARFF a ("cpu.arff");
    std::vector <std::string> attr;
    std::vector <std::vector<double> > duom;
    
    attr = a.GetAttributes();
    duom = a.GetData();
    
    cout<<"---- Atributai:-----"<<endl;
    for (int i = 0; i < attr.size(); i++)
        cout<<a.GetAttributes().at(i)<<" "<<a.GetAttributesTypes().at(i)<<endl;
    
    vector< vector<double> >::iterator iter_ii;
    vector<double> ::iterator iter_jj;
    
    cout<<"---- Duomenys:-----"<<endl;
	for(iter_ii=duom.begin(); iter_ii!=duom.end(); iter_ii++)
	{
		for(iter_jj=(*iter_ii).begin(); iter_jj!=(*iter_ii).end() - 1; iter_jj++)
			cout << *iter_jj <<" ";
		cout << *iter_jj <<endl;
	}
     */
    vector <double> s(3);
    s[0] = 1;
    s[1] = 6;
    s[2] = 3;
    DataObject d(s);
    vector <double> v(3);
    v[0] = 3;
    v[1] = 4.4;
    v[2] = 2.8;
    DataObject dd(v);
    cout<<"Manhattan metrics: "<<DistanceMetrics::getDistance(d, dd, Manhattan)<<endl;
    cout<<"Euclidean metrics: "<<DistanceMetrics::getDistance(d, dd, Euclidean)<<endl;
    cout<<"Chebyshev metrics: "<<DistanceMetrics::getDistance(d, dd, Chebyshev)<<endl;
    cout<<"Average: " <<Statistics::getAverage(d)<<endl;
    cout<<"Correlation coeff: "<<Statistics::getCorrCoef(d, dd)<<endl;
    cout<<"Covariance coeff: "<<Statistics::getCovCoef(d, dd)<<endl;
    cout<<"Random: "<<Statistics::getRandom()<<endl;
    cout<<"Random: "<<Statistics::getRandom(34, 56)<<endl;
    cout<<"Covariance Matrix:"<<endl;
    ObjectMatrix om(2);
    om.addObject(d);
    om.addObject(dd);
    ObjectMatrix cov = Statistics::getCovMatrix(om);
    
    for (int i = 0; i < cov.getObjectCount(); i++)
    {
        DataObject doo = cov.getObjectAt(i);
        vector<double> dooo = doo.getItems();
        for (int j = 0; j < dooo.size(); j++)
            cout<<dooo[j]<< " ";
        cout<<endl;
    }
    
    
    
    alglib::real_2d_array arr;
    
    
    return 0;
}

