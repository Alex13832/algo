///
/// \brief Source file for math algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#ifndef ALGORITHM_MATHS_MATHS_ALGORITHMS_HPP_
#define ALGORITHM_MATHS_MATHS_ALGORITHMS_HPP_

#include <vector>

namespace Algo {

namespace Math {

namespace Discrete {

/// \brief Returns the rows of Pascal's Triangle.
/// \param depth The number of rows.
/// \return The rows of Pascal's Triangle, each item in the vector is one row.
/// \link <a href="https://en.wikipedia.org/wiki/Pascal%27s_triangle">Pascal's triangle, Wikipedia.</a>
std::vector<std::vector<int>> PascalsTriangle(const unsigned int &depth);

/// \brief Computes the angle between the hour and minute hands.
/// \param h The position of the hour hand, e.g. 12.
/// \param m The position of the minute hand, e.g. 59.
/// \return The angle between the hour and minute hands. Return -1 for faulty input.
int ClockAngle(const int &h, const int &m);

/// \brief Computes the greatest common divisor, using the Euclidean algorithm.
/// \tparam T Type used.
/// \param a First number.
/// \param b Second number.
/// \return GCD(a, b)
/// \link <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">GCD, Wikipedia.</a>
/// \link <a href="https://en.wikipedia.org/wiki/Euclidean_algorithm">Euclidean algorithm, Wikipedia.</a>
template<typename T>
T Gcd(T a, T b);

/// \brief Computes the least common multiple.
/// \tparam T Type used.
/// \param a First number.
/// \param b Second number.
/// \return LCM(a, b)
/// \link <a href="https://en.wikipedia.org/wiki/Least_common_multiple">LCM, Wikipedia.</a>
template<typename T>
T Lcm(T a, T b);

/// \brief Computes the binomial coefficient of a and b.  nCk, n Choose k is the same computation.
/// \tparam T Type used.
/// \param n First number.
/// \param k Second number.
/// \return Bin(a, b)
/// \link <a href="https://en.wikipedia.org/wiki/Binomial_coefficient">Binomial coefficient, Wikipedia.</a>
template<typename T>
T Bin(T n, T k);
} // namespace Discrete

namespace Random {

/// \brief Returns a random number sampled from a uniform distribution with lower and upper limits a and b.
/// \param a Lower limit.
/// \param b Upper Limit
/// \return A random uniform number x such that a < x < b.
/// \link <a href="https://en.wikipedia.org/wiki/Uniform_distribution_(continuous)">Uniform distribution, Wikipedia.</a>
double Uniform(const double &a, const double &b);

/// \brief Returns a random number from the uniform distribution between 0 and 1.
/// \return see brief.
double Random();

/// \brief Returns an exponentially distributed random number.
/// \param lambda Rate parameter, must be greater than zero.
/// \param upper_limit The upper limit.
/// \return See brief.
/// \link <a href="https://en.wikipedia.org/wiki/Exponential_distribution">Exponential distribution, Wikipedia.</a>
double Exp(const double &lambda);

/// \brief Returns a random number sampled from the Weibull distribution.
/// \param lambda Scale parameter.
/// \param k Shape parameter.
/// \return See brief.
/// \line <a href="https://en.wikipedia.org/wiki/Weibull_distribution">Weibull distribution, Wikipedia.</a>
double Weibull(const double &lambda, const double &k);
} // namespace Random
} // namespace Math
} // namespace Algo

#endif //ALGORITHM_MATHS_MATHS_ALGORITHMS_HPP_
