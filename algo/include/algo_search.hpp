///
/// \brief Header for search algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
/// Change list:
/// 2015-06-18 Binary search
///

#ifndef ALGORITHM_SEARCH_SEARCH_ALGORITHMS_HPP_
#define ALGORITHM_SEARCH_SEARCH_ALGORITHMS_HPP_

#include <vector>

namespace algo::search {

/////////////////////////////////////////////
/// Binary search
/////////////////////////////////////////////

/// \brief Searches for value in vec with binary search. The input list has to be sorted. This implementation is left-most oriented.
/// \tparam T Type used.
/// \param vec The vector to search in.
/// \param value The value to search for.
/// \return The position of found element, otherwise -1.
/// \link <a href="https://en.wikipedia.org/wiki/Binary_search_algorithm">Binary search, Wikipedia.</a>
/// \todo{alex011235} Unit test.
template<typename T>
int Binary(const std::vector<T>& vec, T value);

/////////////////////////////////////////////
/// Selection search
/////////////////////////////////////////////

/// \brief Finds the k smallest items in vec.
/// \tparam T Type used.
/// \param vec The vector to search in.
/// \param k The value to find.
/// \return The k smallest values.
/// \link <a href="https://en.wikipedia.org/wiki/Selection_algorithm">Selection search, Wikipedia.</a>
/// \todo{alex011235} Unit test.
template<typename T>
std::vector<T> SelectionMin(std::vector<T> vec, T k);

/// \brief Finds the k largest items in vec.
/// \tparam T Type used.
/// \param vec The vector to search in.
/// \param k The value to find.
/// \return The k largest values.
/// \link <a href="https://en.wikipedia.org/wiki/Selection_algorithm">Selection search, Wikipedia.</a>
/// \todo{alex011235} Unit test.
template<typename T>
std::vector<T> SelectionMax(std::vector<T> vec, T k);
}// namespace algo::search

#endif//ALGORITHM_SEARCH_SEARCH_ALGORITHMS_HPP_
