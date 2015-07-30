/** ------------------------------------------------------------
* Implementation of the BubbleSort. Should be good for a 
* small amount of items to be sorted.
* Alexander Karlsson, 2015-07-30
* -------------------------------------------------------------- */
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
vector<T> bubble_sort(vector<T> lst) {
	size_t n = lst.size();

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n-1; j++) {
			if (lst[j] > lst[j+1]) {
				swap(lst[j],lst[j+1]);
			}
		}
	}

	return lst;
}