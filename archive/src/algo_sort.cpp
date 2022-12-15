///
/// \brief Source file for sort algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
#include "algo_sort.hpp"

#include <algorithm>
#include <cmath>
#include <list>

namespace algo::sort {

/////////////////////////////////////////////
/// Bubble-sort
/////////////////////////////////////////////

template<typename T>
void Bubble(std::vector<T> &vec)
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
template void Bubble<unsigned>(std::vector<unsigned> &vec);
template void Bubble<signed>(std::vector<signed> &vec);
template void Bubble<double>(std::vector<double> &vec);
template void Bubble<std::string>(std::vector<std::string> &vec);

/////////////////////////////////////////////
/// Bucket-sort
/////////////////////////////////////////////

template<typename T>
void Bucket(std::vector<T> &vec)
{
  if (vec.empty()) {
    return;
  }

  if (std::any_of(vec.begin(), vec.end(), [](T t) { return t < 0; })) {
    return;
  }

  auto max_elem_ptr = std::max_element(vec.begin(), vec.end());
  int nbrOfBuckets{static_cast<int>(sqrt(*max_elem_ptr))};
  std::vector<std::vector<T>> buckets(nbrOfBuckets + 1);

  // Put in buckets
  for (const T &x : vec) {
    buckets[static_cast<T>(sqrt(x))].push_back(x);
  }

  // Put back elements
  int count{0};
  for (const std::vector<T> &bucket : buckets) {
    for (T e : bucket) {
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
template void Bucket<unsigned>(std::vector<unsigned> &vec);
template void Bucket<int>(std::vector<int> &vec);
template void Bucket<double>(std::vector<double> &vec);

/////////////////////////////////////////////
/// Gnome-sort
/////////////////////////////////////////////

template<typename T>
void Gnome(std::vector<T> &vec)
{
  int i{0};
  size_t n{vec.size()};

  while (static_cast<size_t>(i) < n) {

    if (i == 0)
      i++;
    if (vec[i] >= vec[i - 1])
      i++;
    else {
      std::swap(vec[i], vec[i - 1]);
      i--;
    }
  }
}

// Defines what types may be used for Gnome-sort.
template void Gnome<unsigned>(std::vector<unsigned> &vec);
template void Gnome<int>(std::vector<int> &vec);
template void Gnome<double>(std::vector<double> &vec);
template void Gnome<std::string>(std::vector<std::string> &vec);

/////////////////////////////////////////////
/// Heap-sort
/////////////////////////////////////////////

/// \brief Sift-down operation for binary heaps. Puts new elements to the appropriate indices.
/// \tparam T Type in vector.
/// \param vec the vector to arrange the elements.
/// \param start The starting position.
/// \param len The length.
/// \link <a href=https://en.wikipedia.org/wiki/Binary_heap#Extract>SiftDown, Wikipedia.</>
template<typename T>
void Siftdown(std::vector<T> &vec, int start, int len)
{
  int root{start};
  while (root * 2 + 1 <= len) {
    int child{root * 2 + 1};
    int swap{root};

    if (vec[swap] < vec[child]) {
      swap = child;
    }

    if (child + 1 <= len && vec[swap] < vec[child + 1]) {
      swap = child + 1;
    }

    if (swap == root) {
      return;
    } else {
      T t{vec[root]};
      vec[root] = vec[swap];
      vec[swap] = t;
      root = swap;
    }
  }
}

/// \brief Builds the heap vector, largest value at the root.
/// \tparam T Type in vector.
/// \param vec The vector to heapify.
/// \param len Number of elements.
template<typename T>
void Heapify(std::vector<T> &vec, size_t len)
{
  int start = floor((len - 2.0) / 2.0);

  while (start >= 0) {
    Siftdown(vec, start, len - 1);
    start--;
  }
}

/// \brief Internal function for the Heapsort algorithm.
/// \tparam T Type in vector.
/// \param vec The vector to be sorted.
/// \param len Number of elements.
template<typename T>
void HeapSortPriv(std::vector<T> &vec, size_t len)
{
  Heapify(vec, len);

  size_t end{len - 1};
  while (end > 0) {
    std::swap(vec[end], vec[0]);
    end--;
    Siftdown(vec, 0, end);
  }
}

template<typename T>
void Heap(std::vector<T> &vec)
{
  if (vec.empty()) {
    return;
  }
  HeapSortPriv(vec, vec.size());
}

// Defines what types may be used for Heap-sort.
template void Heap<unsigned>(std::vector<unsigned> &vec);
template void Heap<int>(std::vector<int> &vec);
template void Heap<double>(std::vector<double> &vec);
template void Heap<std::string>(std::vector<std::string> &vec);

/////////////////////////////////////////////
/// Insertion-sort
/////////////////////////////////////////////

template<typename T>
void Insertion(std::vector<T> &vec)
{
  if (vec.empty()) {
    return;
  }

  size_t N{vec.size()};
  for (size_t i = 0; i < N; i++) {
    for (size_t j = i; j > 0 && vec[j - 1] > vec[j]; j--)
      std::swap(vec[j], vec[j - 1]);
  }
}

// Defines what types may be used for Insertion-sort.
template void Insertion<unsigned>(std::vector<unsigned> &vec);
template void Insertion<int>(std::vector<int> &vec);
template void Insertion<double>(std::vector<double> &vec);
template void Insertion<std::string>(std::vector<std::string> &vec);

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
  std::copy(A.begin(), A.end(), Al.begin());
  std::copy(B.begin(), B.end(), Bl.begin());
  return merge(Al, Bl);
}

template<typename T>
void Merge(std::vector<T> &lst)
{
  lst = MergeSortPriv(lst);
}

// Defines what types may be used for Merge-sort.
template void Merge<unsigned>(std::vector<unsigned> &vec);
template void Merge<int>(std::vector<int> &vec);
template void Merge<double>(std::vector<double> &vec);
template void Merge<std::string>(std::vector<std::string> &vec);

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
void Quick(std::vector<T> &vec)
{
  if (vec.empty()) {
    return;
  }
  QuickSort(vec, 0, vec.size() - 1);
}

// Defines what types may be used for Quick-sort.
template void Quick<unsigned>(std::vector<unsigned> &vec);
template void Quick<int>(std::vector<int> &vec);
template void Quick<double>(std::vector<double> &vec);
template void Quick<std::string>(std::vector<std::string> &vec);
}// namespace algo::sort