///
/// \brief Unit tests for sort algorithms.
/// \author alex011235
/// \date 2020-04-17
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "gtest/gtest.h"

#include "maths_algorithms.hpp"

/////////////////////////////////////////////
/// Random numbers
/////////////////////////////////////////////

///////////////////////////////////
/// Uniform random numbers
///////////////////////////////////

TEST(math_random_numbers, test_randu_normal)
{
  const double lower{0.2};
  const double upper{0.5};

  for (size_t i = 0; i < 1000; ++i) {
    double randu{Algo::Math::Random::Uniform(lower, upper)};
    EXPECT_LT(randu, upper);
    EXPECT_GT(randu, lower);
  }
}

TEST(math_random_numbers, test_randu_limits_equal)
{
  const double lower{0.5};
  const double upper{0.5};
  double randu{Algo::Math::Random::Uniform(lower, upper)};
  EXPECT_EQ(randu, lower);
}

TEST(math_random_numbers, test_randu_upper_less_than_lower)
{
  const double lower{0.8};
  const double upper{0.5};
  for (size_t i = 0; i < 1000; ++i) {
    double randu{Algo::Math::Random::Uniform(lower, upper)};
    EXPECT_LT(randu, lower);
    EXPECT_GT(randu, upper);
  }
}