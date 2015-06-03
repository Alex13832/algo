#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <list>

class Graph {
	int V;
	std::list<int> *adj;
public:
	Graph(int V);
	void addEdge(int u, int v);
	void BFS(int s);
};

#endif
