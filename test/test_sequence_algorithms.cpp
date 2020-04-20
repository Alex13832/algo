///
/// \brief Unit tests for sort algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "gtest/gtest.h"

#include "sequence_algorithms.hpp"

#include <algorithm>
#include <cmath>

using namespace std;
using namespace algo::sequence;

TEST(test_long_incr_sub, test_empty)
{
  vector<int> vec{};
  EXPECT_TRUE(LongestIncreasingSub(vec).empty());
}

TEST(test_long_incr_sub, test_single_input)
{
  vector<int> in{1};
  vector<int> ans{1};
  vector<int> out{LongestIncreasingSub(in)};
  EXPECT_TRUE(equal(out.begin(), out.end(), ans.begin()));
}

TEST(test_long_incr_sub, test_standard)
{
  vector<int> in{1, 2, 3, 4, 5, 6, 5, 1, 2, 3, 4, 5, 6, 7, 8, 1};
  vector<int> ans{1, 2, 3, 4, 5, 6, 7, 8};
  vector<int> out{LongestIncreasingSub(in)};
  EXPECT_TRUE(equal(out.begin(), out.end(), ans.begin()));
}

TEST(test_long_incr_sub, test_with_negative)
{
  vector<int> in{1, 2, 3, -3, -2, -1, 0, 1, 2, 0};
  vector<int> ans{-3, -2, -1, 0, 1, 2};
  vector<int> out{LongestIncreasingSub(in)};
  EXPECT_TRUE(equal(out.begin(), out.end(), ans.begin()));
}

TEST(test_long_incr_sub, test_float)
{
  vector<float> in{9.0, 10.0, M_SQRT2, M_E, M_PI, 2.0};
  vector<float> ans{M_SQRT2, M_E, M_PI};
  vector<float> out{LongestIncreasingSub(in)};
  EXPECT_TRUE(equal(out.begin(), out.end(), ans.begin()));
}
