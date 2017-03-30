#pragma once
#include <cmath>
#include "Helpers.h"

void Compute_SOR(double **P, double **RHS, double **RESIDUAL, int it, int itmax, int jMax, int iMax, float delX, float delY, float omega, float rit, float eps)
{
	float temp;
	float test;
	

	while (it < itmax )
	{
		//Pressure boundary condition here
		for (int j = jMax; j >= 1; --j)
		{
			P[j][0] = P[j][1];
			P[j][iMax + 1] = P[j][iMax];
		}

		for (int i = 1; i <= iMax; ++i)
		{
			P[0][i] = P[1][i];
			P[jMax + 1][i] = P[jMax][i];
		}

		//Calculating pressure and residual matrices
		for (int j = jMax; j >= 1; j--)
		{
			for (int i = 1; i <= iMax; ++i)
			{
		
				P[j][i] = (1 - omega)*P[j][i] + ((omega) / (sum_pow2(delX) + sum_pow2(delY)))*((((P[j][i + 1]) + (P[j][i - 1])) / (pow(delX, 2))) + (((P[j + 1][i]) + (P[j - 1][i])) / (pow(delY, 2))) - RHS[j][i]); /// equation (3.44)																																																												 //cout << "RHS Matrix       " << RHS[j][i]<<nl<<nl;
				RESIDUAL[j][i] = ((P[j][i + 1] + P[j][i - 1]) / (pow(delX, 2))) + ((P[j + 1][i] + P[j - 1][i]) / (pow(delY, 2))) - RHS[j][i];

			}
		}

		for (int j = jMax; j >= 1; j--)
		{
			for (int i = 1; i <= iMax; ++i)
			{
				temp = pow(RESIDUAL[j][i], 2);
				rit += temp;
			}
		}

		//writeMAT(P, 0, iMax + 1, 0, jMax + 1, "SOR: "); //For Debugging
		rit = sqrt(rit);
		test = sqrt(rit/(iMax*jMax));  // Check later 
		++it;
	}

	//For visualisation purposes only, not used in calculations but in order not to have zero values on the four corners of the domain when visualizing
	P[jMax + 1][0] = P[jMax + 1][1]; //Top left corner
	P[jMax + 1][iMax + 1] = P[jMax + 1][iMax]; //Top right corner
	P[0][0] = P[0][1]; //bottom left corner
	P[0][iMax + 1] = P[0][iMax]; // bottom right corner
}