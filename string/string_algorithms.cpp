///
/// \brief Unit tests for sort algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
#include "string_algorithms.hpp"

#include <vector>

using namespace std;

namespace StringAlgorithm {

string BitapSearch(const string &text, const string &pattern)
{
  size_t m = pattern.length();

  if (m == 0) return text;

  vector<int> R(m, 0);
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

  return string{};
}

int LastOccurrence(string str, char c)
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

vector<int> BoyerMore(string &text, const string &pattern)
{
  int m = pattern.length(), n = text.length(), i = m - 1, j = i;
  int chunk = 0, w_length = m;
  vector<int> matches;

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
      i = i + m - min(j, 1 + LastOccurrence(text, text[i]));
      j = m - 1;
    }
  } while (i < n - 1);

  return matches;
}

string LongestCommonSubstring(string A, string B)
{

  if (A.empty() || B.empty()) {
    return "";
  }

  // Append blank spaces to search in whole strings, note for-loops start on 1.
  A = " " + A + " ";
  B = " " + B + " ";

  vector<vector<int>> L(A.length(), vector<int>(B.length(), 0));
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

  string res = A.substr(x_longest - max_substr, max_substr);

  if (res[0] == ' ') {
    return string(res.begin() + 1, res.end());
  }

  return res;
}

/// \brief Returns the hash for str.
/// \param str The string to hash.
/// \return hash.
unsigned long fingerprint(const string &str)
{
  hash<string> shash;
  return shash(str);
}

vector<int> RabinKarpSingle(const string &text, const string &pattern)
{
  vector<int> pos;
  size_t n = text.length();
  size_t m = pattern.length();
  unsigned long hash_p = fingerprint(pattern);
  unsigned long hash_t = fingerprint(text.substr(0, m));

  for (size_t i = 0; i < (n - m + 1); i++) {
    if (hash_t == hash_p) {
      if (text.substr(i, m) == pattern) pos.push_back(i);
    }
    string temp = text.substr(i + 1, m);
    hash_t = fingerprint(temp);
  }

  return pos;
}

vector<int> RabinKarpMulti(const string &text, set<string> patterns, int m)
{
  set<unsigned long> hash_pm;
  vector<int> pos;
  size_t n = text.length();

  for (const auto &pattern: patterns) {
    hash_pm.insert(fingerprint(pattern));
  }

  unsigned long hash_t = fingerprint(text.substr(0, m));

  for (size_t j = 0; j < (n - m + 1); j++) {
    bool h_find = hash_pm.find(hash_t) != hash_pm.end();
    bool p_find = patterns.find(text.substr(j, m)) != patterns.end();
    if (h_find && p_find) pos.push_back(j);

    string temp = text.substr(j + 1, m);
    hash_t = fingerprint(temp);
  }

  return pos;
}
} // StringAlgorithm
