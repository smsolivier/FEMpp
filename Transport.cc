#include "Transport.hh"

#include "quad.hh"

#include <iostream>

using namespace std; 

Transport::Transport(Mesh &mesh, int n, double Sigmaa, double Sigmat, double q) :
	mesh(mesh), n(n), Sigmaa(Sigmaa), Sigmat(Sigmat), q(q)
{

	// generate mu and w 
	GaussWeights(n, mu, w); 

}

void Transport::zeroMoment(vector<vector<double>> &psi, vector<double> &phi) {

	int Nx = psi[0].size(); // number of x points 

	phi.resize(Nx, 0); 

	for (int i=0; i<Nx; i++) {

		for (int j=0; j<n; j++) {

			phi[i] += psi[j,i] * w[j] 

		}
	}
}

int main() {

	Mesh mesh(10, 1, 2); 
	int n = 8; 
	double Sigmaa = 1; 
	double Sigmat = 1; 
	double q = 1; 

	Transport tr(mesh, n, Sigmaa, Sigmat, q); 

	cout << mesh.N << endl; 

}
