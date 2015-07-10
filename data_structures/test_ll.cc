#include "linked_list.h"
#include <iostream>
using namespace std;

int main() {
	LinkedList<int> L;

	L.push_back(0);
	L.push_back(1);
	L.push_back(2);
	L.push_back(3);
	L.push_back(4);
	L.push_back(5);
	L.push_back(6);
	

	L.print();

	cout << "first node " << L.front() << endl;
	cout << "last node " << L.back() << endl;
	
	cout << "remove first" << endl;
	L.removeFirst();
	L.print();
	cout << "remove last" << endl;
	L.removeLast();
	L.print();

	int k = 2;
	cout << "remove at " << k << endl;
	L.removeAt(k);
	L.print();

}