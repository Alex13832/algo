// Misc. algorithms on arrays
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int max(int x, int y)
{
      return x > y ? x : y;
}

// Solves the maximum subarray problem by using Kadane's algorithm
// Dynamic programming approach
int max_subarray(int* arr, size_t size)
{
      int max_ending_here = arr[0], max_so_far = arr[0];
      size_t i = 0;

      for (i = 0; i < size; i++) {
            max_ending_here = max(arr[i], max_ending_here + arr[i]);
            max_so_far = max(max_so_far, max_ending_here);
      }

      return max_so_far;
}

// Rotates the matrix Im 90 degrees clockwise order
void rotate90(int N, int Im[][N])
{
      N = N - 1;
      int i = 0, j, offset = 0;

      for (i = offset; i < N-offset; i++) {
            for (j = offset; j < N-offset; j++) {
                  // Store tempory, circular dependecy
                  int temp = Im[N-j][i];

                  Im[N-j][i] = Im[N-i][N-j];
                  Im[N-i][N-j] = Im[j][N-i];
                  Im[j][N-i] = Im[i][j];
                  Im[i][j] = temp;
            }
            offset++;
      }
}

// If a (or more) zero is found in mat on row i and column j,
// the elements on row and column i,j will be set to 0
void zero_entries_fix(int N, int M, int mat[][M])
{
      int matcp[N][M];
      memcpy(matcp, mat, N*M*sizeof(int));

      bool found = false;
      int found_column = 0, i, j;

      for (i = 0; i < N; i++) {
            for (j = 0; j < M; j++) {

                  if (!found && matcp[i][j] == 0) {
                        found_column = j;       // Save the found column
                        found = true;
                        matcp[i][j] = 1;        // Set to 1 in order not to check again
                        j = 0;                  // restart, elements -> 0, on that row
                  }

                  if (found) mat[i][j] = 0;
            }

            if (found) {
                  for (j = 0; j < N; j++)
                        mat[j][found_column] = 0;

                  i--;        // check same row for multiple zeros
                              // i >= 0, since i++ after next }
            }

            found = false;
            found_column = 0;
      }
}
