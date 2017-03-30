#pragma once

void Compute_RHS(double **RHS, double **F, double **G, float timestep, int jmax, int imax, float delX, float delY) {


	for (int j = jmax; j >= 1; --j) {
		for (int i = 1; i <= imax; i++)
		{
			RHS[j][i] = (1 / timestep)*(((F[j][i] - F[j][i - 1]) / delX) + ((G[j][i] - G[j - 1][i]) / delY));
		}
	}
	return;
}
