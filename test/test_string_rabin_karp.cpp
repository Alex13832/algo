//
// Created by Alexander Karlsson on 2019-10-13.
//

#include "gtest/gtest.h"

#include "string_algorithms.h"

using namespace std;

TEST(test_rabin_karp, single_input) {
  string sentence = "one two one three one two hello one";
  vector<int> pos = StringAlgorithm::RabinKarpSingle(sentence, "one");
  EXPECT_EQ(pos.size(), 4);
}

TEST(test_rabin_karp, multi_input) {
  string sentence = "one two one three one two hello one";
  set<string> words;
  words.insert("one");
  words.insert("two");
  vector<int> pos = StringAlgorithm::RabinKarpMulti(sentence, words, 3);
  EXPECT_EQ(pos.size(), 6);
}

TEST(test_rabin_karp, not_found_single) {
  string sentence = "one two one three one two hello one";
  vector<int> pos = StringAlgorithm::RabinKarpSingle(sentence, "four");
  EXPECT_EQ(pos.size(), 0);
}

TEST(test_rabin_karp, not_found_multi) {
  string sentence = "one two one three one two hello one";
  set<string> words;
  words.insert("four");
  words.insert("five");
  vector<int> pos = StringAlgorithm::RabinKarpMulti(sentence, words, 3);
  EXPECT_EQ(pos.size(), 0);
}
