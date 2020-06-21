///
/// \brief Header for graph algorithms.
/// \author alex011235
/// \date 2020-05-03
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
/// Change list:
/// 2015-07-06 Edmonds-Karp max-flow.
/// 2015-08-01 Kosaraju strongly connected components.
/// 2016-03-14 Breadth-First-Sears (BFS).
/// 2016-03-14 Dijkstra shortest path.
/// 2016-09-24 Nearest neighbor travelling salesman approximation.
/// 2016-09-25 Prim's minimum spanning trees.
/// 2016-09-25 Floyd-Warshall Shortest path.
/// 2016-10-02 Bellman-Ford shortest path.
/// 2020-05-12 BFS shortest path.
/// 2020-05-13 IsBipartite
///

#include <vector>

#ifndef ALGO_ALGO_INCLUDE_ALGO_GRAPH_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_GRAPH_HPP_

namespace algo::graph {

// https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#p3-express-intent

using Nodes = std::vector<int>;
using Weights = std::vector<double>;
using Visited = std::vector<bool>;

struct Edge {
  int u, v;
  double w;
};

using Edges = std::vector<Edge>;

struct Connection {
  int node;
  double weight;
};

struct Path {
  Nodes nodes;
  bool is_path;
};

// Multi-dimensional
using Graph = std::vector<std::vector<Connection>>;
using NodeMat = std::vector<Nodes>;
using WeightMat = std::vector<Weights>;

// //////////////////////////////////////////
//  Graph functions
// //////////////////////////////////////////

/// \brief Returns a new graph.
/// \param size The number of nodes in the graph, zero-indexed!
/// \note The graph is zero-indexed, that is to keep to internal indices (in vectors) the same.
/// \return A new graph.
Graph NewGraph(size_t size);

/// \brief Adds a new edge from u to v with weight w.
/// \param graph The graph to change.
/// \param u Source.
/// \param v Destination.
/// \param w Weight.
/// \return Returns true if added, otherwise false.
bool MakeEdge(Graph &graph, const int &u, const int &v, const double &w);

/// \brief Adds a new edge from u to v.
/// \param graph The graph to change.
/// \param u Source.
/// \param v Destination.
/// \return Returns true if added, otherwise false.
bool MakeEdge(Graph &graph, const int &u, const int &v);

/// \brief Adds a new directed edge from u to v with weight w.
/// \param graph The graph to change.
/// \param u Source.
/// \param v Destination.
/// \param w Weight.
/// \return Returns true if added, otherwise false.
bool MakeDirEdge(Graph &graph, const int &u, const int &v, const double &w);

/// \brief Adds a new directed edge from u to v.
/// \param graph The graph to change.
/// \param u Source.
/// \param v Destination.
/// \return Returns true if added, otherwise false.
bool MakeDirEdge(Graph &graph, const int &u, const int &v);

/// \brief Updates the weight for the edge(u, v) = weight.
/// \param graph The input graph.
/// \param u Source node.
/// \param v Destination node.
/// \param weight New weight.
void SetWeight(Graph &graph, const int &u, const int &v, double weight);

/// \brief Gets the weight at edge(u, v).
/// \param graph The input graph.
/// \param u Source node.
/// \param v Destination node.
/// \return The weight at edge(u, v).
double GetWeight(Graph &graph, const int &u, const int &v);

/// \brief Returns the edges as a vector of the input graph.
/// \param graph The input graph.
/// \return A list of edges.
Edges GetEdges(const Graph &graph);

// //////////////////////////////////////////
//  Breadth-First-Search (BFS)
// //////////////////////////////////////////

/// \brief Runs Breadth-First-Search on the input graph from the source node.
/// \param graph Input graph.
/// \param source Source node.
/// \returnﬁ
Nodes BFS(const Graph &graph, const int &source);

/// \brief Returns the shortest path from source to dest in graph. The path length is measured by number of edges.
/// \param graph The input graph.
/// \param source The source node.
/// \param dest The destination node.
/// \return The path from source to dest, and if it is a path.
Path ShortestPathBFS(const Graph &graph, const int &source, const int &dest);

/// \brief Checs if the input graph is bipartite.
/// \param graph The input grpah.
/// \param src Source node.
/// \return True if bipartite, otherwise false.
/// \link <a href="https://en.wikipedia.org/wiki/Bipartite_graph#Testing_bipartiteness">Bipartite graph, Wikipedia.</a>
bool IsBipartite(const Graph &graph);

// //////////////////////////////////////////
//  Nearest neighbor, TSP
// //////////////////////////////////////////

/// \brief Returns a path through all nodes.
/// \details This is an approximation of the travelling salesman problem.
/// \note There's no guarantee that the returned path is the optimal. Also, small change to find a path at all.
/// \param graph The input graph.
/// \param source Starting node.
/// \return A path through all nodes.
/// \link <a href="https://en.wikipedia.org/wiki/Nearest_neighbour_algorithm">Nearest neighbor, Wikipedia.</a>
Nodes AllNodesPath(const Graph &graph, const int &source);

// //////////////////////////////////////////
//  Dijkstra's, shortest path
// //////////////////////////////////////////

/// \brief Returns the shortest path between the source and destination in the input graph.
/// \details This implementation is based on Dijkstra's algorithm for shortest path.
/// \param graph The input graph.
/// \param source The source node.
/// \param dest The destination node.
/// \return The nodes constructing the shortest path.
/// \link <a href="https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm">Dijkstra's algorithm, Wikipedia.</a>
Nodes ShortestPathDijkstra(const Graph &graph, const int &source, const int &dest);

// //////////////////////////////////////////
//  Bellman-Ford, shortest path
// //////////////////////////////////////////

/// \brief Returns the shortest path between source and all other nodes in the input graph.
/// \note Use ShortestPathDijkstra if all edge weights are positive, since (Dijkstra's) algorithm is faster.
/// \param graph The input graph.
/// \param source Source node.
/// \return A list of nodes prev = nodes[prev], for tracking each path to source. And weights.
/// \link <a href="https://en.wikipedia.org/wiki/Bellman–Ford_algorithm">Bellman-Ford, Wikipedia.</a>
std::pair<Weights, Nodes> ShortestPathBF(const Graph &graph, const int &source);

/// \brief Returns the shortest oath between the source and destination (dest) in the input graph.
/// \details This algorithm uses the Bellman-Ford algorithm which allows negative edge weights. Use ShortestPathDijkstra
/// if all edge weights are positive (faster).
/// \param graph The input graph.
/// \param source Source node.
/// \param dest Destination node.
/// \return The nodes constructing the path from source to dest.
std::pair<Nodes, double> ShortestPathBF(const Graph &graph, const int &source, const int &dest);

// //////////////////////////////////////////
//  Floyd-Warshall, all-pair shortest dist
// //////////////////////////////////////////

/// \brief Finds the shortest path between all the nodes in the input graph.
/// \details Implementation follows the Floyd-Warshall algorithm.
/// \param graph The input graph.
/// \return A matrix, where each entry (for each node) is the path to all other nodes.
/// \link <a href="https://en.wikipedia.org/wiki/Floyd–Warshall_algorithm">Floyd-Warshall, Wikipedia.</a>
NodeMat ShortestDistAllPairs(const Graph &graph);

/// \brief Returns the shortest path from source to dest in graph.
/// \param graph The input graph.
/// \param source Source node.
/// \param dest Destination node.
/// \return Shortest path from source to dest.
Nodes ShortestDistAllPairsPath(const Graph &graph, const int &source, const int &dest);

// //////////////////////////////////////////
//  Prim's, minimum spanning tree
// //////////////////////////////////////////

/// \brief Returns the minimum spanning tree (MST) in the input graph from the node source.
/// \details This implementation is based on Prim's algorithm.
/// \param graph The graph.
/// \param source The source.
/// \return The nodes that constructs the MST.
/// \link <a href="https://en.wikipedia.org/wiki/Prim%27s_algorithm">Prim's algorithm, Wikipedia.</a>
Graph MinSpanningTree(const Graph &graph, const int &source, double &total_weight);

// //////////////////////////////////////////
//  Ford-Fulkerson, maximum flow
// //////////////////////////////////////////

/// \brief Computes the maximum flow in the input graph from source to destination.
/// \details This implementation uses BFS for finding paths, which means that it's a Edmonds-Karp implementation.
/// \param graph The input graph.
/// \param source Then source node.
/// \param dest The destination node.
/// \return Maximum flow.
/// \link <a href="https://en.wikipedia.org/wiki/Ford–Fulkerson_algorithm">Ford-Fulkerson, Wikipedia.</a>
double MaxFlow(Graph graph, const int &source, const int &dest);

// //////////////////////////////////////////
//  Kosaraju, strongly connected components
// //////////////////////////////////////////

/// \brief Returns a list of the strongly connected components in graph.
/// \details This function follows the Kosaraju algorithm.
/// \param graph The input graph.
/// \return A list of connected components, each item is a list of nodes.
/// \link <a href="https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm">Kosaraju's algorithm, Wikipedia.</a>
/// \link <a href="https://en.wikipedia.org/wiki/Strongly_connected_component">Strongly connected component, Wikipedia.<a/>
NodeMat StrConnComponents(const Graph &graph);

}// namespace algo::graph

#endif//ALGO_ALGO_INCLUDE_ALGO_GRAPH_HPP_
