///
/// \brief Unit tests for sort algorithms.
/// \author alex011235
/// \date 2019-10-17
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "gtest/gtest.h"

#include "sort_algorithms.hpp"

#include <algorithm>

using namespace std;

/////////////////////////////////////////////
/// Merge-sort
/////////////////////////////////////////////

TEST(test_sort_merge_sort, simple_test_ints)
{
  vector<int> numbers{1, 9, 10, 2, 1, 1, 3, 2, 1, 4, 40, 40, 1};
  vector<int> b_sort{Sort::MergeSort(numbers)};

  EXPECT_TRUE(is_sorted(b_sort.begin(), b_sort.end()));
}

TEST(test_sort_merge_sort, test_empty)
{
  vector<int> numbers;
  vector<int> b_sort{Sort::MergeSort(numbers)};

  EXPECT_EQ(b_sort.size(), 0);
}

TEST(test_sort_merge_sort, already_sorted)
{
  vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 15};
  vector<int> b_sort{Sort::MergeSort(numbers)};

  EXPECT_TRUE(is_sorted(b_sort.begin(), b_sort.end()));
}

TEST(test_sort_merge_sort, negative_numbers)
{
  vector<int> numbers{-1, -10, -5, 5, 6, 1};
  vector<int> b_sort{Sort::MergeSort(numbers)};

  EXPECT_TRUE(is_sorted(b_sort.begin(), b_sort.end()));
}

/////////////////////////////////////////////
/// Bubble-sort
/////////////////////////////////////////////

TEST(test_sort_bubble_sort, simple_test_ints)
{
  vector<int> numbers{1, 9, 10, 2, 1, 1, 3, 2, 1, 4, 50, 40, 40};
  vector<int> b_sort{Sort::BubbleSort(numbers)};
  EXPECT_TRUE(is_sorted(b_sort.begin(), b_sort.end()));
}

TEST(test_sort_bubble_sort, test_empty)
{
  vector<int> numbers;
  vector<int> b_sort{Sort::BubbleSort(numbers)};
  EXPECT_EQ(b_sort.size(), 0);
}

TEST(test_sort_bubble_sort, already_sorted)
{
  vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 15};
  vector<int> b_sort = Sort::BubbleSort(numbers);
  EXPECT_TRUE(is_sorted(b_sort.begin(), b_sort.end()));
}

TEST(test_sort_bubble_sort, negative_numbers)
{
  vector<int> numbers{-1, -10, -5, 5, 6, 1};
  vector<int> b_sort{Sort::BubbleSort(numbers)};
  EXPECT_TRUE(is_sorted(b_sort.begin(), b_sort.end()));
}

/////////////////////////////////////////////
/// Quick-sort
/////////////////////////////////////////////

TEST(test_sort_quicksort, simple_test_ints)
{
  vector<int> numbers{1, 9, 10, 2, 1, 1, 3, 2, 1, 4, 50, 40, 40};
  Sort::QuickSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_quicksort, test_empty)
{
  vector<int> numbers;
  Sort::QuickSort(numbers);
  EXPECT_EQ(numbers.size(), 0);
}

TEST(test_sort_quicksort, already_sorted)
{
  vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 15};
  Sort::QuickSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_quicksort, negative_numbers)
{
  vector<int> numbers{-1, -10, -5, 5, 6, 1};
  Sort::QuickSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_quicksort, other_type_floating)
{
  vector<double> numbers{-10.5, 2.5, 3.14, -3.14};
  Sort::QuickSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_quicksort, other_type_string)
{
  vector<string> strings{"Venus", "Mars", "Jupiter", "Tellus", "Mercury"};
  Sort::QuickSort(strings);
  EXPECT_TRUE(is_sorted(strings.begin(), strings.end()));
}
