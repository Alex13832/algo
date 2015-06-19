#include "../k_max_min.cc"
#include <vector>
#include <iostream>
using namespace std;

void test_k_min() {
	vector<double> d = {1.22,6.66,3.33,1.99,1.88,2.33,2.99,2.11,1.44};
	vector<int> i = {1,105,62,99,45,9,104,18,103,22,102};

	double k_max_d = find_k_min(d, 4);
	int k_max_i = find_k_min(i, 6);
	cout << k_max_d << endl;
	cout << k_max_i << endl;

	vector<double> kmins = find_k_mins(d, 4);
	cout << "4-min elements ";
	for (auto el: kmins) {
		cout << el << " ";
	}
	cout << endl;
}


void test_k_max() {
	vector<double> d = {1.22,6.66,3.33,1.99,1.88,2.33,2.99,2.11,1.44};
	vector<int> i = {1,105,62,99,45,9,104,18,103,22,102};

	double k_max_d = find_k_max(d, 3);
	int k_max_i = find_k_max(i, 3);
	cout << k_max_d << endl;
	cout << k_max_i << endl;

	vector<double> kmaxs = find_k_maxs(d, 4);
	cout << "4-max elements ";
	for (auto el: kmaxs) {
		cout << el << " ";
	}
	cout << endl;
}


int main() {
	cout << "k-min test " << endl;
	test_k_min();
	cout << "k-max test " << endl;
	test_k_max();
}