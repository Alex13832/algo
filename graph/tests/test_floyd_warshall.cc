/** ------------------------------------------------------------
 Tests for floyd_warshall.cc
 Alexander Karlsson, 2015-08-02
* -------------------------------------------------------------- */
#include "../floyd_warshall.cc"

int main()
{
	cout << "Test 1 " << endl;

	Graph G1(4);
	G1.addDirEdge(0,2,1);
	G1.addDirEdge(0,1,2);
	G1.addDirEdge(1,3,0);
	G1.addDirEdge(1,1,3);
	G1.addDirEdge(1,5,2);
	G1.addDirEdge(2,2,0);
	G1.addDirEdge(2,3,3);
	G1.addDirEdge(3,4,0);

	vector<vector<int>> fw1 = floyd_warshall(G1);

	for (auto vec: fw1) {
		for (auto v: vec) {
			cout << v << "     ";
		}
		cout << endl;
	}

	cout << "Test path (G1)"<< endl;
	vector<int> path1 = get_path(G1,0,3);

	for (auto p: path1) cout << p << "    ";
	cout << endl;

	cout << "Test 2" << endl;

	Graph G2(5);
	G2.addDirEdge(0,5,1);
	G2.addDirEdge(0,2,3);
	G2.addDirEdge(1,2,2);
	G2.addDirEdge(2,3,0);
	G2.addDirEdge(2,7,4);
	G2.addDirEdge(3,4,2);
	G2.addDirEdge(3,1,4);
	G2.addDirEdge(4,1,0);
	G2.addDirEdge(4,3,1);

	vector<vector<int>> fw2 = floyd_warshall(G2);

	for (auto vec: fw2) {
		for (auto v: vec) {
			cout << v << "     ";
		}
		cout << endl;
	}

	cout << "Test path (G2)"<< endl;
	vector<int> path = get_path(G2,0,4);

	for (auto p: path) cout << p << "    ";
	cout << endl;
}
