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
const std::string path{"../../test/testfiles/prims/"};
}

/////////////////////////////////////////////
/// Graph functions tests
/////////////////////////////////////////////

TEST(test_algo_graph, test_make_edge_weight)
{
  Graph graph{NewGraph(2)};

  EXPECT_TRUE(MakeEdge(graph, 0, 1, 1));
  EXPECT_TRUE(MakeEdge(graph, 1, 0, 1));

  EXPECT_FALSE(MakeEdge(graph, 0, 0, 1));// Trying to add with same node ids.
  EXPECT_FALSE(MakeEdge(graph, 1, 1, 1));
  EXPECT_FALSE(MakeEdge(graph, 2, 1, 1));// Trying to add to a missing node.
  EXPECT_FALSE(MakeEdge(graph, 1, 2, 1));
}

TEST(test_algo_graph, test_make_edge_no_weight)
{
  Graph graph{NewGraph(2)};

  EXPECT_TRUE(MakeEdge(graph, 0, 1));
  EXPECT_TRUE(MakeEdge(graph, 1, 0));
  EXPECT_TRUE(MakeEdge(graph, 0, 0));
  EXPECT_TRUE(MakeEdge(graph, 1, 1));

  EXPECT_FALSE(MakeEdge(graph, 2, 1));
  EXPECT_FALSE(MakeEdge(graph, 1, 2));
}

TEST(test_algo_graph, test_make_dir_edge_weight)
{
  Graph graph(2);
  EXPECT_TRUE(MakeDirEdge(graph, 0, 1, 1));
  EXPECT_TRUE(MakeDirEdge(graph, 1, 0, 1));
  EXPECT_TRUE(MakeDirEdge(graph, 0, 0, 1));
  EXPECT_TRUE(MakeDirEdge(graph, 1, 1, 1));

  EXPECT_FALSE(MakeDirEdge(graph, 2, 1, 1));
  EXPECT_FALSE(MakeDirEdge(graph, 1, 2, 1));
}

TEST(test_algo_graph, test_make_dir_edge_no_weight)
{
  Graph graph{NewGraph(2)};

  EXPECT_TRUE(MakeDirEdge(graph, 0, 1));
  EXPECT_TRUE(MakeDirEdge(graph, 1, 0));
  EXPECT_TRUE(MakeDirEdge(graph, 0, 0));
  EXPECT_TRUE(MakeDirEdge(graph, 1, 1));

  EXPECT_FALSE(MakeDirEdge(graph, 2, 1));
  EXPECT_FALSE(MakeDirEdge(graph, 1, 2));
}

/////////////////////////////////////////////
/// Prim's algorithm tests
/////////////////////////////////////////////

TEST(tst_algo_graph, test_prims_forbidden)
{
  Graph G1{NewGraph(7)};
  int total_weight{0};
  EXPECT_TRUE(MinimumSpanningTree(G1, 7, total_weight).empty());

  EXPECT_TRUE(MinimumSpanningTree(G1, -1, total_weight).empty());

  Graph G2{NewGraph(0)};
  EXPECT_TRUE(MinimumSpanningTree(G2, 0, total_weight).empty());
}

TEST(test_algo_graph, test_prims_simple)
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

  int total_weight{0};
  Graph gmst{MinimumSpanningTree(G, 0, total_weight)};

  EXPECT_EQ(total_weight, 93);
}

//Test-case file is downloaded from "Project Euler", problem 107
Graph ReadPrimsFile()
{
  Graph G{NewGraph(40)};
  vector<int> total;
  ifstream infile(path + "p107_network.txt");
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

TEST(test_algo_graph, test_prims_project_euler_107)
{
  Graph G{ReadPrimsFile()};
  int total_weight{0};
  Graph gmst{MinimumSpanningTree(G, 0, total_weight)};

  int ans = 261832 - total_weight;

  EXPECT_EQ(ans, 259679);
}