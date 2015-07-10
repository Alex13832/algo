#include "../singly_linked_list.cc"
#include <iostream>
#include <string>
using namespace std;

int main() {
	SinglyLinkedList<string> L;

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

	/* Testing extremes */
	SinglyLinkedList<string> L2;

	cout << "Test pop_back/front from empty list " << endl;
	L2.pop_back(); // Pop from empty list
	L2.pop_front();
	cout << "ok" << endl;

	cout << "Test pop_back from list with size == 1 " << endl;
	L2.push_back("a");
	cout << "Length " << L2.length() << endl;
	L2.pop_back();
	L2.print();
	cout << "Length: " << L2.length() << endl;

	cout << "Test pop_front from list with size == 1" << endl;
	L2.push_back("a");
	cout << "Length " << L2.length() << endl;
	L2.pop_front();
	L2.print();
	cout << "Length: " << L2.length() << endl;


}