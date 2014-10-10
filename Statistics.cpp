/*! \class Statistics
    \brief A class of static methods for calculating statistical information.
 */
#include <cmath>
#include "Statistics.h"
#include "AdditionalMethods.h"
#include "DataObject.h"
#include <time.h>
#include <stdlib.h>

double Statistics::getAverage(ObjectMatrix om, int k)
{
    double average;
    int n = om.getObjectCount();
    double s = 0.0;
    for (int i = 0; i < n; i++)
        s += om.getObjectAt(i).getFeatureAt(k);
    average = s / n;
    return average;
}
std::vector<double> Statistics::getAverageColumns(ObjectMatrix om)
{

    std::vector<double> columnSum;
    int n = om.getObjectCount(), i, j;
    int m = om.getObjectAt(0).getFeatureCount();
    std::vector<double> average;
    average.reserve(m);

    double s, oCaunt = float(n);
    for (i = 0; i < m; i++) //hold features
    {
        s = 0.0;
        for (j = 0; j < n; j++) //for each object
            s += om.getObjectAt(j).getFeatureAt(i);

        average.push_back(s / oCaunt);
    }
    return average;
}


double Statistics::getCorrCoef(ObjectMatrix om, int k, int l)
{
    double to_return = 0.0;
    double avgFeatureK = Statistics::getAverage(om, k);
    double avgFeatureL = Statistics::getAverage(om, l);
    double fractionTop = 0.0, fractionBottom = 0.1, tmp1 = 0.0, tmp2 = 0.0, diffK, diffL;
    int n = om.getObjectCount();

    for (int i = 0; i < n; i++)
    {
        diffK = om.getObjectAt(i).getFeatureAt(k) - avgFeatureK;
        diffL = om.getObjectAt(i).getFeatureAt(l) - avgFeatureL;
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
        diffK = om.getObjectAt(i).getFeatureAt(k) - avgFeatureK;
        diffL = om.getObjectAt(i).getFeatureAt(l) - avgFeatureL;
        to_return += diffK * diffL;
    }

    to_return = to_return / (n - 1);
    return to_return;
}

double Statistics::getRandom()
{
    // srand(time(NULL) + AdditionalMethods::PID);
    return (double)rand()/RAND_MAX;
}

double Statistics::getRandom(double min, double max)
{
    return min + Statistics::getRandom() * (max - min);
}

ObjectMatrix Statistics::getCovMatrix(ObjectMatrix om)
{
    double tmp = 0.0;
    std::vector<double> dd;
    int n = om.getObjectAt(0).getFeatureCount();
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

void Statistics::initSeed()
{
    srand(time(NULL) + AdditionalMethods::PID);
}
