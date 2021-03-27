///
/// \brief Header for string algorithms.
/// \author alex011235
/// \date 2020-04-19
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
/// Change list:
/// 2015-07-21 Boyer-More
/// 2015-06-19 Longest common substring
/// 2015-06-16 Rabin-Karp
/// 2015-08-07 Levenshtein distance
///

#ifndef ALGORITHM_SRC_STRING_STRING_HPP_
#define ALGORITHM_SRC_STRING_STRING_HPP_

#include <set>
#include <string>
#include <vector>

namespace algo::string {

/// \brief Returns the found locations of the pattern in text.
/// The implementation is based on the Boyer-Moore string-search algorithm.
/// \param text The text to look for the pattern.
/// \param pattern The substring to match.
/// \return A list of locations.
/// \link <a href="https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm">Boyer-More, Wikipedia.</a>
std::vector<int> SearchBoyerMoore(std::string& text, const std::string& pattern);

/// \brief Returns the starting positions of the substring pattern in text.
/// \param text The text to search within.
/// \param pattern The substring to match.
/// \return Starting positions.
/// \link <a href="https://en.wikipedia.org/wiki/Rabin–Karp_algorithm">Rabin-Karp, Wikipedia.</a>
std::vector<int> SearchRabinKarpSingle(const std::string& text, const std::string& pattern);

/// \brief Returns the starting positions of the substring patterns in patterns.
/// \param text The text to search within.
/// \param patterns Substrings to match.
/// \param m Fixed length.
/// \return The starting positions
/// \link <a href="https://en.wikipedia.org/wiki/Rabin–Karp_algorithm">Rabin-Karp, Wikipedia.</a>
std::vector<int> SearchRabinKarpMulti(const std::string& text, std::set<std::string> patterns, int m);

/// \brief Returns the longest common substring that exists in A and B.
/// \param A input string.
/// \param B input string.
/// \return Longest common substring of A and B.
std::string LongestCommonSubstring(std::string A, std::string B);

/// \brief Generates all permutations of the input string str using Heap's algorithm.
/// \param str The input string.
/// \return ALl permutations in a vector.
/// \link <a href="https://en.wikipedia.org/wiki/Heap%27s_algorithm">Heap's algorithm, Wikipedia.</a>
std::vector<std::string> GenerateAllPermutations(std::string& str);

/// \brief Checks if str2 is a rotation of str1, e.g: atc is a rotation of cat.
/// \param str1 First string.
/// \param str2 Second string,
/// \return True if str2 is a rotation of str1.
bool IsRotated(const std::string& str1, const std::string& str2);

/// \brief Compresses the input string, e.g: `Compress("caaaattt") = "ca4t3"`.
/// \param str The input string to compress.
/// \return Compressed string if shorter than input.
std::string Compress(const std::string& str);

/// \brief Tests if the input string has unique chars. Only works fo ASCII [0...255].
/// \param str The string to test.
/// \return True if unique chars otherwise false.
bool HasUniqueChars(const std::string& str);

/////////////////////////////////////////////
/// String metric
/////////////////////////////////////////////

namespace metric {

/// \brief Returns the Levenshtein distance between two strings. This is a string metric for measuring the
/// difference between two strings.
/// \param word_a First word.
/// \param word_b Second word.
/// \return Calculated distance.
/// \link <a href="https://en.wikipedia.org/wiki/Levenshtein_distance">Levenshtein distance, Wikipedia.</a>
int Levenshtein(const std::string& word_a, const std::string& word_b);

/// \brief Returns the Hamming distance between word_a and word_b.
/// \param word_a First word.
/// \param word_b Second word.
/// \return The Hamming distance.
/// \link <a href="https://en.wikipedia.org/wiki/Hamming_distance">Hamming distance, Wikipedia.</a>
int Hamming(const std::string& word_a, const std::string& word_b);

/// \brief Returns the Dice's coefficient between word_a and word_b.
/// \param word_a First word.
/// \param word_b Second word.
/// \return Dice's coefficient.
double Dice(const std::string& word_a, const std::string& word_b);

/// \brief Returns the Jaro-Winkler distance/distance/metric/whatever.
/// \param word_a First word.
/// \param word_b Second word.
/// \return The Jaro-Winkler distance.
/// \note Jaro-Winkler is not a metric in the mathematical sense, it does nt obey the triangle equality, see Wikipedia.
/// \link <a href="https://en.wikipedia.org/wiki/Jaro–Winkler_distance">Jaro-Winkler, Wikipedia.</a>
double JaroWinkler(const std::string& word_a, const std::string& word_b);

}// namespace metric
}// namespace algo::string

#endif//ALGORITHM_SRC_STRING_STRING_HPP_
