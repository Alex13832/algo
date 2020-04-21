///
/// \brief Header for string algorithms.
/// \author alex011235
/// \date 2020-04-19
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2015-07-21 Boyer-More.
/// 2015-06-19 Longest common substring.
/// 2015-06-16 Rabin-Karp.
/// 2015-08-07 Levenshtein distance.
/// 2019-10-13 Bitap search.
///

#ifndef ALGORITHM_SRC_STRING_STRING_HPP_
#define ALGORITHM_SRC_STRING_STRING_HPP_

#include <set>
#include <string>

namespace algo {

namespace strings {

/// \brief The algorithm tells whether a given text contains a substring which is "approximately equal" to a given pattern.
/// \param text The text to search within.
/// \param pattern The pattern to match.
/// \return String with match.
/// \link <a href="https://en.wikipedia.org/wiki/Bitap_algorithm">Bitap, Wikipedia.</a>
std::string BitapSearch(const std::string &text, const std::string &pattern);

/// \brief Returns the found locations of the pattern in text.
/// The implementation is based on the Boyer-Moore string-search algorithm.
/// \param text The text to look for the pattern.
/// \param pattern The substring to match.
/// \return A list of locations.
/// \link <a href="https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm">Boyer-More, Wikipedia.</a>
std::vector<int> SearchBoyerMoore(std::string &text, const std::string &pattern);

/// \brief Returns the longest common substring that exists in A and B.
/// \param A input string.
/// \param B input string.
/// \return Longest common substring of A and B.
std::string LongestCommonSubstring(std::string A, std::string B);

/// \brief Returns the starting positions of the substring pattern in text.
/// \param text The text to search within.
/// \param pattern The substring to match.
/// \return Starting positions.
/// \link <a href="https://en.wikipedia.org/wiki/Rabin–Karp_algorithm">Rabin-Karp, Wikipedia.</a>
std::vector<int> SearchRabinKarpSingle(const std::string &text, const std::string &pattern);

/// \brief Returns the starting positions of the substring patterns in patterns.
/// \param text The text to search within.
/// \param patterns Substrings to match.
/// \param m Fixed length.
/// \return The starting positions
/// \link <a href="https://en.wikipedia.org/wiki/Rabin–Karp_algorithm">Rabin-Karp, Wikipedia.</a>
std::vector<int> SearchRabinKarpMulti(const std::string &text, std::set<std::string> patterns, int m);

/// \brief Generates all permutations of the input string str using Heap's algorithm.
/// \param str The input string.
/// \return ALl permutations in a vector.
/// \link <a href="https://en.wikipedia.org/wiki/Heap%27s_algorithm">Heap's algorithm, Wikipedia.</a>
std::vector<std::string> GenerateAllPermutations(std::string &str);

/// \brief Calculates the Levenshtein distance between two strings. This is a string metric for measuring the
/// difference between two strings.
/// \param word_a Source word.
/// \param word_b Target word.
/// \return Calculated distance.
/// \link <a href="https://en.wikipedia.org/wiki/Levenshtein_distance">Levenshtein distance, Wikipedia.</a>
int LevDistance(const std::string &word_a, const std::string &word_b);

/// \brief Checks if str2 is a rotation of str1, e.g: atc is a rotation of cat.
/// \param str1 First string.
/// \param str2 Second string,
/// \return True if str2 is a rotation of str1.
bool IsRotated(const std::string &str1, const std::string &str2);

/// \brief Compresses the input string, e.g: `Compress("caaaattt") = "ca4t3"`.
/// \param str The input string to compress.
/// \return Compressed string if shorter than input.
std::string Compress(const std::string &str);
}// namespace strings
}// namespace algo

#endif//ALGORITHM_SRC_STRING_STRING_HPP_
