#include "../graph.cc"
#include "../prim.cc"
#include <fstream>
#include <vector>
using namespace std;

bool test_prim1() {
	Graph g(7);
	g.addEdge(0,5,3);
	g.addEdge(0,7,1);
	g.addEdge(1,8,2);
	g.addEdge(1,7,4);
	g.addEdge(2,5,4);
	g.addEdge(3,15,4);
	g.addEdge(3,6,5);
	g.addEdge(4,9,6);
	g.addEdge(5,8,4);
	g.addEdge(5,11,6);
	g.addEdge(3,9,1);
	vector<uint> net1 = prim(g, 0);
	uint sum1 = accumulate(net1.begin(),net1.end(),0);
	bool a = sum1 == 39;

	Graph g2(9);
	g2.addEdge(0,10,1);
	g2.addEdge(0,12,2);
	g2.addEdge(1,9,2);
	g2.addEdge(2,3,4);
	g2.addEdge(2,1,5);
	g2.addEdge(1,8,3);
	g2.addEdge(4,7,3);
	g2.addEdge(4,3,5);
	g2.addEdge(3,5,7);
	g2.addEdge(5,6,7);
	g2.addEdge(3,8,6);
	g2.addEdge(6,9,7);
	g2.addEdge(6,2,8);
	g2.addEdge(7,11,8);
	vector<uint> net2 = prim(g2,0);
	uint sum2 = accumulate(net2.begin(),net2.end(),0);
	bool b = sum2 == 43;
	
	Graph g3(7);
	g3.addEdge(0,16,1);
	g3.addEdge(0,21,3);
	g3.addEdge(0,12,2);
	g3.addEdge(1,20,4);
	g3.addEdge(1,17,3);
	g3.addEdge(2,28,3);
	g3.addEdge(3,18,4);
	g3.addEdge(3,23,6);
	g3.addEdge(3,19,5);
	g3.addEdge(2,31,5);
	g3.addEdge(4,11,6);
	g3.addEdge(5,27,6);
	vector<uint> net3 = prim(g3,0);
	int sum3 = accumulate(net3.begin(),net3.end(),0);
	bool c = sum3 == 93;
	
	return a && b && c;

}

//Test-case file is downloaded from "Project Euler"
//Problem 107
bool test_prim2(){
	Graph g(40);
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
				g.addEdge(col,weight,row); 

			} catch (std::invalid_argument&) { }

		    	s.erase(0, pos + delimiter.length());
			col++;
		}

		try {

			int weight = stoi(s);
			total.push_back(weight);
			g.addEdge(col,weight,row);
			
		} catch (std::invalid_argument&) { }
 		
		row++;
		col = 0;
	}

	int totsum = accumulate(total.begin(),total.end(),0)/2;
	//cout << "totsum " << totsum <<endl;
	vector<uint> weights = prim(g,0);
	int wsum = accumulate(weights.begin(),weights.end(),0);
	//cout << "wsum " << wsum << endl;
	int saved = totsum - wsum;
	//cout << "saved " << saved << endl;
	return saved == 259679;

}

int main() {
	if(test_prim1() && test_prim2()){
		cout << "prim test case pass" << endl;
	} else {
		cout << "prim test case fail" << endl;
	}
}