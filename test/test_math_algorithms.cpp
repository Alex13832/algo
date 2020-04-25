///
/// \brief Unit tests for sort algorithms.
/// \author alex011235
/// \date 2020-04-17
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <functional>
#include <numeric>

#include "cmath"
#include "gtest/gtest.h"
#include "maths_algorithms.hpp"

using namespace std;
using namespace algo::math;
using namespace algo::math::discrete;
using namespace algo::math::random_num;

/////////////////////////////////////////////
/// Discrete
/////////////////////////////////////////////

TEST(math_discrete, test_pascals_triangle_zeroth_row)
{
  vector<vector<int>> rows{discrete::PascalsTriangle(0)};
  EXPECT_EQ(rows.size(), 1);
  int sum{std::accumulate(rows[0].begin(), rows[0].end(), 0)};
  EXPECT_EQ(sum, 1);
}

TEST(math_discrete, test_pascals_triangle_nth_row)
{
  unsigned n{5};
  // The sum of the entries in the nth row of Pascal's triangle is the nth power of 2.
  vector<vector<int>> rows{discrete::PascalsTriangle(n)};
  int sum{std::accumulate(rows[n].begin(), rows[n].end(), 0)};
  EXPECT_EQ(sum, 1U << n);

  n = 30;
  rows = discrete::PascalsTriangle(n);
  sum = std::accumulate(rows[n].begin(), rows[n].end(), 0);
  EXPECT_EQ(sum, 1U << n);
}

TEST(math_discrete, test_clock_angle)
{
  // Test non-valid input
  EXPECT_EQ(ClockAngle(24, 10), -1);
  EXPECT_EQ(ClockAngle(23, 60), -1);
  EXPECT_EQ(ClockAngle(-1, 10), -1);
  EXPECT_EQ(ClockAngle(1, -1), -1);
  // Test valid input
  EXPECT_EQ(ClockAngle(12, 0), 0);
  EXPECT_EQ(ClockAngle(12, 30), 165);
  EXPECT_EQ(ClockAngle(15, 45), 158);
  EXPECT_EQ(ClockAngle(9, 0), 270);
  EXPECT_EQ(ClockAngle(3, 10), 35);
}

TEST(math_discrete, test_knapsack)
{
  vector<int> values{60, 100, 120};
  vector<int> weights{10, 20, 30};
  unsigned capacity{50};
  uint max_load{Knapsack(values, weights, capacity)};
  EXPECT_EQ(max_load, 220);

  values = {10, 40, 30, 50};
  weights = {5, 4, 6, 3};
  capacity = 10;
  max_load = Knapsack(values, weights, capacity);
  EXPECT_EQ(max_load, 90);
}

TEST(math_discrete, test_gcd)
{
  long a{12};
  long b{20};
  EXPECT_EQ(Gcd(a, 0L), a);
  EXPECT_EQ(Gcd(a, a), a);
  EXPECT_EQ(Gcd(a, b), Gcd(a - b, b));
  EXPECT_EQ(Gcd(b, a), Gcd(b, a - b));
  EXPECT_EQ(Gcd(42, 56), 14);
}

TEST(math_discrete, test_lcm)
{
  long a{10};
  long b{20};
  long c{30};
  EXPECT_EQ(Lcm(a, b), Lcm(b, a));
  EXPECT_EQ(Lcm(a, a), a);
  EXPECT_EQ(Lcm(a, Lcm(b, c)), Lcm(Lcm(a, b), c));
  EXPECT_EQ(Lcm(a, Gcd(a, b)), a);
  EXPECT_EQ(Lcm(21L, 6L), 42L);
}

TEST(math_discrete, test_bin)
{
  long n{45};
  long k{68};
  long h{76};
  EXPECT_EQ(Bin(n, k), n / k * Bin(n - 1, k - 1));
  EXPECT_EQ(Bin(n - 1, k) - Bin(n - 1, k - 1), (n - 2 * k) / n * Bin(n, k));
  EXPECT_EQ(Bin(n, h) * Bin(n - h, k), Bin(n, k) * Bin(n - k, h));
  EXPECT_EQ(Bin(n, k), (n + 1 - k) / k * Bin(n, k - 1));
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
    double randu{Uniform(lower, upper)};
    EXPECT_LT(randu, upper);
    EXPECT_GT(randu, lower);
  }
}

TEST(math_random_numbers, test_randu_limits_equal)
{
  const double lower{0.5};
  const double upper{0.5};
  double randu{Uniform(lower, upper)};
  EXPECT_EQ(randu, lower);
}

TEST(math_random_numbers, test_randu_upper_less_than_lower)
{
  const double lower{0.8};
  const double upper{0.5};
  for (size_t i = 0; i < 1000; ++i) {
    double randu{Uniform(lower, upper)};
    EXPECT_LT(randu, lower);
    EXPECT_GT(randu, upper);
  }
}

///////////////////////////////////
/// Exponential distribution
///////////////////////////////////

TEST(math_random_numbers, test_exp_lambda_is_zero)
{
  EXPECT_TRUE(std::isnan(Exp(0.0)));
}

TEST(math_random_numbers, test_exp_lambda_reverse_engineering)
{
  const double lambda{0.5};
  double exp_sum{0.0};
  int runs{100000};

  for (int i = 0; i < runs; i++) {
    double exp{Exp(lambda)};
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
  EXPECT_TRUE(std::isnan(Weibull(0.0, 1.0)));
}

//TEST(math_random_numbers, test_weibull_exp_similarity)
//{
//  const double lambda{0.5};
//  const double wei{Weibull(lambda, 0.5)};
//  const double exp{Exp(1.0 / std::sqrt(lambda))};
//  EXPECT_DOUBLE_EQ(wei, exp);
//}
