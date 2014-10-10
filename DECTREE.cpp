#include "DECTREE.h"

DECTREE::DECTREE()
{
    //ctor
}

DECTREE::~DECTREE()
{
    //dtor
}

DECTREE::DECTREE(double dL, double dT, double tolToNoise, int noOfTrees)
{
    this->r = tolToNoise;
    this->nTree = noOfTrees;

    /*this->r = 0.63;
    this->nTree = 60;*/

    ClusterizationMethods::initializeData(dL, dT);

    alglib::dfbuildrandomdecisionforest(ClusterizationMethods::learnSet, ClusterizationMethods::learnObjQtty, X.getObjectAt(0).getFeatureCount(), X.getClassCount(), nTree, r, this->info, this->df, this->rep);

}

double DECTREE::getStress()
{
    /*DF      -   decision forest model
    XY      -   test set
    NPoints -   test set size

RESULT:
    Its meaning for regression task is obvious. As for
    classification task, it means average relative error when estimating
    posterior probability of belonging to the correct class.*/

    return alglib::dfavgrelerror(df, ClusterizationMethods::testSet, ClusterizationMethods::testObjQtty);
}

ObjectMatrix DECTREE::getProjection()
{
    int ftCount = X.getObjectAt(0).getFeatureCount();
    int objCount = X.getObjectCount();

    initializeYMatrix(objCount, ftCount + X.getClassCount());

    alglib::real_1d_array tmpYObj;
    alglib::real_1d_array tmpXObj;

    tmpYObj.setlength(ftCount);
    tmpXObj.setlength(X.getClassCount());

    DataObject tmpO;
    for (int i = 0; i < objCount; i++)
    {
        tmpO = X.getObjectAt(i);
        for (int ft = 0; ft < ftCount; ft++)
        {
            double feature = tmpO.getFeatureAt(ft);
            tmpYObj(ft) = feature;
            Y.updateDataObject(i, ft, feature);
        }

        alglib::dfprocess(df, tmpYObj, tmpXObj);

        double max_prob = tmpXObj(0);
        int indx = 0;

        for (int j = 0; j < X.getClassCount(); j++)
        {
            Y.updateDataObject(i, j + ftCount, tmpXObj(j));
            if (max_prob < tmpXObj(j))
            {
                max_prob = tmpXObj(j);
                indx = j;
            }
        }

        if (tmpO.getClassLabel() != -1)
            Y.updateDataObjectClass(i, tmpO.getClassLabel());
        else
            Y.updateDataObjectClass(i, indx);
    }

        std::vector <std::string > probabilities; probabilities.reserve(0);

        for (int i = 0; i < X.getClassCount(); i++)
            probabilities.push_back("probability_" + X.getStringClassAttributes().at(i));

        Y.addAtributes(probabilities);

        Y.setPrintClass(X.getStringClassAttributes());

        /*std::string serForest;
        alglib::dfserialize(df, serForest);

        Y.addComment(serForest);*/

    return Y;
}
