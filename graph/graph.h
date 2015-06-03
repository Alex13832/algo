#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <list>
#include <vector>

class Graph {
	int V;
	std::list<int> *adj;
public:
	Graph(int V);
	void addEdge(int u, int v);
	std::vector<int> BFS(int s);
	std::vector<int> DFS(int s);
};

#endif
