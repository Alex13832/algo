/* --------------------------------------------------
* Algorithms for find kth min and kth max elements 
* in a sequence
* Alexander Karlsson 2015-06-19
* --------------------------------------------------- */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Finds the kth smallest item in vec */
template <typename T>
T find_k_min(vector<T>& vec, int k) {
	for (int i = 0; i <= k; ++i) {
		int minIndex = i;
		T minVal = vec[i]; 
		
		for (size_t j = i+1; j < vec.size(); ++j) {
			if (vec[j] < minVal) {
				minIndex = j;
				minVal = vec[j];
			}
		}

		T t = vec[minIndex];
		vec[minIndex] = vec[i];
		vec[i] = t;
	}	

	return vec[k-1];
}

/* Finds the k smallest items in vec */
template <typename T>
vector<T> find_k_mins(vector<T>& vec, int k) {
	find_k_min(vec, k);
	vector<T> temp;
	temp.resize(k);
	copy_n(vec.begin(), k, temp.begin());
	return temp;
}

/* Finds the kth largest item in vec */
template <typename T>
T find_k_max(vector<T>& vec, int k) {
	for (int i = 0; i <= k; ++i) {
		int minIndex = i;
		T minVal = vec[i]; 
		
		for (size_t j = i+1; j < vec.size(); ++j) {
			if (vec[j] > minVal) {
				minIndex = j;
				minVal = vec[j];
			}
		}

		T t = vec[minIndex];
		vec[minIndex] = vec[i];
		vec[i] = t;
	}	

	return vec[k-1];
}

/* Finds the k largest items in vec */
template <typename T>
vector<T> find_k_maxs(vector<T>& vec, int k) {
	find_k_max(vec, k);
	vector<T> temp;
	temp.resize(k);
	copy_n(vec.begin(), k, temp.begin());
	return temp;
}