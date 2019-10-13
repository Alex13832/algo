#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
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
#pragma clang diagnostic pop