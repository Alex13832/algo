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
/// 2022-12-17 Refactor to classes.
/// 2022-12-22 Remove nearest neighbour.
///

#include <cstddef>
#include <vector>

#ifndef ALGO_ALGO_INCLUDE_ALGO_GRAPH_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_GRAPH_HPP_

namespace algo::graph {

// - MARK: Structs, namespaces -

struct Edge {
  int u, v;
  double w;
};

struct Connection {
  int node;
  double weight;
};

using Nodes = std::vector<int>;

struct Path {
  Nodes nodes;
  bool is_path;
};

using Weights = std::vector<double>;
using Visited = std::vector<bool>;
using Edges = std::vector<Edge>;
using RawGraph = std::vector<std::vector<Connection>>;
using NodeMat = std::vector<Nodes>;
using WeightMat = std::vector<Weights>;

// - MARK: Classes -

class Graph {

 public:
  /// \brief Removes the edge between node u and node v.
  /// \param u Node.
  /// \param v Node.
  void RemoveEdge(size_t u, size_t v);

  /// \brief Returns all edges in the graph.
  /// \return Edges.
  Edges GetEdges() const;

  /// \brief Returns the size of graph..
  /// \return Size of graph.
  size_t Size() const;

  /// \brief Returns the raw data structure.
  /// \return A vector<vector<Connection>>.
  RawGraph GetRaw() const;

 protected:
  explicit Graph(size_t size);

  const std::vector<Connection> &At(size_t n) const;

  /// \brief Checks that u and v are not outside any size.
  /// \param u Node.
  /// \param v Node.
  /// \return true if valid.
  bool ValidBounds(size_t u, size_t v) const;

  /// \brief Connects an edge between node u and v.
  /// \param u Node.
  /// \param v Node.
  /// \param weight Weight, use 0.0 if unweighted.
  void ConnectNodes(size_t u, size_t v, double weight);

  /// \brief Updates the weight for the edge(u,v).
  /// \param u Node.
  /// \param v Node.
  /// \param weight New weight.
  void UpdateWeight(size_t u, size_t v, double weight);

  /// \brief Runs Breadth-First-Search on the input graph from the source node.
  /// \param graph Input graph.
  /// \param source Source node.
  /// \return The nodes in the BFS result from source.
  virtual Nodes BFS(size_t source) const;

  /// \brief Returns the shortest path from source to dest. The path length
  /// is measured by number of edges.
  /// \param source The source node.
  /// \param dest The destination node.
  /// \return The path from source to dest, and if it is a path.
  virtual Path ShortestPathBFS(size_t source, size_t dest) const;

  /// \brief Returns the shortest path from source to dest, only allowing
  /// positive edge weights. If there are negative edge weights, then use
  /// ShortestPathBellmanFord.
  /// \param source Source node.
  /// \param dest Destination node.
  /// \return Shortest path from source to dest.
  virtual Nodes ShortestPathDijkstra(size_t source, size_t dest) const;

  bool directed_{false};

 private:
  /// \brief Pops (removes) an edge. Helper function with access to graph_.
  /// \param u Node.
  /// \param v Node.
  void PopEdge(size_t u, size_t v);
  /// \brief Computes the shortest path from all nodes back to source.
  /// \param source The source node.
  /// \return The nodes  for all the shortest path from any node to source.
  Nodes ShortestPathDijkstra(size_t source) const;

  std::vector<std::vector<Connection>> graph_;
  size_t size_;
};

class UndirectedGraph : public Graph {

 public:
  explicit UndirectedGraph(size_t size) : Graph(size)
  {
    directed_ = false;
  };

  /// \brief Inserts two edges (undirected) to the graph between nodes u and v.
  /// \param u Node.
  /// \param v Node.
  void InsertEdge(size_t u, size_t v);

  Nodes BFS(size_t source) const override;

  Path ShortestPathBFS(size_t source, size_t dest) const override;

  /// \brief Checks if the graph is bipartite.
  /// \details A graph is bipartite if the nodes can be divided in two sets
  /// where no edge is connected to a node in the same set.
  /// \return true if bipartite.
  bool IsBipartite() const;
};

class DirectedGraph : public Graph {

 public:
  explicit DirectedGraph(size_t size) : Graph(size)
  {
    directed_ = true;
  };

  /// \brief Inserts one edge (directed) between nodes u and v.
  /// \param u Node.
  /// \param v Node.
  void InsertEdge(size_t u, size_t v);

  Nodes BFS(size_t source) const override;

  Path ShortestPathBFS(size_t source, size_t dest) const override;

  /// \brief Returns a list of the strongly connected components.
  /// \details This function follows the Kosaraju algorithm.
  /// \return A list of connected components, each item is a list of nodes.
  NodeMat StronglyConnectedComponentsKosaraju() const;

 private:
  /// \brief Returns a new graph with all edges pointing in the opposite
  // direction.
  /// \return Reversed graph.
  DirectedGraph Reverse() const;

  /// \brief Visits each node in each node for all connections at n.
  /// \param n Node n.
  /// \param visited Reference to nodes marked as visited.
  /// \param res Visited nodes.
  void Visit(size_t n, Visited &visited, Nodes &res) const;

  /// \brief Visits all nodes.
  /// \return Nodes and visited.
  std::pair<Nodes, Visited> VisitAll() const;
};

class UndirectedWeightedGraph : public Graph {

 public:
  explicit UndirectedWeightedGraph(size_t size) : Graph(size)
  {
    directed_ = false;
  };

  /// \brief Inserts an undirected edge with weight between u and v.
  /// \param u Node.
  /// \param v Node.
  /// \param weight Edge weight.
  void InsertEdge(size_t u, size_t v, double weight);

  /// \brief Sets the weight for edge(u,v).
  /// \param u Node.
  /// \param v Node.
  /// \param weight Weight.
  void SetWeight(size_t u, size_t v, double weight);

  /// \brief Returns the edge weight for edge(u,v).
  /// \param u Node.
  /// \param v Node.
  /// \return Weight.
  double GetWeight(size_t u, size_t v) const;

  /// \brief Checks if all edge weights are positive.
  /// \return True if all edge weights are positive.
  bool AllWeightsPositive() const;

  /// \brief Returns minimum spanning tree (MST) from source.
  /// \details This implementation is based on Prim's algorithm.
  /// \param total_weight Resulting total weight of the MST.
  /// \return The MST:
  UndirectedWeightedGraph MinSpanningTreePrim(double &total_weight) const;

  Nodes ShortestPathDijkstra(size_t source, size_t dest) const override;
};

class DirectedWeightedGraph : public Graph {
 public:
  explicit DirectedWeightedGraph(size_t size) : Graph(size)
  {
    directed_ = true;
  };

  /// \brief Inserts and edge between u and v with weight.
  /// \param u Node.
  /// \param v Node.
  /// \param weight Weight.
  void InsertEdge(size_t u, size_t v, double weight);

  /// \brief Sets the weight for edge(u,v).
  /// \param u Node.
  /// \param v Node.
  /// \param weight Weight.
  void SetWeight(size_t u, size_t v, double weight);

  /// \brief Returns the weight for edge(e,v).
  /// \param u Node.
  /// \param v Node.
  /// \return Weight.
  double GetWeight(size_t u, size_t v) const;

  /// \brief Checks if all edge weights are positive.
  /// \return True if all edge weights are positive.
  bool AllWeightsPositive() const;

  Nodes ShortestPathDijkstra(size_t source, size_t dest) const override;

  /// \brief Returns the shortest path between the source and all other nodes
  /// in the graph. Negative weights are allowed. If only positive, use
  /// ShortestPathDijkstra, which is faster.
  /// \param source The source node.
  /// \return Shortest path from source to all other nodes.
  std::pair<Weights, Nodes> ShortestPathBellmanFord(size_t source) const;

  /// \brief Returns the shortest path from source to dest in the graph.
  /// Negative weights are allowed. If only positive weights, use
  /// ShortestPathDijkstra, which is faster.
  /// \param source Source node.
  /// \param dest Destination node.
  /// \return The path and the total weight.
  std::pair<Nodes, double> ShortestPathSinglePathBellmanFord(size_t source,
                                                             size_t dest) const;

  /// \brief Finds the shortest path between all the nodes in graph. Negative
  /// and positive weights are allowed. No negative cycles.
  /// \return A matrix, where each entry (for each node) is the path to all other nodes.
  NodeMat ShortestDistAllPairsFloydWarshall() const;

  /// \brief Returns the shortest path from source to dest.
  /// \param source Source node.
  /// \param dest Destination node.
  /// \return Shortest path from source to dest.
  Nodes ShortestDistAllPairsPathFloydWarshall(size_t source, size_t dest) const;

  /// \brief Computes the maximum flow from source to destination.
  /// \details This algorithm is also called Ford-Fulkerson, but since this
  /// implementation uses BFS for finding paths, it's an Edmonds-Karp
  /// implementation.
  /// \param source Then source node.
  /// \param dest The destination node.
  /// \return Maximum flow.
  double MaxFlowEdmondsKarp(size_t source, size_t dest);
};

}// namespace algo::graph

#endif//ALGO_ALGO_INCLUDE_ALGO_GRAPH_HPP_
