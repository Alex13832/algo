///
/// \brief Header for network algorithms.
/// \author alex011235
/// \date 2020-04-25
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2015-06-20 Pagerank
///
#ifndef ALGORITHM_NETWORK_NETWORK_ALGORITHMS_HPP_
#define ALGORITHM_NETWORK_NETWORK_ALGORITHMS_HPP_

#include <vector>

namespace algo::network {

using Arr = std::vector<double>;
using Mat = std::vector<Arr>;

/////////////////////////////////////////////
/// PageRank
/////////////////////////////////////////////

/// \brief Computes the rank for the input web graph.
/// \param W Web graph matrix.
/// \param damping Damping factor
/// \param error Convergence threshold.
/// \return The probabilities of a user visiting page i.
/// \link <a href="https://en.wikipedia.org/wiki/PageRank">PageRank, Wikipedia.</a>
Arr PageRank(const Mat &W, const double &damping, const double &error);

/// \brief Converts a matrix with link counts to a transition matrix with probabilities.
/// \param M Link count matrix.
/// \param deg
/// \return Transition matrix.
Mat MatTransition(const Mat &M, const Arr &deg);

}// namespace algo::network

#endif//ALGORITHM_NETWORK_NETWORK_ALGORITHMS_HPP_
