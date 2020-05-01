/** ------------------------------------------------------------
 Implementation of the Floyd-Warshall algorithm. This
 implementation also supports path reconstruction.
 Alexander Karlsson, 2015-08-02
* -------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <climits>
#include "../data_structures/graph.cc"
using namespace std;

/* Floyd-Warshall algorithm */
void floyd_warshall(Graph G, vector<vector<int>>& dist, vector<vector<int>>& next)
{
	size_t V = G.size();

	/* Set all weights*/
	for (auto edge: G.ews) {
		int u = edge.first.first;
		int v = edge.first.second;
		int w = edge.second;

		dist[v][v] = 0;
		dist[u][v] = w;
		next[u][v] = v;
	}

	for (size_t k = 0; k < V; ++k) {
		for (size_t i = 0; i < V; ++i) {
			for (size_t j = 0; j < V; ++j) {
				/* Rearranged from pseudo, caused overflow. */
				if (dist[k][j] < dist[i][j]-dist[i][k]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}
}

/* Returns the distance matrix */
vector<vector<int>> floyd_warshall(Graph G)
{
	size_t V = G.size();
	vector<vector<int>> dist(V,vector<int>(V,INT_MAX)),
	next(V,vector<int>(V,-1));
	floyd_warshall(G, dist, next);

	return dist;
}

/* Returns the shortest path from u to v*/
vector<int> get_path(Graph G, int u, int v)
{
	size_t V = G.size();
	vector<vector<int>> dist(V,vector<int>(V,INT_MAX)),
	next(V,vector<int>(V,-1));

	floyd_warshall(G, dist, next);

	if (next[u][v] ==  -1) throw -1;

	vector<int> path{u};

	/* Search path */
	while (u != v) {
		u = next[u][v];
		path.push_back(u);
	}

	return path;
}
