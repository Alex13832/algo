/** ------------------------------------------------------
* Bit/Number algorithms 
* Alexander Karlsson, begun 2015-07-29
* -------------------------------------------------------- */

#include <climits>
#include <iostream>
using namespace std;

/* Detetects if a+b is overflow */
bool is_overflow(int a, int b) {
	return ( a > (INT_MAX - b));
}





