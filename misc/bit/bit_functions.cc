/** ------------------------------------------------------
* Bit/Number algorithms 
* Alexander Karlsson, begun 2015-07-29
* -------------------------------------------------------- */

#include <climits>
#include <iostream>
#include <cmath>
using namespace std;

/* Detetects if a+b is overflow */
bool is_overflow(int a, int b) {
	return ( a > (INT_MAX - b));
}

/* Test if two integers have opposite signs */
bool opposite(int a, int b) {
	return a*b < 0;
}


