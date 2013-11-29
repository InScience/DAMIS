/* 
 * File:   AdditionalMethods.h
 * Author: mindaugas
 *
 * Created on October 24, 2013, 12:12 PM
 */

#ifndef ADDITIONALMETHODS_H
#define	ADDITIONALMETHODS_H

#include "ObjectMatrix.h"
#include "DataObject.h"
#include "alglib/ap.h"

class AdditionalMethods
{
        public:
            AdditionalMethods();
            virtual ~AdditionalMethods();
            
            /*! \fn double** ObjectMatrixToDouble(ObjectMatrix matrix);
             *  \brief Converts ObjectMatrix to 2D array of doubles.
             *  \param matrix - an ObjectMatrix that needs to be converted to array of doubles.
             *  \return array - a two-dimensional array of doubles. 
             */
            static double** ObjectMatrixToDouble(ObjectMatrix matrix);
            
            static ObjectMatrix DoubleToObjectMatrix(double** matrix, int rows, int cols);  
            static double** Array2D(int rows, int cols); 
            static alglib::real_1d_array ObjectMatrixTo1DArray(ObjectMatrix matrix);
            static ObjectMatrix alglib1DArrayToObjectMatrix(alglib::real_1d_array array, int featureCount);
            static std::vector<std::string> split(const std::string &s, char delim);
            static std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);
            static int PID;
};

#endif	/* ADDITIONALMETHODS_H */

