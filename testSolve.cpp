#include "Solve.hh"

#include "helper.hh"

#include <iostream>
#include <fstream>
#include <cmath>

#include "printVector.hh"

using namespace std;  

int main(int argc, char *argv[]) {

	int Nx = 20; 

	double xb = 1; 

	int p = 4; 

	Mesh mesh(Nx, xb, p); 

	int Nt = 40;  
	double tb = M_E; 
	double a = 1; 
	double b = 1; 
	double c = 1; 
	double q = 0; 
	double alpha = 1; 

	double f0 = 1;  

	Solve sol(mesh, Nt, tb, a, b, c, q, f0, alpha); 

	sol.solveTime(); 

}