#include "../binary_search.cc"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <time.h>
using namespace std;

void test_nbrs(string file) {
	ifstream infile(file);
	vector<int> vec;
	string line;

	while (getline(infile, line)){	
					
		try {
			int num = stoi(line);
			vec.push_back(num);
		} catch (std::invalid_argument&) { }
					
 	}

	clock_t t0, t1;
	int nbr = 25423;
	cout << "Binary search test (iterative) for numbers -----------" << endl;
	t0 = clock();
	int found = binary_search_it(vec, nbr);
	t1 = clock();
	cout << nbr << " found at: " << found << endl;
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);
	cout << "------------------------------------------------------" << endl;

	cout << "Binary search test (recursive) for numbers -----------" << endl;
	t0 = clock();
	found = binary_search(vec, nbr, 0, vec.size());
	t1 = clock();
	cout << nbr << " found at: " << found << endl;
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);
	cout << "------------------------------------------------------" << endl;
}


void test_strings(string file) {
	ifstream infile(file);
	vector<string> vec;
	string line;

	while (getline(infile, line)){	
		string s = line;	
		vec.push_back(s);
 	}

 	sort(vec.begin(),vec.end());

	clock_t t0, t1;
	string testi = "ureterosigmoidostomies";
	cout << "Binary search test (iterative) for strings -----------" << endl;
	t0 = clock();
	int found = binary_search_it(vec, testi);
	t1 = clock();
	cout << testi << " found at: " << found << endl;
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);
	cout << "------------------------------------------------------" << endl;

	cout << "Binary search test (recursive) for strings -----------" << endl;
	t0 = clock();
	found = binary_search(vec, testi, 0, vec.size());
	t1 = clock();
	cout << testi << " found at: " << found << endl;
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);
	cout << "------------------------------------------------------" << endl;
}


/* Binary Seach test */
int main() {
	test_nbrs("testfiles/nbrs_ordered.txt");
	test_strings("testfiles/eng.txt");
}