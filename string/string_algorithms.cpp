///
/// \brief Source file for string algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
#include "string_algorithms.hpp"

#include <vector>

namespace algo {

namespace strings {

std::string BitapSearch(const std::string &text, const std::string &pattern)
{
  size_t m = pattern.length();

  if (m == 0) return text;

  std::vector<int> R(m, 0);
  R[0] = 1;

  for (size_t i = 0; i < text.length(); i++) {
    // Update the bit array
    for (size_t k = m; k >= 1; k -= 1) {
      R[k] = (R[k - 1] > 0) & (text[i] == pattern[k - 1]);
    }

    if (R[m] > 0) {
      return text.substr(i - m + 1);
    }
  }

  return std::string{};
}

int LastOccurrence(std::string str, char c)
{
  int index = str.length();
  while (index != 0) {
    if (str[index] == c) {
      return index;
    }
    index--;
  }
  return 0;
}

std::vector<int> SearchBoyerMoore(std::string &text, const std::string &pattern)
{
  int m = pattern.length(), n = text.length(), i = m - 1, j = i;
  int chunk = 0, w_length = m;
  std::vector<int> matches;

  do {
    if (pattern[j] == text[i]) {
      if (j == 0) {
        matches.push_back(i + chunk);
        text = text.substr(i + w_length);
        chunk = chunk + i + w_length;
        n = text.length(), i = m - 1, j = i;
      } else {
        i--;
        j--;
      }
    } else {
      i = i + m - std::min(j, 1 + LastOccurrence(text, text[i]));
      j = m - 1;
    }
  } while (i < n - 1);

  return matches;
}

std::string LongestCommonSubstring(std::string A, std::string B)
{

  if (A.empty() || B.empty()) {
    return "";
  }

  // Append blank spaces to search in whole strings, note for-loops start on 1.
  A = " " + A + " ";
  B = " " + B + " ";

  std::vector<std::vector<int>> L(A.length(), std::vector<int>(B.length(), 0));
  int max_substr = 0, x_longest = 0;

  for (size_t i = 1; i < A.length(); ++i) {
    for (size_t j = 1; j < B.length(); ++j) {

      if (A[i - 1] == B[j - 1]) {
        L[i][j] = L[i - 1][j - 1] + 1;

        if (L[i][j] > max_substr) {
          max_substr = L[i][j];
          x_longest = i;
        }
      } else {
        L[i][j] = 0;
      }
    }
  }

  std::string res = A.substr(x_longest - max_substr, max_substr);

  if (res[0] == ' ') {
    return std::string(res.begin() + 1, res.end());
  }

  return res;
}

/// \brief Returns the hash for str.
/// \param str The string to hash.
/// \return hash.
unsigned long fingerprint(const std::string &str)
{
  std::hash<std::string> shash;
  return shash(str);
}

std::vector<int> SearchRabinKarpSingle(const std::string &text, const std::string &pattern)
{
  std::vector<int> pos;
  size_t n = text.length();
  size_t m = pattern.length();
  unsigned long hash_p = fingerprint(pattern);
  unsigned long hash_t = fingerprint(text.substr(0, m));

  for (size_t i = 0; i < (n - m + 1); i++) {
    if (hash_t == hash_p) {
      if (text.substr(i, m) == pattern) pos.push_back(i);
    }
    std::string temp = text.substr(i + 1, m);
    hash_t = fingerprint(temp);
  }

  return pos;
}

std::vector<int> SearchRabinKarpMulti(const std::string &text, std::set<std::string> patterns, int m)
{
  std::set<unsigned long> hash_pm;
  std::vector<int> pos;
  size_t n = text.length();

  for (const auto &pattern: patterns) {
    hash_pm.insert(fingerprint(pattern));
  }

  unsigned long hash_t = fingerprint(text.substr(0, m));

  for (size_t j = 0; j < (n - m + 1); j++) {
    bool h_find = hash_pm.find(hash_t) != hash_pm.end();
    bool p_find = patterns.find(text.substr(j, m)) != patterns.end();
    if (h_find && p_find) pos.push_back(j);

    std::string temp = text.substr(j + 1, m);
    hash_t = fingerprint(temp);
  }

  return pos;
}

/// \brief Hidden function for generating all the permutations of the input str.
/// \param n Size of str;
/// \param str The input string.
/// \param vec The permutations.
void Heaps(size_t n, std::string &str, std::vector<std::string> &vec)
{
  if (n == 1) {
    vec.emplace_back(str);
  } else
    for (size_t i = 0; i < n; i++) {
      Heaps(n - 1, str, vec);
      if (n % 2 == 0) {
        std::swap(str[i], str[n - 1]);
      } else {
        std::swap(str[0], str[n - 1]);
      }
    }
}

std::vector<std::string> GenerateAllPermutations(std::string &str)
{
  size_t n{str.size()};
  std::vector<std::string> vec;
  Heaps(n, str, vec);
  return vec;
}
} // namespace strings
} // namespace algo
