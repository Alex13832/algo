#include "../dijkstra.cc"
#include "../dijkstra_pq.cc"
#include "../../data_structures/graph.cc"
#include <vector>

/* Test for dijkstra and dijkstra_pq*/
bool test_dijkstra() {
	vector<vector<pair<int,int>>> adj;

	adj[0].push_back(make_pair(5, 1));



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
	vector<uint> dist = dijkstra(g,0);
	int res1 = dist[5];
	bool a = res1 == 12;

	Graph g2(6);
	g2.addEdge(0,2,2);
	g2.addEdge(0,4,1);
	g2.addEdge(1,1,2);
	g2.addEdge(1,5,3);
	g2.addEdge(2,8,3);
	g2.addEdge(2,10,4);
	g2.addEdge(4,3,5);
	g2.addEdge(3,2,4);
	g2.addEdge(3,6,5);

	vector<uint> dist2 = dijkstra_pq(g2,0);
	int res2 = dist2[5];
	bool b = res2 == 13;

	return a && b;
}

int main() {
	if (test_dijkstra()) {
		cout << "dijkstra test case pass" << endl;
	} else {
		cout << "dijkstra test case fail" << endl;
	}
}
