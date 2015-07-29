/** ------------------------------------------------------
* Tests for Bit/Number algorithms 
* Alexander Karlsson, begun 2015-07-29
* -------------------------------------------------------- */

#include "../bit_functions.cc"
#include <iostream>
using namespace std;

/* Tests for overlow */
void test_overflow() { 
	cout << "Testing overflow " << endl;
	
	int a = INT_MAX-2;
	int b = 10;
	bool of = is_overflow(a,b);

	if (of) {
		cout << "Overflow" << endl;
	} else {
		cout << (a + b) << endl;
	}
	cout << endl;

	a = INT_MAX - 10;
	b = 8;
	of = is_overflow(a,b);

	if (of) {
		cout << "Overflow" << endl;
	} else {
		cout << "Not overflow, a + b = " << (a + b) << endl;
	}
	cout << endl;
}


/* Tests for opposite signs */ 
void test_opposite() {
	cout << "Testing opposite signs" << endl;

	int a = -5;
	int b = 5;
	
	if (opposite(a,b)) cout << "opposite signs" << endl;
	else cout << "Equal signs" << endl;

	a = -5;
	b = -5;

	if (opposite(a,b)) cout << "opposite signs" << endl;
	else cout << "Equal signs" << endl;
	
	a = 5;
	b = 5;

	if (opposite(a,b)) cout << "opposite signs" << endl;
	else cout << "Equal signs" << endl;
	
}




int main() {
	test_overflow();
	test_opposite();
}
