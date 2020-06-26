///
/// \brief Unit tests for network algorithms.
/// \author alex011235
/// \date 2020-04-25
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <fstream>
#include <iostream>
#include <numeric>

#include "gtest/gtest.h"
#include "include/algo.hpp"

using namespace std;
using namespace algo::network;

namespace {
const std::string kFilePath{"../../test/testfiles/pagerank/"};
}

/////////////////////////////////////////////
/// PageRank tests
/////////////////////////////////////////////

TEST(test_algo_network, pagerank_4x4)
{
  // This is the transition matrix with probabilities.
  Mat M{{0.0, 0.3333, 0.3333, 0.3333},
        {0.0, 0.0, 0.5, 0.5},
        {1, 0.0, 0.0, 0.0},
        {0.5, 0.0, 0.5, 0.0}};

  Arr rank{PageRank(M, 0.001, 0.8)};
  double sum{accumulate(rank.begin(), rank.end(), 0.0)};
  EXPECT_GT(sum, 0.98);
  EXPECT_LT(sum, 1.02);
}

TEST(test_algo_network, pagerank_5x5_1)
{
  // This is the transition matrix with probabilities.
  Mat M{{0.0, 0.5, 0.5, 0.0, 0.0},
        {0.0, 0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 0.5, 0.5},
        {0.0, 0.0, 0.0, 0.0, 1.0},
        {1.0, 0.0, 0.0, 0.0, 0.0}};

  Arr rank{PageRank(M, 0.001, 0.8)};
  double sum{accumulate(rank.begin(), rank.end(), 0.0)};
  EXPECT_GT(sum, 0.98);
  EXPECT_LT(sum, 1.02);
}

TEST(test_algo_network, pagerank_5x5_deg)
{
  // This is a matrix with link counts.
  Mat M{{0, 1, 0, 0, 0},
        {0, 0, 2, 2, 1},
        {0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0}};

  std::vector<int> deg{1, 5, 1, 1, 2};
  Mat trans{MatTransition(M, deg)};
  Arr rank{PageRank(trans, 0.85, 0.0001)};
  double sum{accumulate(rank.begin(), rank.end(), 0.0)};
  EXPECT_GT(sum, 0.98);
  EXPECT_LT(sum, 1.02);
}

TEST(test_algo_network, pagerank_8x8)
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

  Arr rank{PageRank(M, 0.0001, 0.85)};
  double sum{accumulate(rank.begin(), rank.end(), 0.0)};
  EXPECT_GT(sum, 0.98);
  EXPECT_LT(sum, 1.02);
}

TEST(test_algo_network, pagerank_50)
{
  // Testfile downloaded from http://introcs.cs.princeton.edu/java/16pagerank/
  Mat M(50, std::vector<double>(50, 0));
  M[0][7] = 1;
  M[0][34] = 1;

  M[1][14] = 1;
  M[1][22] = 2;
  M[1][45] = 1;

  M[2][19] = 1;
  M[2][25] = 1;
  M[2][33] = 1;

  M[3][4] = 1;
  M[3][17] = 1;
  M[3][27] = 1;
  M[3][36] = 1;
  M[3][42] = 1;

  M[4][17] = 2;
  M[4][27] = 2;

  M[5][43] = 1;

  M[6][13] = 2;
  M[6][28] = 1;

  M[7][41] = 1;

  M[8][19] = 1;
  M[8][48] = 1;

  M[9][11] = 1;
  M[9][30] = 1;
  M[9][46] = 1;

  M[10][0] = 1;
  M[10][7] = 1;
  M[10][28] = 3;
  M[10][29] = 2;
  M[10][41] = 1;

  M[11][21] = 1;
  M[11][30] = 1;

  M[12][9] = 1;
  M[12][11] = 1;
  M[12][21] = 2;
  M[12][26] = 2;

  M[13][22] = 1;
  M[13][23] = 1;
  M[13][47] = 1;

  M[14][8] = 1;
  M[14][48] = 1;

  M[15][34] = 1;
  M[15][49] = 1;

  M[16][9] = 1;

  M[17][20] = 1;
  M[17][24] = 1;
  M[17][38] = 1;

  M[18][6] = 1;
  M[18][28] = 1;
  M[18][32] = 1;
  M[18][42] = 1;

  M[19][15] = 1;
  M[19][40] = 1;

  M[20][3] = 1;
  M[20][35] = 1;
  M[20][36] = 1;
  M[20][46] = 1;

  M[21][1] = 1;
  M[21][14] = 1;
  M[21][22] = 1;

  M[22][6] = 1;

  M[23][11] = 1;
  M[23][21] = 1;
  M[23][22] = 1;

  M[24][4] = 1;
  M[24][5] = 1;
  M[24][38] = 1;

  M[25][34] = 1;

  M[26][9] = 1;
  M[26][26] = 1;
  M[26][48] = 1;

  M[27][5] = 1;
  M[27][24] = 1;
  M[27][31] = 1;

  M[28][22] = 1;
  M[28][39] = 1;
  M[28][44] = 1;

  M[29][49] = 1;
  M[29][22] = 1;

  M[30][23] = 1;
  M[30][37] = 1;

  M[31][18] = 1;
  M[31][32] = 1;

  M[32][5] = 1;
  M[32][6] = 1;
  M[32][13] = 1;
  M[32][27] = 1;
  M[32][37] = 1;
  M[32][47] = 1;

  M[33][8] = 1;
  M[33][19] = 1;

  M[34][2] = 1;
  M[34][19] = 1;
  M[34][40] = 1;

  M[35][9] = 1;
  M[35][46] = 1;

  M[36][42] = 1;

  M[37][5] = 1;
  M[37][9] = 1;
  M[37][35] = 2;
  M[37][47] = 1;

  M[38][35] = 1;
  M[38][37] = 1;

  M[39][18] = 1;
  M[39][42] = 1;

  M[40][15] = 1;

  M[41][28] = 1;
  M[41][44] = 1;

  M[42][31] = 1;

  M[43][24] = 1;
  M[43][37] = 1;
  M[43][38] = 1;

  M[44][7] = 1;
  M[44][39] = 1;

  M[45][8] = 1;
  M[45][14] = 2;
  M[45][15] = 1;
  M[45][49] = 1;

  M[46][16] = 1;

  M[47][23] = 1;
  M[47][30] = 1;

  M[48][12] = 1;
  M[48][21] = 1;
  M[48][33] = 2;

  M[49][1] = 1;
  M[49][34] = 1;
  M[49][22] = 1;

  std::vector<int> deg{2, 4, 3, 5, 4, 1, 3, 1, 2, 3, 8, 2, 6, 3, 2, 2, 1, 3, 4, 2, 4, 3, 1, 3, 3, 1, 3, 3, 3, 2, 2, 2, 6, 2, 3, 2, 1, 5, 2, 2, 1, 2, 1, 3, 2, 5, 1, 2, 4, 3};
  Mat p{MatTransition(M, deg)};
  Arr rank{PageRank(p, 0.0001, 0.85)};
  double sum{accumulate(rank.begin(), rank.end(), 0.0)};
  EXPECT_GT(sum, 0.98);
  EXPECT_LT(sum, 1.02);
}
