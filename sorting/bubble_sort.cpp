/** ------------------------------------------------------------
* Implementation of BubbleSort.
* Alexander Karlsson, 2015-07-30
* -------------------------------------------------------------- */
#include "sorting_algorithms.h"

using namespace std;
std::vector<int> Sorting::BubbleSort(std::vector<int> lst) {
  if (lst.empty()) {
    vector<int> empt;
    return empt;
  }

  size_t n = lst.size();

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n - 1; j++) {
      if (lst[j] > lst[j + 1]) {
        std::swap(lst[j], lst[j + 1]);
      }
    }
  }

  return lst;
}