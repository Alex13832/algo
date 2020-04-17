/* -----------------------------------------------------
* Insertion sort implementation.
* Alexander Karlsson 2015-06-21
* Updated 2016-10-02 (Bentley 1993)
* ------------------------------------------------------ */
#include <vector>
#include <utility>

using namespace std;

/* Insertion sort */
template<typename T>
void insertion_sort(vector<T> &vec)
{
  size_t N = vec.size();
  for (size_t i = 0; i < N; i++) {
    for (size_t j = i; j > 0 && vec[j - 1] > vec[j]; j--)
      swap(vec[j], vec[j - 1]);
  }
}
