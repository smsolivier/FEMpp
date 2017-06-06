#include "Solve.hh"

#include "helper.hh"

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std; 

Solve::Solve(Mesh mesh, double a, double b, double c, 
	double q, double f0, double alpha) : 
		mesh(mesh), a(a), b(b), c(c), q(q), f0(f0), alpha(alpha) 
{

	t_prev = 0; // initialize previous time step 

	t = linspace(0, tb, Nt+1); // vector of evenly spaced time steps  

	fcount = 0; // counter for output files 

	// output properties 
	cout << "a = " << a << endl; 
	cout << "b = " << b << endl; 
	cout << "c = " << c << endl; 
	cout << "f0 = " << f0 << endl; 
	cout << "alpha  = " << alpha << endl; 

}

double Solve::qf(double x, double t) {

	return a/tb*sin(M_PI*x/mesh.xb) + b*t/tb*M_PI/mesh.xb*cos(M_PI*x/mesh.xb) + c*t/tb*sin(M_PI*x/mesh.xb); 

}

void Solve::genLocal(Element &el, double upwind, double upwind_prev, double t) {

	// printVector(el.M); 

	for (int i=0; i<el.p; i++) {

		for (int j=0; j<el.p; j++) {

			double x = el.xglob[j]; // current x global location of node 

			// time 
			el.A[i][j] = a/dt*el.M[i][j]; 

			// space part 
			el.A[i][j] += alpha*(-b*el.S[i][j] + c*el.M[i][j]); 

			el.rhs[i] += el.f[j] * a/dt*el.M[i][j]; 

			el.rhs[i] -= el.f[j] * (1 - alpha)*(-b*el.S[i][j] + c*el.M[i][j]); 

			// el.rhs[i] += qf(x, t)*el.M[i][j]; 
			el.rhs[i] += q*el.M[i][j]; 

		}
	}

	// apply upwinding 
	el.A[el.A.size()-1][el.A.size()-1] += alpha*b; 
	el.rhs.back() -= (1 - alpha) * el.f[el.f.size()-1] * b; 

	// left boundary 
	el.rhs[0] += b*(alpha*upwind + (1-alpha)*upwind_prev); 

}

void Solve::advance(double t) {

	dt = t - t_prev; // time step 

	vector<double> xout; 
	vector<double> fout;  

	for (int i=0; i<mesh.N; i++) {

		Element &el = mesh.el[i]; 

		// generate local system 
		if (i > 0) {

			Element &el_down = mesh.el[i-1]; 

			genLocal(el, el_down.f.back(), el_down.f_prev.back(), t); 

		}

		else {

			genLocal(el, f0, 0, t); 

		}

		vector<double> x_i; 
		vector<double> f_i; 

		el.solve(x_i, f_i);

		for (int j=0; j<x_i.size(); j++) {

			xout.push_back(x_i[j]); 
			fout.push_back(f_i[j]); 

		}

	}

	writeCurve(xout, fout, t); 

	t_prev = t; // update previous time step 

}

void Solve::writeCurve(vector<double> &x, vector<double> &f, double t) {

	ofstream file; 

	file.open("data/" + to_string(fcount) + ".curve"); 

	file << "# DG" << endl; 

	for (int i=0; i<x.size(); i++) {

		file << x[i] << " " << f[i] << endl; 

	}

	file.close(); 

	fcount += 1; 

}