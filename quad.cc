#include "quad.hh"

#include <cmath>
#include <iostream>

using namespace std; 

double GaussWeights(int n, vector<double> &mu, vector<double> &w) {

	mu.resize(n); 
	w.resize(n); 

	if (n == 8) {

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

	}

	else {

		cout << "--- FATAL ERROR: gauss order not supported ---" << endl; 
		exit(0); 

	}
}