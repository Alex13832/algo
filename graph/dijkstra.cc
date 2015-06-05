//Dijkstra's algorithm implementation. 
#include "graph.h"
#include <queue>
#include <climits>
using namespace std;

// -1 infinity
// -2 undefined

bool mySort(pair<int,int> i, pair<int,int> j) {
	return i.second < j.second;
}



void Graph::dijkstra(int s) {
	vector<int> dist(V,0);
	vector<int> prev(V,0);
	vector<pair<int,int>> q;


	for(size_t i = 0; i < sizeof(adj); i++) {
		if ( i != s ) {
			dist[i] = INT_MAX;
			prev[i] = -2;	
		}

		q.push_back(pair<int,int>(i,dist[i]));
	}

	sort(q.begin(),q.end(),mySort);

	while (!q.empty()) {
		pair<int,int> p = q[0];
		q.erase(q.begin());
		int u = p.first;

		for (auto v = adj[u].begin(); v != adj[u].end(); ++v) {
			int alt = dist[u] + getEdgeWeight(u,*v);
			
			if (alt < dist[*v]) {
				dist[*v] = alt;
				prev[*v] = u;

				for(auto p2: q) {
					if (p2.first == v) {
						cout << p2.first << endl;
					}
				}
				
			}	

		}
			
		sort(q.begin(),q.end(),mySort);

	}


	
			


}
