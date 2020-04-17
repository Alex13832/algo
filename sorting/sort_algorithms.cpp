///
/// \brief Unit tests for sort algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
#include "sort_algorithms.hpp"

#include <algorithm>
#include <cmath>
#include <list>

namespace Sort {

/////////////////////////////////////////////
/// Bubble-sort
/////////////////////////////////////////////

template<typename T>
void BubbleSort(std::vector<T> &vec)
{
  if (vec.empty()) {
    return;
  }

  size_t n{vec.size()};

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n - 1; j++) {
      if (vec[j] > vec[j + 1]) {
        std::swap(vec[j], vec[j + 1]);
      }
    }
  }
}

// Defines what types may be used for Bubble-sort.
template void BubbleSort<unsigned>(std::vector<unsigned> &vec);
template void BubbleSort<signed>(std::vector<signed> &vec);
template void BubbleSort<float>(std::vector<float> &vec);
template void BubbleSort<double>(std::vector<double> &vec);
template void BubbleSort<std::string>(std::vector<std::string> &vec);

/////////////////////////////////////////////
/// Bucket-sort
/////////////////////////////////////////////

template<typename T>
void BucketSort(std::vector<T> &vec)
{
  if (vec.empty()) {
    return;
  }

  if (std::any_of(vec.begin(), vec.end(), [](T t) { return t < 0; })) {
    return;
  }

  auto maxElemPtr{max_element(vec.begin(), vec.end())};
  int nbrOfBuckets{static_cast<int>(sqrt(*maxElemPtr))};
  std::vector<std::vector<T>> buckets(nbrOfBuckets + 1);

  // Put in buckets
  for (T x: vec) {
    buckets[static_cast<T>(sqrt(x))].push_back(x);
  }

  // Put back elements
  int count{0};
  for (const std::vector<T> &bucket: buckets) {
    for (T e: bucket) {
      vec[count++] = e;
    }
  }

  // Insertion sort (Bentley 1993)
  for (size_t i = 1; i < vec.size(); i++) {
    for (size_t j = i; j > 0 && vec[j - 1] > vec[j]; j--)
      std::swap(vec[j], vec[j - 1]);
  }
}

// Defines what types may be used for Bucket-sort.
template void BucketSort<unsigned>(std::vector<unsigned> &vec);
template void BucketSort<signed>(std::vector<signed> &vec);
template void BucketSort<float>(std::vector<float> &vec);
template void BucketSort<double>(std::vector<double> &vec);

/////////////////////////////////////////////
/// Merge-sort
/////////////////////////////////////////////

/// \brief Merge step.
/// \tparam T Type in lists.
/// \param A First list.
/// \param B Second list.
/// \return A sorted and merged vector.
template<typename T>
std::vector<T> merge(std::list<T> &A, std::list<T> &B)
{
  std::vector<T> C;

  while (!A.empty() && !B.empty()) {
    if (A.front() > B.front()) {
      C.push_back(B.front());
      B.pop_front();
    } else {
      C.push_back(A.front());
      A.pop_front();
    }
  }

  while (!A.empty()) {
    C.push_back(A.front());
    A.pop_front();
  }

  while (!B.empty()) {
    C.push_back(B.front());
    B.pop_front();
  }

  return C;
}

template<typename T>
std::vector<T> MergeSortPriv(const std::vector<T> &lst)
{

  if (lst.empty()) {
    return lst;
  }

  size_t n{lst.size()};

  // Base case
  if (n == 1) {
    return lst;
  }

  size_t half{n / 2};
  std::vector<T> A, B;

  for (auto it = lst.begin(); it != (lst.begin() + half); ++it) {
    A.push_back(*it);
  }
  for (auto it = (lst.begin() + half); it != lst.end(); ++it) {
    B.push_back(*it);
  }

  A = MergeSortPriv(A);
  B = MergeSortPriv(B);

  std::list<T> Al(A.size()), Bl(B.size());
  copy(A.begin(), A.end(), Al.begin());
  copy(B.begin(), B.end(), Bl.begin());

  return merge(Al, Bl);
}

template<typename T>
void MergeSort(std::vector<T> &lst)
{
  lst = MergeSortPriv(lst);
}

// Defines what types may be used for Bubble-sort.
template void MergeSort<unsigned>(std::vector<unsigned> &vec);
template void MergeSort<signed>(std::vector<signed> &vec);
template void MergeSort<float>(std::vector<float> &vec);
template void MergeSort<double>(std::vector<double> &vec);
template void MergeSort<std::string>(std::vector<std::string> &vec);

/////////////////////////////////////////////
/// Quick-sort
/////////////////////////////////////////////

template<typename T>
int Partition(std::vector<T> &vec, int low, int high)
{
  T x{vec[high]};
  int i{low - 1};

  for (int j = low; j != high; j++) {
    if (vec[j] <= x) {
      i++;
      std::swap(vec[j], vec[i]);
    }
  }

  std::swap(vec[i + 1], vec[high]);
  return i + 1;
}

// Start of the Quicksort algorithm
template<typename T>
void QuickSort(std::vector<T> &vec, int low, int high)
{
  if (low < high) {
    int pivot{Partition(vec, low, high)};
    QuickSort(vec, low, pivot - 1);
    QuickSort(vec, pivot + 1, high);
  }
}

template<typename T>
void QuickSort(std::vector<T> &vec)
{
  if (vec.empty()) {
    return;
  }
  QuickSort(vec, 0, vec.size() - 1);
}

// Defines what types may be used for Quick-sort.
template void QuickSort<unsigned>(std::vector<unsigned> &vec);
template void QuickSort<signed>(std::vector<signed> &vec);
template void QuickSort<float>(std::vector<float> &vec);
template void QuickSort<double>(std::vector<double> &vec);
template void QuickSort<std::string>(std::vector<std::string> &vec);
} // namespace Sorting