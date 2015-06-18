/** ------------------------------------------------------------
* Implementation of Binary Search algorithm.
* Alexander Karlsson 2015-06-18
* -------------------------------------------------------------- */
#include <iostream>
#include <vector>
using namespace std;

/* Binary Search, returns the position where value is found */
template <typename T>
int binary_search(vector<T> A, T value, int min, int max) {
	if (max < min) return -1;

	int mid = (max+min)/2;
	if(A[mid] > value) {
		return binary_search(A, value, min, mid-1);
	} else if (A[mid] < value) {
		return binary_search(A, value, mid+1, max);
	} else {
		return mid;
	}
}