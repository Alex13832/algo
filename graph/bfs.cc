#include <vector>
#include "graph.h"
using namespace std;

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
