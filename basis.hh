void genBasis(int p, vector<Polynomial> &B, vector<Polynomial> &dB) {

	vector<double> x = linspace(-1, 1, p); // local points within element 

	vector<vector<double>> coef(p, vector<double>(p)); // store polynomial coefficients 

	for (int k=0; k<p; k++) {

		vector<vector<double>> A(p, vector<double>(p)); // store system for each basis function 

		for (int i=0; i<p; i++) {

			for (int j=0; j<p; j++) {

				A[i][j] = pow(x[i], j); 

			}
		}

		vector<double> b(p); // rhs 

		b[k] = 1; 

		int err = gauss(p, A, coef[k], b); 

	}

    for (int i=0; i<p; i++) {

        B.push_back(Polynomial(coef[i])); 

        dB.push_back(B[i].derivative()); 

    }
}

