/**
* Heap's algorithm for generating all 
* permutations of a string. 
*/
#include <iostream>
#include <string>
using namespace std;
int count = 0;

string swap(string str, int i, int j) {
	string tmp = str;
	tmp[j] = str[i];
	tmp[i] = str[j];
	str = tmp;
	return str;	
}

string heaps(size_t n, string str) {	
	if (n == 1) {
		cout << str << endl;
		count ++;
		return str;	
	} else {

		for (size_t i = 0; i < n; i++) {
			str = heaps(n-1, str);
			
			if (n % 2 == 0) {
				str = swap(str,i,n-1);
				
			} else {
				str = swap(str,0,n-1);

			}	
			
		}
	}
	return str;
}



int main() {
	string obj;
	cin >> obj;
	int n = obj.length();
	heaps(n,obj);
	cout << "count " << count << endl;

}
