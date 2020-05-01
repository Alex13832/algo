/** ------------------------------------------------------------
 Tests for Kosaraju implementation.
 Alexander Karlsson, 2015-08-01
* -------------------------------------------------------------- */
#include "../kosaraju.cc"
#include <iostream>
using namespace std;

int main()
{
	cout << "Test 1" << endl;
	// From GeeksForGeeks
	Graph G1(5);
	G1.addDirEdge(1,0);
	G1.addDirEdge(2,1);
	G1.addDirEdge(0,2);
	G1.addDirEdge(0,3);
	G1.addDirEdge(3,4);

	vector<vector<int>> str_conn1 = kosaraju(G1);


	for (auto vec: str_conn1) {
		for (auto v: vec) {
			cout << v << " ";
		}
		cout << endl;
	}

	cout << "Test 2 " << endl;
	//From Wikipedia
	Graph G2(8);
	G2.addDirEdge(0,1);
	G2.addDirEdge(1,4);
	G2.addDirEdge(4,0);
	G2.addDirEdge(1,5);
	G2.addDirEdge(4,5);
	G2.addDirEdge(1,2);
	G2.addDirEdge(5,6);
	G2.addDirEdge(6,5);
	G2.addDirEdge(2,6);
	G2.addDirEdge(2,3);
	G2.addDirEdge(3,2);
	G2.addDirEdge(7,6);
	G2.addDirEdge(3,7);
	G2.addDirEdge(7,3);


	vector<vector<int>> str_conn2 = kosaraju(G2);

	for (auto vec: str_conn2) {
		for (auto v: vec) {
			cout << v << " ";
		}
		cout << endl;
	}

	cout << "Test 3" << endl;
	//My own
	Graph G3(6);
	G3.addDirEdge(0,1);
	G3.addDirEdge(1,2);
	G3.addDirEdge(2,0);
	G3.addDirEdge(1,3);
	G3.addDirEdge(3,4);
	G3.addDirEdge(5,3);
	G3.addDirEdge(4,5);


	vector<vector<int>> str_conn3 = kosaraju(G3);

	for (auto vec: str_conn3) {
		for (auto v: vec) {
			cout << v << " ";
		}
		cout << endl;
	}

}
