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
            /*! \fn ObjectMatrix DoubleToObjectMatrix(double** matrix, int rows, int cols);
             *  \brief Converts a two-dimensional array to ObjectMatrix object.
             *  \param matrix - a two-dimensional array that needs to be converted to an ObjectMatrix object.
             *  \param rows - a number of rows in \a matrix.
             *  \param cols - a number of columns in \a matrix.
             *  \return ObjectMatrix - an object of an ObjectMatrix class. 
             */
            static ObjectMatrix DoubleToObjectMatrix(double** matrix, int rows, int cols);  
            /*! \fn double** Array2D(int rows, int cols);
             *  \brief Allocates a two-dimensional array of doubles in continuous space.
             *  \param rows - a number of rows needs for allocation.
             *  \param cols - a number of columns needs for allocation.
             *  \return array - a two-dimensional array of doubles. 
             */
            static double** Array2D(int rows, int cols);
            /*! \fn alglib::real_1d_array ObjectMatrixTo1DArray(ObjectMatrix matrix);
             *  \brief Converts the ObjectMatrix DataObjects to alglib's one-dimensional array.
             *  \param matrix - an ObjectMatrix object that needs to be converted.
             *  \return array - an alglib's one-dimensional array. 
             */
            static alglib::real_1d_array ObjectMatrixTo1DArray(ObjectMatrix matrix);
            /*! \fn ObjectMatrix alglib1DArrayToObjectMatrix(alglib::real_1d_array array, int featureCount);
             *  \brief Converts the alglib's one-dimensional array to an ObjectMatrix object.
             *  \param array - an alglib's one-dimensional array that needs to be converted to an ObjectMatrix object.
             *  \param featureCount - a number of features in DataObject.
             *  \return ObjectMatrix - an ObjectMatrix object.
             */
            static ObjectMatrix alglib1DArrayToObjectMatrix(alglib::real_1d_array array, int featureCount);
            /*! \fn vector<string> split(const string &s, char delim);
             *  \brief Splits the string to the tokens separated by a delimiter.
             *  \param &s - an address of the string that needs to be tokenized.
             *  \param delim - a delimiter of words.
             *  \return vector<string> - a vector of tokenized words.
             */
            static std::vector<std::string> split(const std::string &s, char delim);
            /*! \fn vector<string> split(const string &s, char delim, vector<string> &elems);
             *  \brief Splits the string to the tokens separated by a delimiter.
             *  \param s - an address of the string that needs to be tokenized.
             *  \param delim - a delimiter of words.
             *  \param elems - an address of vector of tokenized words.
             */
            static std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);
            /*! \var int PID;
            *  \brief Processor's ID. Used as part of the seed in random numbers generator. 
            */
            static int PID;
};

#endif	/* ADDITIONALMETHODS_H */

