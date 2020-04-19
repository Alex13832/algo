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
using namespace algo;


/////////////////////////////////////////////
/// Bubble-sort
/////////////////////////////////////////////

TEST(test_sort_bubble_sort, simple_test_ints)
{
  vector<int> numbers{1, 9, 10, 2, 1, 1, 3, 2, 1, 4, 50, 40, 40};
  sort::BubbleSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_bubble_sort, test_empty)
{
  vector<int> numbers;
  sort::BubbleSort(numbers);
  EXPECT_EQ(numbers.size(), 0);
}

TEST(test_sort_bubble_sort, already_sorted)
{
  vector<unsigned> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 15};
  sort::BubbleSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_bubble_sort, negative_numbers)
{
  vector<int> numbers{-1, -10, -5, 5, 6, 1};
  sort::BubbleSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_bubble_sort, other_type_float)
{
  vector<double> numbers{-10.5, 2.5, 3.14, -3.14};
  sort::BubbleSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_bubble_sort, other_type_string)
{
  vector<string> strings{"Venus", "Mars", "Jupiter", "Saturn", "Mercury"};
  sort::BubbleSort(strings);
  EXPECT_TRUE(is_sorted(strings.begin(), strings.end()));
}

/////////////////////////////////////////////
/// Bucket-sort
/////////////////////////////////////////////

TEST(test_sort_bucket_sort, simple_test_ints)
{
  vector<int> numbers{1, 9, 10, 2, 1, 1, 3, 2, 1, 4, 50, 40, 40};
  sort::BucketSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_bucket_sort, test_empty)
{
  vector<int> numbers;
  sort::BucketSort(numbers);
  EXPECT_EQ(numbers.size(), 0);
}

TEST(test_sort_bucket_sort, already_sorted)
{
  vector<unsigned> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 15};
  sort::BucketSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_bucket_sort, negative_numbers)
{
  vector<int> numbers{-1, -10, -5, 5, 6, 1};
  sort::BucketSort(numbers);
  EXPECT_FALSE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_bucket_sort, other_type_float_all_positive)
{
  vector<double> numbers{10.5, 2.5, 3.14, 3.14};
  sort::BucketSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

/////////////////////////////////////////////
/// Gnome-sort
/////////////////////////////////////////////

TEST(test_sort_gnome_sort, simple_test_ints)
{
  vector<int> numbers{1, 9, 10, 2, 1, 1, 3, 2, 1, 4, 40, 40, 1};
  sort::GnomeSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_gnome_sort, test_empty)
{
  vector<int> numbers;
  sort::GnomeSort(numbers);
  EXPECT_EQ(numbers.size(), 0);
}

TEST(test_sort_gnome_sort, already_sorted)
{
  vector<unsigned> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 15};
  sort::GnomeSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_gnome_sort, negative_numbers)
{
  vector<int> numbers{-1, -10, -5, 5, 6, 1};
  sort::GnomeSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_gnome_sort, other_type_float)
{
  vector<double> numbers{-10.5, 2.5, 3.14, -3.14};
  sort::GnomeSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_gnome_sort, other_type_string)
{
  vector<string> strings{"Venus", "Mars", "Jupiter", "Saturn", "Mercury"};
  sort::GnomeSort(strings);
  EXPECT_TRUE(is_sorted(strings.begin(), strings.end()));
}

/////////////////////////////////////////////
/// Heap-sort
/////////////////////////////////////////////

TEST(test_sort_heap_sort, simple_test_ints)
{
  vector<int> numbers{1, 9, 10, 2, 1, 1, 3, 2, 1, 4, 40, 40, 1};
  sort::HeapSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_heap_sort, test_empty)
{
  vector<int> numbers;
  sort::HeapSort(numbers);
  EXPECT_EQ(numbers.size(), 0);
}

TEST(test_sort_heap_sort, already_sorted)
{
  vector<unsigned> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 15};
  sort::HeapSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_heap_sort, negative_numbers)
{
  vector<int> numbers{-1, -10, -5, 5, 6, 1};
  sort::HeapSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_heap_sort, other_type_float)
{
  vector<double> numbers{-10.5, 2.5, 3.14, -3.14};
  sort::HeapSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_heap_sort, other_type_string)
{
  vector<string> strings{"Venus", "Mars", "Jupiter", "Saturn", "Mercury"};
  sort::HeapSort(strings);
  EXPECT_TRUE(is_sorted(strings.begin(), strings.end()));
}

/////////////////////////////////////////////
/// Insertion-sort
/////////////////////////////////////////////

TEST(test_sort_insertion_sort, simple_test_ints)
{
  vector<int> numbers{1, 9, 10, 2, 1, 1, 3, 2, 1, 4, 40, 40, 1};
  sort::InsertionSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_insertion_sort, test_empty)
{
  vector<int> numbers;
  sort::InsertionSort(numbers);
  EXPECT_EQ(numbers.size(), 0);
}

TEST(test_sort_insertion_sort, already_sorted)
{
  vector<unsigned> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 15};
  sort::InsertionSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_insertion_sort, negative_numbers)
{
  vector<int> numbers{-1, -10, -5, 5, 6, 1};
  sort::InsertionSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_insertion_sort, other_type_float)
{
  vector<double> numbers{-10.5, 2.5, 3.14, -3.14};
  sort::InsertionSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_insertion_sort, other_type_string)
{
  vector<string> strings{"Venus", "Mars", "Jupiter", "Saturn", "Mercury"};
  sort::InsertionSort(strings);
  EXPECT_TRUE(is_sorted(strings.begin(), strings.end()));
}

/////////////////////////////////////////////
/// Merge-sort
/////////////////////////////////////////////

TEST(test_sort_merge_sort, simple_test_ints)
{
  vector<int> numbers{1, 9, 10, 2, 1, 1, 3, 2, 1, 4, 40, 40, 1};
  sort::MergeSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_merge_sort, test_empty)
{
  vector<int> numbers;
  sort::MergeSort(numbers);
  EXPECT_EQ(numbers.size(), 0);
}

TEST(test_sort_merge_sort, already_sorted)
{
  vector<unsigned> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 15};
  sort::MergeSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_merge_sort, negative_numbers)
{
  vector<int> numbers{-1, -10, -5, 5, 6, 1};
  sort::MergeSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_merge_sort, other_type_float)
{
  vector<double> numbers{-10.5, 2.5, 3.14, -3.14};
  sort::MergeSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_merge_sort, other_type_string)
{
  vector<string> strings{"Venus", "Mars", "Jupiter", "Saturn", "Mercury"};
  sort::MergeSort(strings);
  EXPECT_TRUE(is_sorted(strings.begin(), strings.end()));
}

/////////////////////////////////////////////
/// Quick-sort
/////////////////////////////////////////////

TEST(test_sort_quicksort, simple_test_ints)
{
  vector<int> numbers{1, 9, 10, 2, 1, 1, 3, 2, 1, 4, 50, 40, 40};
  sort::QuickSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_quicksort, test_empty)
{
  vector<int> numbers;
  sort::QuickSort(numbers);
  EXPECT_EQ(numbers.size(), 0);
}

TEST(test_sort_quicksort, already_sorted)
{
  vector<unsigned> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 15};
  sort::QuickSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_quicksort, negative_numbers)
{
  vector<int> numbers{-1, -10, -5, 5, 6, 1};
  sort::QuickSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_quicksort, other_type_float)
{
  vector<double> numbers{-10.5, 2.5, 3.14, -3.14};
  sort::QuickSort(numbers);
  EXPECT_TRUE(is_sorted(numbers.begin(), numbers.end()));
}

TEST(test_sort_quicksort, other_type_string)
{
  vector<string> strings{"Venus", "Mars", "Jupiter", "Saturn", "Mercury"};
  sort::QuickSort(strings);
  EXPECT_TRUE(is_sorted(strings.begin(), strings.end()));
}
