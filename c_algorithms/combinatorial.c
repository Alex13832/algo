#include <stdio.h>

int maxx(int x, int y)
{
      return x > y ? x : y;
}

// Knapsack problem,
// packing your most valuable items without overloading your luggage.
// Input: v: values, w: weights, n: #items, W: capacity
int knapsack(int* v, int* w, size_t n, int W)
{
      int m[n+1][W+1];

      size_t i,j;
      for (i = 0; i < W; i++)
            m[0][i] = 0;

      for (i = 1; i <= n; i++) {
            for (j = 0; j <= W; j++) {
                  if (w[i-1] <= j)
                        m[i][j] = maxx(m[i-1][j], m[i-1][j-w[i-1]] + v[i-1]);
                  else
                        m[i][j] = m[i-1][j];
            }
      }

      return m[n][W];
}
