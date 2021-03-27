///
/// \brief Source file for math algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_math.hpp"

#include <chrono>
#include <cmath>
#include <random>

/////////////////////////////////////////////
/// Discrete
/////////////////////////////////////////////

namespace algo::math::discrete {

PTriangle PascalsTriangle(int depth)
{
  PTriangle rows{};

  for (int line = 1; line <= depth + 1; line++) {
    std::vector<int> row{};
    unsigned int C{1};

    for (int i = 1; i <= line; i++) {
      row.emplace_back(C);
      C = C * (line - i) / i;
    }

    rows.emplace_back(row);
  }
  return rows;
}

int ClockAngle(int h, int m)
{
  if (h < 0 || m < 0 || h > 23 || m > 59) {
    return -1;
  }

  int hour_angle{((h % 12) * 60 + m) / 2};
  int minute_angle{6 * m};
  int angle{std::abs(hour_angle - minute_angle)};
  return angle;
}

int Knapsack(const Items& items, unsigned capacity)
{
  size_t n{items.size()};
  std::vector<std::vector<int>> m(n + 1, std::vector<int>(capacity + 1, 0));

  for (size_t i = 1; i <= n; i++) {
    for (size_t j = 0; j <= capacity; j++) {
      if (items[i - 1].weight <= static_cast<int>(j)) {
        m[i][j] = std::max(m[i - 1][j], m[i - 1][j - items[i - 1].weight] + items[i - 1].value);
      } else {
        m[i][j] = m[i - 1][j];
      }
    }
  }
  return m[n][capacity];
}
}// namespace algo::math::discrete

/////////////////////////////////////////////
/// Random numbers
/////////////////////////////////////////////

namespace algo::math::random_num {

namespace cont {

double Uniform(double a, double b)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed);//Mersenne twister
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(generator);
}

double Random()
{
  return Uniform(0.0, 1.0);
}

double Exp(double lambda)
{
  if (lambda == 0.0) {
    return NAN;
  }
  const double x{Random()};
  return -std::log(1.0 - x) / lambda;
}

double Normal(double mu, double sigma)
{
  double r1{Random()};
  double r2{Random()};
  return mu + sigma * cos(2 * M_PI * r1) * sqrt(-2.0 * log(r2));
}

double Weibull(double lambda, double k)
{
  if (lambda == 0.0) {
    return NAN;
  }

  const double u{1.0 - Random()};
  return lambda * std::pow(-std::log(u), 1.0 / k);
}
}// namespace cont

namespace discr {

int Binomial(int n, double p)
{
  if (p < 0 || p > 1.0) {
    return -1;
  }

  std::vector<double> U(n);
  std::vector<int> V(n);
  std::generate(U.begin(), U.end(), []() { return cont::Random(); });
  std::transform(U.begin(), U.end(), V.begin(), [&p](double x) { return x < p ? 0 : 1; });
  return std::accumulate(V.begin(), V.end(), 0);
}

int Poisson(double lambda)
{
  if (lambda < 0.0) {
    return -1;
  }
  double L{pow(M_E, -lambda)};
  double p{1.0}, u;
  int k{0};

  do {
    k++;
    u = cont::Random();
    p *= u;
  } while (p > L);
  return k - 1;
}

int Geometric(double p)
{
  if (p <= 0 || p > 1.0) {
    return -1;
  }
  int k{0};
  double x{cont::Random()};

  while (x > p) {
    x = cont::Random();
    k++;
  }
  return k;
}

}// namespace discr

}// namespace algo::math::random_num

/////////////////////////////////////////////
/// Prime numbers
/////////////////////////////////////////////

namespace algo::math::prime {

template<typename T>
bool IsPrime(T n)
{
  return GetPrimes<T>(n).back() == n;
}

template bool IsPrime<int>(int n);
template bool IsPrime<long>(long n);

template<typename T>
std::vector<T> GetPrimes(unsigned int n)
{
  std::vector<bool> is_prime(n * 2, true);
  uint limit = static_cast<uint>(sqrt(n) + 1);

  T j, k, x;

  for (size_t i = 2; i < limit; i++) {
    if (is_prime[i]) {
      j = 0;
      k = 0;
      x = i * i;

      while (static_cast<size_t>(j) <= n) {
        j = x + k * i;
        is_prime[j] = false;
        k++;
      }
    }
  }

  std::vector<T> primes;
  T candidate = 0;

  while (static_cast<size_t>(candidate) <= n) {
    if (is_prime[candidate]) {
      primes.emplace_back(candidate);
    }
    candidate++;
  }
  return primes;
}

template std::vector<int> GetPrimes<int>(unsigned int n);
template std::vector<long> GetPrimes<long>(unsigned int n);
}// namespace algo::math::prime
