#include <vector> 
#include <iostream>
#include <cmath> 

// #include "helper.hh"
#include "Polynomial.hh"
#include "quad.hh"
#include "basis.hh"

using namespace std; 

class Element {

public: 

	double start, end; 
	int p; 

	Element(double start, double end, int p); // constructor 

	double Jacobian(double xi); // function for computing the jacobian 
	void genMass(); // generate mass matrix 
	void genStiff(); // generate stiffness matrix 

	vector<double> xglob; // global x values within element 

	// store basis functions 
	vector<Polynomial> B; 
	vector<Polynomial> dB; 

	// local system 
	vector<vector<double>> A; 
	vector<double> rhs; 

	// store solution 
	vector<double> f; 

	// store previous solution 
	vector<double> f_prev; 

	// mass matrix
	vector<vector<double>> M; 

	// stiffness matrix 
	vector<vector<double>> S; 

};