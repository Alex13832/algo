// New implementation of BFS!
// Instead of Graph data strucutre now the graph is a
// vector<vector<pair<int,int>>> structure
//
// Alexander Karlsson 2016-03-14

#include <vector>
#include <iostream>
#include <list>
#include <climits>
using namespace std;

/* Breadth first search algorithm */
vector<int> BFS(vector<vector<pair<int,int>>> G, int s){
	vector<int> distance(G.size(),INT_MAX);
    vector<int> parent(G.size(),-1);

    list<int> q;

    distance[s] = 0;
    q.push_back(s);


	while(!q.empty()) {

        int curr = q.front();
        q.pop_front();

        for (auto n: G[curr]) {
            if (distance[n.first] == INT_MAX) {
                distance[n.first] = distance[curr] + 1;
                parent[n.first] = curr;
                q.push_back(n.first);
            }
        }
	}

	return distance;
}
