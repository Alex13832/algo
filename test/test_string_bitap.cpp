#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by Alexander Karlsson on 2019-10-13.
//
#include "gtest/gtest.h"

#include "string_algorithms.h"

using namespace std;

TEST(test_bitap, test_search) {
  string text = "this is a bitap test";
  string pattern = "bitap";
  string res = StringAlgorithm::bitap_search(text, pattern);
  EXPECT_EQ(res, "bitap test");
}

TEST(test_bitap, search_not_found) {
  string text = "this is a bitap test";
  string pattern = "dijkstra";
  string res = StringAlgorithm::bitap_search(text, pattern);
  EXPECT_EQ(res.size(), 0);
}

TEST(test_bitap, empty_pattern) {
  string text = "this is a bitap test";
  string res = StringAlgorithm::bitap_search(text, "");
  EXPECT_EQ(res, text);
}

#pragma clang diagnostic pop