#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdio.h>
#include <time.h>
#include "../heapsort.cc"
#include "../quicksort.cc"
#include "../insertion_sort.cc"
using namespace std;

int main() {
	vector<int> vec(250000);
	iota(vec.begin(), vec.end(), 0);
	random_shuffle(vec.begin(),vec.end());

	clock_t t0, t1;

	/* QUICKSORT TEST */

	cout << "-------------------------------------------------------" << endl;
	cout << "quicksort test " << endl; 
	cout << "-------------------------------------------------------" << endl;
	t0 = clock(); 
	quicksort(vec, 0, vec.size()-1);
	t1 = clock();
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	cout << endl;
	for (size_t i = 0; i < 4; i++) {
		cout << vec[i] << " ";
	}
	cout << endl;

	for (size_t i = vec.size()-4; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
	cout << "-------------------------------------------------------" << endl;

	/* HEAPSORT TEST */

	cout << "-------------------------------------------------------" << endl;
	cout << "heapsort test  " << endl; 
	cout << "-------------------------------------------------------" << endl;
	random_shuffle(vec.begin(),vec.end());
	t0 = clock(); 
	heapsort(vec, vec.size());
	t1 = clock();
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	cout << endl;
	for (size_t i = 0; i < 4; i++) {
		cout << vec[i] << " ";
	}
	cout << endl;

	for (size_t i = vec.size()-4; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}

	cout << endl;
	cout << "-------------------------------------------------------" << endl;


	/* INSERTION SORT */

	cout << "-------------------------------------------------------" << endl;
	cout << "Insertion sort test  " << endl; 
	cout << "-------------------------------------------------------" << endl;
	random_shuffle(vec.begin(),vec.end());
	t0 = clock(); 
	insertion_sort(vec);
	t1 = clock();
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);

	cout << endl;
	for (size_t i = 0; i < 4; i++) {
		cout << vec[i] << " ";
	}
	cout << endl;

	for (size_t i = vec.size()-4; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}

	cout << endl;
	cout << "-------------------------------------------------------" << endl;

}