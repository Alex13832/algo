///
/// \brief Source file for search algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "search_algorithms.hpp"

#include <algorithm>
#include <cmath>
#include <string>

namespace algo {

namespace search {

/////////////////////////////////////////////
/// Binary search
/////////////////////////////////////////////

template<typename T>
int Binary(const std::vector<T> &vec, const T &value)
{
  if (!std::is_sorted(vec.begin(), vec.end())) {
    return -1;
  }

  int l{0};
  int r = vec.size();

  while (l < r) {

    int m = std::floor((l + r) / 2);
    if (vec[m] < value) {
      l = m + 1;
    } else {
      r = m;
    }
  }

  if (l == vec.size()) {
    return -1;
  }
  return l;
}

template int Binary<int>(const std::vector<int> &vec, const int &value);
template int Binary<std::string>(const std::vector<std::string> &vec, const std::string &value);

/////////////////////////////////////////////
/// Selection search
/////////////////////////////////////////////

template<typename T>
void SelectionMinPriv(std::vector<T> &vec, const T &k)
{
  for (int i = 0; i <= k; ++i) {
    int minIndex = i;
    T minVal = vec[i];

    for (size_t j = i + 1; j < vec.size(); ++j) {
      if (vec[j] < minVal) {
        minIndex = j;
        minVal = vec[j];
      }
    }

    T t = vec[minIndex];
    vec[minIndex] = vec[i];
    vec[i] = t;
  }
}

template<typename T>
std::vector<T> SelectionMin(std::vector<T> vec, const T &k)
{
  std::vector<T> temp{};

  if (vec.empty()) {
    return temp;
  }

  SelectionMinPriv(vec, k);
  temp.resize(k);
  copy_n(vec.begin(), k, temp.begin());
  return temp;
}

template std::vector<int> SelectionMin<int>(std::vector<int> vec, const int &value);
template std::vector<long> SelectionMin<long>(std::vector<long> vec, const long &value);
template std::vector<float> SelectionMin<float>(std::vector<float> vec, const float &value);
template std::vector<double> SelectionMin<double>(std::vector<double> vec, const double &value);

template<typename T>
void SelectionMaxPriv(std::vector<T> &vec, const T &k)
{
  for (int i = 0; i <= k; ++i) {
    int max_index = i;
    T minVal = vec[i];

    for (size_t j = i + 1; j < vec.size(); ++j) {
      if (vec[j] > minVal) {
        max_index = j;
        minVal = vec[j];
      }
    }

    T t = vec[max_index];
    vec[max_index] = vec[i];
    vec[i] = t;
  }
}

template<typename T>
std::vector<T> SelectionMax(std::vector<T> vec, const T &k)
{
  std::vector<T> temp{};

  if (vec.empty()) {
    return temp;
  }

  SelectionMaxPriv(vec, k);
  temp.resize(k);
  copy_n(vec.begin(), k, temp.begin());
  return temp;
}

template std::vector<int> SelectionMax<int>(std::vector<int> vec, const int &value);
template std::vector<long> SelectionMax<long>(std::vector<long> vec, const long &value);
template std::vector<float> SelectionMax<float>(std::vector<float> vec, const float &value);
template std::vector<double> SelectionMax<double>(std::vector<double> vec, const double &value);
} // namespace search
} // namespace algo
