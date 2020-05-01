// Quicksort algorithm 2016-02-02

#include <stdlib.h>
#include <stdio.h>

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int *arr, int low, int high)
{
      int x = arr[high]; // pivot
      int i = low - 1;

      int j;
      for (j = low; j != high; j++) {
            if (arr[j] <= x) {
                  i++;
                  swap(&arr[j], &arr[i]); // Swap elements
            }
      }

      swap(&arr[i+1], &arr[high]);
      return (i + 1);
}

// Sorting using the quicksort algorithm
void quicksort(int* arr, int low, int high)
{
      if (low < high) {
            int pivot = partition(arr, low, high);
            quicksort(arr, low, pivot - 1);
            quicksort(arr, pivot + 1, high);
      }
}
