#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

class Graph {
	int V;
public:	
	std::map<std::pair<int,int>,int> ews; //Edge-Weights
	Graph(int V);
	std::vector<int> *adj;	
	void addEdge(int u, int v); //undirected
	void addEdge(int u, int w, int v); //undirected
	void addDirEdge(int u, int v); //directed
	void addDirEdge(int u, int w, int v); //directed
	void removeEdge(int u, int v);
	std::size_t size() {return V;}
	std::vector<int> * getAdjacent() {return adj;}
	std::map<std::pair<int,int>,int> getEdgeWeights(){return ews;}
	int getEdgeWeight(int u, int v);
	void setEdgeWeight(int u, int w, int v);
};

#endif
