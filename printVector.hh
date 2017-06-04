#ifndef printVector_hh
#define printVector_hh

#include <iostream>

using namespace std; 

void printVector(vector<double> x) {

    for (int i=0; i<x.size(); i++) {

        cout << x[i] << endl; 
    }
}

void printVector(vector<vector<double>> x) {

    for (int i=0; i<x.size(); i++) {

        for (int j=0; j<x[i].size(); j++) {

            cout << x[i][j] << " "; 
        }

        cout << endl; 
    }
}

#endif 