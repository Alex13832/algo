//Dijkstra's algorithm implementation. 
#include "graph.h"
#include <queue>
#include <climits>
using namespace std;

int getSmallest(vector<uint>& dist, vector<bool> visited) {
	uint smallest = UINT_MAX;
	int smallIndex = 0;
	int index = 0;
	for(auto i: dist) {
		if (i < smallest && visited[index] == false) {
			smallest = i;
			smallIndex = index;
		}
		index++;
	}

	return smallIndex;
}

vector<uint> Graph::dijkstra(const int s) {
	vector<uint> dist(V,UINT_MAX);
	vector<uint> prev(V);
	vector<bool> visited(V,false);

	dist[s] = 0;

	while (find(visited.begin(),visited.end(),false) != visited.end()) {
		int i = getSmallest(dist,visited);

		for (auto j = adj[i].begin(); j != adj[i].end(); ++j) {

			if(dist[*j] > (dist[i] + getEdgeWeight(i,*j))) {
				dist[*j] = dist[i] + getEdgeWeight(i,*j);
				prev[*j] = i;
			}
		}

		visited[i] = true;		
	}
	
	return dist;
}
