//BFS implemented using a queue
#include "graph.h"
using namespace std;

vector<int> BFS(Graph G, int s){
	vector<bool> visited(G.size(),false);
	vector<int> q;
	vector<int> res;
	visited[s] = true;
	q.push_back(s);

	while(!q.empty()) {
		s = q.front();
		res.push_back(s);
		q.erase(q.begin());

		for (auto i = G.adj[s].begin(); i != G.adj[s].end(); ++i) {
			if(!visited[*i]) {
				visited[*i] = true;
				q.push_back(*i);
			}
		}			
	}
	
	return res;
}
