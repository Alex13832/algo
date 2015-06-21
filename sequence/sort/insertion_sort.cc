/* -----------------------------------------------------
* Insertion sort implementation. >>SLOW<<
* Alexander Karlsson 2015-06-21
* ------------------------------------------------------ */
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

/* Insertion sort */
template <typename T>
void insertion_sort(vector<T>& vec) {
	size_t N = vec.size();

	for (size_t i = 1; i < N; ++i) {
		T obj = vec[i];
		int j = i;

		while (j > 0 && vec[j-1] > obj) {
			vec[j] = vec[j-1];
			j--;
		}

		vec[j] = obj;
	}
}