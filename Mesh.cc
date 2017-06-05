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