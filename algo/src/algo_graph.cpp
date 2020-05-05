///
/// \brief Source file for graph algorithms.
/// \author alex011235
/// \date 2020-05-03
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "algo_graph.hpp"

#include <numeric>
#include <queue>

namespace algo::graph {

namespace {
constexpr double kDblMin{2.2250738585072014e-308};
constexpr double kDblMax{1.79769e+308};
}// namespace

// //////////////////////////////////////////
//  Graph functions
// //////////////////////////////////////////

Graph NewGraph(size_t size)
{
  return Graph(size);
}

bool MakeEdge(Graph &graph, const int &s, const int &t, const double &w)
{
  if (s >= graph.size() || t >= graph.size() || s == t) {
    return false;
  }

  graph[s].emplace_back(Connection{t, w});
  graph[t].emplace_back(Connection{s, w});
  return true;
}

bool MakeEdge(Graph &graph, const int &s, const int &t)
{
  if (s >= graph.size() || t >= graph.size()) {
    return false;
  }
  graph[s].emplace_back(Connection{t, 0});
  graph[t].emplace_back(Connection{s, 0});
  return true;
}

bool MakeDirEdge(Graph &graph, const int &s, const int &t, const double &w)
{
  if (s >= graph.size() || t >= graph.size()) {
    return false;
  }
  graph[s].push_back(Connection{t, w});
  return true;
}

bool MakeDirEdge(Graph &graph, const int &s, const int &t)
{
  if (s >= graph.size() || t >= graph.size()) {
    return false;
  }
  graph[s].push_back(Connection{t, 0});
  return true;
}

// //////////////////////////////////////////
//  Prim's
// //////////////////////////////////////////
struct comp {
  bool operator()(const Connection &lhs, Connection &rhs) const
  {
    return lhs.weight > rhs.weight;
  }
};

Graph MinimumSpanningTree(const Graph &graph, const int &source, double &total_weight)
{
  if (source >= graph.size() || source < 0 || graph.empty()) {
    return Graph{NewGraph(0)};
  }

  Weights weights(graph.size(), kDblMax);
  Nodes parent(graph.size());
  Nodes visited(graph.size(), 0);
  std::priority_queue<Connection, std::vector<Connection>, comp> pq;

  pq.push(Connection{source, 0});
  weights[source] = 0;

  while (!pq.empty()) {
    Connection U{pq.top()};
    pq.pop();
    int node{U.node};

    for (auto v : graph.at(node)) {
      if (visited[v.node] == 0 && v.weight < weights[v.node]) {
        parent[v.node] = node;
        weights[v.node] = v.weight;
        pq.push(v);
      }
    }
    visited[node] = 1;
  }

  // Construct the MST
  size_t index{parent.size() - 1};
  Graph mst{NewGraph(parent.size())};

  std::for_each(parent.rbegin(), parent.rend(), [&mst, &index, weights](int n) {
    MakeEdge(mst, n, index, weights[index]);
    index--;
  });

  total_weight = std::accumulate(weights.begin(), weights.end(), 0.0);

  return mst;
}

}// namespace algo::graph