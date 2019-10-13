/** ------------------------------------------------------------------
* Boyer-Moore algorithm for finding the location of a substring. 
* This implementation is modified, in a way such that all locations 
* of a substring are found.
* Alexander Karlsson, 2015-07-21
* -------------------------------------------------------------------- */
#include "string_algorithms.h"

#include <vector>

using namespace std;

int StringAlgorithm::last_occurence(string str, char c) {
  int index = str.length();
  while (index != 0) {
    if (str[index] == c) {
      return index;
    }
    index--;
  }
  return 0;
}

/**
 * @brief Returns the found locations of the pattern in text.
 * @param text The text to look for the pattern.
 * @param pattern The substring to match.
 * @return A list of locations.
 * @link <a href="https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm">Boyer-More Wikipedia.</a>
 */
vector<int> StringAlgorithm::boyer_moore(string text, string pattern) {
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
      i = i + m - min(j, 1 + StringAlgorithm::last_occurence(text, text[i]));
      j = m - 1;
    }

  } while (i < n - 1);

  return matches;
}