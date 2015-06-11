#include "graph.h"
#include <algorithm>
using namespace std;

pair<vector<int>,bool> pathDFS(Graph G, int s, int t) {
	vector<bool> discovered(G.size(),false);
	vector<int> stack;
	stack.push_back(s);
	vector<int> prev(G.size(),0);

	while(!stack.empty() && s != t){
		int v = stack.back();
		stack.pop_back();

		if(!discovered[v]) {
			discovered[v] = true;

			for (auto i: G.adj[v]) {
				stack.push_back(i);
				prev[i] = v;
			}
		}	
	}	
	
	vector<int> path{t};
	int next = t;
	while (next != s) {
		next = prev[next];
		path.push_back(next);
	}

	reverse(path.begin(),path.end());
	bool ispath = true;

	if ((path.back()-path.front() > 1) && path.size() == 2) {
		ispath = false;
	}

	return pair<vector<int>,bool>(path,ispath);
}
