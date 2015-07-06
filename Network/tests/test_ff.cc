#include "../../graph/graph.h"
#include "../../graph/graph.cc"
#include "../ford_fulkerson.cc"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

bool test_ford_fulkerson() {
	Graph g(6);
	g.addDirEdge(0,160,1); //230
	g.addDirEdge(0,130,2);
	g.addDirEdge(2,40,1);
	g.addDirEdge(1,100,2);
	g.addDirEdge(2,140,4);
	g.addDirEdge(1,120,3);
	g.addDirEdge(3,90,2);
	g.addDirEdge(4,70,3);
	g.addDirEdge(3,200,5);
	g.addDirEdge(4,40,5);

	int a = ford_fulkerson(g,0,5);
	
	Graph g2(6);
	g2.addDirEdge(0,10,1);
	g2.addDirEdge(0,10,2); //19
	g2.addDirEdge(1,2,2);
	g2.addDirEdge(1,4,3);
	g2.addDirEdge(1,8,4);
	g2.addDirEdge(2,9,4);
	g2.addDirEdge(4,6,3);
	g2.addDirEdge(3,10,5);
	g2.addDirEdge(4,10,5);
	
	int b = ford_fulkerson(g2,0,5);
	
	return a == 230 && b == 19;
	
}



int main() {
	if (test_ford_fulkerson()) {
		cout << "Ford-Fulkerson pass" << endl;
	} else {
		cout << "Ford-Fulkerson fail" << endl;
	}
}	
