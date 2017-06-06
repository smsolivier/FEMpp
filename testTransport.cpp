#include "Solve.hh" 
#include "Mesh.hh" 
#include "Transport.hh"

#include "quad.hh"
#include "helper.hh"
#include "WriteCurve.hh"

#include <iostream>

int main() {

	int Nx = 40; 
	double xb = 1; 
	int p = 4; 

	Mesh *mesh = new Mesh(Nx, xb, p); 
	int n = 8; 
	double Sigmaa = 1; 
	double Sigmat = 1; 
	double q = 1; 

	double tb = 1e-8; 
	int Nt = 50; 

	Transport tr(mesh, n, Sigmaa, Sigmat, q); 

	WriteCurve wc("data/", "phi"); 

	vector<double> t = linspace(0, tb, Nt+1); 

	for (int i=1; i<t.size(); i++) {

		tr.advance(t[i]); 

		wc.print(tr.x, tr.phi); 

	}

}