#include "Solve.hh"
#include "WriteCurve.hh"
#include "helper.hh"

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;  

int main(int argc, char *argv[]) {

	int Nx = 5; 

	double xb = 1; 

	int p = 4; 

	// Mesh mesh(Nx, xb, p); 
	Mesh *mesh = new Mesh(Nx, xb, p); 

	int Nt = 30;  
	double tb = .8*M_E; 
	double a = 1; 
	double b = 1; 
	double c = 1; 
	double q = 0; 
	double alpha = 1; 

	double f0 = 1;  

	Solve sol(mesh, a, b, c, q, f0, alpha); 
	vector<double> t = linspace(0, tb, Nt+1); 

	WriteCurve wc("data/", "DG"); // create curve writer object 

	for (int i=1; i<t.size(); i++) {

		sol.advance(t[i]);

		// printVector(sol.mesh.el[1].f); 

		vector<double> x;  
		vector<double> f; 

		mesh->getf(x, f);

		wc.print(x, f); 

	}

}