/** -----------------------------------------------
* Implementation of linear search. 
* Can be used for unsorted lists.
* Alexander Karlsson 2015-06-19
* ------------------------------------------------- */
#include <iostream>
#include <vector>
using namespace std;

/* Linear Search, returns the index of t */
template <typename T>
int linear_search(vector<T> vec, T t) {
	for (size_t i = 0; i < vec.size(); ++i) {
		if (vec[i] == t) return i;
	}
	return -1;
}