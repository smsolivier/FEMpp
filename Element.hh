#include <vector> 
#include <iostream>
#include <cmath> 

// #include "helper.hh"
#include "Polynomial.hh"

using namespace std; 

class Element {

public: 

	double start, end; 
	int p; 

	Element(double start, double end, int p) : start(start), end(end), p(p) {}; 
	double Jacobian(double xi); 

	vector<double> xglob; // global x values within element 

	vector<Polynomial> B; 
	vector<Polynomial> dB; 

	vector<vector<double>> A(p, vector<double>(p));

	vector<double> rhs(p);  

};