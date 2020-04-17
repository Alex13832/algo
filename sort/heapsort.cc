/** ------------------------------------------------
* Implementation of the HeapSort algorithm
* Alexander Karlsson, 2015-06-21
* -------------------------------------------------- */
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

/* subroutine of heapify */
template<typename T>
void siftdown(vector<T> &vec, int start, int len)
{
  int root = start;

  while (root * 2 + 1 <= len) {
    int child = root * 2 + 1;
    int swap = root;

    if (vec[swap] < vec[child]) {
      swap = child;
    }

    if (child + 1 <= len && vec[swap] < vec[child + 1]) {
      swap = child + 1;
    }

    if (swap == root) {
      return;
    } else {
      T t = vec[root];
      vec[root] = vec[swap];
      vec[swap] = t;
      root = swap;
    }
  }
}

/* Heap order */
template<typename T>
void heapify(vector<T> &vec, int len)
{
  int start = floor((len - 2) / 2);

  while (start >= 0) {
    siftdown(vec, start, len - 1);
    start--;
  }
}

/* Start of the HeapSort algorithm */
template<typename T>
void heapsort(vector<T> &vec, int len)
{
  heapify(vec, len);

  int end = len - 1;
  while (end > 0) {
    swap(vec[end], vec[0]);
    end--;
    siftdown(vec, 0, end);
  }
}