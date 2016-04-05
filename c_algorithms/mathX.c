#include <stdio.h>
#include <limits.h>
#include "multi_num.c"


// Computes the binomial coefficient of n and k
unsigned binomial(unsigned n, unsigned k)
{
      if (k > n)
            return 0;
      if ((k==0)||(k==n))
            return 1;

      k = min_of(k, n-k);

      unsigned i, c = 1;
      for (i = 0; i < k; i++)
            c = c * (n - i) / (i + 1);

      return c;
}

// Uses multi_num for computation of n-factorial
// Current implementation will print the result, but could be extended
// to return the number struct instead.
void factorial(unsigned n)
{
      number* num = make_number("1");

      size_t i;
      for (i = 1; i < n; i++)
            mult_num(num,i);

      print_number(num);
      free(num);
}

// Uses multi_num for computation of the n:th Fibonacci number
// Current implementation will only print the number.
void fibonacci(unsigned n)
{
      number* num1 = make_number("0");
      number* num2 = make_number("1");
      number* num_temp;

      unsigned i;
      for (i = 1; i < n; i++) {
            num_temp = add_nums(num1, num2);
            num1 = num2;
            num2 = num_temp;
      }

      print_number(num_temp);
      free(num1); free(num2);
}

// Computes the greatest common divisior of x and y
unsigned gcd(unsigned long x, unsigned long y)
{
      unsigned m = x, n = y;

      while (!(m==0||n==0)) {
            if (m >= n)
                  m = m - n;
            else
                  n = n - m;
      }
      return m == 0 ? n : m;
}

// Computes the least common multiple
unsigned lcm(unsigned x, unsigned y)
{
      return x*y / gcd(x,y);
}

int powX(int x, unsigned n)
{
      if (n == 0) return 1;

      int prod = powX(x, n/2);
      if (modulo(n,2) == 0) return prod * prod;
      return x * prod * prod;
}
