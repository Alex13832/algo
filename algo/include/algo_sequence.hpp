///
/// \brief Source file for sequence algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2015-07-20: Longest increasing subsequence.
/// 2016-04-05: Max sub array.
///

#ifndef ALGORITHM_SEQUENCE_SEQUENCE_ALGORITHMS_HPP_
#define ALGORITHM_SEQUENCE_SEQUENCE_ALGORITHMS_HPP_

#include <vector>

namespace algo::sequence {

/// \brief Returns the longest increasing sub sequence of an input sequence.
/// \tparam T Type used.
/// \param seq The input sequence.
/// \return Longest increasing sub sequence.
template<typename T>
std::vector<T> LongestIncreasingSub(const std::vector<T>& seq);

/// \brief Finds the largest sum of any continuous subarray in vec.
/// \tparam T Type used.
/// \param vec The array/vector.
/// \return The maximum sum of any continuous subarray.
template<typename T>
T MaxSubarray(const std::vector<T>& vec);
}// namespace algo::sequence

#endif//ALGORITHM_SEQUENCE_SEQUENCE_ALGORITHMS_HPP_
