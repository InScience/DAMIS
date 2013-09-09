#include <cmath>

#include "Statistics.h"
#include "DataObject.h"
#include <time.h>
#include <stdlib.h>

double Statistics::getAverage(DataObject d){
    double to_return;
    std::vector<double> v = d.getItems();
    int n = d.getFeatureCount();
    double s = 0.0;
    for (int i = 0; i < n; i++)
        s += v[i];
    to_return = s / n;
    return to_return;
}

double Statistics::getCorrCoef(DataObject obj1, DataObject obj2)
{
    double to_return = 0.0;
    double avg_obj1 = 0.0, avg_obj2 = 0.0, meter, denominator, tmp1 = 0.0, tmp2 = 0.0;
    std::vector<double> v1 = obj1.getItems();
    std::vector<double> v2 = obj2.getItems();
    int n = obj1.getFeatureCount();
    
    avg_obj1 = Statistics::getAverage(obj1);
    avg_obj2 = Statistics::getAverage(obj2);
    
    for (int i = 0; i < n; i++)
    {
        meter += (v1[i] - avg_obj1)*(v2[i] - avg_obj2);
        tmp1 += std::pow((v1[i] - avg_obj1), 2);
        tmp2 += std::pow((v2[i] - avg_obj2), 2);
    }
    denominator = std::sqrt(tmp1 * tmp2);
    to_return = meter / denominator;
    return to_return;
}

double Statistics::getCovCoef(DataObject obj1, DataObject obj2)
{
    double to_return = 0.0, avg_obj1, avg_obj2;
    int n = obj1.getFeatureCount();
    std::vector<double> v1 = obj1.getItems();
    std::vector<double> v2 = obj2.getItems();
    avg_obj1 = Statistics::getAverage(obj1);
    avg_obj2 = Statistics::getAverage(obj2);
    for (int i = 0; i < n; i++)
        to_return += (v1[i] - avg_obj1)*(v2[i] - avg_obj2);
    
    to_return = to_return / (n - 1);
    return to_return;
}

double Statistics::getRandom()
{
    srand(time(NULL));
    return (double)rand() / RAND_MAX;
}

double Statistics::getRandom(double min, double max)
{
    return min + Statistics::getRandom()*(max - min);
}

ObjectMatrix Statistics::getCovMatrix(ObjectMatrix om)
{
    std::vector<DataObject> d = om.DataObjects;
    double tmp = 0.0;
    std::vector<double> dd;
    int n = om.getObjectCount();
    ObjectMatrix cov(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tmp = Statistics::getCovCoef(d[i], d[j]);
            dd.push_back(tmp);
        }
        DataObject dobj(dd);
        cov.addObject(dobj);
        dd.clear();
    }
    
    return cov;
}