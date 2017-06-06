#include "Solve.hh"

#include "helper.hh"

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std; 

Solve::Solve(Mesh *mesh, double a, double b, double c, 
	double q, double f0, double alpha, int DIR) : 
		mesh(mesh), a(a), b(b), c(c), q(q), f0(f0), alpha(alpha), DIR(DIR)
{

	t_prev = 0; // initialize previous time step 

}

void Solve::genLocal(Element &el, double upwind, double upwind_prev, double t) {
	/* generate local system for element el */ 

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
			el.rhs[i] += (alpha*(el.Q[j] + q) + (1-alpha)*(el.Q_prev[j] + q))*el.M[i][j]; 

		}
	}

	// sweep left to right 
	if (DIR == 0) {

		// apply upwinding 
		el.A[el.A.size()-1][el.A.size()-1] += alpha*b; 
		el.rhs.back() -= (1 - alpha) * el.f[el.f.size()-1] * b; 

		// left boundary 
		el.rhs[0] += b*(alpha*upwind + (1-alpha)*upwind_prev); 

	}

	// sweep right to left 
	else if (DIR == 1) {

		el.A[0][0] -= alpha*b; 

		el.rhs[0] += (1 - alpha) * el.f[0] * b; 

		el.rhs.back() -= b * (alpha*upwind + (1-alpha)*upwind_prev); 

	}

}

void Solve::sweepLR(double t) {

	for (int i=0; i<mesh->N; i++) {

		Element &el = mesh->el[i]; 

		// generate local system 
		if (i > 0) {

			Element &el_down = mesh->el[i-1];

			genLocal(el, el_down.f.back(), el_down.f_prev.back(), t);

		}

		else {

			genLocal(el, f0, 0, t); 

		} 

		el.solve();

	}

}

void Solve::sweepRL(double t) {

	for (int i=mesh->N-1; i>=0; i--) {

		Element &el = mesh->el[i]; 

		// generate local system 
		if (i != mesh->N-1) {

			Element &el_down = mesh->el[i+1]; // upwind element 

			genLocal(el, el_down.f[0], el_down.f_prev[0], t); 

		}

		else {

			genLocal(el, f0, 0, t); 

		}

		el.solve(); 

	}

}

void Solve::advance(double t) {

	dt = t - t_prev; // time step  

	if (DIR == 0) {

		sweepLR(t); 

	}

	else if (DIR == 1) {

		sweepRL(t); 

	}

	t_prev = t; // update previous time step 

}
