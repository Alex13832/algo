/** ------------------------------------------------------------
* Tests for Matrix multiplication (mat_mult.cc)
* Alexander Karlsson, 2015-07-22
* -------------------------------------------------------------- */
#include "../mat_mult.cc"
using namespace std;

int main() {
	matrix<double> A1(2, 2);
	matrix<double> A2(2, 2);

	A1(0,0) = 1;
	A1(0,1) = 2;
	A1(1,0) = 2;
	A1(1,1) = 1;

	A2(0,0) = 1;
	A2(0,1) = 1;
	A2(1,0) = 2;
	A2(1,1) = 2;

	matrix<double> C;
	try {
		C = mat_mult(A1,A2);
	} catch (int e) {
		if (e == -1) cout << "Wrong dimensions" << endl;
	}

	for (unsigned i = 0; i < C.size1 (); i++) {
		for (unsigned j = 0; j < C.size2 (); j++) {
			cout << C(i,j) << " ";
		}
		cout << endl;
	}
	cout << endl;

	matrix<double> A(3, 3);
	matrix<double> B(3, 3);

	A(0,0) = 1;
	A(0,1) = 2;
	A(0,2) = 3;
	A(1,0) = 4;
	A(1,1) = 5;
	A(1,2) = 6;
	A(2,0) = 7;
	A(2,1) = 8;
	A(2,2) = 9;

	B(0,0) = 0;
	B(0,1) = 0;
	B(0,2) = 1;
	B(1,0) = 0;
	B(1,1) = 1;
	B(1,2) = 0;
	B(2,0) = 1;
	B(2,1) = 0;
	B(2,2) = 1;


	try {
		matrix<double> C2 = mat_mult(A,B);

		for (unsigned i = 0; i < C2.size1 (); i++) {
			for (unsigned j = 0; j < C2.size2 (); j++) {
				cout << C2(i,j) << " ";
			}
			cout << endl;
		}

	} catch (int e) {
		if (e == -1) cout << "Wrong dimensions" << endl;
	}



	cout << endl;

	matrix<double> E(2, 2);
	matrix<double> D(1, 2);

	matrix<double> C3;
	try {
		C = mat_mult(E,D);
	} catch (int e) {
		if (e == -1) cout << "Wrong dimensions" << endl;
	}
}