///
/// \brief Unit tests for greedy algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "algo.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace algo::greedy;

// ///////////////////////////////////////////
// Stable match tests

TEST(Greedy, StableMatchFourCouples)
{
  Prefs m_prefs{
      {4, 1, 2, 3},
      {2, 3, 1, 4},
      {2, 4, 3, 1},
      {3, 1, 4, 2},
  };

  Prefs w_prefs{
      {4, 1, 3, 2},
      {1, 3, 2, 4},
      {1, 2, 3, 4},
      {4, 1, 3, 2},
  };

  std::vector<Match> correct{
      {1, 4},
      {2, 3},
      {3, 2},
      {4, 1},
  };

  auto matches = StableMatching(m_prefs, w_prefs);
  EXPECT_FALSE(matches.empty());
  EXPECT_TRUE(equal(correct.begin(), correct.end(), matches.begin()));
}

TEST(Greedy, StableMathchEightCouples)
{
  Prefs m_prefs{
      {5, 7, 1, 2, 6, 8, 4, 3},// Keep this format
      {2, 3, 7, 5, 4, 1, 8, 6},// Keep this format
      {8, 5, 1, 4, 6, 2, 3, 7},// Keep this format
      {3, 2, 7, 4, 1, 6, 8, 5},// Keep this format
      {7, 2, 5, 1, 3, 6, 8, 4},// Keep this format
      {1, 6, 7, 5, 8, 4, 2, 3},// Keep this format
      {2, 5, 7, 6, 3, 4, 8, 1},// Keep this format
      {3, 8, 4, 5, 7, 2, 6, 1},// Keep this format
  };

  Prefs w_prefs{
      {5, 3, 7, 6, 1, 2, 8, 4},// Keep this format
      {8, 6, 3, 5, 7, 2, 1, 4},// Keep this format
      {1, 5, 6, 2, 4, 8, 7, 3},// Keep this format
      {8, 7, 3, 2, 4, 1, 5, 6},// Keep this format
      {6, 4, 7, 3, 8, 1, 2, 5},// Keep this format
      {2, 8, 5, 3, 4, 6, 7, 1},// Keep this format
      {7, 5, 2, 1, 8, 6, 4, 3},// Keep this format
      {7, 4, 1, 5, 2, 3, 6, 8},// Keep this format
  };

  std::vector<Match> correct{
      {1, 5}, {2, 3}, {3, 8}, {4, 6}, {5, 7}, {6, 1}, {7, 2}, {8, 4},
  };

  auto matches = StableMatching(m_prefs, w_prefs);
  EXPECT_FALSE(matches.empty());
  EXPECT_TRUE(equal(correct.begin(), correct.end(), matches.begin()));
}
