#include <vector>
#include <iostream> 
#include <cmath>

using namespace std; 

#include "Polynomial.hh"
#include "helper.hh"
#include "gauss.hh"
#include "printVector.hh"

#include <fstream>

#include "basis.hh" 

int main() {

    int p = 4; 

    vector<Polynomial> B, dB; 

    genBasis(p, B, dB); 

    vector<double> x = linspace(-1, 1, 50); 

    vector<vector<double>> f(p, vector<double>(x.size()));

    ofstream file; 
    file.open("out.txt");  

    for (int i=0; i<B.size(); i++) {

        f[i] = dB[i].evaluate(x);

    }

    for (int i=0; i<x.size(); i++) {

        file << x[i] << " ";

        for (int j=0; j<p; j++) {

            file << f[j][i] << " "; 
        } 

        file << endl; 

    }

    file.close();

}