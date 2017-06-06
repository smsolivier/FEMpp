#ifndef Solve_hh
#define Solve_hh

#include <vector> 
#include "Mesh.hh"

using namespace std; 

class Solve {

public:

	Solve(Mesh mesh, double a, double b, double c, 
		double q, double f0, double alpha); 

	void genLocal(Element &el, double upwind, double upwind_prev, double t);

	void advance(double t); 

	void writeCurve(vector<double> &x, vector<double> &f, double t); 

	double dt; // store time step 

	vector<double> t; // time 

	int fcount; // store number of outputs written 

	Mesh mesh; 
	int Nt; // number of time steps 
	double tb; // end of time 
	double a, b, c, q, f0; 
	double alpha; 

	double t_prev; // store previous time step 

	double qf(double x, double t); 
};

#endif 