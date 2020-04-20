///
/// \brief Source file for search algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "sequence_algorithms.hpp"

#include <algorithm>
#include <cmath>

namespace algo {

namespace sequence {

/////////////////////////////////////////////
/// Longest increasing subsequence
/////////////////////////////////////////////

/// \brief Finds the longest increasing subsequence in the input vector seq.
/// \tparam T Value used.
/// \param seq The input sequence.
/// \return The longest increasing subsequence.
/// \link <a href="https://en.wikipedia.org/wiki/Longest_increasing_subsequence">Longest increasing subsequence, Wikipedia.</a>
template<typename T>
std::vector<T> LongestIncreasingSub(const std::vector<T> &seq)
{
  if (seq.empty()) {
    return std::vector<T>{};
  }
  size_t N{seq.size()};
  // P stores the index of the predecessor of seq[i]
  std::vector<T> P(N);
  // M stores the index of the smallest value seq[k]
  std::vector<T> M(N + 1);
  T L{1};

  for (size_t i = 0; i < N; i++) {
    T min{1}, max{L}, mid{0};

    /* Binary search */
    while (min <= max) {
      mid = ceil((min + max) / 2);

      if (seq[M[mid]] < seq[i]) {
        min = mid + 1;
      } else {
        max = mid - 1;
      }
    }

    T Lhat = min;
    P[i] = M[Lhat - 1];
    M[Lhat] = i;

    if (Lhat > L) {
      L = Lhat;
    }
  }

  // Reconstruction of the longest subsequence
  std::vector<T> subseq(L + 1);
  T k = M[L];

  for (int i = L; i >= 0; i--) {
    subseq[i] = seq[k];
    k = P[k];
  }
  subseq[0] = -1;

  std::vector<T> out(subseq.size() - (subseq.size() - L));
  std::copy_n(subseq.begin() + (subseq.size() - L), subseq.size() - 1, out.begin());
  return out;
}

template std::vector<int> LongestIncreasingSub<int>(const std::vector<int> &seq);
template std::vector<long> LongestIncreasingSub<long>(const std::vector<long> &seq);
template std::vector<float> LongestIncreasingSub<float>(const std::vector<float> &seq);
} // namespace sequence
} // namespace algo
