/**
* Heap's algorithm for generating all
* permutations of a string.
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/* Heaps algorithm */
void heaps(size_t n, string& str, int& count) {
	if (n == 1) {
		cout << str << endl;
		count++;
	} else
		for (size_t i = 0; i < n; i++) {
			heaps(n-1, str, count);
			if (n % 2 == 0) swap(str[i],str[n-1]);
			else swap(str[0],str[n-1]);
		}
}

int main() {
	int count = 0;
	string obj;
	cin >> obj;
	int n = obj.length();
	cout << "-------------------" << endl;
	heaps(n,obj, count);
	cout << "-------------------" << endl;
	cout << "count " << count << endl;
}
