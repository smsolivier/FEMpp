#ifndef Element_hh
#define Element_hh

#include <vector>

#include "Polynomial.hh"

using namespace std; 

class Element {

public: 

	double start, end; 
	int p; 

	Element(double start, double end, int p); // constructor 

	void genBasis(); // generate legendre polynomial basis functions 
	double Jacobian(double xi); // function for computing the jacobian 
	void genMass(); // generate mass matrix 
	void genStiff(); // generate stiffness matrix 
	double xiToX(double xi); // map xi to global x 
	double evaluate(double xi); // evaluate f at xi 
	void solve(); // solve local system 
	void interpolate(vector<double> &xout, vector<double> &fout); // interpolate for plotting 

	vector<double> xglob; // global x values within element 
	vector<double> xloc; // local x values within element 

	// store basis functions 
	vector<Polynomial> B; 
	vector<Polynomial> dB; 

	// local system 
	vector<vector<double>> A; 
	vector<double> rhs; 

	// store solution 
	vector<double> f; 

	// store source 
	vector<double> Q; 
	vector<double> Q_prev; 

	// store previous solution 
	vector<double> f_prev; 

	// mass matrix
	vector<vector<double>> M; 

	// stiffness matrix 
	vector<vector<double>> S; 

	double h; // element width 

};

#endif 