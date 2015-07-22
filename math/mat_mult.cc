/** ------------------------------------------------------------
* O(n^3) matrix multiplication algorithm.
* This implementation use the boost library, may be changed 
* later.
* Alexander Karlsson, 2015-07-22
* -------------------------------------------------------------- */
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iostream>
using namespace boost::numeric::ublas;
using namespace std;


/* Matrix multiplication, use numbers! */
template <typename T>
matrix<T> mat_mult(matrix<T> A, matrix<T> B) {
	size_t x = A.size1(); // Number of rows in A
	size_t y = A.size2(); // Number of columns in A, number of rows in B
	size_t y2 = B.size1(); // Number of rows in B
	size_t z = B.size2(); // Number of columns in B
	matrix<T> C(x,z); // Resulting matrix

	/* Dimensions must agree */
	if (y != y2) throw -1;

	for (size_t i = 0; i < x; ++i) {
		for (size_t j = 0; j < z; ++j) {
			C(i,j) = 0;
			for (size_t k = 0; k < y; ++k) {
				C(i,j) = C(i,j) + A(i,k)*B(k,j);
			}
		}
	}

	return C;
}