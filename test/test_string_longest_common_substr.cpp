//
// Created by Alexander Karlsson on 2019-10-13.
//

#include "gtest/gtest.h"

#include "string_algorithms.h"

using namespace std;

TEST(test_longest_common_substring, standard) {
  string A("otirpporeijgpowkruskaldijkstrawithicecreamergjeågjeopnpoqerhgldijkstrassadar");
  string B("iuthewriuthkruskaldijksfuiqgfuqygfnvkjkruskaldijkstrawithicecreamdfbiehf5d");

  string C = StringAlgorithm::LongestCommonSubstring(A, B);

  EXPECT_EQ(C, "kruskaldijkstrawithicecream");
}

TEST(test_longest_common_substring, empty_first) {
  string A("");
  string B("iuthewriuthkruskaldijksfuiqgfuqygfnvkjkruskaldijkstrawithicecreamdfbiehf5d");

  string C = StringAlgorithm::LongestCommonSubstring(A, B);

  EXPECT_EQ(C, "");
}

TEST(test_longest_common_substring, empty_second) {
  string A("otirpporeijgpowkruskaldijkstrawithicecreamergjeågjeopnpoqerhgldijkstrassadar");
  string B("");

  string C = StringAlgorithm::LongestCommonSubstring(A, B);

  EXPECT_EQ(C, "");
}

TEST(test_longest_common_substring, empty_input) {
  string A("");
  string B("");

  string C = StringAlgorithm::LongestCommonSubstring(A, B);

  EXPECT_EQ(C, "");
}

TEST(test_longest_common_substring, one_word) {
  string A("calculator");
  string B("culat");

  string C = StringAlgorithm::LongestCommonSubstring(A, B);

  EXPECT_EQ(C, "culat");
}

TEST(test_longest_common_substring, one_char) {
  string x = StringAlgorithm::LongestCommonSubstring("x", "x");
  EXPECT_EQ(x, "x");

  x = StringAlgorithm::LongestCommonSubstring("x", "y");
  EXPECT_EQ(x, "");
}