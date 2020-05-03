///
/// \brief Header for graph algorithms.
/// \author alex011235
/// \date 2020-05-03
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
///

#include <vector>

#ifndef ALGO_ALGO_INCLUDE_ALGO_GRAPH_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_GRAPH_HPP_

namespace algo::graph {

struct Connection {
  int node, weight;
};

using Nodes = std::vector<int>;
using Weights = std::vector<int>;
using Graph = std::vector<std::vector<Connection>>;

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
bool MakeEdge(Graph &graph, const int &s, const int &t, const int &w);

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
bool MakeDirEdge(Graph &graph, const int &s, const int &t, const int &w);

/// \brief Adds a new directed edge from s to t.
/// \param graph The graph to change.
/// \param s Source.
/// \param t Destination.
/// \return Returns true if added, otherwise false.
bool MakeDirEdge(Graph &graph, const int &s, const int &t);

// //////////////////////////////////////////
//  Prim's
// //////////////////////////////////////////

/// \brief Returns the minimum spanning tree (MST) in the input graph from the node source.
/// \details This implementation is based on Prim's algorithm.
/// \param graph The graph.
/// \param source The source.
///
/// \return The nodes that constructs the MST.
/// \link <a href="https://en.wikipedia.org/wiki/Prim%27s_algorithm">Prim's algorithm, Wikipedia.</a>
Graph MinimumSpanningTree(const Graph &graph, const int &source, int &total_weight);

}// namespace algo::graph

#endif//ALGO_ALGO_INCLUDE_ALGO_GRAPH_HPP_
