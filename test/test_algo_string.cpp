///
/// \brief Unit tests for string algorithms.
/// \author alex011235
/// \date 2019-10-13
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
#include <algorithm>
#include <set>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "include/algo_string.hpp"

namespace {
namespace str = algo::string;
}  // namespace

/////////////////////////////////////////////
/// Boyer-More
/////////////////////////////////////////////

TEST(TestAlgoString, BoyerMoreNbrOfOccurences0) {
  std::string text{"Banana banana"};
  const std::string pattern{"Manana"};
  const std::vector<int> matches{str::SearchBoyerMoore(text, pattern)};
  EXPECT_EQ(matches.size(), 0);
}

TEST(TestAlgoString, BoyerMoreNbrOfOccurences1) {
  std::string text{"Banana banana"};
  const std::string pattern{"Banana ba"};
  const std::vector<int> matches{str::SearchBoyerMoore(text, pattern)};
  EXPECT_EQ(matches.size(), 1);
}

TEST(TestAlgoString, BoyerMoreNbrOfOccurencesMany) {
  std::string text{
      "Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
      "alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer "
      "delicata consectetuer est at. At nisl cucumber facete qui, eu oblique "
      "Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
      "alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer "
      "delicata consectetuer est at. At nisl cucumber facete qui, eu oblique "};

  const std::string pattern{"cucumber"};

  const std::vector<int> matches = str::SearchBoyerMoore(text, pattern);
  EXPECT_EQ(matches.size(), 8);
}

TEST(TestAlgoString, BoyerMoreEmptyInputPattern) {
  std::string text{"Banana banana"};
  const std::vector<int> matches{str::SearchBoyerMoore(text, "")};
  EXPECT_EQ(matches.size(), 0);
}

TEST(TestAlgoString, BoyerMoreEmptyInputText) {
  std::string text;
  const std::string pattern{"Banana"};
  const std::vector<int> matches{str::SearchBoyerMoore(text, pattern)};
  EXPECT_EQ(matches.size(), 0);
}

TEST(TestAlgoString, BoyerMoreEmptyInput) {
  std::string empty;
  const std::vector<int> matches{str::SearchBoyerMoore(empty, empty)};
  EXPECT_EQ(matches.size(), 0);
}

/////////////////////////////////////////////
/// Longest common substring
/////////////////////////////////////////////

TEST(TestAlgoString, LongestCommonSubstringStandard) {
  const std::string A{"otirpporeijgpowkruskaldijkstrawithicecreamergjeågjeopnpoqerhgldijkstrassadar"};
  const std::string B{"iuthewriuthkruskaldijksfuiqgfuqygfnvkjkruskaldijkstrawithicecreamdfbiehf5d"};
  const std::string C{str::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "kruskaldijkstrawithicecream");
}

TEST(TestAlgoString, LongestCommonSubstringEmptyFirst) {
  const std::string A;
  const std::string B{"iuthewriuthkruskaldijksfuiqgfuqygfnvkjkruskaldijkstrawithicecreamdfbiehf5d"};
  const std::string C{str::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(TestAlgoString, LongestCommonSubstringEmptySecond) {
  const std::string A{"otirpporeijgpowkruskaldijkstrawithicecreamergjeågjeopnpoqerhgldijkstrassadar"};
  const std::string B;
  const std::string C{str::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(TestAlgoString, LongestCommonSubstringEmptyInput) {
  const std::string A;
  const std::string B;
  const std::string C{str::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "");
}

TEST(TestAlgoString, LongestCommonSubstringOneWord) {
  const std::string A{"calculator"};
  const std::string B{"culat"};
  const std::string C{str::LongestCommonSubstring(A, B)};
  EXPECT_EQ(C, "culat");
}

TEST(TestAlgoString, LongestCommonSubstringOneChar) {
  std::string x{str::LongestCommonSubstring("x", "x")};
  EXPECT_EQ(x, "x");

  x = str::LongestCommonSubstring("x", "y");
  EXPECT_EQ(x, "");
}

/////////////////////////////////////////////
/// Rabin-Karp
/////////////////////////////////////////////

TEST(TestAlgoString, RabinKarpSingleInput) {
  const std::string sentence{"one two one three one two hello one"};
  const std::vector<int> pos{str::SearchRabinKarpSingle(sentence, "one")};
  EXPECT_EQ(pos.size(), 4);
}

TEST(TestAlgoString, RabinKarpMultiInput) {
  const std::string sentence{"one two one three one two hello one"};
  const std::set<std::string> words{"one", "two"};
  const std::vector<int> pos = str::SearchRabinKarpMulti(sentence, words, 3);
  EXPECT_EQ(pos.size(), 6);
}

TEST(TestAlgoString, RabinKarpNotFoundSingle) {
  const std::string sentence{"one two one three one two hello one"};
  const std::vector<int> pos{str::SearchRabinKarpSingle(sentence, "four")};
  EXPECT_EQ(pos.size(), 0);
}

TEST(TestAlgoString, RabinKarpNotFoundMulti) {
  const std::string sentence{"one two one three one two hello one"};
  const std::set<std::string> words{"four", "five"};
  const std::vector<int> pos{str::SearchRabinKarpMulti(sentence, words, 3)};
  EXPECT_EQ(pos.size(), 0);
}

/////////////////////////////////////////////
/// Heap's algorithm
/////////////////////////////////////////////

TEST(TestAlgoString, HeapsGenerate) {
  std::string sample{"METAL"};
  std::vector<std::string> perms{str::GenerateAllPermutations(sample)};
  EXPECT_EQ(perms.size(), 120);  // 5!
  EXPECT_TRUE(find(perms.begin(), perms.end(), "LATEM") != perms.end());
  EXPECT_TRUE(find(perms.begin(), perms.end(), "MEALT") != perms.end());
}

/////////////////////////////////////////////
/// Rotated string
/////////////////////////////////////////////

TEST(TestAlgoString, RotatedStringStandard) {
  EXPECT_FALSE(str::IsRotated("judaspriest", "priestsjudas"));
  EXPECT_TRUE(str::IsRotated("judaspriest", "priestjudas"));
  EXPECT_TRUE(str::IsRotated("a", "a"));
  EXPECT_TRUE(str::IsRotated("", ""));
}

/////////////////////////////////////////////
/// Compressed string
/////////////////////////////////////////////

TEST(TestAlgoString, CompressedStringStandard) {
  std::string str;
  EXPECT_EQ(str::Compress(str), "");
  str = "aa";
  EXPECT_EQ(str::Compress(str), "aa");
  str = "aaabbbb";
  EXPECT_EQ(str::Compress(str), "a3b4");
  str = "abbbcddefgggggggggggh";
  EXPECT_EQ(str::Compress(str), "ab3cd2efg11h");
}

/////////////////////////////////////////////
/// Unique chars
/////////////////////////////////////////////

TEST(TestAlgoString, HasUniqueCharsStandard) {
  EXPECT_TRUE(str::HasUniqueChars("abcdefg123"));
  EXPECT_TRUE(str::HasUniqueChars("a"));
  EXPECT_TRUE(str::HasUniqueChars(""));
  EXPECT_FALSE(str::HasUniqueChars("abcdefg113"));
  EXPECT_FALSE(str::HasUniqueChars("aa"));
}

/////////////////////////////////////////////
/// Levenshtein distance
/////////////////////////////////////////////

TEST(TestAlgoString, LevestDistStandard) {
  EXPECT_EQ(str::metric::Levenshtein("abracadabra", "cadabraabra"), 6);
  EXPECT_EQ(str::metric::Levenshtein("book", "back"), 2);
  EXPECT_EQ(str::metric::Levenshtein("book", "book"), 0);
  EXPECT_EQ(str::metric::Levenshtein("book", "read"), 4);
  EXPECT_EQ(str::metric::Levenshtein("book", ""), 4);
}

/////////////////////////////////////////////
/// Hamming distance
/////////////////////////////////////////////

TEST(TestAlgoString, TestHammingDistance) {
  EXPECT_EQ(str::metric::Hamming("Venus", "Jupiter"), -1);
  EXPECT_EQ(str::metric::Hamming("", ""), 0);
  EXPECT_EQ(str::metric::Hamming("A", "a"), 1);
  EXPECT_EQ(str::metric::Hamming("Aa", "Ab"), 1);
  EXPECT_EQ(str::metric::Hamming("Karolin", "Kerstin"), 3);
  EXPECT_EQ(str::metric::Hamming("Kathrin", "Kerstin"), 4);
  EXPECT_EQ(str::metric::Hamming("1011101", "1001001"), 2);
}

/////////////////////////////////////////////
/// Dice coefficient
/////////////////////////////////////////////

TEST(TestAlgoString, TestDiceCoeff) {
  EXPECT_EQ(str::metric::Dice("night", "nacht"), 0.25);
  double dice{str::metric::Dice("complement", "compliment")};
  EXPECT_GT(dice, 0.7777);
  EXPECT_LT(dice, 0.7778);
  dice = str::metric::Dice("bazaar", "bizarre");
  EXPECT_GT(dice, 0.3635);
  EXPECT_LT(dice, 0.3637);
  dice = str::metric::Dice("algorithms are fun", "logarithms are not");
  EXPECT_GT(dice, 0.5881);
  EXPECT_LT(dice, 0.5883);
  EXPECT_EQ(str::metric::Dice("equal string", "equal string"), 1.0);
  EXPECT_EQ(str::metric::Dice("ga ga ga", "ga ga ga"), 1.0);
}

/////////////////////////////////////////////
/// Jaro-Winkler (distance)
/////////////////////////////////////////////

TEST(TestAlgoString, TestJaroWinkler) {
  double jw{str::metric::JaroWinkler("crate", "trace")};
  EXPECT_GT(jw, 0.733333);
  EXPECT_LT(jw, 0.733334);

  jw = str::metric::JaroWinkler("crate", "crate");
  EXPECT_EQ(jw, 1.0);

  jw = str::metric::JaroWinkler("abcde", "fghij");
  EXPECT_EQ(jw, 0.0);

  jw = str::metric::JaroWinkler("trate", "trace");
  EXPECT_GT(jw, 0.906666);
  EXPECT_LT(jw, 0.906668);

  jw = str::metric::JaroWinkler("arnab", "aranb");
  EXPECT_GT(jw, 0.946666);
  EXPECT_LT(jw, 0.946668);

  jw = str::metric::JaroWinkler("dwayne", "duane");
  EXPECT_GT(jw, 0.839);
  EXPECT_LT(jw, 0.841);
}