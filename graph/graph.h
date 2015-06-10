#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

class Graph {
	int V;
	std::vector<int> *adj;
	std::map<std::pair<int,int>,int> ews; //Edge-Weights
public:
	Graph(int V);
	void addEdge(int u, int v); //undirected
	void addEdge(int u, int w, int v); //undirected
	void addDirEdge(int u, int v); //directed
	void addDirEdge(int u, int w, int v); //directed
	void removeEdge(int u, int v);
	std::vector<int> * getAdjacent();
	std::vector<int> BFS(int s);
	std::vector<int> DFS(int s);
	std::vector<uint> dijkstra(int s);
	std::vector<uint> dijkstra_pq(int s);
	std::vector<int> bellman_ford(int s);
	std::vector<uint> prim(int s);	
	std::map<std::pair<int,int>,int> getEdgeWeights();
	int getEdgeWeight(int u, int v);
	
};

#endif
