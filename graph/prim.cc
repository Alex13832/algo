//Implementation of Prim's Algorithm
//The output is a minimum spanning tree (MST)
#include <climits>
#include <queue>
#include "graph.h"
using namespace std;

struct comp {
  bool operator() (const pair<uint,uint>& lhs, const pair<uint,uint>& rhs) const
  {return lhs.second>rhs.second;}
};

vector<uint> Graph::prim(int s){
	vector<uint> weight(V,UINT_MAX);	
	vector<uint> parent(V);
	vector<uint> visited(V,false);
	priority_queue<pair<uint,uint>, vector<pair<uint,uint>>,comp> pq;
	pq.push(pair<uint,uint>(s,0));
	weight[s] = 0;

	while (!pq.empty()) {
		pair<uint,uint> U = pq.top();
		pq.pop();
		uint u = U.first;

		for (auto v: adj[u]) {
			if(!visited[v] && (uint) getEdgeWeight(u,v) < weight[v]) {
				parent[v] = u;
				weight[v] = getEdgeWeight(u,v);
				pq.push(pair<uint,uint>(v,weight[v]));
			}
		}

		visited[u] = true;
		
	}

	return weight;
}
