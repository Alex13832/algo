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
