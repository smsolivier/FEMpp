#ifndef helper_hh
#define helper_hh

#include <vector>

using namespace std; 

vector<double> linspace(double start, double end, int N); // generate evenly spaced points 

void printVector(vector<double> x); // print 1D vector 

void printVector(vector<vector<double>> x); // print 2D vector 

#endif 