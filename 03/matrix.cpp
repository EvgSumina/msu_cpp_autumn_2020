#include <iostream>
#include "matrix.h"
using namespace std;


Array::Array(int *array, size_t length): array(array), length(length){};

	
int &Array::operator [](size_t index)
{
	if (index < length)
	{
		return array[index];
	}
	throw out_of_range("Array index out of bounds");
}


const int &Array::operator [](size_t index) const
{
	if (index < length)
	{
		return array[index];
	}
	throw out_of_range("Array index out of bounds");
}


Matrix::Matrix(size_t row, size_t col): cols(col), rows(row)
{
	matrix = new int*[row];
	for (size_t i = 0; i < row; i++)
	{
		matrix[i] = new int[col];
	}
}


Matrix::Matrix(const Matrix& matr): cols(matr.getCols()), rows(matr.getRows()) {
	size_t Rows = matr.getRows();
	size_t Cols = matr.getCols();
	matrix = new int*[Rows];
	for (size_t i = 0; i < Rows; i++)
	{
		matrix[i] = new int[Cols];
		for (size_t j = 0; j < Cols; j++)
		{
			matrix[i][j] = matr.matrix[i][j];
		}
	}
}


size_t Matrix::getRows() const {return rows;}


size_t Matrix::getCols() const {return cols;}


Array Matrix::operator[](size_t index)
{
	if (index < rows)
	{
		return Array(matrix[index], cols);
	}
	throw out_of_range("Matrix index out of bounds");
}


const Array Matrix::operator[](size_t index) const
{
	if (index < rows)
	{
		return Array(matrix[index], cols);
	}
	throw out_of_range("Matrix index out of bounds");
}


Matrix& Matrix::operator *=(int a)
{
	for (size_t i = 0; i < rows; i++)
	{
		for(size_t j = 0; j < cols; j++)
		{
			matrix[i][j] *= a;
		}
	}
	return *this;
}


Matrix Matrix::operator +(const Matrix& SecondMatrix) const
{
	if ((rows != SecondMatrix.getRows()) || (cols != SecondMatrix.getCols()))
	{
		throw out_of_range("Input arrays must have same dimensions");
	}	
	Matrix ResultMatrix = Matrix(rows, cols);
	for (size_t i = 0; i < rows; i++)
	{
		for(size_t j = 0; j < cols; j++)
		{
			ResultMatrix[i][j] = matrix[i][j] + SecondMatrix[i][j];
		}
	}
	return ResultMatrix;
}


bool Matrix::operator ==(const Matrix& SecondMatrix) const
{
	if ((rows != SecondMatrix.getRows()) || (cols != SecondMatrix.getCols()))
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < rows; i++)
		{
			for(size_t j = 0; j < cols; j++)
			{
				if (matrix[i][j] != SecondMatrix[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
}


Matrix& Matrix::operator =(const Matrix& SecondMatrix)
{
	if (this == &SecondMatrix) 
		return *this;
	if ((rows != SecondMatrix.getRows()) || (cols != SecondMatrix.getCols()))
	{
		throw out_of_range("Input arrays must have same dimensions");
	}
	for (unsigned int i = 0; i < rows; i++)
	{
		for(unsigned int j = 0; j < cols; j++)
		{
			matrix[i][j] = SecondMatrix[i][j];
		}
	}
	return *this;
}


bool Matrix::operator !=(const Matrix& SecondMatrix) const
{
	return !(*this == SecondMatrix);
}


Matrix::~Matrix()
{
	for (size_t i = 0; i < rows; i++)
	{
		delete matrix[i];
	}
	delete matrix;
}


ostream & operator <<(ostream & out, const Matrix& matrix)
{
	size_t rows = matrix.getRows();
	size_t cols = matrix.getCols();
	for (size_t i = 0; i < rows; i++)
	{
		for(size_t j = 0; j < cols; j++)
		{
			out << matrix[i][j] << " ";
		}
		out << '\n';
	}
	return out;
}
