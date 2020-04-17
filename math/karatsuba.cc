/** ------------------------------------------------
* Karatsuba implementation
* Should be implemented with "Big Integer".
* ulong is only used for demonstration purposes.
* --------------------------------------------------*/
#include <iostream>
#include <cmath>

using namespace std;

/* Returns the length of nbr */
int size(ulong nbr)
{
  char buffer[64];
  return sprintf(buffer, "%lu", nbr);
}

/* Splits the integer nbr at m */
pair<ulong, ulong> split(ulong nbr, int m)
{
  ulong splitter = pow(10, m);
  ulong high = nbr / splitter;
  ulong low = nbr % splitter;
  return pair<ulong, ulong>(high, low);
}

/* The Karatsuba algorithm */
ulong karatsuba(ulong nbr1, ulong nbr2)
{
  if (nbr1 < 10 || nbr2 < 10) {
    return nbr1 * nbr2;
  }

  int mid = max(size(nbr1), size(nbr2)) / 2;

  pair<ulong, ulong> spl1 = split(nbr1, mid);
  ulong high1 = spl1.first;
  ulong low1 = spl1.second;

  pair<ulong, ulong> spl2 = split(nbr2, mid);
  ulong high2 = spl2.first;
  ulong low2 = spl2.second;

  ulong z0 = karatsuba(low1, low2);
  ulong z1 = karatsuba((low1 + high1), (low2 + high2));
  ulong z2 = karatsuba(high1, high2);

  return z2 * pow(10, 2 * mid) + (z1 - z2 - z0) * pow(10, mid) + z0;
}

int main()
{
  ulong a, b;
  cin >> a;
  cin >> b;
  cout << karatsuba(a, b) << endl;
}