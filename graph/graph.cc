#include "graph.h"
using namespace std;

Graph::Graph(int V){ 
	this->V = V;
	adj = new vector<int>[V];
}

void Graph::addEdge(int u, int v){
	adj[u].push_back(v);
}

void Graph::addEdgeWeight(int u, int v, int w){
	auto p1 = pair<int,int>(u,v);
	ews.insert(pair<pair<int,int>,int>(p1,w));	
	//auto p2 = pair<int,int>(v,u);
	//ews.insert(pair<pair<int,int>,int>(p2,w));
}

map<pair<int,int>,int> Graph::getEdgeWeights() {
	return ews;
}

int Graph::getEdgeWeight(int u, int v) {
	auto p = pair<int,int>(u,v);
	return ews[p];
}


