#include "Element.hh" 

using namespace std; 

Element::Element(double start, double end, int p) : start(start), end(end), p(p) {

	// generate global points 
	xglob = linspace(start, end, p); 

	// get basis functions 
	genBasis(p, B, dB); 

	// initialize sizes
	f.resize(p); 
	f_prev.resize(p); 

	A.resize(p); 
	M.resize(p); 
	S.resize(p); 
	for (int i=0; i<p; i++) {

		A[i].resize(p); 
		M[i].resize(p); 
		S[i].resize(p); 

	}

	rhs.resize(p); 

	// generate mass, stiff matrices 
	genMass(); 
	genStiff(); 

}

double Element::Jacobian(double xi) {
	/* Compute Jacobian (dx/dxi) */ 

	double sum = 0; 
	for (int i=0; i<p; i++) {

		sum += xglob[i] * dB[i].evaluate(xi); 

	}

	return sum; 

}

void Element::genMass() {
	/* fill mass matrix */ 

	for (int i=0; i<p; i++) {

		for (int j=0; j<p; j++) {

			auto func = [this, i, j] (double xi) {return B[i].evaluate(xi)*B[j].evaluate(xi)*Jacobian(xi); };

			M[i][j] = GaussQuad(func); 

		}
	}
}

void Element::genStiff() {
	/* fill stiffness matrix */ 

	for (int i=0; i<p; i++) {

		for (int j=0; j<p; j++) {

			auto func = [this, i, j] (double xi) {return dB[i].evaluate(xi)*B[j].evaluate(xi); }; 

			S[i][j] = GaussQuad(func); 

		}
	}
}

int main() {

	Element el(0, 1, 4); 

	el.genStiff(); 

	printVector(el.S); 

}