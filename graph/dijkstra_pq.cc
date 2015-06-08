//An implementation of Dijktra's shortest path algorithm 
//using a priority queue.
#include "graph.h"
#include <queue>
using namespace std;

struct comp_dijkstra {
  bool operator() (const pair<uint,uint>& lhs, const pair<uint,uint>& rhs) const
  {return lhs.second>rhs.second;}
};

vector<uint> Graph::dijkstra_pq(const int s) {
	priority_queue<pair<uint,uint>, vector<pair<uint,uint>>,comp_dijkstra> pq;
	vector<uint> dist(V,UINT_MAX);
	vector<int> prev(V,0);
	dist[s] = 0;
	pq.push(pair<uint,uint>(s,0));

	while (!pq.empty()) {
		pair<uint,uint> U = pq.top();
		pq.pop();
		uint u = U.first;
		
		for (auto v: adj[u]) {
			uint alt = dist[u] + getEdgeWeight(u,v);
			if (alt < dist[v]) {
				dist[v] = alt;
				prev[v] = u;	
				pq.push(pair<int,int>(v,alt));
			}
		}	
	}
	for (auto p: prev) {
		cout << p << " ";
	}

	return dist;
}
