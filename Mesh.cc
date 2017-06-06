#include "Mesh.hh" 

#include <iostream>

#include "helper.hh"

using namespace std; 

Mesh::Mesh(int N, double xb, int p) : N(N), xb(xb), p(p) {

	x = linspace(0, xb, N+1); // element edges 

	h = xb/N; // element width 

	// append elements 
	for (int i=0; i<N; i++) {

		el.push_back(Element(x[i], x[i+1], p)); 

	}

}

void Mesh::getf(vector<double> &x, vector<double> &f) {

	x.clear(); 
	f.clear(); 

	for (int i=0; i<N; i++) {

		vector<double> x_el; 
		vector<double> f_el; 

		el[i].interpolate(x_el, f_el); 

		for (int j=0; j<x_el.size(); j++) {

			x.push_back(x_el[j]); 
			f.push_back(f_el[j]); 

		}

	}

}