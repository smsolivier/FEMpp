vector<double> linspace(double start, double end, int N) {
	/* generate N evenly spaced points between [start, end] */ 

	vector<double> x(N); 

	double h = (end - start)/(N-1); 

	for (int i=0; i<N; i++) {

		x[i] = h*i + start; 

	}

	return x; 

}