#include "graph.h"
#include <cmath>
using namespace std;

Graph::Graph(int V){ 
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int u, int v){
	adj[u].push_back(v);
}

void Graph::addEdge(int u, int w, int v) {
	adj[u].push_back(v);
	pair<int,int> p1 = pair<int,int>(u,v);
	ews.insert(pair<pair<int,int>,int>(p1,w));

	adj[v].push_back(u);
	auto p2 = pair<int,int>(v,u);
	ews.insert(pair<pair<int,int>,int>(p2,w));	
}

void Graph::addDirEdge(int u, int v) {
	adj[u].push_back(v);	
}

void Graph::addDirEdge(int u, int w, int v) {
	adj[u].push_back(v);
	pair<int,int> p1 = pair<int,int>(u,v);
	ews.insert(pair<pair<int,int>,int>(p1,w));	
}

int Graph::getEdgeWeight(int u, int v) {
	auto p1 = pair<int,int>(u,v);
	return ews[p1];
}

void Graph::setEdgeWeight(int u, int w, int v) {
	auto p1 = pair<int,int>(u,v);
	ews[p1] = w;
}

void Graph::removeEdge(int u, int v) {
	auto itu = find(adj[u].begin(),adj[u].end(),v);
	if (itu != adj[u].end()) {
		adj[u].erase(itu);
	}
	
	auto itv = find(adj[v].begin(),adj[v].end(),u);
	if (itv != adj[v].end()) {
		adj[v].erase(itv);
	}

	ews.erase(pair<int,int>(u,v));
	ews.erase(pair<int,int>(v,u));

}

/* Flips all edges in G, returns that graph */
Graph transpose(Graph G) {
	Graph G2(G.size());
	size_t N = G.size();

	for (size_t i = 0; i < N; i++) {
		for (auto u: G.adj[i]) {
			G2.addDirEdge(u,i);
		}
	}
	return G2;
}