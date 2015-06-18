#include "../binary_search.cc"
#include <iostream>
#include <vector>
using namespace std;

/* Binary Seach test */
int main() {
	vector<int> A = {1,23,45,77,88,99,100,233,444,3332,5545,13133};
	int a = 3332;
	int m = binary_search(A, a, 0, A.size());
	cout << a << " found at: " << m << endl;

	vector<string> B = {"Amanda","Anna","Becky","Cecilia","Doris","Katarina"};
	string obj = "Doris";
	int b = binary_search(B, obj, 0, B.size());
	cout << obj << " found at: " << b << endl;

	vector<char> C = {'a','b','e','k','m','o','q'};
	char c1obj = 'a';
	char c2obj = 'c';
	int c1 = binary_search(C, c1obj, 0, C.size());
	int c2 = binary_search(C, c2obj, 0, C.size());
	cout << c1obj << " found at: " << c1 << endl;
	cout << c2obj << " found at: " << c2 << endl;
}