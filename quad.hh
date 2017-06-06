#include <vector>

#include "helper.hh"

using namespace std; 

// generate weights, abcisae 
vector<vector<double>> createRef1dQuad(double x1, double x2, int order);

double GaussQuad(auto &f, int p) {
	/* do gauss integration using weights, absicae from createRef1dQuad */ 

	vector<vector<double>> quad = createRef1dQuad(-1, 1, p);  

	double sum = 0; 
	for (int i=0; i<quad.size(); i++) {

		sum += f(quad[i][0])*quad[i][1]; 

	}	

	return sum; 

}