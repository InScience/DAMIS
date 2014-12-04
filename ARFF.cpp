#include "ARFF.h"
#include "AdditionalMethods.h"
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
//#include "DataObject.h"

/*! \class ARFF
 *  \brief A class for reading data from or writing data to an arff file.
 */

ARFF::ARFF()
{
    classFound = false;
    data.reserve(0);
    attributes.reserve(0);
    attributeIntClass.reserve(0);
    attributeStringClass.reserve(0);
    attributesTypes.reserve(0);
    objIntClass.reserve(0);
}

ARFF::ARFF(const char* path)
{
	classFound = false;

	data.reserve(0);
    attributes.reserve(0);
    attributeIntClass.reserve(0);
    attributeStringClass.reserve(0);
    attributesTypes.reserve(0);
    objIntClass.reserve(0);

    this->fileToRead = path;
    this->readArffFile();

}

ARFF::~ARFF()
{

}
std::vector<int> ARFF::getAttributeClasses()
{
         return this->attributeIntClass;
}
std::vector<std::string> ARFF::getAttributeStringClasses()
{
    return this->attributeStringClass;
}

void ARFF::readArffFile()
{

    //LOG(INFO) << "Initiating arff file " << DamisFile::getFilePath() << " read";

    std::stringstream s;
    std::ifstream file (this->fileToRead);
    std::string line_from_file;
    std::string tmp1, tmp2, tmp3;
    std::vector<std::string> tmp, tmp4;
    std::vector<std::string> stringVector; stringVector.reserve(0);
    std::vector<double> doubleVector; doubleVector.reserve(0);

    int line_no = 1;
    if (file.is_open() != false)
    {
        readSuccess = true;
        while (std::getline(file, line_from_file))
        {
            if (line_from_file.length() == 0)
            {
                line_no++;
                continue;
            }
            std::istringstream iss(line_from_file);
            std::string sub;
            iss >> sub;
            if (sub == "%")
            {
                line_no++;
                continue;
            }
            else
            {
                std::transform(sub.begin(), sub.end(), sub.begin(), ::toupper);
                if (sub == "@ATTRIBUTE")
                {
                    iss >> tmp1;
                    iss >> tmp2;

                    std::transform(tmp1.begin(), tmp1.end(), tmp1.begin(), ::toupper);
                    std::transform(tmp2.begin(), tmp2.end(), tmp2.begin(), ::toupper);
                    if (tmp1 == "CLASS" || tmp1 == "'CLASS'")
                    {

                        ARFF::classFound = true;
                        ARFF::classAttributeIndex = ARFF::attributes.size();
                      //  LOG(INFO) << "Found CLASS attribute at index " << ArffFile::classAttributeIndex;

                        int startClassList = line_from_file.find("{");
                        int endClassList = line_from_file.find("}");

                        if (startClassList != std::string::npos && endClassList != std::string::npos) //if both brackets found
                        {
                            tmp3.assign(line_from_file, startClassList + 1, endClassList - startClassList - 1);

                           // LOG(INFO) << "Classes are " << tmp3;
                            tmp4 = AdditionalMethods::split(tmp3, ','); //split resulting string
                            std::string className;
                            for (unsigned int i = 0; i < tmp4.size(); i++) //push back each class label
                            {
                                //trim spaces from start
                                tmp4[i].erase(tmp4[i].begin(), std::find_if(tmp4[i].begin(), tmp4[i].end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
                                //trim spaces from end
                                tmp4[i].erase(std::find_if(tmp4[i].rbegin(), tmp4[i].rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), tmp4[i].end());

                                className.assign(tmp4[i]);
                                std::transform(className.begin(), className.end(), className.begin(), ::toupper);

                                ARFF::attributeStringClass.push_back(className);
                                ARFF::attributeIntClass.push_back(i);
                            }
                        }
                        else
                          {
//                              std::cout << "Class atribute is ill-defined, cannot find {} brackets";
                              readSuccess = false;
                          }
                    }
                    else if (tmp2 == "REAL"  || tmp2 == "INTEGER" || tmp2 == "NUMERIC")
                    {
                        ARFF::attributes.push_back(tmp1);
                        ARFF::attributesTypes.push_back(tmp2);
                    }
                }
                else if (sub == "@DATA" || sub == "@RELATION")
                {
                    line_no++;
                    continue;
                }
                else
                {
                    tmp = AdditionalMethods::split(line_from_file, ','); //split data section by comma

                    int noOfAttr = (ARFF::classFound) ? ARFF::attributes.size() + 1 : ARFF::attributes.size(); //if there are class add 1 to atrributes

                    if (tmp.size() == noOfAttr)
                    {
                        bool badClass;

                        if (ARFF::classFound)
                                badClass = true;
                             else
                                badClass = false;

                        bool badAtrrSection = false;

                        std::string className;
                        int classInt;

                        for (unsigned int i = 0; i < tmp.size(); i++) // for each attribute in each data line
                        {
                            if (ARFF::classFound && (i == ARFF::classAttributeIndex))
                            {
                                //check if the class attribute in data section is valid
                                 //trim spaces from start
                                tmp[i].erase(tmp[i].begin(), std::find_if(tmp[i].begin(), tmp[i].end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
                                //trim spaces from end
                                tmp[i].erase(std::find_if(tmp[i].rbegin(), tmp[i].rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), tmp[i].end());

                                className.assign(tmp[i]);
                                std::transform(className.begin(), className.end(), className.begin(), ::toupper);

                                if (className !="?")
                                {
                                    for (int cA = 0; cA < ARFF::attributeStringClass.size(); cA++)
                                    {
                                        if (ARFF::attributeStringClass.at(cA) == className)
                                        {
                                            badClass = false;
                                            classInt = ARFF::attributeIntClass.at(cA);
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    badClass = false;
                                }

                                if (badClass)
                                {
//                                    std::cout << "Found invalid class at line - " << line_no;
                                    readSuccess = false;
                                    //continue;
                                }
                            }
                            else
                            {
                                //try to convert to double
                                char *err;
                                double x = strtod(tmp[i].c_str(), &err);

                                if (*err == 0 && tmp[i] !="")
                                    doubleVector.push_back(x);
                                else
                                {
//                                    std::cout << "File is not valid (skipping object), found non numeric value \\ " << tmp[i] << " \\ at line " <<line_no <<" at position " <<i;
                                    badAtrrSection = true;
                                    readSuccess = false;

                                }
                            }
                        } //end for tmp.size();

                        if (badAtrrSection == false  && badClass == false)
                        {
                            if (ARFF::classFound)
                                {
                                    if(className == "?")
                                        ARFF::objIntClass.push_back(-1);
                                    else
                                        ARFF::objIntClass.push_back(ARFF::attributeIntClass.at(classInt));
                                  //  std::cout << ARFF::attributeIntClass.at(classInt) << std::endl;
                                }
                            ARFF::data.push_back(doubleVector); //add to matrix
                        }
                        doubleVector.clear();
                    }
                    else
                       {
//                        std::cout << "Data section line " << line_no << " does not have required quantity features ";
                          readSuccess = false;
                       }
                }
            }
            line_no++;
        }
        file.close();
    }
    else
        {
//            std::cout << "Cannot open file " << this->fileToRead << " for reading into ARFF object";
            readSuccess = false;
        }

    if (ARFF::data.empty() || ARFF::attributes.empty())
        {
      //      std::cout << "Data file " << this->fileToRead << " does not contain either attribute or correct data section ";
            readSuccess = false;
        }
}

int ARFF::getObjectClass(int i)
{
    return objIntClass.at(i);
}

/**
 * Returns indicates is class attribute found
 */
bool ARFF::isClassFound()
{
  return ARFF::classFound;
}

/**
 * Returns objects class list <int> (data section)
 */
std::vector<int> ARFF::getIntClass()
{

    return  ARFF::objIntClass;
}

void ARFF::writeStatData(std::string statFile, double err, double calcTime)
{
    std::scientific;
    std::ofstream file(statFile.c_str());
    file << "%"<<std::endl;
    file<<"@ATTRIBUTE algError REAL"<<std::endl;
    file<<"@ATTRIBUTE calcTime REAL"<<std::endl;
    file <<"%"<<std::endl;
    file<<"@DATA"<<std::endl;
    time_t endTime;
    time(&endTime);
    file << err << ", "<<difftime(endTime, AdditionalMethods::startTime);
    file.close();

 //   AdditionalMethods::deleteFile();

}

std::vector<std::string> ARFF::getAttributes()
{
    return attributes;
}

std::vector<std::vector<double> > ARFF::getData()
{
    return data;
}

void ARFF::writeData(const char* path, std::vector<std::string> comments, std::vector<DataObject> data, std::vector <std::string> classLabels, std::vector<std::string> attributeLabels)
{
    std::ofstream file (path);
    int n = data.size();
    int k = 0;
    std::vector<std::string> tmp;
    file << "%"<<std::endl;

    if (!comments.empty())
    {
        for (int i = 0; i < comments.size(); i++)
        {
            //tmp = AdditionalMethods::split(comments.at(i), '\n');
            file <<comments.at(i);
            /*for (int j = 0; j < tmp.size(); j++)
            {
                file <<"% " << tmp[j] << std::endl;
            }*/
        }
         file << "%"<<std::endl;
    }

    for (int i = 0; i < attributeLabels.size(); i++)
        file<<"@ATTRIBUTE "<<attributeLabels.at(i)<<std::endl;

    if (!classLabels.empty())
    {
        file <<"@ATTRIBUTE Class {";
        for (int i = 0; i < classLabels.size() - 1; i++)
        {
            file << classLabels.at(i) << ", ";
        }
        file << classLabels.at(classLabels.size() - 1) << "}"<< std::endl;
    }

    file << "%"<<std::endl;
    file<<"@DATA"<<std::endl;

    if (!data.empty())
    {
 //   int featureCount = data.at(0).getFeatureCount();

        for (int i = 0; i < n; i++)
        {
            k = data.at(i).getFeatureCount();
            for (int j = 0; j < k - 1; j++)
                file<<data.at(i).getFeatureAt(j)<<", ";

                if (!classLabels.empty() && data.at(i).getClassLabel() != -1)
                    file<<data.at(i).getFeatureAt(k - 1)<< ", " << classLabels.at(data.at(i).getClassLabel()) << std::endl;
                else if (!classLabels.empty() && data.at(i).getClassLabel() == -1)
                    file<<data.at(i).getFeatureAt(k - 1)<< ", ?" << std::endl;
                else
                    file<<data.at(i).getFeatureAt(k - 1) << std::endl;
        }
    }
    file.close();
}

std::string ARFF::getFailReason()
{
    return failReason;
}

bool ARFF::isSuccessfullyRead()
{
    return readSuccess;
}


