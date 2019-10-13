//
// Created by Alexander Karlsson on 2019-10-13.
//
#include "gtest/gtest.h"

#include "string_algorithms.h"

using namespace std;

/**
 * Test if the bitap algorithm finds the pattern.
 */
TEST(string_algorithms_bitap, test_search) {

  string text = "this is a bitap test";
  string pattern = "bitap";

  string res = StringAlgorithm::bitap_search(text, pattern);
  EXPECT_EQ(res, "bitap test");
}

/**
 * Test what happens if pattern is not found.
 */
TEST(string_algorithms_bitap, test_search_not_found) {
  string text = "this is a bitap test";
  string pattern = "dijkstra";

  string res = StringAlgorithm::bitap_search(text, pattern);
  EXPECT_EQ(res.size(), 0);
}

/**
 * Test what happens if pattern is empty.
 */
TEST(string_algorithms_bitap, test_empty_pattern) {
  string text = "this is a bitap test";
  string pattern = "";

  string res = StringAlgorithm::bitap_search(text, pattern);
  EXPECT_EQ(res, text);
}