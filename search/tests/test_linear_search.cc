#include "../linear_search.cc"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <time.h>
using namespace std;

void test_strings(string file) {
	ifstream infile(file);
	vector<string> vec;
	string line;

	while (getline(infile, line)){	
		string s = line;	
		vec.push_back(s);
 	}
 	
	clock_t t0, t1;
	t0 = clock();
	string testi = "ureterosigmoidostomies";
	int found = linear_search(vec, testi);
	t1 = clock();
	cout << "found at: " << found << endl;
	printf ("Used %g CPU seconds\n",
	(t1 - t0) / (double)CLOCKS_PER_SEC);
}


/* Binary Seach test */
int main() {
	test_strings("testfiles/eng.txt");
}