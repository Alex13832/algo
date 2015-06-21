#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdio.h>
#include <time.h>
#include "../heapsort.cc"
#include "../quicksort.cc"
using namespace std;

int main() {
	vector<int> vec(50000000);
	iota(vec.begin(), vec.end(), 0);
	random_shuffle(vec.begin(),vec.end());

	clock_t t0, t1;

	cout << "quicksort test -------------- " << endl; 
	t0 = clock(); 
	quicksort(vec, 0, vec.size()-1);
	t1 = clock();
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	cout << endl;
	for (size_t i = 0; i < 10; i++) {
		cout << vec[i] << " ";
	}
	cout << endl;

	for (size_t i = vec.size()-10; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
	cout << "-----------------------------" << endl;

	cout << "heapsort test -------------- " << endl; 
	random_shuffle(vec.begin(),vec.end());
	t0 = clock(); 
	heapsort(vec, vec.size());
	t1 = clock();
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	cout << endl;
	for (size_t i = 0; i < 10; i++) {
		cout << vec[i] << " ";
	}
	cout << endl;

	for (size_t i = vec.size()-10; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}

	cout << endl;

	cout << "-----------------------------" << endl;


}