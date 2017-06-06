#include "helper.hh"

#include <iostream>

vector<double> linspace(double start, double end, int N) {
	/* generate N evenly spaced points between [start, end] */ 

	vector<double> x(N); 

	double h = (end - start)/(N-1); 

	for (int i=0; i<N; i++) {

		x[i] = h*i + start; 

	}

	return x; 

}

void printVector(vector<double> x) {

    for (int i=0; i<x.size(); i++) {

        cout << x[i] << " "; 
    }

    cout << endl; 
    cout << endl; 

}

void printVector(vector<vector<double>> x) {

    for (int i=0; i<x.size(); i++) {

        for (int j=0; j<x[i].size(); j++) {

            cout << x[i][j] << " "; 
        }

        cout << endl; 
    }
}