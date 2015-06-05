#include "graph.h"
#include "graph.cc"
#include "bfs.cc"
#include "dfs.cc"
#include "dijkstra.cc"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool test_BFS(Graph g){
	vector<int> values = {0,1,2,3,4,5,6};
	vector<int> res = g.BFS(0);
	bool comp = equal(res.begin(),res.end(),values.begin());
	return comp;
}

bool test_DFS(Graph g){
	vector<int> values = {0,1,3,4,2,5,6};
	vector<int> res = g.DFS(0);
	bool comp = equal(res.begin(),res.end(),values.begin());
	return comp;
}


void test_dijkstra() {
	Graph g(6);
	g.addEdge(0,1);
	g.addEdge(0,2);
	g.addEdge(1,3);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(2,4);
	g.addEdge(3,4);
	g.addEdge(3,5);
	g.addEdge(4,5);

	g.addEdgeWeight(0,1,4);
	g.addEdgeWeight(0,2,2);
	g.addEdgeWeight(1,3,5);
	g.addEdgeWeight(1,2,1);
	g.addEdgeWeight(2,3,8);
	g.addEdgeWeight(2,4,10);
	g.addEdgeWeight(3,4,2);
	g.addEdgeWeight(3,5,6);
	g.addEdgeWeight(4,5,3);
	
	g.dijkstra(0);

	
}


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

	if (test_BFS(g)) {
		cout << "BFS pass" << endl;
	} else {
		cout << "BFS fail" << endl;
	}

	if (test_DFS(g)) {
		cout << "DFS pass" << endl;
	} else {
		cout << "DFS fail" << endl;
	}
	
	test_dijkstra();
 	
}	
