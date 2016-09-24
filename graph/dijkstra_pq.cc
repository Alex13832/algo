// Updated implementation of Dijkstra's algorithm
// Is still using a priority queue.
// Graph structure: vector<vector<pair<int,int>>> adj
//
// Undirected graph:
//            adj[x].push_back(make_pair(y, weight));
//            adj[y].push_back(make_pair(x, weight));
//
// Alexander Karlsson 2016-03-14

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>
using namespace std;

#define UINT_MAX 4294967295U

struct comp_dijkstra {
  bool operator() (const pair<uint,uint>& lhs, const pair<uint,uint>& rhs) const
  {return lhs.second>rhs.second;}
};

vector<uint> dijkstra_pq(vector<vector<pair<int, int> >> G, const int s)
{
    priority_queue<pair<uint,uint>, vector<pair<uint,uint>>,comp_dijkstra> pq;
    
    vector<uint> dist(G.size(),UINT_MAX);
    vector<int> prev(G.size(),0);

	dist[s] = 0;
	pq.push(pair<uint,uint>(s,0));

	while (!pq.empty()) {
		pair<uint,uint> U = pq.top();
		pq.pop();
		uint u = U.first;

		for (auto v: G[u]) {
			uint alt = dist[u] + v.second;
			if (alt < dist[v.first]) {
				dist[v.first] = alt;
				prev[v.first] = u;
				pq.push(pair<int,int>(v.first,alt));
			}
		}
	}

	return dist;
}
