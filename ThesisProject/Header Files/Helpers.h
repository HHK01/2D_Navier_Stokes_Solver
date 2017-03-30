#pragma once

#include <iostream>
#include <string>
#define nl '\n'
#define tb '\t'
using namespace std;

#pragma region FUNCTION: Draw Horizontal Rule
void DrawHorizontalRule() {

	for (int i = 0; i < 50; ++i) {

		cout << "_";
	}
	cout << nl << nl;
	return;
}

#pragma endregion

#pragma region TEMPLATE: Sum of eW,eW over delx^2 Template
template <class T> T sum_pow2(T del) {

	return ((2) / pow(del, 2));
}
#pragma endregion

#pragma region FUNCTION: Display Array/Matrix

void Display_Matrix(double **M, int Max_i, int Max_j, string title) {

	cout << title << nl;
	for (int j = Max_j; j >= 0; --j) {
		for (int i = 0; i <= Max_i; i++)
		{
			cout << scientific << M[j][i] << tb;
		}

		cout << nl << nl;
	}
	cout << nl << nl;
}
#pragma endregion
