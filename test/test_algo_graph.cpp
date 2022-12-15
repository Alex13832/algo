///
/// \brief Unit tests for graph algorithms.
/// \author alex011235
/// \date 2020-05-03
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "algo.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace algo::graph;

/////////////////////////////////////////////
/// - MARK: UndirectedGraph -

TEST(UndirectedGraph, InsertEdge)
{
  UndirectedGraph ug{3};
  ug.InsertEdge(0, 1);
  ug.InsertEdge(0, 2);
  auto edges = ug.GetEdges();
  EXPECT_EQ(edges.size(), 4);
}

TEST(UndirectedGraph, RemoveEdge)
{
  UndirectedGraph ug{3};
  ug.InsertEdge(0, 1);
  ug.InsertEdge(0, 2);
  auto edges = ug.GetEdges();
  EXPECT_EQ(edges.size(), 4);
  ug.RemoveEdge(0, 1);
  edges = ug.GetEdges();
  EXPECT_EQ(edges.size(), 2);
}

// MARK: BFS

TEST(UndirectedGraph, BreadthFirstSearchInvalidA)
{
  UndirectedGraph ug{0};
  auto nodes = ug.BFS(0);
  EXPECT_TRUE(nodes.empty());
}

TEST(UndirectedGraph, BreadthFirstSearchInvalidB)
{
  UndirectedGraph ug{1};
  EXPECT_TRUE(ug.BFS(-1).empty());// Source < 0
  EXPECT_TRUE(ug.BFS(1).empty()); // Source >= size
}

TEST(UndirectedGraph, BreadthFirstSearchA)
{
  UndirectedGraph ug{6};
  ug.InsertEdge(0, 1);
  ug.InsertEdge(0, 2);
  ug.InsertEdge(1, 3);
  ug.InsertEdge(3, 4);
  ug.InsertEdge(2, 3);
  ug.InsertEdge(2, 4);
  ug.InsertEdge(4, 5);

  Nodes corr{0, 2, 4, 5};
  auto path = ug.ShortestPathBFS(0, 5);
  EXPECT_TRUE(path.is_path);
  EXPECT_TRUE(equal(corr.begin(), corr.end(), path.nodes.begin()));
}

TEST(UndirectedGraph, BreadthFirstSearchB)
{
  UndirectedGraph ug{7};
  ug.InsertEdge(0, 1);
  ug.InsertEdge(0, 2);
  ug.InsertEdge(2, 3);
  ug.InsertEdge(2, 4);
  ug.InsertEdge(3, 5);
  ug.InsertEdge(3, 6);

  Nodes corr{0, 2, 3, 6};
  auto path = ug.ShortestPathBFS(0, 6);
  EXPECT_TRUE(path.is_path);
  EXPECT_TRUE(equal(corr.begin(), corr.end(), path.nodes.begin()));
}

// MARK: Is bipartite

TEST(UndirectedGraph, IsBipartiteInvalid)
{
  EXPECT_FALSE(UndirectedGraph{0}.IsBipartite());
  EXPECT_FALSE(UndirectedGraph{1}.IsBipartite());
}

TEST(UndirectedGraph, IsBipartiteA)
{
  UndirectedGraph ug{6};
  ug.InsertEdge(0, 1);
  ug.InsertEdge(0, 2);
  ug.InsertEdge(1, 3);
  ug.InsertEdge(2, 4);
  ug.InsertEdge(3, 5);
  ug.InsertEdge(4, 5);
  EXPECT_TRUE(ug.IsBipartite());
}

TEST(UndirectedGraph, IsBipartiteB)
{
  UndirectedGraph ug{8};
  Nodes as{0, 2, 4, 6, 7};
  Nodes bs{1, 3, 5};

  for (const auto& a : as) {
    for (const auto& b : bs) {
      ug.InsertEdge(a, b);
    }
  }

  EXPECT_TRUE(ug.IsBipartite());
}

TEST(UndirectedGraph, IsNotBipartite)
{
  UndirectedGraph ug{5};
  ug.InsertEdge(0, 1);
  ug.InsertEdge(0, 2);
  ug.InsertEdge(1, 3);
  ug.InsertEdge(2, 4);
  ug.InsertEdge(3, 4);
  EXPECT_FALSE(ug.IsBipartite());
}

/////////////////////////////////////////////
/// - MARK: DirectedGraph -

TEST(DirectedGraph, InsertEdgeBounds)
{
  size_t graph_size{3};
  DirectedGraph dg{graph_size};
  dg.InsertEdge(graph_size, graph_size - 1);
  dg.InsertEdge(graph_size - 1, graph_size);
  dg.InsertEdge(graph_size, graph_size);
  dg.InsertEdge(graph_size - 1, graph_size - 2);// Valid
  auto edges = dg.GetEdges();
  EXPECT_EQ(edges.size(), 1);
}

TEST(DirectedGraph, RemoveEdge)
{
  size_t graph_size{2};
  DirectedGraph dg{graph_size};
  dg.InsertEdge(0, 1);
  dg.InsertEdge(1, 0);

  auto edges = dg.GetEdges();
  EXPECT_EQ(edges.size(), 2);

  dg.RemoveEdge(0, 1);
  edges = dg.GetEdges();
  EXPECT_EQ(edges.size(), 1);

  dg.RemoveEdge(1, 0);
  edges = dg.GetEdges();
  EXPECT_EQ(edges.size(), 0);
}

TEST(DirectedGraph, BreadthFirstSearch)
{
  DirectedGraph dg{5};
  dg.InsertEdge(0, 1);
  dg.InsertEdge(0, 2);
  dg.InsertEdge(1, 3);
  dg.InsertEdge(2, 4);
  dg.InsertEdge(3, 4);

  Nodes corr{0, 2, 4};
  auto path = dg.ShortestPathBFS(0, 4);
  EXPECT_TRUE(path.is_path);
  EXPECT_TRUE(equal(corr.begin(), corr.end(), path.nodes.begin()));
}

// MARK: Strongly connected components

TEST(DirectedGraph, StronglyConnectedComponentsA)
{
  DirectedGraph dg{5};
  dg.InsertEdge(1, 0);
  dg.InsertEdge(2, 1);
  dg.InsertEdge(0, 2);
  dg.InsertEdge(0, 3);
  dg.InsertEdge(3, 4);

  NodeMat corr{{0, 1, 2}, {3}, {4}};
  auto scc = dg.StronglyConnectedComponentsKosaraju();

  for (size_t i = 0; i < corr.size(); ++i) {
    EXPECT_TRUE(equal(corr[i].begin(), corr[i].end(), scc[i].begin()));
  }
  EXPECT_EQ(scc.size(), 3);
}

TEST(DirectedGraph, StronglyConnectedComponentsB)
{
  DirectedGraph dg{8};
  dg.InsertEdge(0, 1);
  dg.InsertEdge(1, 4);
  dg.InsertEdge(4, 0);
  dg.InsertEdge(1, 5);
  dg.InsertEdge(4, 5);
  dg.InsertEdge(1, 2);
  dg.InsertEdge(5, 6);
  dg.InsertEdge(6, 5);
  dg.InsertEdge(2, 6);
  dg.InsertEdge(2, 3);
  dg.InsertEdge(3, 2);
  dg.InsertEdge(7, 6);
  dg.InsertEdge(3, 7);
  dg.InsertEdge(7, 3);

  NodeMat corr{{0, 4, 1}, {2, 3, 7}, {5, 6}};
  auto scc = dg.StronglyConnectedComponentsKosaraju();

  for (size_t i = 0; i < corr.size(); ++i) {
    EXPECT_TRUE(equal(corr[i].begin(), corr[i].end(), scc[i].begin()));
  }
  EXPECT_EQ(scc.size(), 3);
}

TEST(DirectedGraph, StronglyConnectedComponentsC)
{
  DirectedGraph dg{2};
  dg.InsertEdge(0, 1);

  NodeMat corr{{0, 1}};
  auto scc = dg.StronglyConnectedComponentsKosaraju();

  EXPECT_EQ(scc.size(), 2);
  EXPECT_EQ(corr[0][0], scc[0][0]);
  EXPECT_EQ(corr[0][1], scc[1][0]);// Goofy order, I know.
}

TEST(DirectedGraph, StronglyConnectedComponentsInvalid)
{
  EXPECT_TRUE(DirectedGraph{1}.StronglyConnectedComponentsKosaraju().empty());
}

/////////////////////////////////////////////
/// - MARK: UndirectedWeightedGraph -

TEST(UndirectedWeightedGraph, CreateGraph)
{
  size_t graph_size{3};
  UndirectedWeightedGraph uwg{graph_size};
  uwg.InsertEdge(0, 1, 1);
  uwg.InsertEdge(0, 2, 2);
  uwg.InsertEdge(1, 2, 3);
  auto edges = uwg.GetEdges();
  EXPECT_EQ(edges.size(), 2 * graph_size);
}

TEST(UndirectedWeightedGraph, MakeEdgeBounds)
{
  size_t graph_size{3};
  UndirectedWeightedGraph uwg{graph_size};
  uwg.InsertEdge(graph_size, graph_size - 1, 1.0);
  uwg.InsertEdge(graph_size - 1, graph_size, 1.0);
  uwg.InsertEdge(1, 1, 1.0);
  uwg.InsertEdge(graph_size - 1, graph_size - 2, 1.0);
  auto edges = uwg.GetEdges();
  EXPECT_EQ(edges.size(), 2);
}

TEST(UndirectedWeightedGraph, SetGetWeightBounds)
{
  size_t graph_size{2};
  double default_weight{1.0};
  UndirectedWeightedGraph wg{graph_size};
  wg.InsertEdge(0, 1, default_weight);
  wg.SetWeight(0, 2, 5.0);
  wg.SetWeight(2, 1, 5.0);
  wg.SetWeight(1, 1, 5.0);
  EXPECT_EQ(wg.GetWeight(0, 1), default_weight);
}

TEST(UndirectedWeightedGraph, SetGetWeight)
{
  size_t graph_size{2};
  double default_weight{1.0};
  double updated_weight{1.0};
  UndirectedWeightedGraph wg{graph_size};
  wg.InsertEdge(0, 1, default_weight);
  wg.SetWeight(0, 1, updated_weight);
  EXPECT_EQ(wg.GetWeight(0, 1), updated_weight);
}

TEST(UndirectedWeightedGraph, RemoveEdge)
{
  size_t graph_size{2};
  double default_weight{1.0};

  UndirectedWeightedGraph wg{graph_size};
  wg.InsertEdge(0, 1, default_weight);

  auto edges = wg.GetEdges();
  EXPECT_EQ(edges.size(), 2);

  wg.RemoveEdge(0, 1);
  edges = wg.GetEdges();
  EXPECT_EQ(edges.size(), 0);
}

TEST(UndirectedWeightedGraph, AllWeightsPositive)
{
  UndirectedWeightedGraph uwg{3};
  uwg.InsertEdge(0, 1, 10.0);
  uwg.InsertEdge(0, 2, 11.0);
  EXPECT_TRUE(uwg.AllWeightsPositive());
}

TEST(UndirectedWeightedGraph, AllWeightsNotPositive)
{
  UndirectedWeightedGraph uwg{3};
  uwg.InsertEdge(0, 1, 10.0);
  uwg.InsertEdge(0, 2, -11.0);
  EXPECT_FALSE(uwg.AllWeightsPositive());
}

// MARK: Minimum spanning tree

TEST(UndirectedWeightedGraph, MinimumSpanningTreeInvalid)
{
  double total_weight{0.0};
  UndirectedWeightedGraph uwg2{0};
  auto mst3 = uwg2.MinSpanningTreePrim(total_weight);
  EXPECT_EQ(mst3.Size(), 0);
}

TEST(UndirectedWeightedGraph, MinimumSpanningTreeContainsNegative)
{
  UndirectedWeightedGraph uwg{3};
  uwg.InsertEdge(0, 1, 1.0);
  uwg.InsertEdge(0, 2, 2.0);
  uwg.InsertEdge(1, 2, -3.0);
  double total_weight{0.0};
  auto mst = uwg.MinSpanningTreePrim(total_weight);
  EXPECT_EQ(mst.Size(), 0);
  EXPECT_EQ(total_weight, 0.0);
}

TEST(UndirectedWeightedGraph, MinimumSpanningTreeA)
{
  UndirectedWeightedGraph uwg{7};
  uwg.InsertEdge(0, 1, 16);
  uwg.InsertEdge(0, 3, 21);
  uwg.InsertEdge(0, 2, 12);
  uwg.InsertEdge(1, 4, 20);
  uwg.InsertEdge(1, 3, 17);
  uwg.InsertEdge(2, 3, 28);
  uwg.InsertEdge(3, 4, 18);
  uwg.InsertEdge(3, 6, 23);
  uwg.InsertEdge(3, 5, 19);
  uwg.InsertEdge(3, 5, 31);
  uwg.InsertEdge(4, 6, 11);
  uwg.InsertEdge(5, 6, 27);

  double total_weight{0.0};
  auto mst = uwg.MinSpanningTreePrim(total_weight);
  EXPECT_EQ(total_weight, 93);
}

//Test-case file is downloaded from "Project Euler", problem 107
UndirectedWeightedGraph ReadPrimsFile()
{
  UndirectedWeightedGraph uwg{40};
  vector<int> total;
  ifstream infile("testfiles/prims/p107_network.txt");
  string line;
  int row = 0;
  int col = 0;

  while (getline(infile, line)) {
    size_t pos;
    string token;
    while ((pos = line.find(',')) != string::npos) {
      token = line.substr(0, pos);

      try {
        auto weight = stoi(token);
        total.push_back(weight);
        uwg.InsertEdge(col, row, weight);
      } catch (std::invalid_argument&) {
        //std::cerr << "Didn't go well!" << std::endl;
      }

      line.erase(0, pos + 1);
      col++;
    }

    try {
      auto weight = stoi(line);
      total.push_back(weight);
      uwg.InsertEdge(col, row, weight);
    } catch (std::invalid_argument&) {
    }

    row++;
    col = 0;
  }
  return uwg;
}

TEST(UndirectedWeightedGraph, MinimumSpanningTreeProjectEuler107)
{
  auto uwg = ReadPrimsFile();
  double total_weight{0.0};
  auto mst = uwg.MinSpanningTreePrim(total_weight);
  auto ans = 261832.0 - total_weight;
  EXPECT_EQ(ans, 259679.0);
}

// MARK: Shortest path Dijkstra

TEST(UndirectedWeightedGraph, ShortestPathDijkstraInvalid)
{
  UndirectedWeightedGraph uwg{1};
  EXPECT_TRUE(uwg.ShortestPathDijkstra(0, 1).empty());// Size < 2

  UndirectedWeightedGraph uwg1{2};
  EXPECT_TRUE(uwg.ShortestPathDijkstra(0, 3).empty()); // Dest > size
  EXPECT_TRUE(uwg.ShortestPathDijkstra(3, 2).empty()); // Source > size
  EXPECT_TRUE(uwg.ShortestPathDijkstra(-1, 1).empty());// Source < 0
  EXPECT_TRUE(uwg.ShortestPathDijkstra(0, -1).empty());// Dest < 0
  EXPECT_TRUE(uwg.ShortestPathDijkstra(1, 1).empty()); // Source == dest
}

TEST(UndirectedWeightedGraph, ShortestPathDijkstraA)
{
  UndirectedWeightedGraph uwg{7};
  uwg.InsertEdge(0, 1, 5.0);
  uwg.InsertEdge(0, 2, 10.0);
  uwg.InsertEdge(2, 4, 2.0);
  uwg.InsertEdge(1, 4, 3.0);
  uwg.InsertEdge(1, 3, 6.0);
  uwg.InsertEdge(4, 3, 2.0);
  uwg.InsertEdge(3, 5, 6.0);
  uwg.InsertEdge(4, 6, 2.0);
  uwg.InsertEdge(6, 5, 2.0);

  Nodes correct1{0, 1, 4, 6};
  auto nodes1 = uwg.ShortestPathDijkstra(0, 6);
  EXPECT_TRUE(equal(nodes1.begin(), nodes1.end(), correct1.begin()));

  Nodes correct2{4, 6, 5};
  auto nodes2 = uwg.ShortestPathDijkstra(4, 5);
  EXPECT_TRUE(equal(nodes2.begin(), nodes2.end(), correct2.begin()));
}

TEST(UndirectedWeightedGraph, ShortestPathDijkstraB)
{
  UndirectedWeightedGraph uwg{6};
  uwg.InsertEdge(0, 2, 2.0);
  uwg.InsertEdge(0, 1, 4.0);
  uwg.InsertEdge(1, 2, 1.0);
  uwg.InsertEdge(1, 3, 5.0);
  uwg.InsertEdge(2, 3, 8.0);
  uwg.InsertEdge(2, 4, 10.0);
  uwg.InsertEdge(4, 5, 3.0);
  uwg.InsertEdge(3, 4, 2.0);
  uwg.InsertEdge(3, 5, 6.0);

  Nodes correct{0, 2, 1, 3, 4, 5};
  auto nodes = uwg.ShortestPathDijkstra(0, 5);
  EXPECT_TRUE(equal(nodes.begin(), nodes.end(), correct.begin()));

  reverse(correct.begin(), correct.end());
  auto nodes1 = uwg.ShortestPathDijkstra(5, 0);
  EXPECT_TRUE(equal(nodes1.begin(), nodes1.end(), correct.begin()));
}

/////////////////////////////////////////////
/// - MARK: DirectedWeightedGraph -

TEST(DirectedWeightedGraph, MakeEdgeBounds)
{
  size_t graph_size{3};
  DirectedWeightedGraph dwg{graph_size};
  dwg.InsertEdge(graph_size, graph_size - 1, 2.0);
  dwg.InsertEdge(graph_size - 1, graph_size, 2.0);
  dwg.InsertEdge(graph_size, graph_size, 2.0);
  dwg.InsertEdge(graph_size - 1, graph_size - 2, 2.0);// Valid
  auto edges = dwg.GetEdges();
  EXPECT_EQ(edges.size(), 1);
}

TEST(DirectedWeightedGraph, SetWeightBounds)
{
  size_t graph_size{2};
  double w{42.0};
  DirectedWeightedGraph dwg{graph_size};
  dwg.InsertEdge(0, graph_size - 1, w);
  EXPECT_EQ(dwg.GetWeight(0, graph_size - 1), w);
  dwg.SetWeight(0, graph_size - 1, 2 * w);
  EXPECT_EQ(dwg.GetWeight(0, graph_size - 1), 2 * w);
}

TEST(DirectedWeightedGraph, RemoveEdge)
{
  size_t graph_size{3};
  double w{42.0};
  DirectedWeightedGraph dwg{graph_size};
  dwg.InsertEdge(0, 1, w);
  dwg.InsertEdge(0, 2, w);
  auto edges = dwg.GetEdges();
  EXPECT_EQ(edges.size(), 2);

  dwg.RemoveEdge(0, 1);
  edges = dwg.GetEdges();
  EXPECT_EQ(edges.size(), 1);
}

TEST(DirectedWeightedGraph, AllWeightsPositive)
{
  DirectedWeightedGraph dwg{3};
  dwg.InsertEdge(0, 1, 10.0);
  dwg.InsertEdge(1, 2, 12.0);
  EXPECT_TRUE(dwg.AllWeightsPositive());
}

TEST(DirectedWeightedGraph, AllWeightsNotPositive)
{
  DirectedWeightedGraph dwg{3};
  dwg.InsertEdge(0, 1, 10.0);
  dwg.InsertEdge(1, 2, -12.0);
  EXPECT_FALSE(dwg.AllWeightsPositive());
}

// MARK: Shortest path Dijkstra

TEST(DirectedWeightedGraph, ShortestPathDijkstraA)
{
  DirectedWeightedGraph dwg{7};
  dwg.InsertEdge(0, 1, 5.0);
  dwg.InsertEdge(0, 2, 10.0);
  dwg.InsertEdge(2, 4, 2.0);
  dwg.InsertEdge(1, 4, 3.0);
  dwg.InsertEdge(1, 3, 6.0);
  dwg.InsertEdge(4, 3, 2.0);
  dwg.InsertEdge(3, 5, 6.0);
  dwg.InsertEdge(4, 6, 2.0);
  dwg.InsertEdge(6, 5, 2.0);

  Nodes correct1{0, 1, 4, 6};
  auto nodes1 = dwg.ShortestPathDijkstra(0, 6);
  EXPECT_TRUE(equal(nodes1.begin(), nodes1.end(), correct1.begin()));

  Nodes correct2{4, 6, 5};
  auto nodes2 = dwg.ShortestPathDijkstra(4, 5);
  EXPECT_TRUE(equal(nodes2.begin(), nodes2.end(), correct2.begin()));
}

// MARK: ShortestPathBellmanFord

TEST(DirectedWeightedGraph, ShortestPathBellmanFordInvalid)
{
  DirectedWeightedGraph dwg1{2};
  EXPECT_TRUE(dwg1.ShortestPathBellmanFord(0).first.empty());

  DirectedWeightedGraph dwg2{3};
  EXPECT_TRUE(dwg2.ShortestPathBellmanFord(-1).first.empty());
  EXPECT_TRUE(dwg2.ShortestPathBellmanFord(3).first.empty());
}

TEST(DirectedWeightedGraph, ShortestPathBellmanFordNegativeWeightCycle)
{
  DirectedWeightedGraph dwg{5};
  dwg.InsertEdge(0, 1, 3.0);
  dwg.InsertEdge(1, 2, 4.0);
  dwg.InsertEdge(1, 3, 5.0);
  dwg.InsertEdge(3, 4, 2.0);
  dwg.InsertEdge(4, 1, -8.0);
  // Empty if negative-weight cycle found
  EXPECT_TRUE(dwg.ShortestPathBellmanFord(0).second.empty());
}

TEST(DirectedWeightedGraph, ShortestPathBellmanFordA)
{
  DirectedWeightedGraph dwg{5};
  dwg.InsertEdge(0, 1, 4.0);
  dwg.InsertEdge(0, 2, 2.0);
  dwg.InsertEdge(1, 2, 3.0);
  dwg.InsertEdge(2, 1, 1.0);
  dwg.InsertEdge(1, 3, 2.0);
  dwg.InsertEdge(1, 4, 3.0);
  dwg.InsertEdge(2, 3, 4.0);
  dwg.InsertEdge(2, 4, 5.0);
  dwg.InsertEdge(4, 3, -5.0);

  Nodes corr{0, 3, 2, 1, 6};
  auto res = dwg.ShortestPathBellmanFord(0);
  EXPECT_TRUE(equal(corr.begin(), corr.end(), res.first.begin()));
}

TEST(DirectedWeightedGraph, ShortestPathBellmanFordB)
{
  DirectedWeightedGraph dwg{6};
  dwg.InsertEdge(0, 1, 10.0);
  dwg.InsertEdge(0, 5, 8.0);
  dwg.InsertEdge(1, 3, 2.0);
  dwg.InsertEdge(2, 1, 1.0);
  dwg.InsertEdge(3, 2, -2.0);
  dwg.InsertEdge(4, 3, -1.0);
  dwg.InsertEdge(4, 1, -4.0);
  dwg.InsertEdge(5, 4, 1.0);

  Nodes corr{0, 5, 5, 7, 9, 8};
  auto res = dwg.ShortestPathBellmanFord(0);
  EXPECT_TRUE(equal(corr.begin(), corr.end(), res.first.begin()));
}

TEST(DirectedWeightedGraph, ShortestPathBellmanFordSinglePathA)
{
  DirectedWeightedGraph dwg{6};
  dwg.InsertEdge(0, 1, 10.0);
  dwg.InsertEdge(0, 5, 8.0);
  dwg.InsertEdge(1, 3, 2.0);
  dwg.InsertEdge(2, 1, 1.0);
  dwg.InsertEdge(3, 2, -2.0);
  dwg.InsertEdge(4, 3, -1.0);
  dwg.InsertEdge(4, 1, -4.0);
  dwg.InsertEdge(5, 4, 1.0);

  Nodes corr{0, 5, 4, 1, 3, 2};
  auto path_weight = dwg.ShortestPathSinglePathBellmanFord(0, 2);
  EXPECT_TRUE(equal(corr.begin(), corr.end(), path_weight.first.begin()));
  EXPECT_EQ(path_weight.second, 5.0);
}

TEST(DirectedWeightedGraph, ShortestPathBellmanFordSinglePathInvalid)
{
  DirectedWeightedGraph dwg1{2};
  EXPECT_TRUE(dwg1.ShortestPathSinglePathBellmanFord(0, 1).first.empty());

  DirectedWeightedGraph dwg2{3};
  auto res = dwg2.ShortestPathSinglePathBellmanFord(-1, 1);
  EXPECT_TRUE(res.first.empty());// Source < 0
  res = dwg2.ShortestPathSinglePathBellmanFord(3, 1);
  EXPECT_TRUE(res.first.empty());// Source >= size
  res = dwg2.ShortestPathSinglePathBellmanFord(0, -1);
  EXPECT_TRUE(res.first.empty());// Dest < 0
  res = dwg2.ShortestPathSinglePathBellmanFord(0, 3);
  EXPECT_TRUE(res.first.empty());// Dest >= size
}

// - MARK: ShortestDistAllPairsFloydWarshall

TEST(DirectedWeightedGraph, ShortestDistAllPairsFloydWarshallA)
{
  DirectedWeightedGraph dwg{4};
  dwg.InsertEdge(0, 1, 2);
  dwg.InsertEdge(0, 2, 1);
  dwg.InsertEdge(1, 0, 3);
  dwg.InsertEdge(1, 3, 1);
  dwg.InsertEdge(1, 2, 5);
  dwg.InsertEdge(2, 0, 2);
  dwg.InsertEdge(2, 3, 3);
  dwg.InsertEdge(3, 0, 4);

  Nodes corr{0, 1, 3};
  auto path = dwg.ShortestDistAllPairsPathFloydWarshall(0, 3);
  EXPECT_TRUE(equal(path.begin(), path.end(), corr.begin()));
}

TEST(DirectedWeightedGraph, ShortestDistAllPairsFloydWarshallB)
{
  DirectedWeightedGraph dwg{5};
  dwg.InsertEdge(0, 1, 5);
  dwg.InsertEdge(0, 3, 2);
  dwg.InsertEdge(1, 2, 2);
  dwg.InsertEdge(2, 0, 3);
  dwg.InsertEdge(2, 4, 7);
  dwg.InsertEdge(3, 2, 4);
  dwg.InsertEdge(3, 4, 1);
  dwg.InsertEdge(4, 0, 1);
  dwg.InsertEdge(4, 1, 3);

  Nodes corr{0, 3, 4};
  auto path = dwg.ShortestDistAllPairsPathFloydWarshall(0, 4);
  EXPECT_TRUE(equal(path.begin(), path.end(), corr.begin()));
}

TEST(DirectedWeightedGraph, ShortestDistAllPairsFloydWarshallInvalid)
{

  DirectedWeightedGraph dwg0{2};
  auto path = dwg0.ShortestDistAllPairsPathFloydWarshall(0, 1);
  EXPECT_TRUE(path.empty());

  DirectedWeightedGraph dwg{3};

  path = dwg.ShortestDistAllPairsPathFloydWarshall(-1, 1);
  EXPECT_TRUE(path.empty());

  path = dwg.ShortestDistAllPairsPathFloydWarshall(0, -1);
  EXPECT_TRUE(path.empty());

  path = dwg.ShortestDistAllPairsPathFloydWarshall(4, 1);
  EXPECT_TRUE(path.empty());

  path = dwg.ShortestDistAllPairsPathFloydWarshall(0, 4);
  EXPECT_TRUE(path.empty());

  path = dwg.ShortestDistAllPairsPathFloydWarshall(2, 2);
  EXPECT_TRUE(path.empty());
}

// - MARK: MaxFlowEdmondsKarp

TEST(DirectedWeightedGraph, MaxFlowEdmondsKarpA)
{
  DirectedWeightedGraph dwg{6};
  dwg.InsertEdge(0, 1, 160.0);
  dwg.InsertEdge(0, 2, 130.0);
  dwg.InsertEdge(2, 1, 40.0);
  dwg.InsertEdge(1, 2, 100.0);
  dwg.InsertEdge(2, 4, 140.0);
  dwg.InsertEdge(1, 3, 120.0);
  dwg.InsertEdge(3, 2, 90.0);
  dwg.InsertEdge(4, 3, 70.0);
  dwg.InsertEdge(3, 5, 200.0);
  dwg.InsertEdge(4, 5, 40.0);

  auto max_flow = dwg.MaxFlowEdmondsKarp(0, 5);
  EXPECT_EQ(max_flow, 230.0);
}

TEST(DirectedWeightedGraph, MaxFlowEdmondsKarpB)
{
  DirectedWeightedGraph dwg{6};
  dwg.InsertEdge(0, 1, 10.0);
  dwg.InsertEdge(0, 2, 10.0);
  dwg.InsertEdge(1, 2, 2.0);
  dwg.InsertEdge(1, 3, 4.0);
  dwg.InsertEdge(1, 4, 8.0);
  dwg.InsertEdge(2, 4, 9.0);
  dwg.InsertEdge(4, 3, 6.0);
  dwg.InsertEdge(3, 5, 10.0);
  dwg.InsertEdge(4, 5, 10.0);

  auto max_flow = dwg.MaxFlowEdmondsKarp(0, 5);
  EXPECT_EQ(max_flow, 19.0);
}

TEST(DirectedWeightedGraph, MaxFlowEdmondsKarpInvalid)
{
  DirectedWeightedGraph dwg{4};
  dwg.InsertEdge(0, 1, 10.0);
  dwg.InsertEdge(2, 3, 10.0);

  auto max_flow = dwg.MaxFlowEdmondsKarp(0, 2);
  EXPECT_EQ(max_flow, 0.0);// No path in graph

  DirectedWeightedGraph dwg1{2};
  max_flow = dwg1.MaxFlowEdmondsKarp(-1, 1);
  EXPECT_EQ(max_flow, 0.0);// source < size

  max_flow = dwg1.MaxFlowEdmondsKarp(0, -1);
  EXPECT_EQ(max_flow, 0.0);// dest < size

  max_flow = dwg1.MaxFlowEdmondsKarp(1, 1);
  EXPECT_EQ(max_flow, 0.0);// dest == source

  max_flow = dwg1.MaxFlowEdmondsKarp(2, 1);
  EXPECT_EQ(max_flow, 0.0);// source >= size

  max_flow = dwg1.MaxFlowEdmondsKarp(1, 2);
  EXPECT_EQ(max_flow, 0.0);// dest >= size
}
