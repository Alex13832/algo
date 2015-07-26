//BFS implemented using a queue
#include "../data_structures/graph.h"
#include <list>
using namespace std;

vector<int> BFS(Graph G, int s){
	vector<bool> visited(G.size(),false);
	list<int> q;
	vector<int> res;
	visited[s] = true;
	q.push_back(s);

	while(!q.empty()) {
		s = q.front();
		res.push_back(s);
		q.pop_front();

		for (auto i = G.adj[s].begin(); i != G.adj[s].end(); ++i) {
			if(!visited[*i]) {
				visited[*i] = true;
				q.push_back(*i);
			}
		}			
	}
	
	return res;
}
