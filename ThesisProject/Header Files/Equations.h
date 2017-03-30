#pragma once
#include <cmath>
#define nl '\n'


	#pragma region Sum1_Template

double sum1(double **Matrix, int i, int j, int i_offset1 = 0, int j_offset1 = 0, int i_offset2 = 0, int j_offset2 = 0, int power = 1, bool isSubtracted = 0, bool isAbs = 0)
{

	if (isSubtracted) {
		if (isAbs) {
		return abs(pow((((*(*(Matrix + j + j_offset1) + i + i_offset1)) - (*(*(Matrix + j + j_offset2) + i + i_offset2))) / 2), power));
		}
		else return (pow((((*(*(Matrix + j + j_offset1) + i + i_offset1)) - (*(*(Matrix + j + j_offset2) + i + i_offset2))) / 2), power));
	}
	else{
		if (isAbs) {
		return abs(pow((((*(*(Matrix + j + j_offset1) + i + i_offset1)) + (*(*(Matrix + j + j_offset2) + i + i_offset2))) / 2), power));
	}
		else return pow((((*(*(Matrix + j + j_offset1) + i + i_offset1)) + (*(*(Matrix + j + j_offset2) + i + i_offset2))) / 2), power);
	} 

}

#pragma endregion

////////////////////////////////

	#pragma region [del(u^2)/delx]
double del_U2_del_X(float delX, double **Matrix, int i, int j, float upwind) {

	//float test1 = ((1 / delX)*((sum1(Matrix, i, j, 0, 0, 1, 0, 2) - sum1(Matrix, i, j, -1, 0, 0, 0, 2))) + (upwind / delX)*((sum1(Matrix, i, j, 0, 0, 1, 0, 1, 0, 1)*sum1(Matrix, i, j, 0, 0, 1, 0, 1, 1)) - (sum1(Matrix, i, j, -1, 0, 0, 0, 1, 0, 1)*sum1(Matrix, i, j, -1, 0, 0, 0, 1, 1))));
	return ((1 / delX)*((sum1(Matrix, i, j, 0, 0, 1, 0, 2) - sum1(Matrix, i, j, -1, 0, 0, 0, 2))) + (upwind / delX)*((sum1(Matrix, i, j, 0, 0, 1, 0, 1, 0, 1)*sum1(Matrix, i, j, 0, 0, 1, 0, 1, 1)) - (sum1(Matrix, i, j, -1, 0, 0, 0,1, 0, 1)*sum1(Matrix, i, j, -1, 0, 0, 0, 1, 1))));
}
#pragma endregion

	#pragma region [del(v^2)/dely]
double del_V2_del_Y(float delY, double **Matrix, int i, int j, float upwind) {

	return ((1 / delY)*((sum1(Matrix, i, j, 0, 0, 0, 1, 2) - sum1(Matrix, i, j, 0, -1, 0, 0, 2))) + (upwind / delY)*((sum1(Matrix, i, j, 0, 0, 0, 1,1, 0, 1)*sum1(Matrix, i, j, 0, 0, 0, 1, 1, 1)) - (sum1(Matrix, i, j, 0, -1, 0, 0, 1, 0, 1)*sum1(Matrix, i, j, 0, -1, 0, 0, 1, 1))));
}
#pragma endregion

	#pragma region [del(uv)/dely]
double del_UV_del_Y(float delY, double **MatrixU, double **MatrixV, int i, int j, float upwind) {
	/*
	Debugging
	double _1 = sum1(MatrixV, i, j, 0, 0, 1, 0);
	double _2 = sum1(MatrixU, i, j, 0, 0, 0, 1);
	double _3 = sum1(MatrixV, i, j, 0, -1, 1, -1);
	double _4 = sum1(MatrixU, i, j, 0, -1, 0, 0);
	double test2 = ((1 / delY)*(sum1(MatrixV, i, j, 0, 0, 1, 0)*sum1(MatrixU, i, j, 0, 0, 0, 1) - sum1(MatrixV, i, j, 0, -1, 1, -1)*sum1(MatrixU, i, j, 0, -1, 0, 0)) + (upwind / delY)*(sum1(MatrixV, i, j, 0, 0, 1, 0, 1, 0, 1)*sum1(MatrixU, i, j, 0, 0, 0, 1, 1, 1) - sum1(MatrixV, i, j, 0, -1, 1, -1, 1, 0, 1)*sum1(MatrixU, i, j, 0, -1, 0, 0, 1, 1)));
	*/
	return ((1 / delY)*(sum1(MatrixV, i, j, 0, 0, 1, 0)*sum1(MatrixU, i, j, 0, 0, 0, 1) - sum1(MatrixV, i, j, 0, -1, 1, -1)*sum1(MatrixU, i, j, 0, -1, 0, 0)) + (upwind / delY)*(sum1(MatrixV, i, j, 0, 0, 1, 0, 1, 0, 1)*sum1(MatrixU, i, j, 0, 0, 0, 1, 1, 1) - sum1(MatrixV, i, j, 0, -1, 1, -1, 1, 0, 1)*sum1(MatrixU, i, j, 0, -1, 0, 0, 1, 1)));
}

#pragma endregion

	#pragma region [del(uv)/delx]
double del_UV_del_X(float delX, double **MatrixU, double **MatrixV, int i, int j, float upwind) {

	return ((1 / delX)*(sum1(MatrixU, i, j, 0, 0, 0, 1)*sum1(MatrixV, i, j, 0, 0, 1, 0) - sum1(MatrixU ,i, j, -1, 0, -1, 1)*sum1(MatrixV, i, j, -1, 0, 0, 0)) + (upwind / delX)*(sum1(MatrixU, i, j, 0, 0, 0, 1, 1, 0, 1)*sum1(MatrixV, i, j, 0, 0, 1, 0, 1, 1) - sum1(MatrixU, i, j, -1, 0, -1, 1, 1, 0, 1)*sum1(MatrixV, i, j, -1, 0, 0, 0, 1, 1)));
}

#pragma endregion

////////////////////////////////

	#pragma region [del2_U/del_X2]
double del2_U_del_X2(float delX, double **MatrixU, int i, int j ) {

	//float test3 = (((*(*(MatrixU + i + 1) + j)) - 2 * (*(*(MatrixU + i) + j)) + (*(*(MatrixU + i - 1) + j))) / (pow(delX, 2)));
	return (((*(*(MatrixU + j + 1) + i)) - 2*(*(*(MatrixU + j) + i)) + (*(*(MatrixU + j - 1) + i)))/(pow(delX,2)));
}
#pragma endregion

	#pragma region [del2_U/del_Y2]
double del2_U_del_Y2(float delY, double **MatrixU, int i, int j) {
	//float test4 = (((*(*(MatrixU + i) + j + 1)) - 2 * (*(*(MatrixU + i) + j)) + (*(*(MatrixU + i) + j - 1))) / (pow(delY, 2)));
	return (((*(*(MatrixU + j) + i +1)) - 2 * (*(*(MatrixU + j) + i)) + (*(*(MatrixU + j) +i -1))) / (pow(delY, 2)));
}
#pragma endregion

	#pragma region [del2_V/del_X2]
	double del2_V_del_X2(float delX, double **MatrixV, int i, int j) {

	return  (((*(*(MatrixV + j+1) + i)) - 2 * (*(*(MatrixV + j) + i)) + (*(*(MatrixV + j-1) + i))) / (pow(delX, 2)));
}
#pragma endregion

	#pragma region [del2_V/del_Y2]
double del2_V_del_Y2(float delY, double **MatrixV, int i, int j) {

	return  (((*(*(MatrixV + j ) + i+1)) - 2 * (*(*(MatrixV + j) + i)) + (*(*(MatrixV + j ) + i-1))) / (pow(delY, 2)));
}
#pragma endregion

////////////////////////////////

	#pragma region delP_delX
double delP_delX(float delX, double **MatrixP, int i, int j) {

	return (((*(*(MatrixP + j + 1) + i)) - (*(*(MatrixP + j) + i))) / delX);
}
#pragma endregion

	#pragma region delP_delY
double delP_delY(float delY, double **MatrixP, int i, int j) {

	return (((*(*(MatrixP + j) + i +1)) - (*(*(MatrixP + j) + i))) / delY);
}
#pragma endregion

////////////////////////////////


/*
Definitions:
nodeType:the passed array arguments by reference
power: for squaring the passed arguments, default 1
substract: substract the
passed parameter ? else addition

*/

//cout << "delX" << delX<< nl;
//cout << "upwind" << upwind<<nl;
//cout <<"sum 1 : "<<sum1(U, i, j, 0, 0, 1, 0, 2)<<nl;
//cout << "sum 2 : " << sum1(U, i, j, -1, 0, 0, 0, 2) << nl;
//cout << "sum 3: " << sum1(U, i, j, 0, 0, 1, 0, 1, 0, 1) << nl;
//cout << "sum 4: " << sum1(U, i, j, 0, 0, 1, 0, 1, 1) << nl;
//cout << "sum 5: " << sum1(U, i, j, -1, 0, 0, 0, 1, 0, 1) << nl;
//cout << "sum 6" << sum1(U, i, j, -1, 0, 0, 0, 1, 1) << nl;
//cout << "testPart2:  " << (sum1(U, i, j, -1, 0, 0, 0, 1, 0, 1)*sum1(U, i, j, -1, 0, 0, 0, 1, 1))<<nl;
//cout << "testPart2.2:  " << sum1(U, i, j, -1, 0, 0, 0, 1, 0, 1) << nl;
//cout << "testPart2.2:   " << sum1(U, i, j, -1, 0, 0, 0, 1, 1) << nl;