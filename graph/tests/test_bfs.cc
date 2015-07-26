/* --------------------------------------------- 
* Very small test for bfs.cc
* Alexander Karlsson 2015-07-26
* ----------------------------------------------*/

#include "../graph.cc"
#include "../bfs.cc"

int main() {

	Graph G(8);
	
	G.addEdge(0,1);
	G.addEdge(0,2);
	G.addEdge(0,3);
	G.addEdge(1,4);
	G.addEdge(1,5);
	G.addEdge(4,6);
	G.addEdge(4,7);
	
	vector<int> res = BFS(G,0);
	
	for (auto r: res) {
		cout << r << " ";	
	}
	cout << endl;

}