#include "../graph/graph.h"
#include "../graph/graph.cc"
#include "ford_fulkerson.cc"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

void test_ford_fulkerson() {
	Graph g(6);
	g.addDirEdge(0,110,1); //23
	g.addDirEdge(0,120,2);
	g.addDirEdge(2,10,1);
	g.addDirEdge(1,120,3);
	g.addDirEdge(2,110,4);
	g.addDirEdge(4,70,3);
	g.addDirEdge(4,40,5);
	g.addDirEdge(3,190,5);

	int a = ford_fulkerson(g,0,5);
	cout << a << endl;

	Graph g2(6);
	g2.addDirEdge(0,10,1);
	g2.addDirEdge(0,10,2);
	g2.addDirEdge(1,2,2);
	g2.addDirEdge(1,4,3);
	g2.addDirEdge(1,8,4);
	g2.addDirEdge(2,9,4);
	g2.addDirEdge(4,6,3);
	g2.addDirEdge(3,10,5);
	g2.addDirEdge(4,10,5);
	
	int b = ford_fulkerson(g2,0,5);
	cout << b << endl;

}



int main() {
	test_ford_fulkerson();
}	
