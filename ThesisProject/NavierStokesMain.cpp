// NavierStokesMain.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Header Files/allocateMemory.h"
#include "Header Files/Compute_F_G.h"
#include "Header Files/Compute_RHS.h"
#include "Header Files/Write.h"
#include "Header Files/Helpers.h"
#include "Header Files/DataStructure.h"
#include "Header Files/SOR_cycle.h"
#include "Header Files/Compute_NextUV.h"

//Comment or Uncomment to enable/disable Matlab
/*	
	#pragma region MATLAB HEADER
	#include <engine.h>
	#pragma comment (lib,"libeng.lib") // Matlab Engine
	#pragma endregion
*/

using namespace std;
#define nl '\n'
#define nl2 '\n'<<'\n'
#define tb '\t'
#define line "-----------------------------------------------------------"
#define GetHydraulicDia(Length,Height) ((2 * (Length*Height)) / (Length + Height))
#define hr DrawHorizontalRule();

int main()
{		
		// Clean the output file each time we want to write
		cleanFile(); 
		//New struct properties
		RectDomain Domain;
		Time time;
		SOR sor;
		FLuidProps fluid;
		Problem problem;

		//Initial problem calculations		
		Domain.Hydraulic_Dia = GetHydraulicDia(Domain.Length, Domain.Height); // Calculating Hydraulic Diameter
		problem.Rey = ((fluid.density * abs(fluid.Inflow_Velocity)*Domain.Hydraulic_Dia) / fluid.viscocity); //Calculating Reynolds number
		Domain.delX = Domain.Length / Domain.iMax; // Calculating cell step size
		Domain.delY = Domain.Height / Domain.jMax;  // Calculating cell step size
		
			#pragma region Console report & Input

		if (problem.Rey > 2000) {
			cout << "Transition to turbulent air: Calculations are not accurate" << nl;
			cout << "Reynolds: " << problem.Rey;
		}
		cout << "Rey: " << problem.Rey << nl;
		char A; string str1; string str2;
		cout << "Plot U, V or P ?: "; cin >> A;
		switch (A)
		{
		case 'U':case'u':	 str1 = "[C,h]=contourf(new_U, 20);h.LineWidth =0.1;h.LineStyle =':'; title('U (m/s) velocity at Time =  "; str2 = " s'); "; break;
		case 'V':case'v':	 str1 = "[C,h]=contourf(new_V, 20);h.LineWidth =0.1;h.LineStyle =':'; title('V (m/s) velocity at Time =  ";  str2 = " s');"; break;
		case 'P':case'p':	 str1 = "[C,h]=contourf(new_P, 20);h.LineWidth =0.1;h.LineStyle =':'; title('P (Pa) Pressure at Time =  "; str2 = " s'); "; break;
		default: str1 = "[C,h]=contourf(new_U, 20);h.LineWidth =0.1;h.LineStyle =':'; title('U (m/s) velocity at Time =  "; str2 = " s');";
			break;
		}

		#pragma endregion

			#pragma region Allocation memory For Arrays
	double **U = _2DMATRIX(0, Domain.jMax + 1, 0, Domain.iMax + 1); // 2D pointers 
	double **V = _2DMATRIX(0, Domain.jMax + 1, 0, Domain.iMax + 1);
	double **F = _2DMATRIX(0, Domain.jMax + 1, 0, Domain.iMax + 1);
	double **G = _2DMATRIX(0, Domain.jMax + 1, 0, Domain.iMax + 1);
	double **RHS = _2DMATRIX(0, Domain.jMax + 1, 0, Domain.iMax + 1);
	double **P = _2DMATRIX(0, Domain.jMax + 1, 0, Domain.iMax + 1);
	double **RESIDUAL = _2DMATRIX(0, Domain.jMax+1, 0, Domain.iMax+1);

#pragma endregion
	
			#pragma region Assign initial values for U, V, P,F,G, RHS, residual (Zero by default)
		for (int j = Domain.jMax + 1; j >=0 ; --j) {
			for (int i = 0; i <= Domain.iMax+1; i++)
			{
				U[j][i] = problem.Ui;
				V[j][i] = problem.Vi;
				P[j][i] = problem.Pi;
				F[j][i] = 0;
				G[j][i] = 0;
				RHS[j][i] = 0;
				RESIDUAL[j][i] = 0;
			
			}
		}
		
		#pragma endregion
		
		//Comment or Uncomment to enable/disable Matlab
		/*
			#pragma region MATLAB INITIALIZATION

		Engine *MatPlot; // Open new instance with matlab engine
		MatPlot = engOpen("null");																				
		engEvalString(MatPlot, "figure('units','normalized','outerposition',[0 0 1 1]); "); // open only one figure in Matlab
	
			#pragma endregion
		*/
		while (time.t<time.t_end) 
			{

			//Resetting boundary conditions
			#pragma region Setting boundary conditions for Walls and outFlow condition
			for (int j = Domain.jMax; j >= 1; --j) { // row
				for (int i = 1; i <= Domain.iMax; i++) // col
				{
					V[Domain.jMax][i] = 0; // Stationary top wall
					V[0][i] = 0; // Test value //Stationary bottom wall; Check i
					V[j][Domain.iMax + 1] = V[j][Domain.iMax]; // Velocities at outlet outside the domain are equal to their previous ones

					U[j][Domain.iMax] = U[j][Domain.iMax - 1]; // outflow U nodes at boundary are equal to previous values
					U[Domain.jMax + 1][i] = -U[Domain.jMax][i]; // U velocities outside of the top wall are equal to the (negative) ones below them
					U[0][i] = -U[1][i]; // Velocities under the lower wall are equal to the velocities inside the domain

				}
			}
			#pragma endregion 

			//Enforcing the constant velocity at inlet
			#pragma region Problem Statement

			for (int j = Domain.jMax; j >= 1; --j) {

				U[j][1] = fluid.Inflow_Velocity; // inflow conditions
				U[j][0] = U[j][1];
			}
		#pragma endregion 
			
			Compute_FG(F, G, U, V, Domain.iMax, Domain.jMax, time.timeStep, problem.Rey, Domain.delX, Domain.delY, problem.Gx, problem.Gy, Domain.upwind);

			Compute_RHS(RHS, F, G, time.timeStep, Domain.jMax, Domain.iMax, Domain.delX, Domain.delY);

			float rit=1; // For residual norm condition //Not implemeneted in this function
			Compute_SOR(P, RHS, RESIDUAL, sor.it, sor.itmax, Domain.jMax, Domain.iMax, Domain.delX, Domain.delY, sor.omega, rit, sor.eps);

			Compute_NextUV(U, V, F, G, P, time.timeStep, Domain.iMax, Domain.jMax, Domain.delX, Domain.delY);
			
			#pragma region Writing Data in Output.txt
				write_TimeStep(time.n, time.t);
				writeMAT(U, 0, Domain.iMax + 1, 0, Domain.jMax + 1, "U Matrix: ");  // Writing Matrices on Output.txt
				writeMAT(V, 0, Domain.iMax + 1, 0, Domain.jMax + 1, "V Matrix: "); // Writing Matrices on Output.txt
				writeMAT(P, 0, Domain.iMax + 1, 0, Domain.jMax + 1, "P Matrix: "); // Writing Matrices on Output.txt

			#pragma endregion

	//Comment or Uncomment to enable/disable Matlab
				/*
		#pragma region MATLAB VISUALIZATION

				Matlab_Write(U, 0, Domain.iMax + 1, 0, Domain.jMax + 1,"U_Matlab.txt"); // Writing Temporary matrices to be delivered to matlab for display at each timestep
				Matlab_Write(V, 0, Domain.iMax + 1, 0, Domain.jMax + 1, "V_Matlab.txt"); // Writing Temporary matrices to be delivered to matlab for display at each timestep
				Matlab_Write(P, 0, Domain.iMax + 1, 0, Domain.jMax + 1, "P_Matlab.txt"); // Writing Temporary matrices to be delivered to matlab for display at each timestep
			
				engEvalString(MatPlot, "U_Filedir = fullfile('C:\\Users\\User\\Documents\\Visual Studio 2017\\Projects\\ThesisProject\\ThesisProject\\U_Matlab.txt'); UFile = fopen(U_Filedir);"); // Setting file directories and opening corresponding files for writing
				engEvalString(MatPlot, "V_Filedir = fullfile('C:\\Users\\User\\Documents\\Visual Studio 2017\\Projects\\ThesisProject\\ThesisProject\\V_Matlab.txt'); VFile = fopen(V_Filedir);"); // Setting file directories and opening corresponding files for writing
				engEvalString(MatPlot, "P_Filedir = fullfile('C:\\Users\\User\\Documents\\Visual Studio 2017\\Projects\\ThesisProject\\ThesisProject\\P_Matlab.txt'); PFile = fopen(P_Filedir);"); // Setting file directories and opening corresponding files for writing

				engEvalString(MatPlot, "U = cell2mat(textscan(UFile, '%f', 'delimiter', '\t')); 	fclose(UFile);"); // Scanning files and importing data into matlab and then closing said file
				engEvalString(MatPlot, "V = cell2mat(textscan(VFile, '%f', 'delimiter', '\t')); 	fclose(VFile);"); // Scanning files and importing data into matlab and then closing said file
				engEvalString(MatPlot, "P = cell2mat(textscan(PFile, '%f', 'delimiter', '\t')); 	fclose(PFile);"); // Scanning files and importing data into matlab and then closing said file

				string Concat_U_velocity = "new_U = reshape(U, []," + to_string((Domain.jMax + 2)) + ");new_U = transpose(new_U);"; // Dynamically setting the number of rows in Matlab to reshape the matrix// Transposing the matrix col -> row
				string Concat_V_velocity = "new_V = reshape(V, []," + to_string((Domain.jMax + 2)) + ");new_V = transpose(new_V);"; // Dynamically setting the number of rows in Matlab to reshape the matrix// Transposing the matrix col -> row
				string Concat_P_velocity = "new_P = reshape(P, []," + to_string((Domain.jMax + 2)) + ");new_P = transpose(new_P);"; // Dynamically setting the number of rows in Matlab to reshape the matrix// Transposing the matrix col -> row

				engEvalString(MatPlot, Concat_U_velocity.c_str()); // Evaluating above string
				engEvalString(MatPlot, Concat_V_velocity.c_str()); // Evaluating above string
				engEvalString(MatPlot, Concat_P_velocity.c_str()); // Evaluating above string
	
				string plot = str1 + to_string(time.t) + str2;
				engEvalString(MatPlot, plot.c_str());
			
				cleanFile("U_Matlab.txt"); // Cleaning files in order to write matrices at time step n=n+1 
				cleanFile("V_Matlab.txt"); // Cleaning files in order to write matrices at time step n=n+1 
				cleanFile("P_Matlab.txt"); // Cleaning files in order to write matrices at time step n=n+1 
#pragma endregion
					*/
				time.t += time.timeStep; //Restart calculations with next time step
				++time.n; // At final calculations the total timestep will be available for matlab
			}
			

	system("pause");
	return 0;
}


