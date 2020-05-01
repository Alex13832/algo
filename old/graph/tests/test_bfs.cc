/* ----------------------------------------------------------------------------
 Very small test for bfs.cc
 Alexander Karlsson 2015-07-26
* --------------------------------------------------------------------------- */
#include "../bfs.cc"
#include "../graph.cpp"

int main()
{
	GraphLib::Graph_t G = GraphLib::new_graph(8);
	GraphLib::make_edge(G, 0, 1, 0);
	GraphLib::make_edge(G, 0, 2, 0);
	GraphLib::make_edge(G, 0, 3, 0);
	GraphLib::make_edge(G, 1, 4, 0);
	GraphLib::make_edge(G, 1, 5, 0);
	GraphLib::make_edge(G, 4, 6, 0);
	GraphLib::make_edge(G, 4, 7, 0);

	vector<int> res = BFS(G,0);

	for (auto r: res) {
		cout << r << " ";
	}
	cout << endl;

}
