///
/// \brief Header for bit algorithms.
/// \author alex011235
/// \date 2020-08-02
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#ifndef ALGO_ALGO_INCLUDE_ALGO_BIT_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_BIT_HPP_

#include <cmath>

/////////////////////////////////////////////
// Legend:
// &     And
// ^     Exclusive or
// |     or
// ~     not (exclude)
/////////////////////////////////////////////

namespace algo::bit {

enum class Bit {
  False = 0,
  True = 1
};

/// \brief Returns the sign (+-) of x, 0 if positive, -1 if negative.
constexpr auto Sign = [](const auto& x) {
  return -(x < 0);
};

/// \brief Returns true if x is even.
constexpr auto IsEven = [](const auto& x) {
  return (x & 1) == 0;
};

/// \brief Sets bit n in x to either true or false (1/0).
constexpr auto SetBit = [](const auto& x, const auto& n, const Bit& b) {
  if (b == Bit::False) {
    return (x & ~(1 << n));
  }
  return (x | (1 << n));
};

/// \brief Tests if bit n in x is 1.
constexpr auto IsBit = [](const auto& x, const auto& n) {
  return (x & (1 << n)) > 0;
};

/// \brief Changes a bit 0 to 1 or 1 to 0 at position n.
constexpr auto ToggleBit = [](const auto& x, const auto& n) {
  return (x ^ (1 << n));
};

/// \brief Returns true of x is a power of 2, e.g. 2^3 = 8.
constexpr auto IsPow2 = [](const auto& x) {
  return x && !(x & (x - 1));
};

/// \brief Returns the next power of 2, e.g NextPow2(2^3 + 1 = 9) == 2^4 = 16.
constexpr auto NextPow2 = [](auto x) {
  decltype(x) count = 0;
  if (x && !(x & (x - 1))) { return x; }
  while (x != 0) {
    x >>= 1;
    count++;
  }
  return static_cast<decltype(x)>(1) << count;
};

/// \brief Counts the number of set bits in x, e.g. (Using binary number) CountSetBits(10101) == 3.
/// \link <a href="https://www.tutorialspoint.com/c-cplusplus-program-to-count-set-bits-in-an-integer">Algorithm, TutorialsPoint.</a>
constexpr auto CountSetBits = [](auto x) {
  decltype(x) count = 0;
  while (x != 0) {
    if ((x & 1) == 1) {
      count++;
    }
    x = x >> 1;
  }
  return count;
};

/// \brief Swaps the bits in x, e.g. 1010 -> 0101.
constexpr auto SwapBits = [](const auto& x) {
  if (x == 0) { return 1; }
  if (x == 1) { return 0; }
  decltype(x) n = NextPow2(x);
  return x ^ (n - 1);
};

}// namespace algo::bit

#endif//ALGO_ALGO_INCLUDE_ALGO_BIT_HPP_
