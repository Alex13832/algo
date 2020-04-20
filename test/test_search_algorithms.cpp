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

TEST(test_search_binary, test_search_in_empty)
{
  const vector<int> vec{};
  EXPECT_EQ(Binary(vec, 10), -1);
}

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
  const vector<string> vec{"abba", "bono", "cher", "cher", "dion", "eric_c"};
  EXPECT_EQ(Binary(vec, std::string{"cher"}), 2);
}

/////////////////////////////////////////////
/// Selection min search
/////////////////////////////////////////////

TEST(test_search_k_min, test_search_in_empty)
{
  vector<int> vec{};
  EXPECT_TRUE(SelectionMin(vec, 10).empty());
}

TEST(test_search_k_min, test_search_normal)
{
  vector<int> vec{100, 1000, 2, 20, 10, 5, 4};
  vector<int> answer{2, 4, 5, 10};
  vector<int> found{SelectionMin(vec, 4)};
  EXPECT_TRUE(equal(found.begin(), found.end(), answer.begin()));
}

TEST(test_search_k_min, test_search_overflow)
{
  vector<int> vec{1, 2, 3};
  vector<int> found{SelectionMin(vec, 4)};
  EXPECT_TRUE(equal(found.begin(), found.end(), vec.begin()));
}

/////////////////////////////////////////////
/// Selection max search
/////////////////////////////////////////////

TEST(test_search_k_max, test_search_in_empty)
{
  vector<int> vec{};
  EXPECT_TRUE(SelectionMax(vec, 10).empty());
}

TEST(test_search_k_max, test_search_normal)
{
  vector<int> vec{100, 1000, 2, 20, 10, 5, 4};
  vector<int> answer{1000, 100, 20, 10};
  vector<int> found{SelectionMax(vec, 4)};
  EXPECT_TRUE(equal(found.begin(), found.end(), answer.begin()));
}

TEST(test_search_k_max, test_search_overflow)
{
  vector<int> vec{3, 2, 1};
  vector<int> found{SelectionMax(vec, 4)};
  EXPECT_TRUE(equal(found.begin(), found.end(), vec.begin()));
}
