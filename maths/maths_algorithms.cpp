///
/// \brief Source file for math algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "maths_algorithms.hpp"

#include <chrono>
#include <random>

namespace Algo {
namespace Math {

constexpr double Pi{3.14159265358979323846};
constexpr double eul{2.71828182845904523536};

namespace Random {

double Uniform(const double &a, const double &b)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed); //Mersenne twister
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(generator);
}
} // namespace Algo
} // namespace Math
} // namespace Random