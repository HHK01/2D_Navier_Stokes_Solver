----------------------------------------------------------------------------
2D TRANSIENT STATE NAVIER STOKES SOLVER WITH MATLAB VISUALIZATION 
----------------------------------------------------------------------------
Problem
------------
Fluid flow calculations in transient state are difficult to solve analytically. 
This is why numerical solutions such as CFDs are needed to solve complex equations 
such as the Navier Stokes equations. This code provides a solution for a transient 
state flow such as air through a rectangular two dimensional box.

Features
------------
What this code provides:

	-Variable grid size (width x length)
	-Variable step sizes (delta x and y)
	-Variable time step and duration 
	-Pressure and U,V velocities (in x and y direction) visualization using Matlab engine.
	-View Matrices results in Output.txt file
	-Apply changes to fluid property
	-Set initial fluid velocity

What this code does NOT provide:

	-Unstructured Grids
	-3D solver
	-Turbulence (Any Reynold > 2000 generates unrealistic results)
	-Flow around obstacle such as cylinder
	-Computational efficiency for large areas
	-Time dependent viscosity

Installation & Usage
------------
You can use this code without any additional installations. However to run Matlab contour plot you need to follow these steps:

	Step 1 - You need to have Matlab installed on your PC or else the visualization module won't work.

	Step 2 - In solution explorer, right-click on 'Thesis' and go to properties

	Step 3 - Go to Linker - Input . In Additional Dependencies, click on the menu arrow and click edit. 
			Write 'libeng.lib' (without quotations) and click Ok.

	Step 4 - We need to set the path of Matlab to let Visual Studio know where Matlab is:
			Under Configuration Properties, Go to VC++ Directories.
			# For Executable Directories, click on the menu arrow on the left and click edit, then add the main directory of Matlab:
			for me this was (without quotations): 'C:\Program Files\MATLAB\MATLAB Production Server\R2015a\bin\win64'

			# For Include Directories, add the path (without quotations) 'C:\Program Files\MATLAB\MATLAB Production Server\R2015a\extern\include'
				Note: this path might change in your version of Matlab. Wherever you installed Matlab, just go to extern folder then include and include this directory here.
			
			# For Librairy Directories, add the path (without quotations) 'C:\Program Files\MATLAB\MATLAB Production Server\R2015a\extern\lib\win64\microsoft'
				Note: Again this path might change in your version., just make sure you include '..\extern\lib\win64\microsoft' in the Librairy  directory

	Step 5 - We need to tell Visual Studio to load any DLLs that Matlab relies on:
			
			# Under Configuration Properties, Go to Debugging and set the Environment field to the following:
			
			PATH=C:\Program Files\MATLAB\MATLAB Production Server\R2015a\bin\win64

			Which is the same path as in step 4 - Executable Directories

	Step 6 - Uncomment the three block of code: 'MATLAB HEADER', 'MATLAB INITIALIZATION' and 'MATLAB VISUALIZATION'

	Step 7 - In the 'MATLAB VISUALIZATION' section, we need to change the directory for the three text files (U_Matlab, V_Matlab and P_Matlab),
			 this is to tell matlab to go to these files and read data from them. So if you save this project on your desktop, you need to copy 
			 the directory name of these three text files and replace them inside the 'endEvalString' method.

		For Example: 
		engEvalString(MatPlot, "U_Filedir = fullfile('C:\\Users\\User\\Documents\\Visual Studio 2017\\Projects\\ThesisProject\\ThesisProject\\U_Matlab.txt'); UFile = fopen(U_Filedir);");
		Here i specified the directory of U_Matlab.txt in the main project folder with double \\ because we need to escape '\' with another '\\'
		If you set the project on your Desktop the directory might be : 'C:\\Users\\User\\Desktop\\ThesisProject\\ThesisProject\\U_Matlab.txt'

If you need any help with these, just contact me at hilalhakla@gmail.com

Author's Note
------------
The main problem that i analyzed in this code is a simple constant velocity(0.00365 m/s) at the inlet, with fixed walls
and pressure outlet. You can change the boundary conditions however you want in the 'problem statement' 
and  'Setting boundary conditions for Walls and outFlow condition' blocks of code. 
You can change your problem given in the data structure and the main code will adapt to these changes.
Finally, You are free to use this code for educational purposes or further analysis.

Support
------------
If you need any support, you can contact me at hilalhakla@gmail.com

License
-------
MIT License

Copyright (c) 2017 Hilal Hakla

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


Reference
------------
Michael Griebel, Thomas Dornseifer, Tilman Neunhoeffer, Numerical Simulation in Fluid Dynamics, A Practical Introduction, 1997 
