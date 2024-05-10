///
/// \brief Unit tests for sequence algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"
#include "include/algo_sequence.hpp"

namespace {
namespace seq = algo::sequence;
}  // namespace

/////////////////////////////////////////////
/// Longest increasing sub sequence tests
/////////////////////////////////////////////

TEST(TestAlgoSequence, LongestIncrSubseqEmpty) {
  const std::vector<int> vec{};
  EXPECT_TRUE(seq::LongestIncreasingSub(vec).empty());
}

TEST(TestAlgoSequence, LongestIncrSubseqSingleInput) {
  const std::vector<int> in{1};
  std::vector<int> ans{1};
  std::vector<int> out{seq::LongestIncreasingSub(in)};
  EXPECT_TRUE(equal(out.begin(), out.end(), ans.begin()));
}

TEST(TestAlgoSequence, LongestIncrSubseqStandard) {
  const std::vector<int> in{1, 2, 3, 4, 5, 6, 5, 1, 2, 3, 4, 5, 6, 7, 8, 1};
  std::vector<int> ans{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> out{seq::LongestIncreasingSub(in)};
  EXPECT_TRUE(equal(out.begin(), out.end(), ans.begin()));
}

TEST(TestAlgoSequence, LongestIncrSubseqWithNegative) {
  const std::vector<int> in{1, 2, 3, -3, -2, -1, 0, 1, 2, 0};
  std::vector<int> ans{-3, -2, -1, 0, 1, 2};
  std::vector<int> out{seq::LongestIncreasingSub(in)};
  EXPECT_TRUE(equal(out.begin(), out.end(), ans.begin()));
}

TEST(TestAlgoSequence, LongestIncrSubseqFloat) {
  const std::vector<float> in{9.0, 10.0, 1.42, 2.7, 3.14, 2.0};
  std::vector<float> ans{1.42, 2.7, 3.14};
  std::vector<float> out{seq::LongestIncreasingSub(in)};
  EXPECT_TRUE(equal(out.begin(), out.end(), ans.begin()));
}

/////////////////////////////////////////////
/// Test max subarray
/////////////////////////////////////////////

TEST(TestAlgoSequence, MaxSubArrayTestEmpty) {
  const std::vector<int> vec{};
  EXPECT_EQ(seq::MaxSubarray(vec), 0);
}

TEST(TestAlgoSequence, MaxSubArrayTestOneElement) {
  const std::vector<int> vec{1};
  EXPECT_EQ(seq::MaxSubarray(vec), 1);
}

TEST(TestAlgoSequence, MaxSubArrayTestOnlyIncreasing) {
  std::vector<int> vec{1, 2, 3, 4, 5, 6};
  const int sum{accumulate(vec.begin(), vec.end(), 0)};
  EXPECT_EQ(seq::MaxSubarray(vec), sum);
}

TEST(TestAlgoSequence, MaxSubArrayTestDecreasing) {
  std::vector<int> vec{7, 6, 5, 4, 3, 2, 1};
  const int sum{accumulate(vec.begin(), vec.end(), 0)};
  EXPECT_EQ(seq::MaxSubarray(vec), sum);
}

TEST(TestAlgoSequence, MaxSubArrayTestStandard) {
  const std::vector<int> vec{-5, 5, 5, 5, -5, -5, -5, 5, 5, 5, 5, -5};
  EXPECT_EQ(seq::MaxSubarray(vec), 20);
}
