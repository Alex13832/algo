///
/// \brief Unit tests for string algorithms.
/// \author alex011235
/// \date 2019-10-13
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
#include "algo.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace algo;

/////////////////////////////////////////////
/// Boyer-More
/////////////////////////////////////////////

TEST(test_algo_string, boyer_more_nbr_of_occurences_0)
{
  std::string text{"Banana banana"};
  std::string pattern{"Manana"};
  vector<int> matches{algo::string::SearchBoyerMoore(text, pattern)};
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_algo_string, boyer_more_nbr_of_occurences_1)
{
  std::string text{"Banana banana"};
  std::string pattern{"Banana ba"};
  vector<int> matches{algo::string::SearchBoyerMoore(text, pattern)};
  EXPECT_EQ(matches.size(), 1);
}

TEST(test_algo_string, boyer_more_nbr_of_occurences_many)
{
  std::string text{
      "Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
      "alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer "
      "delicata consectetuer est at. At nisl cucumber facete qui, eu oblique "
      "Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
      "alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer "
      "delicata consectetuer est at. At nisl cucumber facete qui, eu oblique "};

  std::string pattern{"cucumber"};

  vector<int> matches = algo::string::SearchBoyerMoore(text, pattern);
  EXPECT_EQ(matches.size(), 8);
}

TEST(test_algo_string, boyer_more_empty_input_pattern)
{
  std::string text{"Banana banana"};
  vector<int> matches{algo::string::SearchBoyerMoore(text, "")};
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_algo_string, boyer_more_empty_input_text)
{
  std::string text{""};
  std::string pattern{"Banana"};
  vector<int> matches{algo::string::SearchBoyerMoore(text, pattern)};
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_algo_string, boyer_more_empty_input)
{
  std::string empty;
  vector<int> matches{algo::string::SearchBoyerMoore(empty, empty)};
  EXPECT_EQ(matches.size(), 0);
}

/////////////////////////////////////////////
/// Longest common substring
/////////////////////////////////////////////

TEST(test_algo_string, longest_common_substring_standard)
{
  std::string A{"otirpporeijgpowkruskaldijkstrawithicecreamergjeågjeopnpoqerhgldijkstrassadar"};
  std::string B{"iuthewriuthkruskaldijksfuiqgfuqygfnvkjkruskaldijkstrawithicecreamdfbiehf5d"};
  std::string C{algo::string::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "kruskaldijkstrawithicecream");
}

TEST(test_algo_string, longest_common_substring_empty_first)
{
  std::string A;
  std::string B{"iuthewriuthkruskaldijksfuiqgfuqygfnvkjkruskaldijkstrawithicecreamdfbiehf5d"};
  std::string C{algo::string::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(test_algo_string, longest_common_substring_empty_second)
{
  std::string A{"otirpporeijgpowkruskaldijkstrawithicecreamergjeågjeopnpoqerhgldijkstrassadar"};
  std::string B;
  std::string C{algo::string::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(test_algo_string, longest_common_substring_empty_input)
{
  std::string A, B;
  std::string C{algo::string::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(test_algo_string, longest_common_substring_one_word)
{
  std::string A{"calculator"};
  std::string B{"culat"};
  std::string C{algo::string::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "culat");
}

TEST(test_algo_string, longest_common_substring_one_char)
{
  std::string x{algo::string::LongestCommonSubstring("x", "x")};
  EXPECT_EQ(x, "x");

  x = algo::string::LongestCommonSubstring("x", "y");
  EXPECT_EQ(x, "");
}

/////////////////////////////////////////////
/// Rabin-Karp
/////////////////////////////////////////////

TEST(test_algo_string, rabin_karp_single_input)
{
  std::string sentence{"one two one three one two hello one"};
  vector<int> pos{algo::string::SearchRabinKarpSingle(sentence, "one")};
  EXPECT_EQ(pos.size(), 4);
}

TEST(test_algo_string, rabin_karp_multi_input)
{
  std::string sentence{"one two one three one two hello one"};
  set<std::string> words{"one", "two"};
  vector<int> pos = algo::string::SearchRabinKarpMulti(sentence, words, 3);
  EXPECT_EQ(pos.size(), 6);
}

TEST(test_algo_string, rabin_karp_not_found_single)
{
  std::string sentence{"one two one three one two hello one"};
  vector<int> pos{algo::string::SearchRabinKarpSingle(sentence, "four")};
  EXPECT_EQ(pos.size(), 0);
}

TEST(test_algo_string, rabin_karp_not_found_multi)
{
  std::string sentence{"one two one three one two hello one"};
  set<std::string> words{"four", "five"};
  vector<int> pos{algo::string::SearchRabinKarpMulti(sentence, words, 3)};
  EXPECT_EQ(pos.size(), 0);
}

/////////////////////////////////////////////
/// Heap's algorithm
/////////////////////////////////////////////

TEST(test_algo_string, heaps_generate)
{
  std::string sample{"METAL"};
  vector<std::string> perms{algo::string::GenerateAllPermutations(sample)};
  EXPECT_EQ(perms.size(), 120);
  EXPECT_TRUE(find(perms.begin(), perms.end(), "LATEM") != perms.end());
  EXPECT_TRUE(find(perms.begin(), perms.end(), "MEALT") != perms.end());
}

/////////////////////////////////////////////
/// Levenshtein distance
/////////////////////////////////////////////

TEST(test_algo_string, levest_dist_standard)
{
  EXPECT_EQ(algo::string::metric::Levenshtein("abracadabra", "cadabraabra"), 6);
  EXPECT_EQ(algo::string::metric::Levenshtein("book", "back"), 2);
  EXPECT_EQ(algo::string::metric::Levenshtein("book", "book"), 0);
  EXPECT_EQ(algo::string::metric::Levenshtein("book", "read"), 4);
  EXPECT_EQ(algo::string::metric::Levenshtein("book", ""), 4);
}

/////////////////////////////////////////////
/// Rotated string
/////////////////////////////////////////////

TEST(test_algo_string, rotated_string_standard)
{
  EXPECT_FALSE(algo::string::IsRotated("judaspriest", "priestsjudas"));
  EXPECT_TRUE(algo::string::IsRotated("judaspriest", "priestjudas"));
  EXPECT_TRUE(algo::string::IsRotated("a", "a"));
  EXPECT_TRUE(algo::string::IsRotated("", ""));
}

/////////////////////////////////////////////
/// Compressed string
/////////////////////////////////////////////

TEST(test_algo_string, compressed_string_standard)
{
  std::string str{""};
  EXPECT_EQ(algo::string::Compress(str), "");
  str = "aa";
  EXPECT_EQ(algo::string::Compress(str), "aa");
  str = "aaabbbb";
  EXPECT_EQ(algo::string::Compress(str), "a3b4");
  str = "abbbcddefgggggggggggh";
  EXPECT_EQ(algo::string::Compress(str), "ab3cd2efg11h");
}

/////////////////////////////////////////////
/// Unique chars
/////////////////////////////////////////////

TEST(test_algo_string, has_unique_chars_standard)
{
  EXPECT_TRUE(algo::string::HasUniqueChars("abcdefg123"));
  EXPECT_TRUE(algo::string::HasUniqueChars("a"));
  EXPECT_TRUE(algo::string::HasUniqueChars(""));
  EXPECT_FALSE(algo::string::HasUniqueChars("abcdefg113"));
  EXPECT_FALSE(algo::string::HasUniqueChars("aa"));
}
