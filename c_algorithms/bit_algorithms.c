// Bit algorithms
// Some code Credit to Sean Eron Anderson at Stanford University
// Modified to usable code by me, Alexander Karlsson
// begun 2016-02-02
#include <stdlib.h>
#include <limits.h>

/** LEGEND ============================================
      &     And
      ^     Exclusive or
      |     or
      ~     not (exclude)
=======================================================*/

int sign_of_int(int n)
{
      return -(n < 0);
}

// ec == economy, save one operation :)
int sign_of_int_ec(int n)
{
      return n >> (sizeof(int) * CHAR_BIT - 1);
}

int opposite_sign(int x, int y)
{
      return ((x ^ y) < 0);
}

// Returns a non-negative number of even numbers
int is_even(int x)
{
      return (x & 1) == 0;
}

// Test if bit n is 1
int isbitNset(unsigned x, unsigned n)
{
      return (x & (1 << n));
}

// Set bit n to 1
int setbitN(unsigned x, unsigned n)
{
      return (x | (1 << n));
}

// Set bit n to 0
int unsetbitN(unsigned x, unsigned n)
{
      return (x & ~(1 << n));
}

// Toggle bit n -> 1, 1 -> 0
int togglebitN(unsigned x, unsigned n)
{
      return (x ^ (1 << n));
}

// Returns the absolute number of x
unsigned int abs_of_int(int x)
{
      int const mask = x >> (sizeof(int) * CHAR_BIT - 1);
      unsigned res = (x + mask) ^ mask;
      return res;
}

// Returns the smallest of x and y
int min_of(int x, int y)
{
      return x < y ? x : y;
}

// Returns the smallest of x, y and z
int min_of3(int x, int y, int z)
{
      return x < y ? (x < z ? x : z) : (y < z ? y : z);
}

// Returns the larger of x and y
int max_of(int x, int y)
{
      return x > y ? x : y;
}

// Returns if x is a power of 2
int is_power_of2(int x)
{
      return x && !(x & (x - 1)); // iff true: pos && !0
}

// Returns the next power of 2 number, e.g. in: 1022 out: 1024
unsigned int next_power_of2(unsigned x)
{
      unsigned count = 0;

      if (x && !(x & (x -  1)))
            return x;

      while (x != 0) {
            x >>= 1;
            count++;
      }

      return 1 << count;
}

// Swaps the bits in x (1010 -> 0101)
int swap_bits(int x)
{
      unsigned int n = next_power_of2(x);
      return x ^ (n - 1);
}

// Count the number of bits set in n
unsigned count_bits(unsigned n)
{
      return n == 0 ? 0 : ((n % 2 == 0 ? 0 : 1) + count_bits(n/2));
}

// Count the number of set bits, from 1 up to n
unsigned count_bitsN(unsigned n)
{
      unsigned count = 0, i;
      for (i = 0; i <=n; i++)
            count += count_bits(i);

      return count;
}

// Adds two numbers with bit operations
int add(int x, int y)
{
      while (y != 0) {
            int carry = x & y;
            x = x ^ y;
            y = carry << 1;
      }

      return x;
}

// Modulo operation, but only for divisors n that are powers of two
int modulo(unsigned x, unsigned n)
{
      return (x & (n - 1));
}

// Negate n nibbles from 0 counting up to n
int neg_nibbles(unsigned x, unsigned n)
{
      int m = (1 << (4*(n + 1)));
      return x - modulo(x, m);
}
