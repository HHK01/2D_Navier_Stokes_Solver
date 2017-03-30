#pragma once

	struct RectDomain
{
	//Defaults
	float Length = 1; //example 1m
	float Height = 0.5;//example 0.5m
	int iMax = 10;//20 //example: 3 squares // Maximum domain length divisions 20
	int jMax = 10; //10 Maximum domain Height divisions
	float Hydraulic_Dia; // For Rectangular and Squared domains only
	float delX;
	float delY;
	float upwind = 0.5;// upwind differencing factor for discretization; should be between 0 and 1 where upwind = 0 means central differencing and 1 donor-cell
};

	struct Time
{
	//Defaults
	float t = 0; // time
	float t_end = 1; // 1 second
	float n = 1; // time step at each loop n = 1, 2, 3 ...
	float timeStep = 0.01; //0.1 second
};

	struct SOR
{
	//Defaults
	int it = 1; //
	int itmax = 10;
	float eps = 10e-3;
	float omega = 1.2; // SOR factor 
};

	struct FLuidProps
{
	//Fluid  = Air
	float density = 1.225; //kg/m^3 
	float viscocity = 1.7894e-5; // kg/m-s
	float Inflow_Velocity = 0.00365; // m/s
};

	struct Problem
{
	float Rey;
	float Gx = 0; //Gravity in X direction
	float Gy = 0; // Gravtity in Y direction
	double Ui = 0; //Set all the velocities in x direction to 0(default)
	double Vi = 0; //Set all the velocities in y direction to 0(default)
	double Pi = 0; //Set all the pressure on cell faces to 0(default)
};
