///
/// \brief Header for string algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2015-06-21 Quick-sort.
/// 2015-07-30 Bubble-sort.
/// 2015-07-30 Merge-sort.
/// 2016-10-02 Bucket-sort.
///

#ifndef ALGORITHM_SORTING_SORTING_HPP_
#define ALGORITHM_SORTING_SORTING_HPP_

#include <iostream>
#include <list>
#include <vector>

namespace Sort {

/// \brief Bubble sort.
/// \tparam T Type in vector.
/// \param lst The list to sort.
/// \link <a href="https://en.wikipedia.org/wiki/Bubble_sort">Bubble sort, Wikipedia.</a>
template<typename T>
void BubbleSort(std::vector<T> &vec);

/// \brief Bucket sort algorithm.
/// \tparam T Type in vector.
/// \param vec the vector to be sorted.
/// \link <a href="https://en.wikipedia.org/wiki/Bucket_sort">Bucket sort, Wikipedia.</a>
template<typename T>
void BucketSort(std::vector<T> &vec);

/// \brief Merge sort, divide and conquer algorithm.
/// \tparam T Type in vector.
/// \param lst The list to sort.
/// \return A sorted list.
/// \link <a href="https://en.wikipedia.org/wiki/Merge_sort">Merge sort, Wikipedia.</a>
template<typename T>
void MergeSort(std::vector<T> &lst);

/// \brief Quick-sort algorithm.
/// \tparam T Type to be sorted.
/// \param vec Input vector to sort.
/// \link <a href="https://en.wikipedia.org/wiki/Quicksort">Quicksort, Wikipedia.</a>
template<typename T>
void QuickSort(std::vector<T> &vec);
} // namespace Sorting

#endif //ALGORITHM_SORTING_SORTING_H_PP
