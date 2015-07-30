/** ------------------------------------------------------------
* Implementation of the Merge Sort Algorithm
* Alexander Karlsson, begun 2015-07-30
* -------------------------------------------------------------- */
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

/** Merge step. Uses linked list datastructures, hopefully better
  than using vectors since we have to move all items n steps when
  removing the first elements. */
template <typename T>
vector<T> merge(list<T> A, list<T> B) {
	vector<T> C;

	while (!A.empty() || !B.empty()) {
		if (A.front() > B.front()) {
			C.push_back(B.front());
			B.pop_front();
		} else {
			C.push_back(A.front());
			A.pop_front();
		}
	}

	while (!A.empty()) {
		C.push_back(A.front());
		A.pop_front();
	}

	while (!B.empty()) {
		C.push_back(B.front());
		B.pop_front();
	}

	return C;
}

/* Merge Sort divide and conquer algorithm */
template <typename T>
vector<T> merge_sort(vector<T> lst) {
	size_t n = lst.size();

	if (n == 1) return lst;

	size_t half = n/2;
	vector<T> A,B;

	for (auto it = lst.begin(); it!=(lst.begin()+half); ++it) {
		A.push_back(*it);
	}
	for (auto it = (lst.begin()+half); it!=lst.end(); ++it) {
		B.push_back(*it);
	}

	A = merge_sort(A);
	B = merge_sort(B);

	list<T> Al(A.size()), Bl(B.size());
	copy(A.begin(),A.end(),Al.begin());
	copy(B.begin(),B.end(),Bl.begin());

	return merge(Al,Bl);
}
