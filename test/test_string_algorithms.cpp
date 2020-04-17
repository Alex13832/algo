///
/// \brief Unit tests for sort algorithms.
/// \author alex011235
/// \date 2019-10-13
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
#include "gtest/gtest.h"

#include "string_algorithms.hpp"

using namespace std;

/////////////////////////////////////////////
/// Bitap search
/////////////////////////////////////////////

TEST(test_bitap, test_search)
{
  string text{"this is a bitap test"};
  string pattern{"bitap"};
  string res{String::BitapSearch(text, pattern)};
  EXPECT_EQ(res, "bitap test");
}

TEST(test_bitap, search_not_found)
{
  string text{"this is a bitap test"};
  string pattern{"dijkstra"};
  string res{String::BitapSearch(text, pattern)};
  EXPECT_EQ(res.size(), 0);
}

TEST(test_bitap, empty_pattern)
{
  string text{"this is a bitap test"};
  string res{String::BitapSearch(text, "")};
  EXPECT_EQ(res, text);
}

/////////////////////////////////////////////
/// Boyer-More
/////////////////////////////////////////////

TEST(test_boyer_more, nbr_of_occurences_0)
{
  string text{"Banana banana"};
  string pattern{"Manana"};
  vector<int> matches{String::BoyerMore(text, pattern)};
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_boyer_more, nbr_of_occurences_1)
{
  string text{"Banana banana"};
  string pattern{"Banana ba"};
  vector<int> matches{String::BoyerMore(text, pattern)};
  EXPECT_EQ(matches.size(), 1);
}

TEST(test_boyer_more, nbr_of_occurences_many)
{
  string text{"Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
              "alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer "
              "delicata consectetuer est at. At nisl cucumber facete qui, eu oblique "
              "Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
              "alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer "
              "delicata consectetuer est at. At nisl cucumber facete qui, eu oblique "};

  string pattern{"cucumber"};

  vector<int> matches = String::BoyerMore(text, pattern);
  EXPECT_EQ(matches.size(), 8);
}

TEST(test_boyer_more, empty_input_pattern)
{
  string text{"Banana banana"};
  vector<int> matches{String::BoyerMore(text, "")};
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_boyer_more, empty_input_text)
{
  string text{""};
  string pattern{"Banana"};
  vector<int> matches{String::BoyerMore(text, pattern)};
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_boyer_more, empty_input)
{
  string empty;
  vector<int> matches{String::BoyerMore(empty, empty)};
  EXPECT_EQ(matches.size(), 0);
}

/////////////////////////////////////////////
/// Longest common substring
/////////////////////////////////////////////

TEST(test_longest_common_substring, standard)
{
  string A{"otirpporeijgpowkruskaldijkstrawithicecreamergjeågjeopnpoqerhgldijkstrassadar"};
  string B{"iuthewriuthkruskaldijksfuiqgfuqygfnvkjkruskaldijkstrawithicecreamdfbiehf5d"};
  string C{String::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "kruskaldijkstrawithicecream");
}

TEST(test_longest_common_substring, empty_first)
{
  string A;
  string B{"iuthewriuthkruskaldijksfuiqgfuqygfnvkjkruskaldijkstrawithicecreamdfbiehf5d"};
  string C{String::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(test_longest_common_substring, empty_second)
{
  string A{"otirpporeijgpowkruskaldijkstrawithicecreamergjeågjeopnpoqerhgldijkstrassadar"};
  string B;
  string C{String::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(test_longest_common_substring, empty_input)
{
  string A, B;
  string C{String::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(test_longest_common_substring, one_word)
{
  string A{"calculator"};
  string B{"culat"};
  string C{String::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "culat");
}

TEST(test_longest_common_substring, one_char)
{
  string x{String::LongestCommonSubstring("x", "x")};
  EXPECT_EQ(x, "x");

  x = String::LongestCommonSubstring("x", "y");
  EXPECT_EQ(x, "");
}

/////////////////////////////////////////////
/// Rabin-Karp
/////////////////////////////////////////////

TEST(test_rabin_karp, single_input)
{
  string sentence{"one two one three one two hello one"};
  vector<int> pos{String::RabinKarpSingle(sentence, "one")};
  EXPECT_EQ(pos.size(), 4);
}

TEST(test_rabin_karp, multi_input)
{
  string sentence{"one two one three one two hello one"};
  set<string> words{"one", "two"};
  vector<int> pos = String::RabinKarpMulti(sentence, words, 3);
  EXPECT_EQ(pos.size(), 6);
}

TEST(test_rabin_karp, not_found_single)
{
  string sentence{"one two one three one two hello one"};
  vector<int> pos{String::RabinKarpSingle(sentence, "four")};
  EXPECT_EQ(pos.size(), 0);
}

TEST(test_rabin_karp, not_found_multi)
{
  string sentence{"one two one three one two hello one"};
  set<string> words{"four", "five"};
  vector<int> pos{String::RabinKarpMulti(sentence, words, 3)};
  EXPECT_EQ(pos.size(), 0);
}
