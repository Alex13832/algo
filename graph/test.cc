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


bool test_dijkstra() {
	
	Graph g(7);
	g.addEdge(0,5,1);
	g.addEdge(0,10,2);
	g.addEdge(2,2,4);
	g.addEdge(1,3,4);
	g.addEdge(1,6,3);
	g.addEdge(4,2,3);
	g.addEdge(3,6,5);
	g.addEdge(4,2,6);
	g.addEdge(6,2,5);

	vector<uint> dist = g.dijkstra(0);
	int res1 = dist[5];
	bool a = res1 == 12;

	Graph g2(6);
	g2.addEdge(0,2,2);
	g2.addEdge(2,2,0);
	g2.addEdge(0,4,1);
	g2.addEdge(1,4,0);
	g2.addEdge(1,1,2);
	g2.addEdge(2,1,1);
	g2.addEdge(1,5,3);
	g2.addEdge(3,5,1);
	g2.addEdge(2,8,3);
	g2.addEdge(3,8,2);
	g2.addEdge(2,10,4);
	g2.addEdge(4,10,2);
	g2.addEdge(4,3,5);
	g2.addEdge(5,3,4);
	g2.addEdge(3,2,4);
	g2.addEdge(4,2,3);
	g2.addEdge(3,6,5);
	g2.addEdge(5,6,3);
	
	vector<uint> dist2 = g2.dijkstra(0);
	int res2 = dist2[5];
	bool b = res2 == 13;

	return a && b;
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
	
	if (test_dijkstra()) {
		cout << "Dijkstra pass" << endl;
	} else {
		cout << "Dijkstra fail" << endl;
	}
		
 	
}	
