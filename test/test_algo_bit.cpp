///
/// \brief Unit tests for bit algorithms.
/// \author alex011235
/// \date 2020-08-02
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <climits>

#include "gtest/gtest.h"
#include "include/algo_bit.hpp"

TEST(TestAlgoBit, TestSignof) {
  EXPECT_EQ(algo::bit::Sign(-1), -1);
  EXPECT_EQ(algo::bit::Sign(0), 0);
  EXPECT_EQ(algo::bit::Sign(1), 0);
  EXPECT_EQ(algo::bit::Sign(-7897987), -1);
  EXPECT_EQ(algo::bit::Sign(545646545), 0);
  EXPECT_EQ(algo::bit::Sign(LONG_MIN), -1);
  EXPECT_EQ(algo::bit::Sign(ULONG_MAX), 0);
  EXPECT_EQ(algo::bit::Sign(CHAR_MAX), 0);
  EXPECT_EQ(algo::bit::Sign(LONG_LONG_MAX), 0);
}

TEST(TestAlgoBit, TestIsEven) {
  EXPECT_EQ(algo::bit::IsEven(0), true);
  EXPECT_EQ(algo::bit::IsEven(1), false);
  EXPECT_EQ(algo::bit::IsEven(2), true);
  EXPECT_EQ(algo::bit::IsEven(2 << 10), true);
  EXPECT_EQ(algo::bit::IsEven(-1), false);
  EXPECT_EQ(algo::bit::IsEven(-2), true);
  EXPECT_EQ(algo::bit::IsEven(LONG_MIN), true);
  EXPECT_EQ(algo::bit::IsEven(LONG_MAX - 1), true);
}

TEST(TestAlgoBit, TestSetBit) {
  EXPECT_EQ(algo::bit::SetBit(0, 3, true), 8);
  EXPECT_EQ(algo::bit::SetBit(0, 30, true), 1073741824);
  EXPECT_EQ(algo::bit::SetBit(0, 0, true), 1);
  EXPECT_EQ(algo::bit::SetBit(1, 0, false), 0);
  EXPECT_EQ(algo::bit::SetBit(0xFFFFF, 15, false), 0xF7FFF);
  EXPECT_EQ(algo::bit::SetBit(0xF7FFF, 3, false), 0xF7FF7);
}

TEST(TestAlgoBit, TestIsBit) {
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 15), true);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 14), false);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 13), true);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 12), false);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 11), true);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 10), false);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 9), true);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 8), false);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 7), true);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 6), false);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 5), true);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 4), false);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 3), true);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 2), false);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 1), true);
  EXPECT_EQ(algo::bit::IsBit(0xAAAA, 0), false);
}

TEST(TestAlgoBit, TestToggleBit) {
  EXPECT_EQ(algo::bit::ToggleBit(0xBBBB, 14), 0xFBBB);
  EXPECT_EQ(algo::bit::ToggleBit(0xFBBB, 14), 0xBBBB);
}

TEST(TestAlgoBit, TestIsPow2) {
  EXPECT_EQ(algo::bit::IsPow2(2 << 10), true);
  EXPECT_EQ(algo::bit::IsPow2(256), true);
  EXPECT_EQ(algo::bit::IsPow2((2 << 12) - 1), false);
}

TEST(TestAlgoBit, TestNextPow2) {
  EXPECT_EQ(algo::bit::NextPow2(1), 1);
  EXPECT_EQ(algo::bit::NextPow2(3), 4);
  EXPECT_EQ(algo::bit::NextPow2(5), 8);
  EXPECT_EQ(algo::bit::NextPow2(513), 1024);
  EXPECT_EQ(algo::bit::NextPow2(1025), 2048);
  EXPECT_EQ(algo::bit::NextPow2((1 << 12) + 1), 1 << 13);
}

TEST(TestAlgoBit, TestCountSetBits) {
  EXPECT_EQ(algo::bit::CountSetBits(0b1010101), 4);
  EXPECT_EQ(algo::bit::CountSetBits(0xFF), 8);
  EXPECT_EQ(algo::bit::CountSetBits(0), 0);
}

TEST(TestAlgoBit, TestSwapBits) {
  EXPECT_EQ(algo::bit::SwapBits(0b101010), 0b010101);
  EXPECT_EQ(algo::bit::SwapBits(0b111000), 0b000111);
  EXPECT_EQ(algo::bit::SwapBits(0b111111), 0);
  EXPECT_EQ(algo::bit::SwapBits(170), 85);
  EXPECT_EQ(algo::bit::SwapBits(1), 0);
  EXPECT_EQ(algo::bit::SwapBits(0), 1);
}
