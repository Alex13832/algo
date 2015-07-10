#include "../linked_list.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	LinkedList<string> L;

	L.push_back("a");
	L.push_back("b");
	L.push_back("c");
	L.push_back("d");
	L.push_back("e");
	L.push_back("f");
	L.push_back("g");
	

	L.print();

	cout << "first node " << L.front() << endl;
	cout << "last node " << L.back() << endl;
	
	cout << "remove first" << endl;
	L.pop_front();
	L.print();
	cout << "remove last" << endl;
	L.pop_back();
	L.print();

	int k = 2;
	cout << "remove at " << k << endl;
	L.removeAt(k);
	L.print();

	cout << "add first " << endl;
	L.push_front("a");
	L.print();

	int k2 = 3;
	cout << "insert at " << k2 << endl;
	L.insertAt(3,"d");
	L.print();

	cout << "value at " << 0 << ": " << L.at(0) << endl;
	cout << "value at " << k2 << ": " << L.at(k2) << endl;
	cout << "value at " << L.length()-1 << ": " << L.at(L.length()-1) << endl;

}