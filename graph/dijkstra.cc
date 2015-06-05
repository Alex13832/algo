//Dijkstra's algorithm implementation. 
#include "graph.h"
#include <queue>
#include <climits>
using namespace std;

pair<uint,uint> getSmallest(vector<pair<uint,uint>>& vec) {
	uint smallest = UINT_MAX;
	pair<uint,uint> p_small;
	int smallIndex = 0;
	int index = 0;
	for(auto i: vec) {
		if (i.second < smallest) {
			smallest = i.second;
			p_small = i;
			smallIndex = index;
		}
		index = 0;
	}
	
	vec.erase(vec.begin()+smallIndex);
	return p_small;
}

void Graph::dijkstra(const int s) {
	vector<uint> dist(V,UINT_MAX);
	dist[s] = 0;
	vector<uint> prev(V,0);
	vector<pair<uint,uint>> q;

	for(size_t i = 0; i < V; i++) {
		q.push_back(pair<uint,uint>(i,dist[i]));
	}
		

	while (!q.empty()) {
		pair<uint,uint> p = getSmallest(q);
		
		cout << p.first << endl;
		
		uint u = p.first;
				
		for (auto v = adj[u].begin(); v != adj[u].end(); ++v) {
			int alt = (dist[u] + getEdgeWeight(u,*v));				
								
			if (alt < dist[*v]) {
				dist[*v] = alt;
				prev[*v] = u;
				
				for (auto &node: q) {
					if (node.first == *v) {
						node.second = alt;
					}
				}
				
			}
				
		}
				
	}
	
	for (auto m: dist){
		cout << m << " ";
	}
	
	cout << endl;
	
	for (auto m: prev){
		cout << m << " ";
	}
	

}
