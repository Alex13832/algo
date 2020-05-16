///
/// \brief Unit tests for graph algorithms.
/// \author alex011235
/// \date 2020-05-03
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>

#include "gtest/gtest.h"
#include "include/algo_graph.hpp"

using namespace std;
using namespace algo::graph;

namespace {
const std::string kFilePath{"../../test/testfiles/prims/"};
}

/////////////////////////////////////////////
/// Graph functions tests
/////////////////////////////////////////////

TEST(test_algo_graph, graph_make_edge_weight)
{
  Graph graph{NewGraph(2)};

  EXPECT_TRUE(MakeEdge(graph, 0, 1, 1));
  EXPECT_TRUE(MakeEdge(graph, 1, 0, 1));

  EXPECT_FALSE(MakeEdge(graph, 0, 0, 1));// Trying to add with same node ids.
  EXPECT_FALSE(MakeEdge(graph, 1, 1, 1));
  EXPECT_FALSE(MakeEdge(graph, 2, 1, 1));// Trying to add to a missing node.
  EXPECT_FALSE(MakeEdge(graph, 1, 2, 1));
}

TEST(test_algo_graph, graph_make_edge_no_weight)
{
  Graph graph{NewGraph(2)};

  EXPECT_TRUE(MakeEdge(graph, 0, 1));
  EXPECT_TRUE(MakeEdge(graph, 1, 0));
  EXPECT_TRUE(MakeEdge(graph, 0, 0));
  EXPECT_TRUE(MakeEdge(graph, 1, 1));

  EXPECT_FALSE(MakeEdge(graph, 2, 1));
  EXPECT_FALSE(MakeEdge(graph, 1, 2));
}

TEST(test_algo_graph, graph_make_dir_edge_weight)
{
  Graph graph{NewGraph(2)};
  EXPECT_TRUE(MakeDirEdge(graph, 0, 1, 1));
  EXPECT_TRUE(MakeDirEdge(graph, 1, 0, 1));
  EXPECT_TRUE(MakeDirEdge(graph, 0, 0, 1));
  EXPECT_TRUE(MakeDirEdge(graph, 1, 1, 1));

  EXPECT_FALSE(MakeDirEdge(graph, 2, 1, 1));
  EXPECT_FALSE(MakeDirEdge(graph, 1, 2, 1));
}

TEST(test_algo_graph, graph_make_dir_edge_no_weight)
{
  Graph graph{NewGraph(2)};

  EXPECT_TRUE(MakeDirEdge(graph, 0, 1));
  EXPECT_TRUE(MakeDirEdge(graph, 1, 0));
  EXPECT_TRUE(MakeDirEdge(graph, 0, 0));
  EXPECT_TRUE(MakeDirEdge(graph, 1, 1));

  EXPECT_FALSE(MakeDirEdge(graph, 2, 1));
  EXPECT_FALSE(MakeDirEdge(graph, 1, 2));
}

TEST(test_algo_graph, graph_get_weight)
{
  Graph graph{NewGraph(2)};
  EXPECT_EQ(GetWeight(graph, -1, 1), 0.0);// source < 0
  EXPECT_EQ(GetWeight(graph, 2, 1), 0.0); // source >= size

  graph = NewGraph(3);
  MakeEdge(graph, 0, 1, 1);
  EXPECT_EQ(GetWeight(graph, 0, 2), 0.0);// Missing edge
}

/////////////////////////////////////////////
/// Prim's tests
/////////////////////////////////////////////

TEST(test_algo_graph, prims_forbidden)
{
  Graph G1{NewGraph(7)};
  double total_weight{0.0};
  EXPECT_TRUE(MinSpanningTree(G1, 7, total_weight).empty());

  EXPECT_TRUE(MinSpanningTree(G1, -1, total_weight).empty());

  Graph G2{NewGraph(0)};
  EXPECT_TRUE(MinSpanningTree(G2, 0, total_weight).empty());
}

TEST(test_algo_graph, prims_simple)
{
  Graph G{NewGraph(7)};

  MakeEdge(G, 0, 1, 16);
  MakeEdge(G, 0, 3, 21);
  MakeEdge(G, 0, 2, 12);
  MakeEdge(G, 1, 4, 20);
  MakeEdge(G, 1, 3, 17);
  MakeEdge(G, 2, 3, 28);
  MakeEdge(G, 3, 4, 18);
  MakeEdge(G, 3, 6, 23);
  MakeEdge(G, 3, 5, 19);
  MakeEdge(G, 3, 5, 31);
  MakeEdge(G, 4, 6, 11);
  MakeEdge(G, 5, 6, 27);

  double total_weight{0.0};
  Graph gmst{MinSpanningTree(G, 0, total_weight)};

  EXPECT_EQ(total_weight, 93);
}

//Test-case file is downloaded from "Project Euler", problem 107
Graph ReadPrimsFile()
{
  Graph G{NewGraph(40)};
  vector<int> total;
  ifstream infile(kFilePath + "p107_network.txt");
  string line;
  int row = 0;
  int col = 0;

  while (getline(infile, line)) {
    string s = line;
    string delimiter = ",";

    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
      token = s.substr(0, pos);

      try {
        int weight = stoi(token);
        total.push_back(weight);
        MakeEdge(G, col, row, weight);
      } catch (std::invalid_argument&) {
      }

      s.erase(0, pos + delimiter.length());
      col++;
    }

    try {
      int weight = stoi(s);
      total.push_back(weight);
      MakeEdge(G, col, row, weight);
    } catch (std::invalid_argument&) {
    }

    row++;
    col = 0;
  }
  return G;
}

TEST(test_algo_graph, prims_project_euler_107)
{
  Graph G{ReadPrimsFile()};
  double total_weight{0.0};
  Graph gmst{MinSpanningTree(G, 0, total_weight)};

  double ans = 261832.0 - total_weight;

  EXPECT_EQ(ans, 259679.0);
}

/////////////////////////////////////////////
/// Dijkstra's tests
/////////////////////////////////////////////

TEST(test_algo_graph, dijkstra_simple1)
{
  Graph graph{NewGraph(7)};
  MakeEdge(graph, 0, 1, 5.0);
  MakeEdge(graph, 0, 2, 10.0);
  MakeEdge(graph, 2, 4, 2.0);
  MakeEdge(graph, 1, 4, 3.0);
  MakeEdge(graph, 1, 3, 6.0);
  MakeEdge(graph, 4, 3, 2.0);
  MakeEdge(graph, 3, 5, 6.0);
  MakeEdge(graph, 4, 6, 2.0);
  MakeEdge(graph, 6, 5, 2.0);

  Nodes correct{0, 1, 4, 6};
  Nodes nodes{ShortestPathDijkstra(graph, 0, 6)};
  EXPECT_TRUE(equal(nodes.begin(), nodes.end(), correct.begin()));

  Nodes correct1{4, 6, 5};
  Nodes nodes1{ShortestPathDijkstra(graph, 4, 5)};
  EXPECT_TRUE(equal(nodes1.begin(), nodes1.end(), correct1.begin()));
}

TEST(test_algo_graph, dijkstra_simple2)
{
  Graph graph{NewGraph(6)};
  MakeEdge(graph, 0, 2, 2.0);
  MakeEdge(graph, 0, 1, 4.0);
  MakeEdge(graph, 1, 2, 1.0);
  MakeEdge(graph, 1, 3, 5.0);
  MakeEdge(graph, 2, 3, 8.0);
  MakeEdge(graph, 2, 4, 10.0);
  MakeEdge(graph, 4, 5, 3.0);
  MakeEdge(graph, 3, 4, 2.0);
  MakeEdge(graph, 3, 5, 6.0);

  Nodes correct{0, 2, 1, 3, 4, 5};
  Nodes nodes{ShortestPathDijkstra(graph, 0, 5)};
  EXPECT_TRUE(equal(nodes.begin(), nodes.end(), correct.begin()));

  reverse(correct.begin(), correct.end());
  Nodes nodes1{ShortestPathDijkstra(graph, 5, 0)};
  EXPECT_TRUE(equal(nodes1.begin(), nodes1.end(), correct.begin()));
}

TEST(test_algo_graph, dijkstra_forbidden)
{
  Graph graph{NewGraph(1)};
  EXPECT_TRUE(ShortestPathDijkstra(graph, 0, 1).empty());// Size < 2
  Graph graph1{NewGraph(2)};
  EXPECT_TRUE(ShortestPathDijkstra(graph1, 0, 3).empty()); // Dest > size
  EXPECT_TRUE(ShortestPathDijkstra(graph1, 3, 2).empty()); // Source > size
  EXPECT_TRUE(ShortestPathDijkstra(graph1, -1, 1).empty());// Source < 0
  EXPECT_TRUE(ShortestPathDijkstra(graph1, 0, -1).empty());// Dest < 0
  EXPECT_TRUE(ShortestPathDijkstra(graph1, 1, 1).empty()); // Source == dest
}

/////////////////////////////////////////////
/// Nearest neighbor tests
/////////////////////////////////////////////

TEST(test_algo_graph, nn_simple1)
{
  Graph graph{NewGraph(5)};
  MakeEdge(graph, 0, 1, 70.0);
  MakeEdge(graph, 0, 2, 35.0);
  MakeEdge(graph, 0, 3, 40.0);
  MakeEdge(graph, 0, 4, 60.0);
  MakeEdge(graph, 1, 3, 40.0);
  MakeEdge(graph, 1, 2, 25.0);
  MakeEdge(graph, 1, 4, 50.0);
  MakeEdge(graph, 2, 3, 10.0);
  MakeEdge(graph, 2, 4, 12.0);
  MakeEdge(graph, 3, 4, 15.0);

  Nodes nodes{AllNodesPath(graph, 4)};
  EXPECT_EQ(nodes.size(), graph.size());
}

TEST(test_algo_graph, nn_empty_in)
{
  Graph graph{NewGraph(0)};
  Nodes nodes{AllNodesPath(graph, 0)};
  EXPECT_TRUE(nodes.empty());
}

TEST(test_algo_graph, nn_negative_source)
{
  Graph graph{NewGraph(2)};
  Nodes nodes{AllNodesPath(graph, -1)};
  EXPECT_TRUE(nodes.empty());
}

TEST(test_algo_graph, nn_source_larger_than_nbr_node)
{
  Graph graph{NewGraph(2)};
  Nodes nodes{AllNodesPath(graph, 2)};
  EXPECT_TRUE(nodes.empty());
}

/////////////////////////////////////////////
/// Bellman-Ford tests
/////////////////////////////////////////////

TEST(test_algo_graph, bf_negative_cycle)
{
  Graph graph{NewGraph(5)};
  MakeDirEdge(graph, 0, 1, 3.0);
  MakeDirEdge(graph, 1, 2, 4.0);
  MakeDirEdge(graph, 1, 3, 5.0);
  MakeDirEdge(graph, 3, 4, 2.0);
  MakeDirEdge(graph, 4, 1, -8.0);
  // Empty if negative-weight cycle found
  EXPECT_TRUE(ShortestPathBF(graph, 0).second.empty());
}

TEST(test_algo_graph, bf_simple1)
{
  Graph graph{NewGraph(5)};
  MakeDirEdge(graph, 0, 1, 4.0);
  MakeDirEdge(graph, 0, 2, 2.0);
  MakeDirEdge(graph, 1, 2, 3.0);
  MakeDirEdge(graph, 2, 1, 1.0);
  MakeDirEdge(graph, 1, 3, 2.0);
  MakeDirEdge(graph, 1, 4, 3.0);
  MakeDirEdge(graph, 2, 3, 4.0);
  MakeDirEdge(graph, 2, 4, 5.0);
  MakeDirEdge(graph, 4, 3, -5.0);

  Nodes corr{0, 3, 2, 1, 6};
  pair<Weights, Nodes> res{ShortestPathBF(graph, 0)};
  EXPECT_TRUE(equal(corr.begin(), corr.end(), res.first.begin()));
}

TEST(test_algo_graph, bf_simple2)
{
  Graph graph{NewGraph(6)};
  MakeDirEdge(graph, 0, 1, 10.0);
  MakeDirEdge(graph, 0, 5, 8.0);
  MakeDirEdge(graph, 1, 3, 2.0);
  MakeDirEdge(graph, 2, 1, 1.0);
  MakeDirEdge(graph, 3, 2, -2.0);
  MakeDirEdge(graph, 4, 3, -1.0);
  MakeDirEdge(graph, 4, 1, -4.0);
  MakeDirEdge(graph, 5, 4, 1.0);

  Nodes corr{0, 5, 5, 7, 9, 8};
  pair<Weights, Nodes> res{ShortestPathBF(graph, 0)};
  EXPECT_TRUE(equal(corr.begin(), corr.end(), res.first.begin()));
}

TEST(test_algo_graph, bf_forbidden_cases)
{
  Graph graph{NewGraph(2)};
  EXPECT_TRUE(ShortestPathBF(graph, 0).first.empty());

  graph = NewGraph(3);
  EXPECT_TRUE(ShortestPathBF(graph, -1).first.empty());
  EXPECT_TRUE(ShortestPathBF(graph, 3).first.empty());
}

TEST(test_algo_graph, bf_single_path)
{
  Graph graph{NewGraph(6)};
  MakeDirEdge(graph, 0, 1, 10.0);
  MakeDirEdge(graph, 0, 5, 8.0);
  MakeDirEdge(graph, 1, 3, 2.0);
  MakeDirEdge(graph, 2, 1, 1.0);
  MakeDirEdge(graph, 3, 2, -2.0);
  MakeDirEdge(graph, 4, 3, -1.0);
  MakeDirEdge(graph, 4, 1, -4.0);
  MakeDirEdge(graph, 5, 4, 1.0);

  Nodes corr{0, 5, 4, 1, 3, 2};
  pair<Nodes, double> pathAndWeight{ShortestPathBF(graph, 0, 2)};
  EXPECT_TRUE(equal(corr.begin(), corr.end(), pathAndWeight.first.begin()));
  EXPECT_EQ(pathAndWeight.second, 5.0);
}

TEST(test_algo_graph, bf_single_path_forbidden_input)
{
  Graph punyGraph{NewGraph(2)};
  EXPECT_TRUE(ShortestPathBF(punyGraph, 0, 1).first.empty());

  Graph graph{NewGraph(3)};
  EXPECT_TRUE(ShortestPathBF(graph, -1, 1).first.empty());// Source < 0
  EXPECT_TRUE(ShortestPathBF(graph, 3, 1).first.empty()); // Source >= size
  EXPECT_TRUE(ShortestPathBF(graph, 0, -1).first.empty());// Dest < 0
  EXPECT_TRUE(ShortestPathBF(graph, 0, 3).first.empty()); // Dest >= size
}

/////////////////////////////////////////////
/// Breadth-First-Search tests
/////////////////////////////////////////////

TEST(test_algo_graph, bfs_forbidden_input)
{
  Graph empty_graph{NewGraph(0)};
  Nodes nodes1{BFS(empty_graph, 0)};
  EXPECT_TRUE(nodes1.empty());// Empty graph

  Graph graph{NewGraph(1)};
  EXPECT_TRUE(BFS(graph, -1).empty());// Source < 0
  EXPECT_TRUE(BFS(graph, 1).empty()); // Source >= size
}

TEST(test_algo_graph, shortest_paht_bfs1)
{
  Graph graph{NewGraph(6)};
  MakeEdge(graph, 0, 1);
  MakeEdge(graph, 0, 2);
  MakeEdge(graph, 1, 3);
  MakeEdge(graph, 3, 4);
  MakeEdge(graph, 2, 3);
  MakeEdge(graph, 2, 4);
  MakeEdge(graph, 4, 5);

  Nodes corr{0, 2, 4, 5};
  Path path{ShortestPathBFS(graph, 0, 5)};
  EXPECT_TRUE(path.is_path);
  EXPECT_TRUE(equal(corr.begin(), corr.end(), path.nodes.begin()));
}

TEST(test_algo_graph, shortest_path_bfs2)
{
  Graph graph{NewGraph(7)};
  MakeEdge(graph, 0, 1);
  MakeEdge(graph, 0, 2);
  MakeEdge(graph, 2, 3);
  MakeEdge(graph, 2, 4);
  MakeEdge(graph, 3, 5);
  MakeEdge(graph, 3, 6);

  Nodes corr{0, 2, 3, 6};
  Path path{ShortestPathBFS(graph, 0, 6)};
  EXPECT_TRUE(path.is_path);
  EXPECT_TRUE(equal(corr.begin(), corr.end(), path.nodes.begin()));
}

TEST(test_algo_graph, shortest_path_bfs_directed)
{
  Graph graph{NewGraph(5)};
  MakeDirEdge(graph, 0, 1);
  MakeDirEdge(graph, 0, 2);
  MakeDirEdge(graph, 1, 3);
  MakeDirEdge(graph, 2, 4);
  MakeDirEdge(graph, 3, 4);

  Nodes corr{0, 2, 4};
  Path path{ShortestPathBFS(graph, 0, 4)};
  EXPECT_TRUE(path.is_path);
  EXPECT_TRUE(equal(corr.begin(), corr.end(), path.nodes.begin()));
}

TEST(test_algo_graph, shortest_path_bfs_forbidden)
{
  Graph graph{NewGraph(1)};
  EXPECT_TRUE(ShortestPathBFS(graph, 0, 1).nodes.empty());// Size < 2
  Graph graph1{NewGraph(2)};
  EXPECT_TRUE(ShortestPathBFS(graph1, 0, 3).nodes.empty()); // Dest > size
  EXPECT_TRUE(ShortestPathBFS(graph1, 3, 2).nodes.empty()); // Source > size
  EXPECT_TRUE(ShortestPathBFS(graph1, -1, 1).nodes.empty());// Source < 0
  EXPECT_TRUE(ShortestPathBFS(graph1, 0, -1).nodes.empty());// Dest < 0
  EXPECT_TRUE(ShortestPathBFS(graph1, 1, 1).nodes.empty()); // Source == dest
}

TEST(test_algo_graph, bfs_is_bipartite1)
{
  Graph graph{NewGraph(6)};
  MakeEdge(graph, 0, 1);
  MakeEdge(graph, 0, 2);
  MakeEdge(graph, 1, 3);
  MakeEdge(graph, 2, 4);
  MakeEdge(graph, 3, 5);
  MakeEdge(graph, 4, 5);

  EXPECT_TRUE(IsBipartite(graph));
}

TEST(test_algo_graph, bfs_is_bipartite2)
{
  Graph graph{NewGraph(8)};
  Nodes as{0, 2, 4, 6, 7};
  Nodes bs{1, 3, 5};

  for (const auto& a : as) {
    for (const auto& b : bs) {
      MakeEdge(graph, a, b);
    }
  }

  EXPECT_TRUE(IsBipartite(graph));
}

TEST(test_algo_graph, bfs_is_not_bipartite)
{
  Graph graph{NewGraph(5)};
  MakeEdge(graph, 0, 1);
  MakeEdge(graph, 0, 2);
  MakeEdge(graph, 1, 3);
  MakeEdge(graph, 2, 4);
  MakeEdge(graph, 3, 4);

  EXPECT_FALSE(IsBipartite(graph));
}

TEST(test_algo_graph, bfs_is_bipartite_forbidden_input)
{
  EXPECT_FALSE(IsBipartite(NewGraph(1)));
}

/////////////////////////////////////////////
/// Edmonds-Karp, max flow tests
/////////////////////////////////////////////

TEST(test_algo_graph, max_flow1)
{
  Graph graph{NewGraph(6)};
  MakeDirEdge(graph, 0, 1, 160.0);
  MakeDirEdge(graph, 0, 2, 130.0);
  MakeDirEdge(graph, 2, 1, 40.0);
  MakeDirEdge(graph, 1, 2, 100.0);
  MakeDirEdge(graph, 2, 4, 140.0);
  MakeDirEdge(graph, 1, 3, 120.0);
  MakeDirEdge(graph, 3, 2, 90.0);
  MakeDirEdge(graph, 4, 3, 70.0);
  MakeDirEdge(graph, 3, 5, 200.0);
  MakeDirEdge(graph, 4, 5, 40.0);

  double max_flow(MaxFlow(graph, 0, 5));
  EXPECT_EQ(max_flow, 230.0);
}

TEST(test_algo_graph, max_flow2)
{
  Graph graph{NewGraph(6)};
  MakeDirEdge(graph, 0, 1, 10.0);
  MakeDirEdge(graph, 0, 2, 10.0);
  MakeDirEdge(graph, 1, 2, 2.0);
  MakeDirEdge(graph, 1, 3, 4.0);
  MakeDirEdge(graph, 1, 4, 8.0);
  MakeDirEdge(graph, 2, 4, 9.0);
  MakeDirEdge(graph, 4, 3, 6.0);
  MakeDirEdge(graph, 3, 5, 10.0);
  MakeDirEdge(graph, 4, 5, 10.0);

  double max_flow(MaxFlow(graph, 0, 5));
  EXPECT_EQ(max_flow, 19.0);
}

TEST(test_algo_graph, max_flow_forbidden)
{
  Graph no_path_graph{NewGraph(4)};
  MakeDirEdge(no_path_graph, 0, 1, 10.0);
  MakeDirEdge(no_path_graph, 2, 3, 10.0);

  double max_flow(MaxFlow(no_path_graph, 0, 2));
  EXPECT_EQ(max_flow, 0.0);// No path in graph

  EXPECT_EQ(MaxFlow(NewGraph(2), -1, 1), 0.0);// source < size
  EXPECT_EQ(MaxFlow(NewGraph(2), 0, -1), 0.0);// dest < size
  EXPECT_EQ(MaxFlow(NewGraph(2), 1, 1), 0.0); // dest == source
  EXPECT_EQ(MaxFlow(NewGraph(2), 2, 1), 0.0); // source >= size
  EXPECT_EQ(MaxFlow(NewGraph(2), 1, 2), 0.0); // dest >= size
}

/////////////////////////////////////////////
/// Floyd-Warshall, all-pairs shortest path
/////////////////////////////////////////////

TEST(test_algo_graph, shortest_dist_all_pairs1)
{
  Graph graph{NewGraph(4)};
  MakeDirEdge(graph, 0, 1, 2);
  MakeDirEdge(graph, 0, 2, 1);
  MakeDirEdge(graph, 1, 0, 3);
  MakeDirEdge(graph, 1, 3, 1);
  MakeDirEdge(graph, 1, 2, 5);
  MakeDirEdge(graph, 2, 0, 2);
  MakeDirEdge(graph, 2, 3, 3);
  MakeDirEdge(graph, 3, 0, 4);

  Nodes corr{0, 1, 3};
  Nodes path{ShortestDistAllPairsPath(graph, 0, 3)};
  EXPECT_TRUE(equal(path.begin(), path.end(), corr.begin()));
}

TEST(test_algo_graph, shortest_dist_all_pair2)
{
  Graph graph{NewGraph(5)};
  MakeDirEdge(graph, 0, 1, 5);
  MakeDirEdge(graph, 0, 3, 2);
  MakeDirEdge(graph, 1, 2, 2);
  MakeDirEdge(graph, 2, 0, 3);
  MakeDirEdge(graph, 2, 4, 7);
  MakeDirEdge(graph, 3, 2, 4);
  MakeDirEdge(graph, 3, 4, 1);
  MakeDirEdge(graph, 4, 0, 1);
  MakeDirEdge(graph, 4, 1, 3);

  Nodes corr{0, 3, 4};
  Nodes path{ShortestDistAllPairsPath(graph, 0, 4)};
  EXPECT_TRUE(equal(path.begin(), path.end(), corr.begin()));
}

TEST(test_algo_graph, shortest_dist_all_pairs_forbidden_input)
{
  EXPECT_TRUE(ShortestDistAllPairsPath(NewGraph(2), 0, 1).empty()); // size < 3
  EXPECT_TRUE(ShortestDistAllPairsPath(NewGraph(3), -1, 1).empty());// source < 0
  EXPECT_TRUE(ShortestDistAllPairsPath(NewGraph(3), 0, -1).empty());// dest < 0
  EXPECT_TRUE(ShortestDistAllPairsPath(NewGraph(3), 4, 1).empty()); // source > size
  EXPECT_TRUE(ShortestDistAllPairsPath(NewGraph(3), 0, 4).empty()); // dest > size
  EXPECT_TRUE(ShortestDistAllPairsPath(NewGraph(3), 2, 2).empty()); // source == dest
}

/////////////////////////////////////////////
/// Kosaraju, strongly connected components
/////////////////////////////////////////////

TEST(test_algo_graph, scc_simple1)
{
  Graph graph{NewGraph(5)};
  MakeDirEdge(graph, 1, 0);
  MakeDirEdge(graph, 2, 1);
  MakeDirEdge(graph, 0, 2);
  MakeDirEdge(graph, 0, 3);
  MakeDirEdge(graph, 3, 4);

  NodeMat corr{
      {0, 1, 2},
      {3},
      {4}};
  NodeMat scc{StrConnComponents(graph)};

  for (size_t i = 0; i < corr.size(); ++i) {
    EXPECT_TRUE(equal(corr[i].begin(), corr[i].end(), scc[i].begin()));
  }
  EXPECT_EQ(scc.size(), 3);
}

TEST(test_algo_graph, scc_simple2)
{
  Graph graph{NewGraph(8)};
  MakeDirEdge(graph, 0, 1);
  MakeDirEdge(graph, 1, 4);
  MakeDirEdge(graph, 4, 0);
  MakeDirEdge(graph, 1, 5);
  MakeDirEdge(graph, 4, 5);
  MakeDirEdge(graph, 1, 2);
  MakeDirEdge(graph, 5, 6);
  MakeDirEdge(graph, 6, 5);
  MakeDirEdge(graph, 2, 6);
  MakeDirEdge(graph, 2, 3);
  MakeDirEdge(graph, 3, 2);
  MakeDirEdge(graph, 7, 6);
  MakeDirEdge(graph, 3, 7);
  MakeDirEdge(graph, 7, 3);

  NodeMat corr{
      {0, 4, 1},
      {2, 3, 7},
      {5, 6}};
  NodeMat scc{StrConnComponents(graph)};

  for (size_t i = 0; i < corr.size(); ++i) {
    EXPECT_TRUE(equal(corr[i].begin(), corr[i].end(), scc[i].begin()));
  }
  EXPECT_EQ(scc.size(), 3);
}

TEST(test_algo_graph, scc_minimal)
{
  Graph graph{NewGraph(2)};
  MakeEdge(graph, 0, 1);

  NodeMat corr{{0, 1}};
  NodeMat scc{StrConnComponents(graph)};

  for (size_t i = 0; i < corr.size(); ++i) {
    EXPECT_TRUE(equal(corr[i].begin(), corr[i].end(), scc[i].begin()));
  }
  EXPECT_EQ(scc.size(), 1);
}

TEST(test_algo_graph, scc_forbidden_input)
{
  EXPECT_TRUE(StrConnComponents(NewGraph(1)).empty());
}
