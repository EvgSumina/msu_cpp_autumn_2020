#include "matrix.h"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
	int n = 0;

	Matrix matrix(2, 3);
	for (unsigned int i = 0; i < 2; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			matrix[i][j] = ++n;
		}
	}

	assert(matrix[0][0] == 1);
	assert(matrix[0][1] == 2);
	assert(matrix[0][2] == 3);
	assert(matrix[1][0] == 4);
	assert(matrix[1][1] == 5);
	assert(matrix[1][2] == 6);

	assert(matrix.getRows() == 2);
	assert(matrix.getCols() == 3);

	do
	{	
		try { 
			cout << matrix[0][3]; 
		} 
		catch (const out_of_range&) 
		{ 
			break ; 
		} 
		catch (...) { cout << "error \n"; } 
	} while(0);
	do
	{
		try { 
			cout << matrix[2][0]; 
		} 
		catch (const out_of_range&) { break ; } 
		catch (...) { cout << "error \n"; } 
	} while(0);

	matrix *= 2;

	const Matrix& matrix_2 = matrix;
	assert(matrix_2[0][0] == 2);
	assert(matrix_2[0][1] == 4);
	assert(matrix_2[0][2] == 6);
	assert(matrix_2[1][0] == 8);
	assert(matrix_2[1][1] == 10);
	assert(matrix_2[1][2] == 12);

	const Matrix& matrix_3 = matrix + matrix_2;

	assert(matrix_3[0][0] == 4);
	assert(matrix_3[0][1] == 8);
	assert(matrix_3[0][2] == 12);
	assert(matrix_3[1][0] == 16);
	assert(matrix_3[1][1] == 20);
	assert(matrix_3[1][2] == 24);

	assert(matrix == matrix_2);
	assert(matrix != matrix_3);

	cout << matrix;
	cout << "Success!\n";

	return 0;
}
