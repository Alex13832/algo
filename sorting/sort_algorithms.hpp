///
/// \brief Header for string algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2015-06-21 Quick-sort.
/// 2015-07-30 Bubble-sort.
/// 2015-07-30 Merge-sort.
///

#ifndef ALGORITHM_SORTING_SORTING_H_
#define ALGORITHM_SORTING_SORTING_H_

#include <vector>
#include <iostream>
#include <list>

namespace Sort {

/// \brief Bubble sort.
/// \tparam T type in vector.
/// \param lst The list to sort.
/// \return A sorted list.
template<typename T>
void BubbleSort(std::vector<T> &vec);

/// \brief Merge sort, divide and conquer algorithm.
/// \tparam T type in vector.
/// \param lst The list to sort.
/// \return A sorted list.
template<typename T>
void MergeSort(std::vector<T> &lst);

/// \brief Quick-sort algorithm.
/// \tparam T Type to be sorted.
/// \param vec Input vector to sort.
template<typename T>
void QuickSort(std::vector<T> &vec);
} // namespace Sorting

#endif //ALGORITHM_SORTING_SORTING_H_
