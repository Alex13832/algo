/** ---------------------------------------------------------------------------
 Test for travelling salesman's approximation algorithm.
 Alexander Karlsson 2016-09-24
----------------------------------------------------------------------------- */
#include <vector>
#include <iostream>
#include "../travelling_salesman.cc"

using namespace std;

int main(int argc, char const *argv[])
{
    // Graph
    GraphLib::Graph_t G = GraphLib::new_graph(5);
    GraphLib::make_edge(G, 0, 1, 70);
    GraphLib::make_edge(G, 0, 2, 35);
    GraphLib::make_edge(G, 0, 3, 40);
    GraphLib::make_edge(G, 0, 4, 60);
    GraphLib::make_edge(G, 1, 3, 40);
    GraphLib::make_edge(G, 1, 2, 25);
    GraphLib::make_edge(G, 1, 4, 50);
    GraphLib::make_edge(G, 2, 3, 10);
    GraphLib::make_edge(G, 2, 4, 12);
    GraphLib::make_edge(G, 3, 4, 15);

    // Start node (4) may have an impact on the total travelling distance.
    vector<int> path = nearest_neighbor(G, 5, 4);

    for (auto p: path)
        cout << p << endl;

    return 0;
}
