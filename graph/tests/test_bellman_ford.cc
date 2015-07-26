#include "../../data_structures/graph.cc"
#include "../bellman_ford.cc"
#include <vector>
using namespace std;

bool test_bellman_ford() {
	Graph g(5);
	g.addDirEdge(0,4,2);
	g.addDirEdge(0,-1,1);
	g.addDirEdge(1,3,2);
	g.addDirEdge(3,5,2);
	g.addDirEdge(3,1,1);
	g.addDirEdge(1,2,3);
	g.addDirEdge(4,-3,3);
	g.addDirEdge(1,2,4);
	vector<int> ws = bellman_ford(g,0);
	int sum = accumulate(ws.begin(),ws.end(),0);
	bool a = sum == 0;

	Graph g2(5);
	g2.addDirEdge(0,3,1);
	g2.addDirEdge(1,5,3);
	g2.addDirEdge(3,2,4);
	g2.addDirEdge(4,-8,1);
	g2.addDirEdge(1,4,2);
	bool negCycle = false;
	try {
		bellman_ford(g2,0);
	} catch(std::invalid_argument) {
		negCycle = true;	
	}

	return a && negCycle;
}

int main() {
	if(test_bellman_ford()) {
		cout << "Bellman-Ford pass" << endl;
	} else {
		cout << "Bellman-Ford fail" << endl;
	} 
}