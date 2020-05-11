///
/// \brief Header for graph algorithms.
/// \author alex011235
/// \date 2020-05-03
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2016-03-14 Dijkstra shortest path.
/// 2016-09-24 Nearest neighbor for travelling salesman approximation.
/// 2016-09-25 Prim's algorithm for minimum spanning trees.
///

#include <map>
#include <set>
#include <vector>

#ifndef ALGO_ALGO_INCLUDE_ALGO_GRAPH_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_GRAPH_HPP_

namespace algo::graph {

struct Connection {
  int node;
  double weight;
};

struct Edge {
  int u, v;
  double w;
};

using Nodes = std::vector<int>;
using Weights = std::vector<double>;
using Graph = std::vector<std::vector<Connection>>;
using Visited = std::vector<bool>;
using Edges = std::vector<Edge>;

// //////////////////////////////////////////
//  Graph functions
// //////////////////////////////////////////

/// \brief Returns a new graph.
/// \param size The number of nodes in the graph, zero-indexed!
/// \note The graph is zero-indexed, that is to keep to internal indices (in vectors) the same.
/// \return A new graph.
Graph NewGraph(size_t size);

/// \brief Adds a new edge from s to t with weight w.
/// \param graph The graph to change.
/// \param s Source.
/// \param t Destination.
/// \param w Weight.
/// \return Returns true if added, otherwise false.
bool MakeEdge(Graph &graph, const int &s, const int &t, const double &w);

/// \brief Adds a new edge from s to t.
/// \param graph The graph to change.
/// \param s Source.
/// \param t Destination.
/// \return Returns true if added, otherwise false.
bool MakeEdge(Graph &graph, const int &s, const int &t);

/// \brief Adds a new directed edge from s to t with weight w.
/// \param graph The graph to change.
/// \param s Source.
/// \param t Destination.
/// \param w Weight.
/// \return Returns true if added, otherwise false.
bool MakeDirEdge(Graph &graph, const int &s, const int &t, const double &w);

/// \brief Adds a new directed edge from s to t.
/// \param graph The graph to change.
/// \param s Source.
/// \param t Destination.
/// \return Returns true if added, otherwise false.
bool MakeDirEdge(Graph &graph, const int &s, const int &t);

// //////////////////////////////////////////
//  Nearest neighbor.
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
//  Prim's
// //////////////////////////////////////////

/// \brief Returns the minimum spanning tree (MST) in the input graph from the node source.
/// \details This implementation is based on Prim's algorithm.
/// \param graph The graph.
/// \param source The source.
/// \return The nodes that constructs the MST.
/// \link <a href="https://en.wikipedia.org/wiki/Prim%27s_algorithm">Prim's algorithm, Wikipedia.</a>
Graph MinimumSpanningTree(const Graph &graph, const int &source, double &total_weight);

// //////////////////////////////////////////
//  Dijkstra's
// //////////////////////////////////////////

/// \brief Returns the shortest path between the source and destination in the input graph.
/// \details This implementation is based on Dijkstra's algorithm for shortest path.
/// \param graph The input graph.
/// \param source The source node.
/// \param dest The destination node.
/// \return The nodes constructing the shortest path.
/// \link <a href="https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm">Dijkstra's algorithm, Wikipedia.</a>
Nodes ShortestPath(const Graph &graph, const int &source, const int &dest);

// //////////////////////////////////////////
//  Bellman-Ford
// //////////////////////////////////////////

/// \brief Returns the shortest path between source and all other nodes in the input graph.
/// \note Use ShortestPath if all edge weights are positive, since (Dijkstra's) algorithm is faster.
/// \param graph The input graph.
/// \param source Source node.
/// \return A list of nodes prev = nodes[prev], for tracking each path to source. And weights.
/// \link <a href="https://en.wikipedia.org/wiki/Bellman–Ford_algorithm">Bellman-Ford, Wikipedia.</a>
std::pair<Weights, Nodes> ShortestPathBF(const Graph &graph, const int &source);

/// \brief Returns the shortest oath between the source and destination (dest) in the input graph.
/// \details This algorithm uses the Bellman-Ford algorihtm whích allows negative edge weights. Use ShortestPath
/// if all edege weights are positive (faster).
/// \param graph The input graph.
/// \param source Source node.
/// \param dest Destination node.
/// \return The nodes constructing the path from source to dest.
std::pair<Nodes, double> ShortestPathBF(const Graph &graph, const int &source, const int &dest);

}// namespace algo::graph

#endif//ALGO_ALGO_INCLUDE_ALGO_GRAPH_HPP_
