#ifndef Solve_hh
#define Solve_hh

#include <vector> 
#include "Mesh.hh"

using namespace std; 

class Solve {

public:

	// constructor 
	Solve(Mesh *mesh, double a, double b, double c, 
		double q, double f0, double alpha, int DIR=0); 

	// advance one time step 
	void advance(double t);  

	// Mesh *mesh; // mesh object

protected:

	// generate local system in a single element 
	void genLocal(Element &el, double upwind, double upwind_prev, double t); 

	// sweep left to right 
	void sweepLR(double t); 

	// sweep right to left 
	void sweepRL(double t); 

	Mesh *mesh; // mesh object

	int DIR; // direction of sweeping, 0=left -> right, 1=right -> left 

	double dt; // store time step 

	double a, b, c, q, f0, alpha; // constants 

	double t_prev; // store previous time step 

};

#endif 