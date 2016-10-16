#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bit_algorithms.c"

// Prints the n first lines of Pascal's triangle
void pascals_triangle(int n)
{
      size_t line;
      for (line = 1; line <= n; line++) {
            int C = 1, i;

            for (i = 1; i <= line; i++) {
                  printf("%d ", C);
                  C = C * (line - i) / i;
            }

            putchar('\n');
      }
}

// Computes the angle between the hour and minut hands
int clock_angle(int h, int m)
{
      if (h < 0 || m < 0 || h > 23 || m > 59) {
            printf("Wrong input format\n");
            return -1;
      }

      int hour_angle = 0.5 * ((h % 12)*60 + m);
      int minute_angle = 6*m;
      int angle = abs(hour_angle - minute_angle);
      angle = min_of(360-angle, angle);

      return angle;
}

// Counts the number of twos in the rang 1...n
int count_number2_inrange(unsigned n)
{
      int super_count = 0;

      int i;
      for (i = 1; i <= n; i++) {
            int x = i;
            while (x != 0) {
                  if (x % 10 == 2) super_count++;

                  x /= 10;
            }
      }
      return super_count;
}
