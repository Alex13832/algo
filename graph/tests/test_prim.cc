#include "../../data_structures/graph.cc"
#include "../prim.cc"
#include <fstream>
#include <vector>
using namespace std;

void make_node(vector<vector<pair<int,int>>>& G, int s, int t, int w)
{
	G[s].push_back(make_pair(t, w));
	G[t].push_back(make_pair(s, w));
}

bool test_prim1()
{
	/* Test 1 */
	vector<vector<pair<int,int>>> G1(7);
	make_node(G1, 0, 3, 5);
	make_node(G1, 0, 1, 7);
	make_node(G1, 1, 2, 8);
	make_node(G1, 1, 4, 7);
	make_node(G1, 2, 4, 5);
	make_node(G1, 3, 4, 15);
	make_node(G1, 3, 5, 6);
	make_node(G1, 4, 6, 9);
	make_node(G1, 5, 4, 8);
	make_node(G1, 5, 6, 11);
	make_node(G1, 3, 1, 9);

	vector<uint> net1 = prims(G1, 0);
	uint sum1 = accumulate(net1.begin(),net1.end(),0);
	bool a = sum1 == 39;
	return a;

	/* Test 2 */
	vector<vector<pair<int,int>>> G2(9);
	make_node(G2, 0, 1, 10);
	make_node(G2, 0, 2, 12);
	make_node(G2, 1, 2, 9);
	make_node(G2, 2, 4, 3);
	make_node(G2, 2, 5, 1);
	make_node(G2, 1, 3, 8);
	make_node(G2, 4, 3, 7);
	make_node(G2, 4, 5, 3);
	make_node(G2, 3, 7, 5);
	make_node(G2, 5, 7, 6);
	make_node(G2, 3, 6, 8);
	make_node(G2, 6, 7, 9);
	make_node(G2, 6, 8, 2);
	make_node(G2, 7, 8, 11);

	vector<uint> net2 = prims(G2, 0);
	uint sum2 = accumulate(net2.begin(), net2.end(), 0);
	bool b = sum2 == 43;

	/* Test 3 */
	vector<vector<pair<int,int>>> G3(7);
	make_node(G3, 0, 1, 16);
	make_node(G3, 0, 3, 21);
	make_node(G3, 0, 2, 12);
	make_node(G3, 1, 4, 20);
	make_node(G3, 1, 3, 17);
	make_node(G3, 2, 3, 28);
	make_node(G3, 3, 4, 18);
	make_node(G3, 3, 6, 23);
	make_node(G3, 3, 5, 19);
	make_node(G3, 3, 5, 31);
	make_node(G3, 4, 6, 11);
	make_node(G3, 5, 6, 27);

	vector<uint> net3 = prims(G3,0);
	int sum3 = accumulate(net3.begin(),net3.end(),0);
	bool c = sum3 == 93;


	return a && b && c;
}


//Test-case file is downloaded from "Project Euler"
//Problem 107
bool test_prim2()
{
	vector<vector<pair<int,int>>> G(40);
	vector<int> total;
	ifstream infile("testfiles/p107_network.txt");
	string line;
	int row = 0;
	int col = 0;

	while (getline(infile, line)){
		string s = line;
		string delimiter = ",";

		size_t pos = 0;
		string token;
		while ((pos = s.find(delimiter)) != string::npos) {
		    token = s.substr(0, pos);

			try {
				int weight = stoi(token);
				total.push_back(weight);
				make_node(G, col, row, weight);
			} catch (std::invalid_argument&) { }

			s.erase(0, pos + delimiter.length());
			col++;
		}

		try {
			int weight = stoi(s);
			total.push_back(weight);
			make_node(G, col, row, weight);
		} catch (std::invalid_argument&) { }

		row++;
		col = 0;
	}

	int totsum = accumulate(total.begin(),total.end(),0)/2;
	cout << "totsum " << totsum <<endl;
	vector<uint> weights = prims(G,0);
	int wsum = accumulate(weights.begin(),weights.end(),0);
	cout << "wsum " << wsum << endl;
	int saved = totsum - wsum;
	cout << "saved " << saved << endl;
	return saved == 259679;
}

int main() {
	if(test_prim1() && test_prim2()){
		cout << "prim test case pass" << endl;
	} else {
		cout << "prim test case fail" << endl;
	}
}
