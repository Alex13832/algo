//DFS implementation using a stack
#include "../data_structures/graph.h"
#include <vector>
#include <stack>
using namespace std;


/* Ordinary DFS, all v in explored are default set to false*/
vector<int> DFS(Graph G, int s) {
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


/* Modified DFS, custom explored vector as input */
vector<int> DFS(Graph G, int n, vector<bool>& explored) {
	vector<int> res;
	stack<size_t> S;
	S.push(n);
	
	while(!S.empty()){
		int v = S.top();
		S.pop();
		res.push_back(v);
		cout << v << " - ";
		


		if (!explored[v]) {
			explored[v] = true;
			for (auto w: G.adj[v]) S.push(w);
		} 		
	}	

	return res;
}

void DFS(Graph G, int n, vector<bool>& explored, vector<int>& res) {

	explored[n] = true;
	
	for (auto w: G.adj[n]) {
		if (!explored[w]) DFS(G, w, explored, res);
	}

	res.push_back(n);
}
