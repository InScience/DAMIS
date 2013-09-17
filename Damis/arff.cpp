#include "arff.h"
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

ARFF::ARFF(){
    data.reserve(0);
    attributes.reserve(0);
}

ARFF::ARFF(const char* path){   
    std::ifstream file (path);
    std::string line_from_file;
    std::string tmp1, tmp2;
    std::vector<std::string> tmp;
    std::vector<double> v;
    double d;
    while (std::getline(file, line_from_file))
    {
        if (line_from_file.length() == 0)
            continue;
        std::istringstream iss(line_from_file);		
        std::string sub;
        iss >> sub;
        if (sub == "%")		
            continue;
        else
        {
            std::transform(sub.begin(), sub.end(), sub.begin(), ::toupper);
            if (sub == "@ATTRIBUTE")
            {
                iss >> tmp1;
                iss >> tmp2;
                std::transform(tmp1.begin(), tmp1.end(), tmp1.begin(), ::toupper);
                std::transform(tmp2.begin(), tmp2.end(), tmp2.begin(), ::toupper);
                attributes.push_back(tmp1);
                data_types.push_back(tmp2);
                if (tmp2 != "REAL"  && tmp2 != "INTEGER" && tmp2 != "DATETIME")
                {
                    tmp.push_back(tmp1);
                    meta_data.push_back(tmp);
                    tmp.clear();
                }
            }
            else if (sub == "@DATA" || sub == "@RELATION")
                continue;
            else
            {
                tmp = split(line_from_file, ',');
                for (int i = 0; i < tmp.size(); i++)
                {
                    if (data_types[i] == "REAL" || data_types[i] == "INTEGER")
                        v.push_back(atof(tmp[i].c_str()));
                    else if (data_types[i] != "DATETIME")
                    {
                        d = StringToDouble(tmp[i], i);
                        v.push_back(d);
                    }
                    
                }
                data.push_back(v);
                v.clear();
            }
        }
    }
}

ARFF::~ARFF(){
    data.clear();
    attributes.clear();
}

std::vector<std::string> ARFF::GetAttributes(){
    return attributes;
}

std::vector<std::string> ARFF::GetAttributesTypes(){
    return data_types;
}

std::vector<std::vector<double> > ARFF::GetData(){
    return data;
}

std::vector<std::string> ARFF::split(const std::string &s, char delim, std::vector<std::string> &elems){
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
    
std::vector<std::string> ARFF::split(const std::string& s, char delim){
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

double ARFF::StringToDouble(std::string str, int col)
{
    double to_return = 0;
    int n = meta_data.size();
    int k = 0;
    std::vector<std::string> x;
    double max = 0;
    
    for (int i = 0; i < n; i++)
    {
        if (meta_data[i].at(0) == attributes[col])
        {
            k = i;
            for (int j=1; j < meta_data[i].size(); j++)
            {
                x = split(meta_data[i].at(j), ' ');
                if (x[1] == str)
                {
                    to_return = atof(x[0].c_str());
                    break;
                }
                else
                {
                    if (max < atof(x[0].c_str()))
                        max = atof(x[0].c_str());
                }
            }
        }      
    }
    
    if (to_return == 0)
    {
        to_return = max + 1;
        std::ostringstream strs;
        strs << to_return;
        std::string str2 = strs.str();
        meta_data[k].push_back(std::string(str2) + " " + str);
    }
    
    return to_return;
}