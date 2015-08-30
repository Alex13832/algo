//Dijkstra's algorithm for finding the shortest path. 
//Alexander Karlsson, 2015
#include "../data_structures/graph.h"
#include <vector>
#include <climits>
using namespace std;

vector<uint> dijkstra(Graph G, const int s) {
	vector<uint> dist(G.size(),UINT_MAX);
	vector<uint> prev(G.size());
	vector<bool> visited(G.size(),false);
	dist[s] = 0;

	while (find(visited.begin(),visited.end(),false) != visited.end()) {
		uint smallest = UINT_MAX;
		int i = 0, k = 0;	
		for_each(dist.begin(),dist.end(),[&](uint d){
			if (d < smallest && visited[k] == false) {i = k; smallest = d;}
			k++;	
		});

		for (auto j: G.adj[i]) {
			uint alt = dist[i] + G.getEdgeWeight(i,j);
			if(dist[j] > alt) {
				dist[j] = alt;
				prev[j] = i;
			}
		}
		visited[i] = true;		
	}
	
	return dist;
}
