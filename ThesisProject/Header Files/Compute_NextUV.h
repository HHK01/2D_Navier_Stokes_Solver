#pragma once


void Compute_NextUV(double **U, double **V, double **F,double **G,double **P, float timeStep, int iMax, int jMax, float delX,float delY) {

	for (int j = jMax; j >= 1; --j)
	{
		for (int i = 1; i <= iMax - 1; ++i)
		{

			U[j][i] = F[j][i] - (timeStep / delX)*(P[j][i + 1] - P[j][i]);
		}
	}
	for (int j = jMax - 1; j >= 1; --j)
	{
		for (int i = 1; i <= iMax; ++i)
		{

			V[j][i] = G[j][i] - (timeStep / delY)*(P[j + 1][i] - P[j][i]);
		}
	}

	return;
}