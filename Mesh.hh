#ifndef Mesh_hh
#define Mesh_hh 

#include <vector> 

#include "Element.hh"

class Mesh {

public:

	Mesh(int N, double xb, int p); 

	int N; // number of elements 
	double xb; // domain boundary 
	int p; // order of accuracy in element 

	vector<double> x; // element boundaries 

	double h; // cell width 

	vector<Element> el; // store elements 

};

#endif 