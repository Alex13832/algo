/** ------------------------------------------------------------
* A simple test case for stack.h
* Alexander Karlsson, 2015-07-15
* -------------------------------------------------------------- */
#include "../stack.h"
#include <iostream>
using namespace std;


int main () {

	Stack<int> stack;

	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	stack.push(5);
	stack.push(6);
	stack.push(7);
	stack.push(8);
	stack.push(9);

	// Should print the LIFO-order
	while(!stack.empty()) {
		int k = stack.pop();
		cout << k << " ";
	}

	cout << endl;

}