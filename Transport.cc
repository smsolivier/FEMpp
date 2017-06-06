#include "Transport.hh"
#include "Solve.hh"

#include "quad.hh"
#include "helper.hh"

#include <iostream>

using namespace std; 

Transport::Transport(Mesh *mesh, int n, double Sigmaa, double Sigmat, double q) :
	mesh(mesh), n(n), Sigmaa(Sigmaa), Sigmat(Sigmat), q(q)
{

	// get scattering XS 
	Sigmas = Sigmat - Sigmaa; 

	// resize psi 
	psi.resize(n); 

	// angles and weights 
	quad = createRef1dQuad(-1, 1, n); 

	// make a copy of the mesh for each angle 
	for (int i=0; i<n; i++) {

		vmesh.push_back(*mesh); 

	}

	// instantiate a solver for each angle 
	for (int i=0; i<n; i++) {

		int DIR = 0; 
		if (quad[i][0] < 0) DIR = 1; 
		vsol.push_back(Solve(&vmesh[i], 1/3e8, quad[i][0], Sigmat, q, 0, 1, DIR)); 

	}

}

void Transport::zeroMoment(vector<vector<double>> &psi, vector<double> &phi) {
	/* integrate psi with gauss quadrature */ 

	int Nx = psi[0].size(); // number of x points 

	// ensure correct size
	phi.resize(Nx, 0); 

	// reset to 0 
	for (int i=0; i<Nx; i++) {

		phi[i] = 0; 

	}

	for (int i=0; i<Nx; i++) {

		for (int j=0; j<n; j++) {

			phi[i] += psi[j][i] * quad[j][1]; 

		}
	}
}

void Transport::advance(double t) {

	for (int i=0; i<n; i++) {

		vsol[i].advance(t); 

		vmesh[i].getf(x, psi[i]); 

	}

	zeroMoment(psi, phi); 
}

