#include "../graph/graph.h"
#include "../graph/dfs_path.cc"
#include <algorithm>
#include <climits>
using namespace std;

/** Finds the min of the residual path. */
int find_min(map<pair<int,int>,int> vec, vector<int> path) {
	int min = INT_MAX;

	for (size_t i = 0; i < path.size()-1; ++i) {
		int cand = vec[pair<int,int>(path[i],path[i+1])];
		if (cand < min) min = cand;
	}
	
	return min;
}

/* The FordFulkerson algorithim, computes the maximum flow from s to t in Gf.*/
int ford_fulkerson(Graph Gf, const int s, const int t) { 
	int max_flow = 0;
	bool is_path = true;

	while (is_path) { 
		map<pair<int,int>,int> cf = Gf.getEdgeWeights();
		for (auto e: cf) {
			if(e.second <= 0) {
				Gf.removeEdge(e.first.first,e.first.second);
			}
		} 
	
		pair<vector<int>,bool> pv = pathDFS(Gf,s,t);
		is_path = pv.second;
		vector<int> path = pv.first;
		int cf_min = find_min(cf,path);

		for (size_t i = 0; i < path.size()-1; ++i) {
			int u = path[i];
			int v = path[i+1];
			Gf.setEdgeWeight(u,(Gf.getEdgeWeight(u,v)-cf_min),v);	
			Gf.setEdgeWeight(v,cf_min,u);	
		}
		max_flow += cf_min;
	}

	return max_flow;
}
