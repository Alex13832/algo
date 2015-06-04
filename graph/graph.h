#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <list>
#include <vector>
#include <map>

class Graph {
	int V;
	std::list<int> *adj;
	std::map<std::pair<int,int>,int> ews; //Edge-Weights
public:
	Graph(int V);
	void addEdge(int u, int v);

	// Provides weighted graph implemenation
	// Use only if needed...
	void addEdgeWeight(int u, int v, int w); 

	std::vector<int> BFS(int s);
	std::vector<int> DFS(int s);
	std::map<std::pair<int,int>,int> getEdgeWeights();
};

#endif
