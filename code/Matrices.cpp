// My Matrices project is gone / corrupted from the Power Server
// There is a random save of one called Matrices.save.cpp, but I'm honestly not sure what happened to my original one
// I pulled this from my PC, but I remember it working when I ran it through Hermle's grader - K 

#include "Matrices.h"

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;

        a.resize(rows, vector<double>(cols, 0)); // initalizes all to zero just super compact like;
    }

    ///Add each corresponding element.
    ///usage:  c = a + b;
    /// // throw error at beginning of the function to test for length 
    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
            throw runtime_error("Error: dimensions must agree");

        // if we  get here the dimensions match
        Matrix c(a.getRows(), a.getCols());

        // double foor loop to reach each element for 2d 

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                c(i, j) = a(i, j) + b(i, j);
            }
        }
        return c;
    }

    ///Matrix multiply.  See description.
    ///usage:  c = a * b;
    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
            throw runtime_error("Error: dimensions must agree");

        Matrix c(a.getRows(), b.getCols()); // Create a result matrix with appropriate dimensions

        for (int k = 0; k < a.getRows(); k++) // Outermost loop k
        {
            for (int i = 0; i < b.getCols(); i++) // Middle loop i
            {
                double sum = 0.0;
                for (int j = 0; j < a.getCols(); j++) // Innermost loop j
                {
                    sum += a(k, j) * b(j, i);
                }
                c(k, i) = sum;
            }
        }

        return c;
    }

    ///Matrix comparison.  See description.
    ///usage:  a == b
    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
            return false;

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                if (abs(a(i, j) - b(i, j)) >= 0.001)
                    return false;
            }
        }

        return true;
    }


    ///Matrix comparison.  See description.
    ///usage:  a != b
    bool operator!=(const Matrix& a, const Matrix& b) 
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
            return true;
        }

        for (int i = 0; i < a.getRows(); ++i) {
            for (int j = 0; j < a.getCols(); ++j) {
                if (abs(a(i, j) - b(i, j)) >= 0.001) {
                    return true;
                }
            }
        }
        return false;
    }

    ///Output matrix.
    ///Separate columns by ' ' and rows by '\n'
   
    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                os << setw(10) << right << a(i, j);
            }
            os << endl;
        }
        return os;
    }

	// Spinning really around the origin point
	RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
	{
        // cos && theta here from Trig
		a.at(0).at(0) = cos(theta);
		a.at(0).at(1) = -sin(theta);
		a.at(1).at(0) = sin(theta);
		a.at(1).at(1) = cos(theta);

	}

	// Don't touch this function 
	// Leave these as 0 
	ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
	{
        // scaling 
		a.at(0).at(0) = scale;
		a.at(0).at(1) = 0;
		a.at(1).at(0) = 0;
		a.at(1).at(1) = scale;
	}

	// When I was debugging this and commented it out everything just stood still 
	// it was pretty nifty looking -> this does the "falling" 
	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
	{
        // Translation and shifting 
		for (int i = 0; i < nCols; i++)
		{
			a.at(0).at(i) = xShift;
			a.at(1).at(i) = yShift;
		}
	}
}
