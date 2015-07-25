/** ------------------------------------------------------------
* Tests for DynArray.
* Alexander Karlsson, 2015-07-25
* -------------------------------------------------------------- */
#include "../dyn_array.cc"
using namespace std;

int main() {

	cout << "Test with initialiser constructor" << endl;
	DynArray<int> darr{0,1,2,3,4,5,6,7,8,9,10};
	
	cout << "If resize ok, 0...10 added, and all printed, test is ok" << endl;
	darr.printAll();
	
	cout << "Test size " << darr.size() << endl;
	
	cout << "Test push_back" << endl;
	int k = 11;
	for (size_t i = 0; i < 20; i++) {
		darr.push_back(k);
		k++;
	}
	
	darr.printAll();
	
	cout << "Test operator[]" << endl;
	for (size_t i = 0; i < 5; i++) {
		cout << darr[i] << " ";
	}
	cout << endl;
	
	cout << "And assignment []=" << endl;
	darr[20] = 123;
	darr[21] = 456;
	darr[22] = 789;
	darr.printAll();
	
	cout << "Test back()" << endl;
	cout << darr.back() << endl;
	
	cout << "Test pop_back() " << endl;
	for (size_t i = 0; i < 20; i++) {
		darr.pop_back();
	}	
	darr.printAll();
	
	cout << "Test + DynArray" << endl;
	DynArray<int> darr2{11,12,13,14};
	darr.printAll();
	
	cout << "Test make list with different size " << endl;
	DynArray<int> darr3(20);
	cout << darr3.size() << endl;
	
	cout << "Test make list with same value " << endl;
	DynArray<int> darr4(10,123);
	darr4.printAll();
	
	cout << "Test removeAt()" << endl;
	DynArray<int> darr5{0,1,2,3,4,5,6,7,8,9,10};
	darr5.removeAt(5);
	darr5.removeAt(5);
	darr5.removeAt(5);
	darr5.printAll();
	
	

}
