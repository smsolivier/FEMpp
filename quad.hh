#include <vector>

#include "helper.hh"

using namespace std; 

double GaussWeights(int n, vector<double> &mu, vector<double> &w); 

double GaussQuad(auto &f) {

	// vector<double> mu, w; 

	// GaussWeights(8, mu, w); 

	vector<double> mu = {
		-0.1834346424956498,
		0.1834346424956498,
		-0.5255324099163290,
		0.5255324099163290,
		-0.7966664774136267,
		0.7966664774136267,
		-0.9602898564975363,
		0.9602898564975363
	};

	vector<double> w = {
		0.3626837833783620,
		0.3626837833783620,	
		0.3137066458778873,	
		0.3137066458778873,	
		0.2223810344533745,	
		0.2223810344533745,	
		0.1012285362903763,	
		0.1012285362903763
	};

	double sum = 0; 
	for (int i=0; i<mu.size(); i++) {

		sum += f(mu[i])*w[i]; 

	}	

	return sum; 

}