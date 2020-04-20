///
/// \brief Header for search algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2015-06-18 Binary search
///

#ifndef ALGORITHM_SEARCH_SEARCH_ALGORITHMS_HPP_
#define ALGORITHM_SEARCH_SEARCH_ALGORITHMS_HPP_

#include <vector>

namespace algo {
namespace search {

/// \brief Searches for value in vec with binary search. The input list has to be sorted. This implementation is left-most oriented.
/// \tparam T Type used.
/// \param vec The vector to search in.
/// \param value The value to search for.
/// \return The position of found element, otherwise -1.
/// \link <a href="https://en.wikipedia.org/wiki/Binary_search_algorithm">Binary search, Wikipedia.</a>
template<typename T>
int Binary(const std::vector<T> &vec, const T &value);
} // namespace search
} // namespace algo

#endif //ALGORITHM_SEARCH_SEARCH_ALGORITHMS_HPP_
