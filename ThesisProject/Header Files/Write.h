#pragma once

#include <iostream>
#include <fstream>
#include <string>
#define nl '\n'
#define tb '\t'
#define line "-----------------------------------------------------------"
using namespace std;


	#pragma region Write Matrix On File

void writeMAT(double **Matrix, int Min_i, int Max_i, int Min_j, int Max_j, string Matrix_title = "Matrix:", string filename = "Output.txt") {
	ofstream outputFile;
	//ios_base::app to append content to file
	outputFile.open(filename, ios_base::app);

	outputFile << nl;

	outputFile << Matrix_title << nl;
	for (int j = Max_j; j >= Min_j; --j)
	{
		for (int i = Min_i; i <= Max_i; i++)
		{
			outputFile << scientific << Matrix[j][i] << tb;

		}
		outputFile << nl;
	}
	//outputFile << line;
	outputFile.close();

}

#pragma endregion

	#pragma region Matlab_Write
void Matlab_Write(double **Matrix, int Min_i, int Max_i, int Min_j, int Max_j, string filename = "Output.txt") {
	ofstream outputFile;
	//ios_base::app to append content to file
	outputFile.open(filename, ios_base::app);
	for (int j = Max_j; j >= Min_j; --j)
	{
		for (int i = Min_i; i <= Max_i; i++)
		{
			outputFile << scientific << Matrix[j][i] << tb;

		}
		outputFile << nl;
	
	}

	outputFile.close();

}

#pragma endregion

	#pragma region Write Time step On File

void write_TimeStep(int timeStep, float time, string filename = "Output.txt") {
	ofstream outputFile;
	//ios_base::app to append content to file
	outputFile.open(filename, ios_base::app);
	//outputFile << nl << "************** Time = " << time << ", Time Step = " << timeStep << "**************" << nl;
	outputFile << nl << "Time = " << time << "	Timestep = " << timeStep << nl;

	outputFile.close();

}

#pragma endregion

	#pragma region Clean Output
void cleanFile(string filename = "Output.txt") {
	ofstream outputFile;
	//ios_base::app to append content to file
	outputFile.open(filename);
	outputFile.close();
}
#pragma endregion