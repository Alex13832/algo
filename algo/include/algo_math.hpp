///
/// \brief Source file for math algorithms.
/// \author alex011235
/// \date 2020-04-19
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2015-08-27 Random numbers
/// 2016-04-05 Knapsack, GCD, LCM, Bin, Prime numbers
/// 2016-10-16 Pascal's triangle, ClockAngle
///

#ifndef ALGORITHM_MATHS_MATHS_ALGORITHMS_HPP_
#define ALGORITHM_MATHS_MATHS_ALGORITHMS_HPP_

#include <vector>

namespace algo::math::discrete {

using PTriangle = std::vector<std::vector<int>>;

/// \brief Returns the rows of Pascal's Triangle.
/// \param depth The number of rows.
/// \return The rows of Pascal's Triangle, each item in the vector is one row.
/// \link <a href="https://en.wikipedia.org/wiki/Pascal%27s_triangle">Pascal's triangle, Wikipedia.</a>
PTriangle PascalsTriangle(const int& depth);

/// \brief Computes the angle between the hour and minute hands.
/// \param h The position of the hour hand, e.g. 12.
/// \param m The position of the minute hand, e.g. 59.
/// \return The angle between the hour and minute hands. Return -1 for faulty input.
int ClockAngle(const int& h, const int& m);

// Struct for item in knapsack
struct Item {
  int value, weight;
};

// Knapsack items
using Items = std::vector<Item>;

/// \brief Finds the maximum capacity for the knapsack problem.
/// \param items Items possible to put in the knapsack.
/// \param capacity Maximum capacity for the knapsack.
/// \return Maximum knapsack capacity.
/// \link <a href="https://en.wikipedia.org/wiki/Knapsack_problem">Knapsack, Wikipedia.</a>
/// \link <a href="https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/"> Knapsack, GeeksforGeeks.</a>
int Knapsack(const Items& items, unsigned capacity);

/// \brief Computes the greatest common divisor, using the Euclidean algorithm.
/// \tparam T Type used.
/// \param a First number.
/// \param b Second number.
/// \return GCD(a, b)
/// \link <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">GCD, Wikipedia.</a>
/// \link <a href="https://en.wikipedia.org/wiki/Euclidean_algorithm">Euclidean algorithm, Wikipedia.</a>
constexpr auto GCD = [](auto a, auto b) {
  // Euclidean algorithm:
  decltype(a) c = 0;
  while (b != 0) {
    c = a % b;
    a = b;
    b = c;
  }
  return a;
};

/// \brief Computes the least common multiple using the properties of GCD: LCM(a,b) = a*b/GCD(a,b)
constexpr auto LCM = [](auto a, auto b) {
  return std::abs(a * b) / GCD(a, b);
};

/// \brief Computes the binomial coefficient of a and b.  nCk, n Choose k is the same computation.
/// \tparam T Type used.
/// \param n First number.
/// \param k Second number.
/// \return BIN(a, b)
/// \link <a href="https://en.wikipedia.org/wiki/Binomial_coefficient">Binomial coefficient, Wikipedia.</a>
constexpr auto BIN = [](auto n, auto k) {
  decltype(n) c = 0;
  if (k > n) {
    return c;
  }
  c = 1;
  if ((k == 0) || (k == n)) {
    return c;
  }

  k = std::min(k, n - k);

  for (decltype(k) i = 0; i < k; i++) {
    c = c * (n - i) / (i + 1);
  }

  return c;
};

}// namespace algo::math::discrete

namespace algo::math::random_num {

namespace cont {

/// \brief Returns a random number sampled from a uniform distribution with lower and upper limits a and b.
/// \param a Lower limit.
/// \param b Upper Limit
/// \return A random uniform number x such that a < x < b.
/// \link <a href="https://en.wikipedia.org/wiki/Uniform_distribution_(continuous)">Uniform distribution, Wikipedia.</a>
double Uniform(const double& a, const double& b);

/// \brief Returns a random number from the uniform distribution between 0 and 1.
/// \return U(0, 1) random number.
double Random();

/// \brief Returns an exponentially distributed random number.
/// \param lambda Rate parameter, must be greater than zero.
/// \param upper_limit The upper limit.
/// \return See brief.
/// \link <a href="https://en.wikipedia.org/wiki/Exponential_distribution">Exponential distribution, Wikipedia.</a>
double Exp(const double& lambda);

/// \brief Returns a normal distributed random number, N(mu, sigma). The random number is computed using the
/// Box-Muller transform.
/// \param mu Mean value.
/// \param sigma Standard deviation.
/// \return N(mu, sigma) random number.
/// \link <a href="https://en.wikipedia.org/wiki/Normal_distribution">Normal distribution, Wikipedia.</a>
double Normal(const double& mu, const double& sigma);

/// \brief Returns a random number sampled from the Weibull distribution.
/// \param lambda Scale parameter.
/// \param k Shape parameter.
/// \return See brief.
/// \line <a href="https://en.wikipedia.org/wiki/Weibull_distribution">Weibull distribution, Wikipedia.</a>
double Weibull(const double& lambda, const double& k);

}// namespace cont

namespace discr {

/// \brief Returns a random number sampled from the Binomial distribution.
/// \quote  The binomial distribution is frequently used to model the number of successes in a sample of size
/// n drawn with replacement from a population of size N. - _Wikipedia_
/// \param n Number of independent experiments.
/// \param p The probability of the experiment.
/// \return Binomial(n,p)
/// \link <a href="https://en.wikipedia.org/wiki/Binomial_distribution">Binomial dstribution, Wikipedia.</a>
int Binomial(const int& n, const double& p);

/// \brief Returns a random number sampled from the Poisson distribution.
/// \param lambda Expected number of occurrences.
/// \return Poisson(lambda) random number.
/// \link <a href="https://en.wikipedia.org/wiki/Poisson_distribution">Poisson distribution, Wikipedia.</a>
int Poisson(const double& lambda);

/// \brief Returns a random number sampled from the geometric distribution.
/// \quote The geometric distribution gives the probability that the first occurrence of success requires
/// k independent trials, each with success probability p. - _Wikipedia_
/// \param p Success probability.
/// \return Geometric(p)
/// \link <a href="https://en.wikipedia.org/wiki/Geometric_distribution">Geometric distribution, Wikipedia.</a>
int Geometric(const double& p);

}// namespace discr

}// namespace algo::math::random_num

namespace algo::math::prime {

/// \brief Checks if n is a prime number.
/// \tparam T Type used.
/// \param n Input number.
/// \return True if n is a prime number, otherwise false.
template<typename T>
bool IsPrime(T n);

/// \brief Returns prime numbers less than n in a vector. This implementation is based on the Sieve of Eratosthenes
/// algorithm for computing prime numbers.
/// \tparam T The type used.
/// \param n The maximum prime number (limit).
/// \return A vector<T> of prime numbers.
/// \link <a href="https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes">Sieve of Eratosthenes, Wikipedia.</a>
/// \todo Change ouput to something meaningful.
template<typename T>
std::vector<T> GetPrimes(unsigned int n);

}// namespace algo::math::prime

#endif//ALGORITHM_MATHS_MATHS_ALGORITHMS_HPP_
