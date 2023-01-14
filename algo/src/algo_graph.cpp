///
/// \brief Source file for graph algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_graph.hpp"

#include <algorithm>
#include <numeric>
#include <queue>

namespace algo::graph {

namespace {
struct comp {
  bool operator()(const Connection &lhs, Connection &rhs) const
  {
    return lhs.weight > rhs.weight;
  }
};
}//namespace

// //////////////////////////////////////////
// - MARK: Graph -

// public

void Graph::RemoveEdge(size_t u, size_t v)
{
  if (ValidBounds(u, v)) PopEdge(u, v);
  if (!directed_ && ValidBounds(v, u)) PopEdge(v, u);
}

Edges Graph::GetEdges() const
{
  Edges edges;

  // Construct a list of edges
  for (size_t i = 0; i < Size(); ++i) {
    for (const auto &c : At(i)) {
      edges.emplace_back(Edge{static_cast<int>(i), c.node, c.weight});
    }
  }
  return edges;
}

size_t Graph::Size() const
{
  return size_;
}

RawGraph Graph::GetRaw() const
{
  return graph_;
}

// protected

Graph::Graph(size_t size)
{
  graph_ = std::vector<std::vector<Connection>>(size);
  size_ = size;
}

const std::vector<Connection> &Graph::At(size_t n) const
{
  return graph_.at(n);
}

bool Graph::ValidBounds(size_t u, size_t v) const
{
  return !(u >= Size() || v >= Size() || u == v);
}

void Graph::ConnectNodes(size_t u, size_t v, double weight)
{
  graph_.at(u).emplace_back(Connection{static_cast<int>(v), weight});
}

void Graph::UpdateWeight(size_t u, size_t v, double weight)
{
  auto &sub = graph_.at(u);
  auto it = std::find_if(sub.begin(), sub.end(), [v](auto conn) {
    return conn.node == static_cast<int>(v);
  });

  if (it != sub.end()) {
    it->weight = weight;
  }
}

// MARK: BFS

Nodes Graph::BFS(size_t source) const
{
  // Forbidden input.
  if (graph_.empty() || (source >= Size())) {
    return Nodes{};
  }

  std::vector<int> distance(Size(), std::numeric_limits<int>::max());
  Nodes parent(Size(), -1);
  std::queue<size_t> q;
  q.push(source);
  distance.at(source) = 0;

  while (!q.empty()) {
    auto curr = q.front();
    q.pop();

    for (const auto &n : At(curr)) {
      if (distance.at(n.node) == std::numeric_limits<int>::max()) {
        distance.at(n.node) = distance.at(curr) + 1;
        parent.at(n.node) = static_cast<int>(curr);
        q.push(n.node);
      }
    }
  }
  return parent;
}

// MARK: Shortest path BFS

Path Graph::ShortestPathBFS(size_t source, size_t dest) const
{
  if (Size() < 2 || dest > Size() || source > Size() || source == dest) {
    return Path{Nodes{}, false};
  }

  auto nodes = BFS(source);
  Nodes path;
  auto prev = dest;

  while (prev != source) {
    if (nodes.at(prev) == -1) {
      return Path{Nodes{}, false};
    }
    path.emplace_back(prev);
    prev = nodes.at(prev);
  }

  path.emplace_back(prev);
  std::reverse(path.begin(), path.end());
  return Path{path, true};
}

// MARK: Shortest path Dijkstra

Nodes Graph::ShortestPathDijkstra(size_t source, size_t dest) const
{
  // Forbidden input.
  if (dest > Size() || source > Size() || Size() < 2 || source == dest) {
    return Nodes{};
  }

  const auto nodes = ShortestPathDijkstra(source);// Private
  Nodes path;
  size_t prev{dest};

  while (prev != source) {
    path.emplace_back(prev);
    prev = nodes.at(prev);
  }

  path.emplace_back(source);
  std::reverse(path.begin(), path.end());
  return path;
}

// private

void Graph::PopEdge(size_t u, size_t v)
{
  auto &sub = graph_.at(u);
  auto it = std::find_if(sub.begin(), sub.end(), [v](auto conn) {
    return static_cast<size_t>(conn.node) == v;
  });
  sub.erase(it);
}

Nodes Graph::ShortestPathDijkstra(size_t source) const
{
  std::priority_queue<Connection, std::vector<Connection>, comp> pq;
  Weights dist(Size(), std::numeric_limits<double>::max());
  Nodes prev(Size(), 0);

  dist.at(source) = 0.0;
  pq.push(Connection{static_cast<int>(source), 0.0});

  while (!pq.empty()) {
    auto u = pq.top().node;
    pq.pop();

    for (const auto &v : At(u)) {
      auto alt = dist.at(u) + v.weight;

      if (alt < dist.at(v.node)) {
        dist.at(v.node) = alt;
        prev.at(v.node) = u;
        pq.push(Connection{v.node, alt});
      }
    }
  }

  return prev;
}

// //////////////////////////////////////////
// - MARK: UndirectedGraph -

void UndirectedGraph::InsertEdge(size_t u, size_t v)
{
  if (ValidBounds(u, v) && ValidBounds(v, u)) {
    ConnectNodes(u, v, 0.0);
    ConnectNodes(v, u, 0.0);
  }
}

Nodes UndirectedGraph::BFS(size_t source) const
{
  return Graph::BFS(source);
}

Path UndirectedGraph::ShortestPathBFS(size_t source, size_t dest) const
{
  return Graph::ShortestPathBFS(source, dest);
}

// MARK: IsBipartite

bool UndirectedGraph::IsBipartite() const
{
  if (Size() < 2) {
    return false;
  }

  std::vector<int> colors(Size(), -1);
  colors.front() = 1;

  std::queue<int> q;
  q.push(0);

  // BFS, modified for checking bipartiteness.
  while (!q.empty()) {
    auto curr = q.front();
    q.pop();

    for (const auto &edge : At(curr)) {

      if (colors.at(edge.node) == -1) {
        colors.at(edge.node) = 1 - colors.at(curr);
        q.push(edge.node);

        // Two adjacent nodes have the same color.
      } else if (colors.at(edge.node) == colors.at(curr)) {
        return false;
      }
    }
  }
  return true;
}

// //////////////////////////////////////////
// - MARK: DirectedGraph -

void DirectedGraph::InsertEdge(size_t u, size_t v)
{
  if (ValidBounds(u, v)) ConnectNodes(u, v, 0.0);
}

Nodes DirectedGraph::BFS(size_t source) const
{
  return Graph::BFS(source);
}

Path DirectedGraph::ShortestPathBFS(size_t source, size_t dest) const
{
  return Graph::ShortestPathBFS(source, dest);
}

namespace {

void EraseVisitedNodes(Nodes &nodes, Visited &visited,
                       const Nodes &visited_nodes)
{
  for (const auto &node : visited_nodes) {
    if (std::find(nodes.begin(), nodes.end(), node) != nodes.end()) {
      nodes.erase(remove(nodes.begin(), nodes.end(), node), nodes.end());
    }
    visited.at(node) = true;
  }
}

/// \brief Reverses all vectors of result using std::reverse.
/// \param result Reverse this.
void ReverseSubVectors(NodeMat &result)
{
  std::for_each(result.begin(), result.end(),
                [](auto &res) { std::reverse(res.begin(), res.end()); });
}

}// namespace

void DirectedGraph::Visit(size_t n, Visited &visited, Nodes &res) const
{
  visited.at(n) = true;

  auto it = std::find_if(At(n).begin(), At(n).end(),
                         [&](auto conn) { return !visited.at(conn.node); });

  while (it != At(n).end()) {
    Visit(it->node, visited, res);
    it++;
  }

  res.push_back(n);
}

std::pair<Nodes, Visited> DirectedGraph::VisitAll() const
{
  NodeMat result;
  Nodes nodes;
  Visited visited(Size(), false);

  // Add all nodes with DFS-order
  for (size_t i = 0; i < Size(); i++) {
    if (!visited.at(i)) {
      Visit(i, visited, nodes);
    }
  }
  return std::make_pair(nodes, visited);
}

DirectedGraph DirectedGraph::Reverse() const
{
  DirectedGraph dg{Size()};

  for (size_t i = 0; i < Size(); i++) {
    for (const auto &connection : At(i)) {
      dg.InsertEdge(connection.node, i);
    }
  }
  return dg;
}

NodeMat DirectedGraph::StronglyConnectedComponentsKosaraju() const
{
  if (Size() < 2) return NodeMat{};

  auto visited_all = VisitAll();// DFS step
  auto &nodes = visited_all.first;
  auto &marked_as_visited = visited_all.second;

  // Reverse all edges
  auto graph_reversed = Reverse();
  Visited visited_reversed(Size(), false);
  NodeMat result;

  while (!nodes.empty()) {
    auto &node = nodes.back();
    nodes.pop_back();

    // Is to put one SCC part of G in visited
    Nodes visited_nodes;
    graph_reversed.Visit(node, visited_reversed, visited_nodes);

    // Add SCC-part in result
    result.emplace_back(visited_nodes);
    EraseVisitedNodes(nodes, marked_as_visited, visited_nodes);
  }

  ReverseSubVectors(result);
  return result;
}

// //////////////////////////////////////////
// - MARK: UndirectedWeightedGraph -

void UndirectedWeightedGraph::InsertEdge(size_t u, size_t v, double weight)
{
  if (Graph::ValidBounds(u, v)) {
    Graph::ConnectNodes(u, v, weight);
    Graph::ConnectNodes(v, u, weight);
  }
}

void UndirectedWeightedGraph::SetWeight(size_t u, size_t v, double weight)
{
  if (ValidBounds(u, v)) {
    UpdateWeight(u, v, weight);
    UpdateWeight(v, u, weight);
  }
}

double UndirectedWeightedGraph::GetWeight(size_t u, size_t v) const
{
  const auto sub = At(u);

  auto it = std::find_if(sub.begin(), sub.end(), [v](auto conn) {
    return conn.node == static_cast<int>(v);
  });

  return it->weight;
}

bool UndirectedWeightedGraph::AllWeightsPositive() const
{
  const auto &edges = GetEdges();
  return std::all_of(edges.begin(), edges.end(),
                     [](auto edge) { return edge.w >= 0.0; });
}

// MARK: Minimum Spanning Tree

UndirectedWeightedGraph UndirectedWeightedGraph::MinSpanningTreePrim(
    double &total_weight) const
{
  if (Size() == 0 || !AllWeightsPositive()) {
    return UndirectedWeightedGraph{0};// Empty result.
  }

  Weights weights(Size(), std::numeric_limits<double>::max());
  Nodes parent(Size());
  Visited visited(Size(), false);
  std::priority_queue<Connection, std::vector<Connection>, comp> pq;

  pq.push(Connection{0, 0});
  weights.front() = 0;

  while (!pq.empty()) {
    auto U = pq.top();
    auto node = U.node;
    pq.pop();

    for (const auto &v : At(node)) {
      if (!visited.at(v.node) && v.weight < weights.at(v.node)) {
        parent.at(v.node) = node;
        weights.at(v.node) = v.weight;
        pq.push(v);
      }
    }
    visited.at(node) = true;
  }

  // Construct the MST
  auto index = parent.size() - 1;
  UndirectedWeightedGraph mst{Size()};

  std::for_each(parent.rbegin(), parent.rend(), [&](int n) {
    mst.InsertEdge(n, index, weights.at(index));
    index--;
  });

  total_weight = std::accumulate(weights.begin(), weights.end(), 0.0);
  return mst;
}

// MARK: Shortest path Dijkstra

Nodes UndirectedWeightedGraph::ShortestPathDijkstra(size_t source,
                                                    size_t dest) const
{
  return Graph::ShortestPathDijkstra(source, dest);
}

// //////////////////////////////////////////
// - MARK: DirectedWeightedGraph -

void DirectedWeightedGraph::InsertEdge(size_t u, size_t v, double weight)
{
  if (Graph::ValidBounds(u, v)) {
    Graph::ConnectNodes(u, v, weight);
  }
}

void DirectedWeightedGraph::SetWeight(size_t u, size_t v, double weight)
{
  if (ValidBounds(u, v)) {
    UpdateWeight(u, v, weight);
  }
}

double DirectedWeightedGraph::GetWeight(size_t u, size_t v) const
{
  const auto sub = At(u);

  auto it = std::find_if(sub.begin(), sub.end(), [v](auto conn) {
    return conn.node == static_cast<int>(v);
  });

  return it->weight;
}

bool DirectedWeightedGraph::AllWeightsPositive() const
{
  const auto &edges = GetEdges();
  return std::all_of(edges.begin(), edges.end(),
                     [](auto edge) { return edge.w >= 0.0; });
}

// MARK: ShortestPathDijkstra

Nodes DirectedWeightedGraph::ShortestPathDijkstra(size_t source,
                                                  size_t dest) const
{
  return Graph::ShortestPathDijkstra(source, dest);
}

/// MARK: ShortestPathBellmanFord

namespace {

bool HasNegativeWeightCycles(const Edges &edges, const Weights &weights)
{
  return std::any_of(edges.begin(), edges.end(), [weights](const auto &edge) {
    return weights.at(edge.u) + edge.w < weights.at(edge.v);
  });
}

}// namespace

std::pair<Weights, Nodes> DirectedWeightedGraph::ShortestPathBellmanFord(
    size_t source) const
{
  if (Size() < 3 || source >= Size()) {
    return std::make_pair(Weights{}, Nodes{});
  }

  Weights dist(Size(), std::numeric_limits<double>::max());
  Nodes prev(Size(), -1);
  auto edges = GetEdges();

  dist.at(source) = 0;// Distance to itself is zero

  for (size_t i = 1; i < dist.size(); i++) {
    Weights pre{dist};

    for (const auto &edge : edges) {
      auto &dist_at_u = dist.at(edge.u);
      auto &dist_at_v = dist.at(edge.v);
      auto &prev_at_v = prev.at(edge.v);

      if (dist_at_u + edge.w < dist_at_v) {
        dist_at_v = dist_at_u + edge.w;
        prev_at_v = edge.u;
      }
    }
    // Return earlier if no update
    if (std::equal(dist.begin(), dist.end(), pre.begin())) break;
  }

  if (HasNegativeWeightCycles(edges, dist))
    return std::make_pair(Weights{}, Nodes{});

  return std::make_pair(dist, prev);
}

std::pair<Nodes, double>
DirectedWeightedGraph::ShortestPathSinglePathBellmanFord(size_t source,
                                                         size_t dest) const
{
  if (source >= Size() || dest >= Size() || Size() < 3) {
    return std::make_pair(Nodes{}, 0.0);
  }

  auto weights_paths = ShortestPathBellmanFord(source);
  auto nodes = weights_paths.second;
  Nodes path;
  auto prev = dest;

  while (prev != source) {
    path.emplace_back(prev);
    prev = nodes.at(prev);
  }

  path.emplace_back(prev);
  std::reverse(path.begin(), path.end());
  return std::make_pair(path, weights_paths.first[dest]);
}

// - MARK: ShortestDistAllPairsFloydWarshall

namespace {

void ShortestDistAllPairsPriv(const Edges &edges, size_t V, WeightMat &dist,
                              NodeMat &next)
{
  // Set all weights
  for (auto edge : edges) {
    auto u = edge.u;
    auto v = edge.v;
    dist[v][v] = 0;
    dist[u][v] = edge.w;
    next[u][v] = v;
  }

  for (size_t k = 0; k < V; ++k) {
    for (size_t i = 0; i < V; ++i) {
      for (size_t j = 0; j < V; ++j) {
        // Rearranged from pseudo, caused overflow
        if (dist[k][j] < dist[i][j] - dist[i][k]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          next[i][j] = next[i][k];
        }
      }
    }
  }
}
}//namespace

NodeMat DirectedWeightedGraph::ShortestDistAllPairsFloydWarshall() const
{
  auto N = Size();
  WeightMat dist(N, Weights(N, std::numeric_limits<double>::max()));
  NodeMat next(N, Nodes(N, -1));

  ShortestDistAllPairsPriv(GetEdges(), N, dist, next);
  return next;
}

Nodes DirectedWeightedGraph::ShortestDistAllPairsPathFloydWarshall(
    size_t source, size_t dest) const
{
  if (Size() < 3 || source >= Size() || dest >= Size() || source == dest) {
    return Nodes{};
  }

  auto next = ShortestDistAllPairsFloydWarshall();

  if (next[source][dest] == -1) {
    return Nodes{};
  }

  Nodes path{static_cast<int>(source)};
  size_t uu = source;
  // Search path
  while (uu != dest) {
    uu = next[uu][dest];
    path.emplace_back(uu);
  }

  return path;
}

// - MARK: MaxFlow

namespace {

constexpr auto FindMinOfResiduals = [](const Edges &edges, const Nodes &path) {
  auto min = std::numeric_limits<double>::max();

  for (size_t i = 0; i < path.size() - 1; ++i) {
    for (const auto &edge : edges) {
      if (edge.u == path[i] && edge.v == path[i + 1] && edge.w < min) {
        min = edge.w;
      }
    }
  }
  return min;
};
}//namespace

double DirectedWeightedGraph::MaxFlowEdmondsKarp(size_t source, size_t dest)
{
  if (source >= Size() || dest >= Size() || source == dest) {
    return 0.0;
  }

  // Forbidden case.
  if (!ShortestPathBFS(source, dest).is_path) return 0.0;

  double max_flow{0.0};
  bool is_path{true};
  Nodes prev;

  while (is_path) {
    auto edges = GetEdges();

    for (const auto &edge : edges) {
      if (edge.w <= 0) RemoveEdge(edge.u, edge.v);

      if (!At(source).empty()) {
        auto pv = ShortestPathBFS(source, dest);
        Nodes path{pv.nodes};
        is_path = pv.is_path;

        if (is_path) {
          auto min_capacity = FindMinOfResiduals(GetEdges(), path);

          for (size_t i = 0; i < path.size() - 1; ++i) {
            // Get node in path
            auto u = path.at(i);
            auto v = path.at(i + 1);

            // Update weights
            SetWeight(u, v, GetWeight(u, v) - min_capacity);
            SetWeight(v, u, min_capacity);
          }
          max_flow += min_capacity;
        }
      }
    }
  }
  return max_flow;
}

}// namespace algo::graph
