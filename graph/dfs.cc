//DFS implementation using a stack
#include <vector>
#include <iostream>
#include "graph.h"
using namespace std;

std::vector<int> Graph::DFS(int s) {
	vector<bool> discovered(V,false);
	vector<int> res;
	vector<int> stack;
	stack.push_back(s);

	while(!stack.empty()){
		int v = stack.back();
		res.push_back(v);
		stack.pop_back();

		if(!discovered[v]) {
			discovered[v] = true;

			for (auto i = adj[v].rbegin(); i != adj[v].rend(); ++i) {
				stack.push_back(*i);
			}
		}	
	}	

	return res;
}
