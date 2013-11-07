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
            
            static double** ObjectMatrixToDouble(ObjectMatrix matrix);   // konvertavimas is ObjectMatrix i 2D double masyva
            static ObjectMatrix DoubleToObjectMatrix(double** matrix, int rows, int cols);   // konvertavimas is 2D double masyvo i ObjectMatrix
            static double** Array2D(int rows, int cols);    // 2D double istisines matricos kurimas
            static alglib::real_1d_array ObjectMatrixTo1DArray(ObjectMatrix matrix);
};

#endif	/* ADDITIONALMETHODS_H */

