#include "graph.h"
#include <vector>
using namespace std;

Graph::Graph(int V){ 
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int u, int v){
	adj[u].push_back(v);
}

void Graph::BFS(int s){
	vector<bool> visited(V,false);
	vector<int> q;
	visited[s] = true;
	q.push_back(s);

	while(!q.empty()) {
		s = q.front();
		cout << s << " ";
		q.erase(q.begin());

		for (auto i = adj[s].begin(); i != adj[s].end(); ++i) {
			if(!visited[*i]) {
				visited[*i] = true;
				q.push_back(*i);
			}
		}			
	}
}


int main() {
	Graph g(7);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(2, 5);
	g.addEdge(2, 6);
	g.BFS(0);
	cout << endl;
 	
}	
