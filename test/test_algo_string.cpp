///
/// \brief Unit tests for string algorithms.
/// \author alex011235
/// \date 2019-10-13
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
#include "gtest/gtest.h"
#include "include/algo.hpp"

using namespace std;
using namespace algo;

/////////////////////////////////////////////
/// Boyer-More
/////////////////////////////////////////////

TEST(test_algo_string, boyer_more_nbr_of_occurences_0)
{
  string text{"Banana banana"};
  string pattern{"Manana"};
  vector<int> matches{strings::SearchBoyerMoore(text, pattern)};
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_algo_string, boyer_more_nbr_of_occurences_1)
{
  string text{"Banana banana"};
  string pattern{"Banana ba"};
  vector<int> matches{strings::SearchBoyerMoore(text, pattern)};
  EXPECT_EQ(matches.size(), 1);
}

TEST(test_algo_string, boyer_more_nbr_of_occurences_many)
{
  string text{
      "Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
      "alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer "
      "delicata consectetuer est at. At nisl cucumber facete qui, eu oblique "
      "Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
      "alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer "
      "delicata consectetuer est at. At nisl cucumber facete qui, eu oblique "};

  string pattern{"cucumber"};

  vector<int> matches = strings::SearchBoyerMoore(text, pattern);
  EXPECT_EQ(matches.size(), 8);
}

TEST(test_algo_string, boyer_more_empty_input_pattern)
{
  string text{"Banana banana"};
  vector<int> matches{strings::SearchBoyerMoore(text, "")};
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_algo_string, boyer_more_empty_input_text)
{
  string text{""};
  string pattern{"Banana"};
  vector<int> matches{strings::SearchBoyerMoore(text, pattern)};
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_algo_string, boyer_more_empty_input)
{
  string empty;
  vector<int> matches{strings::SearchBoyerMoore(empty, empty)};
  EXPECT_EQ(matches.size(), 0);
}

/////////////////////////////////////////////
/// Longest common substring
/////////////////////////////////////////////

TEST(test_algo_string, longest_common_substring_standard)
{
  string A{"otirpporeijgpowkruskaldijkstrawithicecreamergjeågjeopnpoqerhgldijkstrassadar"};
  string B{"iuthewriuthkruskaldijksfuiqgfuqygfnvkjkruskaldijkstrawithicecreamdfbiehf5d"};
  string C{strings::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "kruskaldijkstrawithicecream");
}

TEST(test_algo_string, longest_common_substring_empty_first)
{
  string A;
  string B{"iuthewriuthkruskaldijksfuiqgfuqygfnvkjkruskaldijkstrawithicecreamdfbiehf5d"};
  string C{strings::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(test_algo_string, longest_common_substring_empty_second)
{
  string A{"otirpporeijgpowkruskaldijkstrawithicecreamergjeågjeopnpoqerhgldijkstrassadar"};
  string B;
  string C{strings::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(test_algo_string, longest_common_substring_empty_input)
{
  string A, B;
  string C{strings::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(test_algo_string, longest_common_substring_one_word)
{
  string A{"calculator"};
  string B{"culat"};
  string C{strings::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "culat");
}

TEST(test_algo_string, longest_common_substring_one_char)
{
  string x{strings::LongestCommonSubstring("x", "x")};
  EXPECT_EQ(x, "x");

  x = strings::LongestCommonSubstring("x", "y");
  EXPECT_EQ(x, "");
}

/////////////////////////////////////////////
/// Rabin-Karp
/////////////////////////////////////////////

TEST(test_algo_string, rabin_karp_single_input)
{
  string sentence{"one two one three one two hello one"};
  vector<int> pos{strings::SearchRabinKarpSingle(sentence, "one")};
  EXPECT_EQ(pos.size(), 4);
}

TEST(test_algo_string, rabin_karp_multi_input)
{
  string sentence{"one two one three one two hello one"};
  set<string> words{"one", "two"};
  vector<int> pos = strings::SearchRabinKarpMulti(sentence, words, 3);
  EXPECT_EQ(pos.size(), 6);
}

TEST(test_algo_string, rabin_karp_not_found_single)
{
  string sentence{"one two one three one two hello one"};
  vector<int> pos{strings::SearchRabinKarpSingle(sentence, "four")};
  EXPECT_EQ(pos.size(), 0);
}

TEST(test_algo_string, rabin_karp_not_found_multi)
{
  string sentence{"one two one three one two hello one"};
  set<string> words{"four", "five"};
  vector<int> pos{strings::SearchRabinKarpMulti(sentence, words, 3)};
  EXPECT_EQ(pos.size(), 0);
}

/////////////////////////////////////////////
/// Heap's algorithm
/////////////////////////////////////////////

TEST(test_algo_string, heaps_generate)
{
  string sample{"METAL"};
  vector<string> perms{strings::GenerateAllPermutations(sample)};
  EXPECT_EQ(perms.size(), 120);
  EXPECT_TRUE(find(perms.begin(), perms.end(), "LATEM") != perms.end());
  EXPECT_TRUE(find(perms.begin(), perms.end(), "MEALT") != perms.end());
}

/////////////////////////////////////////////
/// Levenshtein distance
/////////////////////////////////////////////

TEST(test_algo_string, levest_dist_standard)
{
  EXPECT_EQ(strings::LevDistance("abracadabra", "cadabraabra"), 6);
  EXPECT_EQ(strings::LevDistance("book", "back"), 2);
  EXPECT_EQ(strings::LevDistance("book", "book"), 0);
  EXPECT_EQ(strings::LevDistance("book", "read"), 4);
  EXPECT_EQ(strings::LevDistance("book", ""), 4);
}

/////////////////////////////////////////////
/// Rotated string
/////////////////////////////////////////////

TEST(test_algo_string, rotated_string_standard)
{
  EXPECT_FALSE(strings::IsRotated("judaspriest", "priestsjudas"));
  EXPECT_TRUE(strings::IsRotated("judaspriest", "priestjudas"));
  EXPECT_TRUE(strings::IsRotated("a", "a"));
  EXPECT_TRUE(strings::IsRotated("", ""));
}

/////////////////////////////////////////////
/// Compressed string
/////////////////////////////////////////////

TEST(test_algo_string, compressed_string_standard)
{
  string str{""};
  EXPECT_EQ(strings::Compress(str), "");
  str = "aa";
  EXPECT_EQ(strings::Compress(str), "aa");
  str = "aaabbbb";
  EXPECT_EQ(strings::Compress(str), "a3b4");
  str = "abbbcddefgggggggggggh";
  EXPECT_EQ(strings::Compress(str), "ab3cd2efg11h");
}

/////////////////////////////////////////////
/// Unique chars
/////////////////////////////////////////////

TEST(test_algo_string, has_unique_chars_standard)
{
  EXPECT_TRUE(strings::HasUniqueChars("abcdefg123"));
  EXPECT_TRUE(strings::HasUniqueChars("a"));
  EXPECT_TRUE(strings::HasUniqueChars(""));
  EXPECT_FALSE(strings::HasUniqueChars("abcdefg113"));
  EXPECT_FALSE(strings::HasUniqueChars("aa"));
}
