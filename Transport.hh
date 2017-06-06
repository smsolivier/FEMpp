#ifndef Transport_hh
#define Transport_hh

#include "Mesh.hh"
#include "Solve.hh"

class Transport {

public: 

	Transport(Mesh &mesh, int n, double Sigmaa, double Sigmat, double q); 
	void zeroMoment(vector<vector<double>> &psi, vector<double> &phi); 

	Mesh mesh; // mesh class 
	int n; // number of discrete ordinates 
	double Sigmaa, Sigmat, q; // material properties 

	vector<double> mu, w; // discrete ordinates and weights 

	vector<vector<double>> psi; 
	vector<double> phi; // scalar flux 
};

#endif 