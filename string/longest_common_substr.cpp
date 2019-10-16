/**--------------------------------------------------------
* Longest common substring implementation, using 
* dynamic programming
* Alexander Karlsson 2015-06-19
* --------------------------------------------------------- */
#include "string_algorithms.h"

#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief Returns the longest common substring that exists in A and B.
 * @param A input string.
 * @param B input string.
 * @return longest common substring of A and B.
 */
string StringAlgorithm::LongestCommonSubstring(string A, string B) {

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
