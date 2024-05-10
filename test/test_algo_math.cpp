///
/// \brief Unit tests for math algorithms.
/// \author alex011235
/// \date 2020-04-17
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <vector>

#include "cmath"
#include "gtest/gtest.h"
#include "include/algo_math.hpp"

namespace {
namespace mathd = algo::math::discrete;
namespace mathr = algo::math::random_num;
namespace mathp = algo::math::prime;
}  // namespace

/////////////////////////////////////////////
/// Discrete
/////////////////////////////////////////////

TEST(TestAlgoMath, DiscretePascalsTriangleZerothRow) {
  const std::vector<std::vector<int>> rows{mathd::PascalsTriangle(0)};
  EXPECT_EQ(rows.size(), 1);
  const int sum{std::accumulate(rows[0].begin(), rows[0].end(), 0)};
  EXPECT_EQ(sum, 1);
}

TEST(TestAlgoMath, DiscretePascalsTriangleNthRow) {
  int n{5};
  // The sum of the entries in the nth row of Pascal's triangle is the nth power of 2.
  std::vector<std::vector<int>> rows{mathd::PascalsTriangle(n)};
  int sum{std::accumulate(rows[n].begin(), rows[n].end(), 0)};
  EXPECT_EQ(sum, 1U << n);

  n = 30;
  rows = mathd::PascalsTriangle(n);
  sum = std::accumulate(rows[n].begin(), rows[n].end(), 0);
  EXPECT_EQ(sum, 1U << n);
}

TEST(TestAlgoMath, DiscreteClockAngle) {
  // Test non-valid input
  EXPECT_EQ(mathd::ClockAngle(24, 10), -1);
  EXPECT_EQ(mathd::ClockAngle(23, 60), -1);
  EXPECT_EQ(mathd::ClockAngle(-1, 10), -1);
  EXPECT_EQ(mathd::ClockAngle(1, -1), -1);
  // Test valid input
  EXPECT_EQ(mathd::ClockAngle(12, 0), 0);
  EXPECT_EQ(mathd::ClockAngle(12, 30), 165);
  EXPECT_EQ(mathd::ClockAngle(15, 45), 158);
  EXPECT_EQ(mathd::ClockAngle(9, 0), 270);
  EXPECT_EQ(mathd::ClockAngle(3, 10), 35);
}

TEST(TestAlgoMath, DiscreteKnapsack) {
  const mathd::Items items{{60, 10}, {100, 20}, {120, 30}};

  unsigned capacity{50};
  int max_load{Knapsack(items, capacity)};
  EXPECT_EQ(max_load, 220);

  const mathd::Items items1{{10, 5}, {40, 4}, {30, 6}, {50, 3}};

  capacity = 10;
  max_load = Knapsack(items1, capacity);
  EXPECT_EQ(max_load, 90);
}

TEST(TestAlgoMath, DiscreteGcd) {
  const long a{12};
  const long b{20};
  EXPECT_EQ(mathd::GCD(a, 0L), a);
  EXPECT_EQ(mathd::GCD(a, a), a);
  EXPECT_EQ(mathd::GCD(a, b), mathd::GCD(a - b, b));
  EXPECT_EQ(mathd::GCD(b, a), mathd::GCD(b, a - b));
  EXPECT_EQ(mathd::GCD(42, 56), 14);
}

TEST(TestAlgoMath, DiscreteLcm) {
  const long a{10};
  const long b{20};
  const long c{30};
  EXPECT_EQ(mathd::LCM(a, b), mathd::LCM(b, a));
  EXPECT_EQ(mathd::LCM(a, a), a);
  EXPECT_EQ(mathd::LCM(a, mathd::LCM(b, c)), mathd::LCM(mathd::LCM(a, b), c));
  EXPECT_EQ(mathd::LCM(a, mathd::GCD(a, b)), a);
  EXPECT_EQ(mathd::LCM(21L, 6L), 42L);
}

TEST(TestAlgoMath, DiscreteBin) {
  const long n{45};
  const long k{68};
  const long h{76};
  EXPECT_EQ(mathd::BIN(n, k), n / k * mathd::BIN(n - 1, k - 1));
  EXPECT_EQ(mathd::BIN(n - 1, k) - mathd::BIN(n - 1, k - 1), (n - 2 * k) / n * mathd::BIN(n, k));
  EXPECT_EQ(mathd::BIN(n, h) * mathd::BIN(n - h, k), mathd::BIN(n, k) * mathd::BIN(n - k, h));
  EXPECT_EQ(mathd::BIN(n, k), (n + 1 - k) / k * mathd::BIN(n, k - 1));
}

TEST(TestAlgoMath, DiscreteBinCornerCases) {
  EXPECT_EQ(mathd::BIN(1, 0), 1);
  EXPECT_EQ(mathd::BIN(1, 1), 1);
}

TEST(TesgAlgoMath, DiscreteBinStandard) {
  EXPECT_EQ(mathd::BIN(5, 3), 10);
  EXPECT_EQ(mathd::BIN(19, 3), 969);
  EXPECT_EQ(mathd::BIN(9, 8), 9);
}

/////////////////////////////////////////////
/// Random numbers
/////////////////////////////////////////////

template <typename T>
double ComputeStd(std::vector<T> a, double avg) {
  transform(a.begin(), a.end(), a.begin(), [&avg](double x) { return pow(x - avg, 2); });
  const double s{accumulate(a.begin(), a.end(), 0.0)};
  return sqrt(s / a.size());
}

///////////////////////////////////
/// Uniform distribution
///////////////////////////////////

TEST(TestAlgoMath, RandomRanduNormal) {
  const double lower{0.2};
  const double upper{0.5};

  for (size_t i = 0; i < 1000UL; ++i) {
    const double randu{mathr::cont::Uniform(lower, upper)};
    EXPECT_LT(randu, upper);
    EXPECT_GT(randu, lower);
  }
}

TEST(TestAlgoMath, RandomRanduLimitsEqual) {
  const double lower{0.5};
  const double upper{0.5};
  const double randu{mathr::cont::Uniform(lower, upper)};
  EXPECT_EQ(randu, lower);
}

TEST(TestAlgoMath, RandomRanduUpperLessThanLower) {
  const double lower{0.8};
  const double upper{0.5};
  for (size_t i = 0; i < 1000; ++i) {
    const double randu{mathr::cont::Uniform(lower, upper)};
    EXPECT_LT(randu, lower);
    EXPECT_GT(randu, upper);
  }
}

///////////////////////////////////
/// Exponential distribution
///////////////////////////////////

TEST(TestAlgoMath, RandomExpLambdaIsZero) { EXPECT_TRUE(std::isnan(mathr::cont::Exp(0.0))); }

TEST(TestAlgoMath, RandomExpLambdaReverseEngineering) {
  const double lambda{0.5};
  double exp_sum{0.0};
  const int runs{100000};

  for (int i = 0; i < runs; i++) {
    const double exp{mathr::cont::Exp(lambda)};
    exp_sum += exp;
  }

  // Derive lambda
  const double mean{exp_sum / runs};
  const double lambd{1.0 / mean};

  EXPECT_LT(lambd, lambda + 0.01);
  EXPECT_GT(lambd, lambda - 0.01);
}

///////////////////////////////////
/// Weibull random numbers
///////////////////////////////////

TEST(TestAlgoMath, RadnomWeibullBetaIsZero) { EXPECT_TRUE(std::isnan(mathr::cont::Weibull(0.0, 1.0))); }

TEST(TestAlgoMath, RandomWeibullMeanVar) {
  const double lambda{2.0};
  const double k{3.0};
  std::vector<double> a(10000);

  generate(a.begin(), a.end(), [&]() { return mathr::cont::Weibull(lambda, k); });
  double avg{accumulate(a.begin(), a.end(), 0.0)};
  avg /= static_cast<double>(a.size());

  // Compute real mean
  const double mean{lambda * tgamma(1.0 + 1.0 / k)};
  const double s{ComputeStd(a, avg)};

  // Compute real standard deviation
  const double var{lambda * lambda * (tgamma(1.0 + 2.0 / k) - pow(tgamma(1.0 + 1.0 / k), 2))};
  const double std{sqrt(var)};

  // Compare estimation with real, a little deviation is expected.
  EXPECT_GT(avg, 0.9 * mean);
  EXPECT_LT(avg, 1.1 * mean);
  EXPECT_GT(s, 0.9 * std);
  EXPECT_LT(s, 1.1 * std);
}

///////////////////////////////////
/// Normal distribution
///////////////////////////////////

TEST(TestAlgoMath, RandomNormalDistribution01) {
  std::vector<double> a(10000);
  const double mu{0.0};
  const double sigma{1.0};
  // N(0, 1) distributed random values.
  generate(a.begin(), a.end(), [&]() { return mathr::cont::Normal(mu, sigma); });
  double avg{accumulate(a.begin(), a.end(), 0.0)};
  avg /= static_cast<double>(a.size());
  const double s{ComputeStd(a, avg)};

  // Avg should be around 0
  EXPECT_GT(avg, -0.1);
  EXPECT_LT(avg, 0.1);
  // Variance should be around 1
  EXPECT_GT(s, 0.9 * sigma);
  EXPECT_LT(s, 1.1 * sigma);
}

TEST(TestAlgoMath, RandomNormalDistribution23) {
  std::vector<double> a(10000);
  const double mu{2};
  const double sigma{3};
  // N(0, 1) distributed random values.
  generate(a.begin(), a.end(), [&]() { return mathr::cont::Normal(mu, sigma); });
  double avg{accumulate(a.begin(), a.end(), 0.0)};
  avg /= static_cast<double>(a.size());
  const double s{ComputeStd(a, avg)};

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

TEST(TestAlgoMath, RandomBinomialOutOfRange) {
  EXPECT_EQ(mathr::discr::Binomial(4, -0.1), -1);
  EXPECT_EQ(mathr::discr::Binomial(4, 1.1), -1);
}

TEST(TestAlgoMath, RandomBinomial) {
  int n{20};
  double p{0.5};
  const double mean{n * p};
  const double std{sqrt(n * p * (1.0 - p))};

  std::vector<int> a(10000);
  generate(a.begin(), a.end(), [&]() { return mathr::discr::Binomial(n, p); });
  double avg{accumulate(a.begin(), a.end(), 0.0)};
  avg /= static_cast<double>(a.size());
  const double s{ComputeStd(a, avg)};

  EXPECT_GT(avg, 0.9 * mean);
  EXPECT_LT(avg, 1.1 * mean);
  EXPECT_GT(s, 0.9 * std);
  EXPECT_LT(s, 1.1 * std);
}

///////////////////////////////////
/// Poisson distribution
///////////////////////////////////

TEST(TestAlgoMath, RandomPoissonOutOfRange) { EXPECT_EQ(mathr::discr::Poisson(-1), -1); }

TEST(TestAlgoMath, RandomPoisson) {
  int lambda{10};
  std::vector<int> a(10000);
  generate(a.begin(), a.end(), [&lambda]() { return mathr::discr::Poisson(lambda); });
  double avg{accumulate(a.begin(), a.end(), 0.0)};
  avg /= static_cast<double>(a.size());
  const double s{ComputeStd(a, avg)};

  EXPECT_GT(avg, 0.9 * lambda);
  EXPECT_LT(avg, 1.1 * lambda);
  EXPECT_GT(s * s, 0.9 * lambda);
  EXPECT_LT(s * s, 1.1 * lambda);
}

///////////////////////////////////
/// Poisson distribution
///////////////////////////////////

TEST(TestAlgoMath, RandomGeometricOutOfRange) {
  EXPECT_EQ(mathr::discr::Geometric(0.0), -1);
  EXPECT_EQ(mathr::discr::Geometric(1.01), -1);
}

TEST(TestAlgoMath, RandomGeometric) {
  double p{0.3};
  const double mean{(1.0 - p) / p};
  const double std{sqrt((1.0 - p) / (p * p))};
  std::vector<int> a(10000);
  generate(a.begin(), a.end(), [&p]() { return mathr::discr::Geometric(p); });
  double avg{accumulate(a.begin(), a.end(), 0.0)};
  avg /= static_cast<double>(a.size());
  const double s{ComputeStd(a, avg)};

  EXPECT_GT(avg, 0.9 * mean);
  EXPECT_LT(avg, 1.1 * mean);
  EXPECT_GT(s, 0.9 * std);
  EXPECT_LT(s, 1.1 * std);
}

/////////////////////////////////////////////
/// Prime numbers
/////////////////////////////////////////////

TEST(TestAlgoMath, PrimeGetAndIsPrime) {
  EXPECT_TRUE(mathp::IsPrime(1));
  EXPECT_TRUE(mathp::IsPrime(2));
  EXPECT_TRUE(mathp::IsPrime(3));
  EXPECT_TRUE(mathp::IsPrime(971));
  EXPECT_TRUE(mathp::IsPrime(3221L));
  EXPECT_TRUE(mathp::IsPrime(6737L));
  EXPECT_TRUE(mathp::IsPrime(7577));
  EXPECT_TRUE(mathp::IsPrime(7919));

  EXPECT_FALSE(mathp::IsPrime(4));
  EXPECT_FALSE(mathp::IsPrime(10));
  EXPECT_FALSE(mathp::IsPrime(12));
  EXPECT_FALSE(mathp::IsPrime(970));
  EXPECT_FALSE(mathp::IsPrime(3220L));
  EXPECT_FALSE(mathp::IsPrime(6739L));
  EXPECT_FALSE(mathp::IsPrime(7576));
  EXPECT_FALSE(mathp::IsPrime(7918));
}
