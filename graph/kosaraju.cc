/** ------------------------------------------------------------
* Implementation of the Kosaraju algorithm. It generates the
* strongly connected components (SCC) of a digraph.
* Alexander Karlsson, 2015-08-01
* -------------------------------------------------------------- */
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include "../data_structures/graph.cc"
using namespace std;

/* DFS-algorithms, slightly modifed */
void DFS(Graph G, int n, vector<bool>& explored, vector<int>& res) {
	explored[n] = true;
	
	for (auto w: G.adj[n]) {
		if (!explored[w]) DFS(G, w, explored, res);
	}
	res.push_back(n);
}


/* Kosaraju algorithm takes G, a directed graph, outputs 
 the strongly connected components of G */
vector<vector<int>> kosaraju(Graph G) {
	vector<vector<int>> result;
	vector<bool> explored(G.size(),false), explored2(G.size(),false);
	vector<int> S;

	/* Add all vertice with DFS-order */
	for (size_t i = 0; i < G.size(); i++) {
		if(!explored[i]) DFS(G, i, explored, S);
	}

	/* Reverse all edges */
	Graph G2 =  transpose(G);

	while (!S.empty()) {
		int v = S.back();
		S.pop_back();
		vector<int> visited;

		/* Is to put one SCC part of G in visited */
		DFS(G2, v, explored2, visited);
		/* Add SCC-part in result */
		result.push_back(visited);

		for (auto v: visited) {
			
			if (find(S.begin(), S.end(), v) != S.end()) {
				S.erase(remove(S.begin(), S.end(), v ), S.end() );
			}
			explored[v] = true;
		}
	}	

	return result;
}