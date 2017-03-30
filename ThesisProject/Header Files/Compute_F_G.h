#pragma once
#include "Equations.h"

/*
For F array		i: [1,imax -1]
				j: [1,jmax]

For G array		i: [1, imax]
				j: [1,jmax -1]
*/

void Compute_FG(double **F, double **G, double **U, double **V, int iMax, int jMax,float timestep,float Rey, float DelX, float DelY,float Gx, float Gy, float upwind) {
	//Setting boundary conditions for F and G
	for (int j = jMax; j >= 1; --j)
	{
		F[j][0] = U[j][0];
		F[j][iMax] = U[j][iMax];
	}
	for (int i = 1; i <= iMax; ++i)
	{
		G[0][i] = V[0][i];
		G[jMax][i] = V[jMax][i];
	}

	//Performing F & G calculations
	for (int j = jMax; j >= 1; --j) { // row
		for (int i = 1; i <= iMax - 1; i++) // col
		{
			F[j][i] = U[j][i] + timestep*((1 / Rey)*(del2_U_del_X2(DelX, U, i, j) + del2_U_del_Y2(DelY, U, i, j)) - del_U2_del_X(DelX, U, i, j, upwind) - del_UV_del_Y(DelY, U, V, i, j,upwind) + Gx);
		}
	}

	for (int j = jMax - 1; j >= 1; --j) {
		for (int i = 1; i <= iMax; i++)
		{
			G[j][i] = V[j][i] + timestep*((1 / Rey)*(del2_V_del_X2(DelX, V, i, j) + del2_V_del_Y2(DelY, V, i, j)) - del_UV_del_X(DelX, U, V, i, j,upwind) - del_V2_del_Y(DelY, V, i, j, upwind) + Gy);
		}
	}

	return;
}