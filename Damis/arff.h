/* 
 * File:   arff.h
 * Author: mindaugas
 *
 * Created on August 28, 2013, 10:01 PM
 */

#ifndef ARFF_H
#define	ARFF_H

#include <vector>
#include <string>

class ARFF
{
public:
    ARFF();   
    ARFF(const char* path);
    ~ARFF();
    
    std::vector<std::string> GetAttributes();
    std::vector<std::string> GetAttributesTypes();
    std::vector<std::vector<double> > GetData();
    void WriteData(char* file);
    
private:
    std::vector<std::vector<double> > data;  // data array
    std::vector<std::string> attributes;  // list of attributes
    std::vector<std::string> data_types;  // list of data types of attributes 
    std::vector<std::vector<std::string> > meta_data;   
    
    std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
    double StringToDouble(std::string str, int column);   // converts string data type to double
};

#endif	/* ARFF_H */

