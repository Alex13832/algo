///
/// \brief Source file for math algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "maths_algorithms.hpp"

#include <chrono>
#include <cmath>
#include <random>

namespace Algo {
namespace Math {

constexpr double Pi{3.14159265358979323846};
constexpr double eul{2.71828182845904523536};

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

// \TODO{alex011235}: Find out how to test the distribution.
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