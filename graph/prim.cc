//Implementation of Prim's Algorithm
//The output is a minimum spanning tree (MST)
#include <climits>
#include <queue>
#include <numeric>
#include "../data_structures/graph.h"
using namespace std;

struct comp {
  bool operator() (const pair<uint,uint>& lhs, const pair<uint,uint>& rhs) const
  {return lhs.second>rhs.second;}
};

vector<uint> prims(vector<vector<pair<int,int>>> G, int s)
{
	vector<uint> weight(G.size(),UINT_MAX);
	vector<uint> parent(G.size());
	vector<uint> visited(G.size(),false);
	priority_queue<pair<uint,uint>, vector<pair<uint,uint>>,comp> pq;
	pq.push(pair<uint,uint>(s,0));
	weight[s] = 0;

	while (!pq.empty()) {
		pair<uint,uint> U = pq.top();
		pq.pop();
		uint u = U.first;

		for (auto v: G[u]) {
			if(!visited[v.first] && (uint) v.second < weight[v.first]) {
				parent[v.first] = u;
				weight[v.first] = v.second;
				pq.push(v);
			}
		}

		visited[u] = true;
	}

	return weight;
}
