/* -----------------------------------------------------
* Quicksort implementation.
* Alexander Karlsson 2015-06-21
* ------------------------------------------------------ */
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template<typename T>
int partition(vector<T> &vec, int low, int high)
{
  int x = vec[high];
  int i = low - 1;

  for (int j = low; j != high; j++) {
    if (vec[j] <= x) {
      i++;
      swap(vec[j], vec[i]);
    }
  }

  swap(vec[i + 1], vec[high]);
  return i + 1;
}

/* Start of the Quicksort algorithm */
template<typename T>
void quicksort(vector<T> &vec, int low, int high)
{
  if (low < high) {
    int pivot = partition(vec, low, high);
    quicksort(vec, low, pivot - 1);
    quicksort(vec, pivot + 1, high);
  }
}