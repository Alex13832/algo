///
/// \brief Unit tests for sort algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "gtest/gtest.h"

#include "search_algorithms.hpp"

#include <algorithm>

using namespace std;
using namespace algo::search;

/////////////////////////////////////////////
/// Binary search
/////////////////////////////////////////////

TEST(test_search_binary, test_not_sorted)
{
  const vector<int> vec{3, 2, 1, 0};
  EXPECT_EQ(Binary(vec, 0), -1);
}

TEST(test_search_binary, test_search)
{
  const vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  EXPECT_EQ(Binary(vec, 8), 8);
}

TEST(test_search_binary, test_search_not_found)
{
  const vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  EXPECT_EQ(Binary(vec, 25), -1);
}

TEST(test_search_binary, test_search_string)
{
  const vector<string> vec{"abba", "bono", "cher", "dion", "eric_c"};
  EXPECT_EQ(Binary(vec, std::string{"cher"}), 2);
}