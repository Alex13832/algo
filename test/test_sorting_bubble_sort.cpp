//
// Created by Alexander Karlsson on 2019-10-16.
//
#include "gtest/gtest.h"

#include "sorting_algorithms.h"

#include <algorithm>

using namespace std;

TEST(test_sorting_bubble_sort, simple_test_ints) {
  vector<int> numbers = {1, 9, 10, 2, 1, 1, 3, 2, 1, 4, 50, 40, 40};

  vector<int> b_sort = Sorting::BubbleSort(numbers);

  bool is_s = is_sorted(b_sort.begin(), b_sort.end());

  EXPECT_TRUE(is_s);
}

TEST(test_sorting_bubble_sort, test_empty) {
  vector<int> numbers;

  vector<int> b_sort = Sorting::BubbleSort(numbers);
  EXPECT_EQ(b_sort.size(), 0);
}

TEST(test_sorting_bubble_sort, already_sorted) {
  vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 15};

  vector<int> b_sort = Sorting::BubbleSort(numbers);

  bool is_s = is_sorted(b_sort.begin(), b_sort.end());

  EXPECT_TRUE(is_s);
}

TEST(test_sorting_bubble_sort, negative_numbers) {
  vector<int> numbers = {-1, -10, -5, 5, 6, 1};

  vector<int> b_sort = Sorting::BubbleSort(numbers);

  bool is_s = is_sorted(b_sort.begin(), b_sort.end());

  EXPECT_TRUE(is_s);
}