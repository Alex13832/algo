///
/// \brief Source file for search algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "search_algorithms.hpp"

#include <algorithm>
#include <cmath>
#include <string>

namespace algo {

namespace search {

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
} // namespace search
} // namespace algo