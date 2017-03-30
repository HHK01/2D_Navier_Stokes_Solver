#pragma once
#include <cstdlib>
#include "stdafx.h"
#include <iostream>
using namespace std;

	#pragma region Allocate Memory

double **_2DMATRIX(int minRow, int maxRow, int minCol, int maxCol) {

	int i;
	double **m;
	m = (double**)malloc((unsigned(maxRow - minRow + 1) * sizeof(double*)));
	if (m == NULL)
	{
		cout << "no more memory \n";
		exit(0);
	}
	m -= minRow;
	for (i = minRow; i <= maxRow; ++i) {
		(m[i]) = (double*)malloc((unsigned(maxCol - minCol + 1) * sizeof(double)));
		if (m[i] == NULL)
		{
			cout << "no more memory \n";
			exit(0);
		}
		m[i] -= minCol;
	}
	return m;
}
#pragma endregion


	#pragma region 1D Allocate Memory

double *_1DMATRIX(int minRow, int maxRow, int minCol, int maxCol) {

	int arraysize = ((maxRow-minRow +1)*(maxCol-minCol +1));
	double *m;

	m = new	double[arraysize];
	return m;
}
#pragma endregion


	#pragma region Free Array Memory
void FREE_RMATRIX(double **m, int minRow, int maxRow, int minCol, int maxCol) {

	for (int i = maxRow; i > minRow; i--) {

		free((char*)(m[i] + minCol));
	}
	free((char*)(m + minRow));
}
#pragma endregion
