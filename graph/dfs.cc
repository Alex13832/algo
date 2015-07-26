//DFS implementation using a stack
#include "../data_structures/graph.h"
using namespace std;

std::vector<int> DFS(Graph G, int s) {
	vector<bool> explored(G.size(),false);
	vector<int> res;
	vector<int> stack;
	stack.push_back(s);
	vector<int> prev(G.size(),0);

	while(!stack.empty()){
		int v = stack.back();
		res.push_back(v);
		stack.pop_back();

		if(!explored[v]) {
			explored[v] = true;

			for (auto i = G.adj[v].rbegin(); i != G.adj[v].rend(); ++i) {
				stack.push_back(*i);
				prev[*i] = v;
			}
		}	
	}	

	return res;
}
