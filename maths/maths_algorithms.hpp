///
/// \brief Source file for math algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#ifndef ALGORITHM_MATHS_MATHS_ALGORITHMS_HPP_
#define ALGORITHM_MATHS_MATHS_ALGORITHMS_HPP_

namespace Algo {

namespace Math {

namespace Random {

/// \brief Returns a random number sampled from a uniform distribution with lower and upper limits a and b.
/// \param a Lower limit.
/// \param b Upper Limit
/// \return A random uniform number x such that a < x < b.
/// \link <a href="https://en.wikipedia.org/wiki/Uniform_distribution_(continuous)">Uniform distribution, Wikipedia.</a>
double Uniform(const double &a, const double &b);

/// \brief Returns an exponentially distributed random number.
/// \param lambda Rate parameter, must be greater than zero.
/// \param upper_limit The upper limit.
/// \return See brief.
double Exp(const double &lambda);
} // namespace Algo
} // namespace Math
} // namespace Random

#endif //ALGORITHM_MATHS_MATHS_ALGORITHMS_HPP_
