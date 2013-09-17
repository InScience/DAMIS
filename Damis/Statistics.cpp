#include <cmath>

#include "Statistics.h"
#include "DataObject.h"
#include <time.h>
#include <stdlib.h>

double Statistics::getAverage(ObjectMatrix om, int k){
    double average;
    int n = om.getObjectCount();
    double s = 0.0;
    for (int i = 0; i < n; i++)
        s += om.DataObjects.at(i).getItems().at(k);
    average = s / n;
    return average;
}

double Statistics::getCorrCoef(ObjectMatrix om, int k, int l)
{
    double to_return = 0.0;
    double avgFeatureK = Statistics::getAverage(om, k);
    double avgFeatureL = Statistics::getAverage(om, l);
    double fractionTop, fractionBottom, tmp1 = 0.0, tmp2 = 0.0, diffK, diffL;
    int n = om.getObjectCount();
    
    for (int i = 0; i < n; i++)
    {
        diffK = om.DataObjects.at(i).getItems().at(k) - avgFeatureK;
        diffL = om.DataObjects.at(i).getItems().at(l) - avgFeatureL;
        fractionTop += diffK * diffL;
        tmp1 += std::pow(diffK, 2);
        tmp2 += std::pow(diffL, 2);
    }
    fractionBottom = std::sqrt(tmp1 * tmp2);
    to_return = fractionTop / fractionBottom;
    
    return to_return;
}

double Statistics::getCovCoef(ObjectMatrix om, int k, int l)
{
    double to_return = 0.0;
    double avgFeatureK = Statistics::getAverage(om, k);
    double avgFeatureL = Statistics::getAverage(om, l);
    double diffK, diffL;
    int n = om.getObjectCount();

    for (int i = 0; i < n; i++)
    {
        diffK = om.DataObjects.at(i).getItems().at(k) - avgFeatureK;
        diffL = om.DataObjects.at(i).getItems().at(l) - avgFeatureL;
        to_return += diffK * diffL;
    }
    
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
    double tmp = 0.0;
    std::vector<double> dd;
    int n = om.DataObjects.at(0).getFeatureCount();
    ObjectMatrix cov(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tmp = Statistics::getCovCoef(om, i, j);
            dd.push_back(tmp);
        }
        DataObject dobj(dd);
        cov.addObject(dobj);
        dd.clear();
    }
    
    return cov;
}