#include "Matrices.h"

namespace Matrices
{
    // Constructor here
	Matrix::Matrix(int _rows, int _cols)
	{
		rows = _rows;
		cols = _cols;

		a.resize(rows, vector<double>(cols, 0));
	}



	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), a.getCols()); 

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				c(i, j) = a(i, j) + b(i, j);
			}
		}

		return c;
	}

	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), b.getCols());

		for (int k = 0; k < a.getRows(); k++)
		{
			for (int i = 0; i < b.getCols(); i++)
			{
				for (int j = 0; j < a.getCols(); j++)
				{
					c(k, i) += a(k, j) * b(j, i);
				}
			}
		}

		return c;
	}


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


	    bool operator!=(const Matrix& a, const Matrix& b) 
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) 
        {
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


    ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(10) << a(i, j) << " ";
			}
			os << endl;
		}
		return os; 
	}

	RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
	{
		//use the linear algebra formula for rotation
		a.at(0).at(0) = cos(theta);
		a.at(0).at(1) = -sin(theta);
		a.at(1).at(0) = sin(theta);
		a.at(1).at(1) = cos(theta);

	}

	ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
	{
		//use the linear algebra formula for scaling: 
		//expand or shrink by a factor 
		a.at(0).at(0) = scale;
		a.at(0).at(1) = 0;
		a.at(1).at(0) = 0;
		a.at(1).at(1) = scale;
	}

	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
	{
		//shift each column value by a certain amount to translate
		for (int i = 0; i < nCols; i++)
		{
			a.at(0).at(i) = xShift;
			a.at(1).at(i) = yShift;
		}
	}
}