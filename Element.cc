#include <vector> 
#include <iostream>
#include <cmath> 

#include "Element.hh" 

#include "quad.hh"
#include "LinearSolver.hh"
#include "helper.hh"

using namespace std; 

Element::Element(double start, double end, int p) : start(start), end(end), p(p) {

	// generate global points 
	xglob = linspace(start, end, p); 

	// local points 
	xloc = linspace(-1, 1, p); 

	h = end - start; // element width 

	// get basis functions 
	genBasis(); 

	// initialize sizes
	f.resize(p); 
	f_prev.resize(p); 
	Q.resize(p); 
	Q_prev.resize(p); 

	A.resize(p); 
	M.resize(p); 
	S.resize(p); 
	for (int i=0; i<p; i++) {

		A[i].resize(p); 
		M[i].resize(p); 
		S[i].resize(p); 

	}

	rhs.resize(p); 

	// generate mass, stiff matrices 
	genMass(); 
	genStiff(); 

}

void Element::genBasis() {

	vector<vector<double>> coef(p, vector<double>(p)); // store polynomial coefficients 

	for (int k=0; k<p; k++) {

		vector<vector<double>> A(p, vector<double>(p)); // store system for each basis function 

		for (int i=0; i<p; i++) {

			for (int j=0; j<p; j++) {

				A[i][j] = pow(xloc[i], j); 

			}
		}

		vector<double> b(p); // rhs 

		b[k] = 1; 

		int err = gauss_elim(p, A, coef[k], b); 

	}

    for (int i=0; i<p; i++) {

        B.push_back(Polynomial(coef[i])); 

        dB.push_back(B[i].derivative()); 

    }
}

double Element::Jacobian(double xi) {
	/* Compute Jacobian (dx/dxi) */ 

	double sum = 0; 
	for (int i=0; i<p; i++) {

		sum += xglob[i] * dB[i].evaluate(xi); 

	}

	return sum; 

}

void Element::genMass() {
	/* fill mass matrix */ 

	for (int i=0; i<p; i++) {

		for (int j=0; j<p; j++) {

			auto func = [this, i, j] (double xi) {return B[i].evaluate(xi)*B[j].evaluate(xi)*Jacobian(xi); };

			M[i][j] = GaussQuad(func, p+1); 

		}
	}
}

void Element::genStiff() {
	/* fill stiffness matrix */ 

	for (int i=0; i<p; i++) {

		for (int j=0; j<p; j++) {

			auto func = [this, i, j] (double xi) {return dB[i].evaluate(xi)*B[j].evaluate(xi); }; 

			S[i][j] = GaussQuad(func, p+1); 

		}
	}
}

double Element::xiToX(double xi) {

	double sum = 0; 

	for (int i=0; i<p; i++) {

		sum += xglob[i] * B[i].evaluate(xi); 
	}

	return sum; 

}

double Element::evaluate(double xi) {

	double sum = 0; 
	for (int i=0; i<p; i++) {

		sum += f[i] * B[i].evaluate(xi); 

	}

	return sum; 

}

void Element::solve() {

	f_prev = f; // make copy of old one 

	for (int i=0; i<f.size(); i++) {

		f[i] = 0; 

	}

	int err = gauss_elim(p, A, f, rhs); // solve system 

	if (err == -1) {

		cout << "--- Linear Solver error --- " << endl; 

	}

	// reset A, rhs 
	for (int i=0; i<p; i++) {

		for (int j=0; j<p; j++) {

			A[i][j] = 0; 

		}

		rhs[i] = 0; 

	}

}

void Element::interpolate(vector<double> &xout, vector<double> &fout) {
	/* interpolate between nodes */ 

	vector<double> xc(p-1); // local midpoint location between nodes 

	// compute midpoints 
	for (int i=1; i<p; i++) {

		xc[i-1] = (xloc[i] - xloc[i-1])/2 + xloc[i-1]; 

	}

	// update output vectors 
	xout.resize(p-1); 
	fout.resize(p-1); 

	for (int i=0; i<p-1; i++) {

		xout[i] = xiToX(xc[i]); // convert to global location 
		fout[i] = evaluate(xc[i]); // evaluate at midpoint 

	}

}