///
/// \brief Unit tests for sort algorithms.
/// \author alex011235
/// \date 2020-04-17
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "gtest/gtest.h"
#include "cmath"

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

///////////////////////////////////
/// Exponentially random numbers
///////////////////////////////////

TEST(math_random_numbers, test_exp_lambda_is_zero)
{
  EXPECT_TRUE(std::isnan(Algo::Math::Random::Exp(0.0)));
}

TEST(math_random_numbers, test_exp_lambda_reverse_engineering)
{
  const double lambda{0.5};
  double exp_sum{0.0};
  int runs{100000};

  for (int i = 0; i < runs; i++) {
    double exp{Algo::Math::Random::Exp(lambda)};
    exp_sum += exp;
  }

  // Derive lambda
  double mean{exp_sum / runs};
  double lambd{1.0 / mean};

  EXPECT_LT(lambd, lambda + 0.01);
  EXPECT_GT(lambd, lambda - 0.01);
}
