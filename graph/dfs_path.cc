#include "graph.h"
#include <algorithm>
#include <climits>
using namespace std;

pair<vector<int>,bool> pathDFS(Graph G, int s, int t) {
	vector<bool> explored(G.size(),false);
	vector<int> stack;
	stack.push_back(s);
	vector<int> prev(G.size(),-1);
	int v = INT_MAX;

	while(!stack.empty() && v != t){
		v = stack.back();
		stack.pop_back();
		if(!explored[v]) {
			explored[v] = true;

			for (auto i: G.adj[v]) {
				stack.push_back(i);
				if (prev[i] == -1) prev[i] = v;
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
	if (path.front() != s || path.back() != t) ispath = false;

	if (find(path.begin(),path.end(),-1) != path.end()) ispath = false;

	if ((path.back()-path.front() > 1) && path.size() == 2) {
		ispath = false;
	}

	return pair<vector<int>,bool>(path,ispath);
}
