//Dijkstra's algorithm for finding the shortest path. 
// Alexander Karlsson, 2015
#include "graph.h"
#include <climits>
using namespace std;

vector<uint> Graph::dijkstra(const int s) {
	vector<uint> dist(V,UINT_MAX);
	vector<uint> prev(V);
	vector<bool> visited(V,false);
	dist[s] = 0;

	while (find(visited.begin(),visited.end(),false) != visited.end()) {
		uint smallest = UINT_MAX;
		int i = 0, k = 0;	
		for_each(dist.begin(),dist.end(),[&](uint d){
			if (d < smallest && visited[k] == false) {i = k; smallest = d;}
			k++;	
		});

		for (auto j: adj[i]) {
			uint alt = dist[i] + getEdgeWeight(i,j);
			if(dist[j] > alt) {
				dist[j] = alt;
				prev[j] = i;
			}
		}
		visited[i] = true;		
	}
	
	return dist;
}
