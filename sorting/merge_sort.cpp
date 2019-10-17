/** ------------------------------------------------------------
* Implementation of the Merge Sort Algorithm
* Alexander Karlsson, 2015-07-30
* -------------------------------------------------------------- */
#include "sorting_algorithms.h"

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

/**
 * @brief Merge step. Uses linked list datastructures, hopefully better
  than using vectors since we have to move all items n steps when
  removing the first elements.
 * @param A first list.
 * @param B second list.
 * @return merged list, sorted.
 */
std::vector<int> merge(std::list<int> A, std::list<int> B) {
  std::vector<int> C;

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

/**
 * @brief  Merge Sort divide and conquer algorithm
 * @param lst the list to sort.
 * @return a sorted list.
 */
std::vector<int> Sorting::MergeSort(std::vector<int> &lst) {

  if (lst.empty()) {
    return lst;
  }

  size_t n = lst.size();

  // Base case
  if (n == 1) return lst;

  size_t half = n / 2;
  std::vector<int> A, B;

  for (auto it = lst.begin(); it != (lst.begin() + half); ++it) {
    A.push_back(*it);
  }
  for (auto it = (lst.begin() + half); it != lst.end(); ++it) {
    B.push_back(*it);
  }

  A = MergeSort(A);
  B = MergeSort(B);

  std::list<int> Al(A.size()), Bl(B.size());
  copy(A.begin(), A.end(), Al.begin());
  copy(B.begin(), B.end(), Bl.begin());

  return merge(Al, Bl);
}