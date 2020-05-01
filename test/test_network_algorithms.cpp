///
/// \brief Unit tests for network algorithms.
/// \author alex011235
/// \date 2020-04-25
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <fstream>
#include <iostream>
#include <numeric>

#include "gtest/gtest.h"
#include "include/algo_network.hpp"

using namespace std;
using namespace algo::network;

namespace {
const std::string path{"../../test/testfiles/pagerank/"};
}

/////////////////////////////////////////////
/// PageRank tests
/////////////////////////////////////////////

TEST(test_network_pagerank, test_4x4)
{
  // This is the transition matrix with probabilities.
  Mat M{{0.0, 0.3333, 0.3333, 0.3333},
        {0.0, 0.0, 0.5, 0.5},
        {1, 0.0, 0.0, 0.0},
        {0.5, 0.0, 0.5, 0.0}};

  Arr rank{PageRank(M, 0.8, 0.001)};
  double sum{accumulate(rank.begin(), rank.end(), 0.0)};
  EXPECT_TRUE(sum > 0.99 && sum < 1.01);
}

TEST(test_network_pagerank, test_5x5_1)
{
  // This is the transition matrix with probabilities.
  Mat M{{0.0, 0.5, 0.5, 0.0, 0.0},
        {0.0, 0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 0.5, 0.5},
        {0.0, 0.0, 0.0, 0.0, 1.0},
        {1.0, 0.0, 0.0, 0.0, 0.0}};

  Arr rank{PageRank(M, 0.8, 0.001)};
  double sum{accumulate(rank.begin(), rank.end(), 0.0)};
  EXPECT_TRUE(sum > 0.99 && sum < 1.01);
}

TEST(test_network_pagerank, test_5x5_deg)
{
  // This is a matrix with link counts.
  Mat M{{0, 1, 0, 0, 0},
        {0, 0, 2, 2, 1},
        {0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0}};

  Arr deg = {1, 5, 1, 1, 2};
  Mat trans{MatTransition(M, deg)};
  Arr rank{PageRank(trans, 0.85, 0.0001)};
  double sum{accumulate(rank.begin(), rank.end(), 0.0)};
  EXPECT_TRUE(sum > 0.99 && sum < 1.01);
}

TEST(test_network_pagerank, test_8x8)
{
  // This is the transition matrix with probabilities.
  Mat M{{0.0, 0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 1, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.5, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0},
        {0.0, 0.3333, 0.0, 0.0, 0.3333, 0.3333, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.3333, 0.3333, 0.3333},
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0},
        {0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.5},
        {0.0, 0.0, 0.0, 0.0, 0, 0.5, 0.5, 0.0}};

  Arr rank{PageRank(M, 0.85, 0.0001)};
  double sum{accumulate(rank.begin(), rank.end(), 0.0)};
  EXPECT_TRUE(sum > 0.99 && sum < 1.01);
}

TEST(test_network_pagerank, test_50)
{
  // Testfile downloaded from http://introcs.cs.princeton.edu/java/16pagerank/
  // This test use link counts.
  ifstream infile(path + "medium.txt");
  string line;
  int num = 0;
  getline(infile, line);
  size_t N = stoi(line);

  Mat M(N, Arr(N));
  Arr degree(N);

  while (getline(infile, line)) {
    vector<int> temp;
    string s = line;
    string delimiter = " ";
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
      token = s.substr(0, pos);
      try {

        num = stoi(token);
        temp.push_back(num);

      } catch (std::invalid_argument&) {
      }
      s.erase(0, pos + delimiter.length());
    }

    try {
      temp.push_back(stod(s));
    } catch (std::invalid_argument& e) {
      cout << e.what() << endl;
    }

    for (size_t i = 0; i < temp.size(); i += 2) {
      M[temp[i]][temp[i + 1]]++;
    }
  }

  for (size_t i = 0; i < N; i++) {
    degree[i] = accumulate(M[i].begin(), M[i].end(), 0.0);
  }

  Mat p = MatTransition(M, degree);
  Arr rank = PageRank(p, 0.85, 0.0001);
  double sum = accumulate(rank.begin(), rank.end(), 0.0);
  EXPECT_TRUE(sum > 0.99 && sum < 1.01);
}