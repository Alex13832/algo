/**
* Heap's algorithm for generating all 
* permutations of a string. 
*/
#include <iostream>
#include <string>
using namespace std;
int count = 0;

/* Swaps str[i] <-> str[j]*/
void swap(string& str, int i, int j) {
	char a = str[i];
	char b = str[j];
	str[j] = a;
	str[i] = b;
}
/* Heaps algorithm */
void heaps(size_t n, string& str) {	
	if (n == 1) {
		cout << str << endl;
		count ++;
	} else {
		for (size_t i = 0; i < n; i++) {
			heaps(n-1, str);
			if (n % 2 == 0) {
				swap(str,i,n-1);
			} else {
				swap(str,0,n-1);
			}	
		}
	}
}

int main() {
	string obj;
	cin >> obj;
	int n = obj.length();
	cout << "-------------------" << endl;
	heaps(n,obj);
	cout << "-------------------" << endl;
	cout << "count " << count << endl;
}
