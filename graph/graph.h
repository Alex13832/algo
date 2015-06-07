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
	void addEdge(int u, int v);
	void addEdge(int u, int w, int v);
	std::vector<int> BFS(int s);
	std::vector<int> DFS(int s);
	std::vector<uint> dijkstra(int s);
	std::vector<uint> prim(int s);	
	std::map<std::pair<int,int>,int> getEdgeWeights();
	int getEdgeWeight(int u, int v);
	
};

#endif
