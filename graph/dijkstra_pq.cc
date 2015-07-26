//An implementation of Dijktra's shortest path algorithm 
//using a priority queue.
#include "../data_structures/graph.h"
#include <queue>
using namespace std;

struct comp_dijkstra {
  bool operator() (const pair<uint,uint>& lhs, const pair<uint,uint>& rhs) const
  {return lhs.second>rhs.second;}
};

vector<uint> dijkstra_pq(Graph G, const int s) {
	priority_queue<pair<uint,uint>, vector<pair<uint,uint>>,comp_dijkstra> pq;
	vector<uint> dist(G.size(),UINT_MAX);
	vector<int> prev(G.size(),0);
	dist[s] = 0;
	pq.push(pair<uint,uint>(s,0));

	while (!pq.empty()) {
		pair<uint,uint> U = pq.top();
		pq.pop();
		uint u = U.first;
		
		for (auto v: G.adj[u]) {
			uint alt = dist[u] + G.getEdgeWeight(u,v);
			if (alt < dist[v]) {
				dist[v] = alt;
				prev[v] = u;	
				pq.push(pair<int,int>(v,alt));
			}
		}	
	}

	return dist;
}
