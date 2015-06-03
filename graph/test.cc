#include "graph.h"
#include "graph.cc"
#include "bfs.cc"
#include <iostream>
using namespace std;


int main() {
	Graph g(7);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(2, 5);
	g.addEdge(2, 6);
	g.BFS(0);
	cout << endl;
 	
}	
