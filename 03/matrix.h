#pragma once
#include <iostream>
using namespace std;


class Array
{
	private:
		int * array;
		size_t length;
	public:
		Array(int *, size_t);
		int & operator [](size_t);
		const int & operator [](size_t) const;
};
	

class Matrix
{
	private:
		int ** matrix;
		size_t cols;
		size_t rows;
	public:
		Matrix(size_t row, size_t col);
		Matrix(const Matrix & mat);
		size_t getRows() const;
		size_t getCols() const;
		Array operator [](size_t);
		const Array operator [](size_t) const;
		Matrix& operator *=(int);
		Matrix operator +(const Matrix&) const;
		Matrix& operator =(const Matrix&);
		bool operator ==(const Matrix&) const;
		bool operator !=(const Matrix&) const;
		friend ostream& operator <<(ostream&, const Matrix&);
		~Matrix();
};
