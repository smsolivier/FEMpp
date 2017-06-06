#include <vector>

using namespace std; 

double GaussWeights(int n, vector<double> &mu, vector<double> &w); 

double GaussQuad(auto &f) {

	vector<double> mu, w; 

	GaussWeights(8, mu, w); 	 

	double sum = 0; 
	for (int i=0; i<mu.size(); i++) {

		sum += f(mu[i])*w[i]; 

	}	

	return sum; 

}