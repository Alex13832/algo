///
/// \brief Source file for math algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "maths_algorithms.hpp"

#include <chrono>
#include <cmath>
#include <random>

namespace algo {
namespace Math {

/////////////////////////////////////////////
/// Discrete
/////////////////////////////////////////////

namespace Discrete {

std::vector<std::vector<int>> PascalsTriangle(const unsigned int &depth)
{
  std::vector<std::vector<int>> rows{};

  for (size_t line = 1; line <= depth + 1; line++) {
    std::vector<int> row{};
    unsigned int C{1};

    for (size_t i = 1; i <= line; i++) {
      row.emplace_back(C);
      C = C * (line - i) / i;
    }

    rows.emplace_back(row);
  }

  return rows;
}

int ClockAngle(const int &h, const int &m)
{
  if (h < 0 || m < 0 || h > 23 || m > 59) {
    return -1;
  }

  int hour_angle{((h % 12) * 60 + m) / 2};
  int minute_angle{6 * m};
  int angle{abs(hour_angle - minute_angle)};
  //angle = std::min(360 - angle, angle);
  return angle;
}

unsigned int Knapsack(const std::vector<int> &v, const std::vector<int> &w, unsigned capacity)
{
  size_t n{v.size()};
  std::vector<std::vector<int>> m(n + 1, std::vector<int>(capacity + 1, 0));

  for (size_t i = 1; i <= n; i++) {
    for (size_t j = 0; j <= capacity; j++) {
      if (w[i - 1] <= j) {
        m[i][j] = std::max(m[i - 1][j], m[i - 1][j - w[i - 1]] + v[i - 1]);
      } else {
        m[i][j] = m[i - 1][j];
      }
    }
  }

  return m[n][capacity];
}

template<typename T>
T Gcd(T a, T b)
{
  // Euclidean algorithm:
  T c{0};
  while (b != 0) {
    c = a % b;
    a = b;
    b = c;
  }
  return a;
}

template unsigned Gcd<unsigned>(unsigned a, unsigned b);
template int Gcd<int>(int a, int b);
template long Gcd<long>(long a, long b);

template<typename T>
T Lcm(T a, T b)
{
  return a * b / Gcd(a, b);
}

template unsigned Lcm<unsigned>(unsigned a, unsigned b);
template long Lcm<long>(long a, long b);

template<typename T>
T Bin(T n, T k)
{
  if (k > n)
    return 0;
  if ((k == 0) || (k == n))
    return 1;

  k = std::min(k, n - k);

  T c = 1;
  for (T i = 0; i < k; i++)
    c = c * (n - i) / (i + 1);

  return c;
}

template unsigned Bin<unsigned>(unsigned a, unsigned b);
template long Bin<long>(long a, long b);
} // namespace Discrete

/////////////////////////////////////////////
/// Random numbers
/////////////////////////////////////////////

namespace Random {

double Uniform(const double &a, const double &b)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed); //Mersenne twister
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(generator);
}

double Random()
{
  return Uniform(0.0, 1.0);
}

double Exp(const double &lambda)
{
  if (lambda == 0.0) {
    return NAN;
  }
  const double x{Random()};
  return -std::log(1.0 - x) / lambda;
}

double Weibull(const double &lambda, const double &k)
{
  if (lambda == 0.0) {
    return NAN;
  }

  const double u{1.0 - Random()};
  return lambda * std::pow(-std::log(u), 1.0 / k);
}
} // namespace Algo
} // namespace Math
} // namespace Random