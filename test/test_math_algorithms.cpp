///
/// \brief Unit tests for math algorithms.
/// \author alex011235
/// \date 2020-04-17
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <functional>
#include <numeric>

#include "cmath"
#include "gtest/gtest.h"
#include "include/algo_math.hpp"

using namespace std;
using namespace algo::math;
using namespace algo::math::discrete;
using namespace algo::math::random_num;
using namespace algo::math::prime;

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
  long a{12}, b{20};
  EXPECT_EQ(Gcd(a, 0L), a);
  EXPECT_EQ(Gcd(a, a), a);
  EXPECT_EQ(Gcd(a, b), Gcd(a - b, b));
  EXPECT_EQ(Gcd(b, a), Gcd(b, a - b));
  EXPECT_EQ(Gcd(42, 56), 14);
}

TEST(math_discrete, test_lcm)
{
  long a{10}, b{20}, c{30};
  EXPECT_EQ(Lcm(a, b), Lcm(b, a));
  EXPECT_EQ(Lcm(a, a), a);
  EXPECT_EQ(Lcm(a, Lcm(b, c)), Lcm(Lcm(a, b), c));
  EXPECT_EQ(Lcm(a, Gcd(a, b)), a);
  EXPECT_EQ(Lcm(21L, 6L), 42L);
}

TEST(math_discrete, test_bin)
{
  long n{45}, k{68}, h{76};
  EXPECT_EQ(Bin(n, k), n / k * Bin(n - 1, k - 1));
  EXPECT_EQ(Bin(n - 1, k) - Bin(n - 1, k - 1), (n - 2 * k) / n * Bin(n, k));
  EXPECT_EQ(Bin(n, h) * Bin(n - h, k), Bin(n, k) * Bin(n - k, h));
  EXPECT_EQ(Bin(n, k), (n + 1 - k) / k * Bin(n, k - 1));
}

/////////////////////////////////////////////
/// Random numbers
/////////////////////////////////////////////

template<typename T>
double ComputeStd(vector<T> a, double avg)
{
  transform(a.begin(), a.end(), a.begin(), [&avg](double x) { return pow(x - avg, 2); });
  double s{accumulate(a.begin(), a.end(), 0.0)};
  return sqrt(s / a.size());
}

///////////////////////////////////
/// Uniform distribution
///////////////////////////////////

TEST(math_random_numbers, test_randu_normal)
{
  const double lower{0.2};
  const double upper{0.5};

  for (size_t i = 0; i < 1000; ++i) {
    double randu{cont::Uniform(lower, upper)};
    EXPECT_LT(randu, upper);
    EXPECT_GT(randu, lower);
  }
}

TEST(math_random_numbers, test_randu_limits_equal)
{
  const double lower{0.5};
  const double upper{0.5};
  double randu{cont::Uniform(lower, upper)};
  EXPECT_EQ(randu, lower);
}

TEST(math_random_numbers, test_randu_upper_less_than_lower)
{
  const double lower{0.8};
  const double upper{0.5};
  for (size_t i = 0; i < 1000; ++i) {
    double randu{cont::Uniform(lower, upper)};
    EXPECT_LT(randu, lower);
    EXPECT_GT(randu, upper);
  }
}

///////////////////////////////////
/// Exponential distribution
///////////////////////////////////

TEST(math_random_numbers, test_exp_lambda_is_zero)
{
  EXPECT_TRUE(std::isnan(cont::Exp(0.0)));
}

TEST(math_random_numbers, test_exp_lambda_reverse_engineering)
{
  const double lambda{0.5};
  double exp_sum{0.0};
  int runs{100000};

  for (int i = 0; i < runs; i++) {
    double exp{cont::Exp(lambda)};
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
  EXPECT_TRUE(std::isnan(cont::Weibull(0.0, 1.0)));
}

TEST(math_random_numbers, test_weibull_mean_var)
{
  double lambda{2.0}, k{3.0};
  vector<double> a(10000);

  generate(a.begin(), a.end(), [&]() { return cont::Weibull(lambda, k); });
  double avg{accumulate(a.begin(), a.end(), 0.0)};
  avg /= a.size();

  // Compute real mean
  double mean{lambda * tgamma(1.0 + 1.0 / k)};
  double s{ComputeStd(a, avg)};

  // Compute real standard deviation
  double var{lambda * lambda * (tgamma(1.0 + 2.0 / k) - pow(tgamma(1.0 + 1.0 / k), 2))};
  double std{sqrt(var)};

  // Compare estimation with real, a little deviation is expected.
  EXPECT_GT(avg, 0.9 * mean);
  EXPECT_LT(avg, 1.1 * mean);
  EXPECT_GT(s, 0.9 * std);
  EXPECT_LT(s, 1.1 * std);
}

///////////////////////////////////
/// Normal distribution
///////////////////////////////////

TEST(math_random_numbers, test_normal_distribution_0_1)
{
  vector<double> a(10000);
  double mu{0.0}, sigma{1.0};
  // N(0, 1) distributed random values.
  generate(a.begin(), a.end(), [&]() { return cont::Normal(mu, sigma); });
  double avg{accumulate(a.begin(), a.end(), 0.0)};
  avg /= a.size();
  double s{ComputeStd(a, avg)};

  // Avg should be around 0
  EXPECT_GT(avg, -0.1);
  EXPECT_LT(avg, 0.1);
  // Variance should be around 1
  EXPECT_GT(s, 0.9 * sigma);
  EXPECT_LT(s, 1.1 * sigma);
}

TEST(math_random_numbers, test_normal_distribution_2_3)
{
  vector<double> a(10000);
  double mu{2}, sigma{3};
  // N(0, 1) distributed random values.
  generate(a.begin(), a.end(), [&]() { return cont::Normal(mu, sigma); });
  double avg{accumulate(a.begin(), a.end(), 0.0)};
  avg /= a.size();
  double s{ComputeStd(a, avg)};

  // Avg should be around 2
  EXPECT_GT(avg, 0.9 * mu);
  EXPECT_LT(avg, 1.1 * mu);
  // Variance should be around 3
  EXPECT_GT(s, 0.9 * sigma);
  EXPECT_LT(s, 1.1 * sigma);
}

///////////////////////////////////
/// Binomial distribution
///////////////////////////////////

TEST(math_random_numbers, test_binomial_out_of_range)
{
  EXPECT_EQ(discr::Binomial(4, -0.1), -1);
  EXPECT_EQ(discr::Binomial(4, 1.1), -1);
}

TEST(math_random_numbers, test_binomial)
{
  int n{20};
  double p{0.5};
  double mean{n * p};
  double std{sqrt(n * p * (1.0 - p))};

  vector<int> a(10000);
  generate(a.begin(), a.end(), [&]() { return discr::Binomial(n, p); });
  double avg{accumulate(a.begin(), a.end(), 0.0)};
  avg /= a.size();
  double s{ComputeStd(a, avg)};

  EXPECT_GT(avg, 0.9 * mean);
  EXPECT_LT(avg, 1.1 * mean);
  EXPECT_GT(s, 0.9 * std);
  EXPECT_LT(s, 1.1 * std);
}

///////////////////////////////////
/// Poisson distribution
///////////////////////////////////

TEST(math_random_numbers, test_poisson_out_of_range)
{
  EXPECT_EQ(discr::Poisson(-1), -1);
}

TEST(math_random_numbers, test_poisson)
{
  int lambda{10};
  vector<int> a(10000);
  generate(a.begin(), a.end(), [&lambda]() { return discr::Poisson(lambda); });
  double avg{accumulate(a.begin(), a.end(), 0.0)};
  avg /= a.size();
  double s{ComputeStd(a, avg)};

  EXPECT_GT(avg, 0.9 * lambda);
  EXPECT_LT(avg, 1.1 * lambda);
  EXPECT_GT(s * s, 0.9 * lambda);
  EXPECT_LT(s * s, 1.1 * lambda);
}

///////////////////////////////////
/// Poisson distribution
///////////////////////////////////

TEST(math_random_numbers, test_geometric_out_of_range)
{
  EXPECT_EQ(discr::Geometric(0.0), -1);
  EXPECT_EQ(discr::Geometric(1.01), -1);
}

TEST(math_random_numbers, test_geometric)
{
  double p{0.3};
  double mean{(1.0 - p) / p};
  double std{sqrt((1.0 - p) / (p * p))};
  vector<int> a(10000);
  generate(a.begin(), a.end(), [&p]() { return discr::Geometric(p); });
  double avg{accumulate(a.begin(), a.end(), 0.0)};
  avg /= a.size();
  double s{ComputeStd(a, avg)};

  EXPECT_GT(avg, 0.9 * mean);
  EXPECT_LT(avg, 1.1 * mean);
  EXPECT_GT(s, 0.9 * std);
  EXPECT_LT(s, 1.1 * std);
}

/////////////////////////////////////////////
/// Prime numbers
/////////////////////////////////////////////

TEST(math_prime_numbers, test_get_and_is_prime)
{
  EXPECT_TRUE(IsPrime(1));
  EXPECT_TRUE(IsPrime(2));
  EXPECT_TRUE(IsPrime(3));
  EXPECT_TRUE(IsPrime(971));
  EXPECT_TRUE(IsPrime(3221L));
  EXPECT_TRUE(IsPrime(6737L));
  EXPECT_TRUE(IsPrime(7577));
  EXPECT_TRUE(IsPrime(7919));

  EXPECT_FALSE(IsPrime(4));
  EXPECT_FALSE(IsPrime(10));
  EXPECT_FALSE(IsPrime(12));
  EXPECT_FALSE(IsPrime(970));
  EXPECT_FALSE(IsPrime(3220L));
  EXPECT_FALSE(IsPrime(6739L));
  EXPECT_FALSE(IsPrime(7576));
  EXPECT_FALSE(IsPrime(7918));
}
