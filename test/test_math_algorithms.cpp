///
/// \brief Unit tests for sort algorithms.
/// \author alex011235
/// \date 2020-04-17
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "maths_algorithms.hpp"

#include "gtest/gtest.h"
#include "cmath"

#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;
using namespace Algo::Math;
using namespace Algo::Math::Random;

/////////////////////////////////////////////
/// Discrete
/////////////////////////////////////////////

TEST(math_discrete, test_pascals_triangle_zeroth_row)
{
  vector<vector<int>> rows{Discrete::PascalsTriangle(0)};
  EXPECT_EQ(rows.size(), 1);
  int sum{std::accumulate(rows[0].begin(), rows[0].end(), 0)};
  EXPECT_EQ(sum, 1);
}

TEST(math_discrete, test_pascals_triangle_nth_row)
{
  unsigned n{5};
  // The sum of the entries in the nth row of Pascal's triangle is the nth power of 2.
  vector<vector<int>> rows{Discrete::PascalsTriangle(n)};
  int sum{std::accumulate(rows[n].begin(), rows[n].end(), 0)};
  EXPECT_EQ(sum, 1U << n);

  n = 30;
  rows = Discrete::PascalsTriangle(n);
  sum = std::accumulate(rows[n].begin(), rows[n].end(), 0);
  EXPECT_EQ(sum, 1U << n);
}

/////////////////////////////////////////////
/// Random numbers
/////////////////////////////////////////////

///////////////////////////////////
/// Uniform distribution
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
/// Exponential distribution
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

///////////////////////////////////
/// Weibull random numbers
///////////////////////////////////

TEST(math_random_numbers, test_weibull_beta_is_zero)
{
  EXPECT_TRUE(std::isnan(Algo::Math::Random::Weibull(0.0, 1.0)));
}

//TEST(math_random_numbers, test_weibull_exp_similarity)
//{
//  const double lambda{0.5};
//  const double wei{Weibull(lambda, 0.5)};
//  const double exp{Exp(1.0 / std::sqrt(lambda))};
//  EXPECT_DOUBLE_EQ(wei, exp);
//}
