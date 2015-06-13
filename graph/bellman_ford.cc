//An implementation of the Bellman-Ford algorithm.
//Computes shortest paths from a single source vertex 
//to all of the other vertices in a weighted digraph
#include "graph.h"
#include <climits>
using namespace std;

vector<int> bellman_ford(Graph G, int s) {
	vector<int> dist(G.size(),INT_MAX);
	dist[s] = 0;
	vector<int> prev(G.size(),-1);
	map<pair<int,int>,int> ew = G.getEdgeWeights();
	cout << " adada 2" << endl;
	for (size_t i = 1; i < dist.size(); i++) {
		for (auto e: ew){
			int w = e.second;
			int u = e.first.first;
			int v = e.first.second;
			
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				prev[v] = u;
				cout << "u " << u << endl;
			}
		}
	} 

	for (auto e: ew) {
		int w = e.second;
		int u = e.first.first;
		int v = e.first.second;

		if (dist[u] + w < dist[v]) {
			throw std::invalid_argument( "Graph contains a negative-weight cycle" );
		}
	}
	for (auto p: prev) {
		cout << p << " ";
	}
	cout << endl;

	return dist;
}
