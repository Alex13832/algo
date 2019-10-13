#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by Alexander Karlsson on 2019-10-13.
//

#include "gtest/gtest.h"

#include "string_algorithms.h"

using namespace std;


TEST(test_boyer_more, nbr_of_occurences_0) {
  string text = "Banana banana";
  string pattern = "Manana";

  vector<int> matches = StringAlgorithm::boyer_moore(text, pattern);
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_boyer_more, nbr_of_occurences_1) {
  string text = "Banana banana";
  string pattern = "Banana ba";

  vector<int> matches = StringAlgorithm::boyer_moore(text, pattern);
  EXPECT_EQ(matches.size(), 1);
}

TEST(test_boyer_more, nbr_of_occurences_many) {
  string text = "Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
                "alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer "
                "delicata consectetuer est at. At nisl cucumber facete qui, eu oblique "
                "Lorem cucumber ipsum dolor sit amet, cucumber vel modus "
                "alienum eu. Omnium oporteat definitiones cu mei. Has et solum cucumber vitae, viderer "
                "delicata consectetuer est at. At nisl cucumber facete qui, eu oblique ";

  string pattern = "cucumber";

  vector<int> matches = StringAlgorithm::boyer_moore(text, pattern);
  EXPECT_EQ(matches.size(), 8);
}

TEST(test_boyer_more, empty_input_pattern) {
  string text = "Banana banana";
  vector<int> matches = StringAlgorithm::boyer_moore(text, "");
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_boyer_more, empty_input_text) {
  string pattern = "Banana";
  vector<int> matches = StringAlgorithm::boyer_moore("", pattern);
  EXPECT_EQ(matches.size(), 0);
}

TEST(test_boyer_more, empty_input) {
  vector<int> matches = StringAlgorithm::boyer_moore("", "");
  EXPECT_EQ(matches.size(), 0);
}
#pragma clang diagnostic pop