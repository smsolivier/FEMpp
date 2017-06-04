#ifndef quad_hh
#define quad_hh

#include <vector> 
#include <cmath>

using namespace std; 

double GaussQuad(auto &f) {

	vector<double> mu = {
		-0.3399810435848563, 
		0.3399810435848563,
		-0.8611363115940526,
		0.8611363115940526
	};

	vector<double> w = {
		0.6521451548625461,
		0.6521451548625461,	
		0.3478548451374538,	
		0.3478548451374538
	};

	double sum = 0; 
	for (int i=0; i<mu.size(); i++) {

		sum += f(mu[i])*w[i]; 

	}	

	return sum; 

}

#endif