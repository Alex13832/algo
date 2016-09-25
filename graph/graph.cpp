/** ---------------------------------------------------------------------------
 Code for representing a graph.
 Alexander Karlsson 2016-09-25
----------------------------------------------------------------------------- */

namespace GraphLib {

using namespace std;

typedef vector<vector<pair<int,int>>> Graph_t;

/**
 Returns a new instance of a graph.
 @param[in] size, the number of nodes in the graph.
*/
Graph_t new_graph(int size)
{
    return Graph_t(size);
}

/**
 Make an undirected edge from s to t with edge weight w.
 @param[in/out] G, the actual graph to work on.
 @param[in] s, node 1.
 @param[in] t, node 2.
 @param[in] w, edge weight.
*/
void make_edge(Graph_t& G, int s, int t, int w)
{
    G[s].push_back(make_pair(t,w));
    G[t].push_back(make_pair(s,w));
}

/**
 Make an edge from s to t with edge weight t. Set t = 0 for no weight.
 @param[in/out] G, the actual graph.
 @param[in] s, starting node.
 @param[in] t, ending node.
 @param[in] w, edge weight.
*/
void make_dir_edge(Graph_t& G, int s, int t, int w)
{
    G[s].push_back(make_pair(t,w));
}

}
