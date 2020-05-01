/** ------------------------------------------------------------
* Tests for Self Organizing Lists
* Alexander Karlsson, 2015-07-17
* -------------------------------------------------------------- */
#include "../self_organizing_list.cc"
#include <iostream>
using namespace std;

int main() {

	/* Testing forward method */

	cout << "Testing forward method -------------"  << endl;
	cout << "Should print 0 4 1 2 3 " << endl;
	cout << endl;

	SOListFront<int> listf;
	listf.push_back(0);
	listf.push_back(1);
	listf.push_back(2);
	listf.push_back(3);
	listf.push_back(4);

	listf[4];
	listf[0];
	listf[0];
	listf[0];
	listf[1];

	for(int i = 0; i < listf.size(); ++i) {
		cout <<  listf.at(i) << " ";
	}

	cout << endl;

	/* Testing transpose method */

	cout << "Testing transpose method -------------"  << endl;
	cout << "Should print 4 0 1 3 2 " << endl;
	cout << endl;
	SOListTranspose<int> listt;

	listt.push_back(0);
	listt.push_back(1);
	listt.push_back(2);
	listt.push_back(3);
	listt.push_back(4);

	listt[4];
	listt[3];
	listt[2];
	listt[1];
	listt[4];

	for(int i = 0; i < listt.size(); ++i) {
		cout <<  listt.at(i) << " ";
	}

	cout << endl;


	/* Testing count method */

	cout << "Testing count method -------------"  << endl;
	cout << "Should print 3 4 0 1 2 " << endl;
	cout << endl;
	SOListCount<int> listc;
	listc.push_back(0);
	listc.push_back(1);
	listc.push_back(2);
	listc.push_back(3);
	listc.push_back(4);

	listc[4];
	listc[3];
	listc[2];
	listc[1];
	listc[4];
	listc[3];
	listc[2];
	listc[1];
	listc[1];
	listc[0];

	for(int i = 0; i < listc.size(); ++i) {
		cout <<  listc.at(i) << " ";
	}

	cout << endl;

}