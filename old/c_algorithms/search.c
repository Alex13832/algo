// Search algorithms, begun 2016-02-03

#include <stdio.h>

// Binary search of arr, note that arr has to be sorted
int binary_search(int* arr, int low, int high, int x)
{
      if (high < low) return -1;

      int mid = (low + high)/2;
      if (arr[mid] > x)
            return binary_search(arr, low, mid-1, x);
      else if
            (arr[mid]< x) return binary_search(arr, mid+1, high, x);
      else
            return mid;
}
