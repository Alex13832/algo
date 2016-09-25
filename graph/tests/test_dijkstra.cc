/** ---------------------------------------------------------------------------
 Tests for Dijkstra's algorithm.
----------------------------------------------------------------------------- */
#include <vector>
#include "../dijkstra_pq.cc"
#include "../graph.cpp"

/* Test for dijkstra and dijkstra_pq*/
bool test_dijkstra()
{
	GraphLib::Graph_t G1 = GraphLib::new_graph(7);
	GraphLib::make_edge(G1, 0, 1, 5);
	GraphLib::make_edge(G1, 0, 2, 10);
	GraphLib::make_edge(G1, 2, 4, 2);
	GraphLib::make_edge(G1, 1, 4, 3);
	GraphLib::make_edge(G1, 1, 3, 6);
	GraphLib::make_edge(G1, 4, 3, 2);
	GraphLib::make_edge(G1, 3, 5, 6);
	GraphLib::make_edge(G1, 4, 6, 2);
	GraphLib::make_edge(G1, 6, 5, 2);

	vector<uint> dist = dijkstra_pq(G1, 0);
	int res1 = dist[5];
	bool a = res1 == 12;

	GraphLib::Graph_t G2 = GraphLib::new_graph(6);
	GraphLib::make_edge(G2, 0, 2, 2);
	GraphLib::make_edge(G2, 0, 1, 4);
	GraphLib::make_edge(G2, 1, 2, 1);
	GraphLib::make_edge(G2, 1, 3, 5);
	GraphLib::make_edge(G2, 2, 3, 8);
	GraphLib::make_edge(G2, 2, 4, 10);
	GraphLib::make_edge(G2, 4, 5, 3);
	GraphLib::make_edge(G2, 3, 4, 2);
	GraphLib::make_edge(G2, 3, 5, 6);

	vector<uint> dist2 = dijkstra_pq(G2,0);
	int res2 = dist2[5];
	bool b = res2 == 13;

	return a && b;
}

int main()
{
	if (test_dijkstra()) {
		cout << "dijkstra test case pass" << endl;
	} else {
		cout << "dijkstra test case fail" << endl;
	}
}
