#ifndef Transport_hh
#define Transport_hh

#include "Mesh.hh"
#include "Solve.hh"

class Transport {

public: 

	Transport(Mesh *mesh, int n, double Sigmaa, double Sigmat, double q); 
	void zeroMoment(vector<vector<double>> &psi, vector<double> &phi); 
	void advance(double t); 

	Mesh *mesh; // mesh object  
	int n; // number of discrete ordinates 
	double Sigmaa, Sigmat, Sigmas, q; // material properties 

	vector<vector<double>> quad; // store angles and weights 

	vector<vector<double>> psi; // angular flux 
	vector<double> phi; // scalar flux 

	Mesh *mesh2; 
	vector<Mesh> vmesh; // store a mesh object for each angle 
	vector<Solve> vsol; // store a solver for each angle 

	vector<double> x; 
	
};

#endif 