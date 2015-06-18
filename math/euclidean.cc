/** -------------------------------------------------------
* Implementation of the Euclidean Algorithm. The algorithm 
* is used for finding the greatest common divisor (gcd) of
* two integers a an b.
* Alexander Karlsson, 2015-06-18
* --------------------------------------------------------- */
#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;

/* Recursive implmentation */
ulong gcd_r(ulong a, ulong b) {

	if (b == 0) {
		return a;
	} else {
		return gcd_r(b, a % b);
	} 
}

/* Iterative implementation */
ulong gcd_i(ulong a, ulong b) {
	ulong c = 0;
	while (b != 0) {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}


int main() {
	clock_t t0, t1;
	t0 = clock();
	ulong ans_r = gcd_r(555523423465466455,2545622442464642525);
	t1 = clock();
	cout << ans_r << endl;
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	t0 = clock();
	ulong ans_i = gcd_i(555523423465466455,2545622442464642525);
	t1 = clock();
	cout << ans_i << endl;
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);
}