/* -------------------------------------------------------------------
* Fast Fourier Transform (FFT) and inverse FFT (iFFT) 
* Alexander Karlsson, begun 2015-08-12
* -------------------------------------------------------------------- */
#include <complex>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <valarray>

using namespace std;

typedef complex<double> complx;
typedef valarray<complx> comp_array;
typedef valarray<comp_array> comp_mat;

# define M_PI 3.14159265358979323846

bool poweroftwo(size_t N)
{
  if (N % 2 != 0) return false;

  while (N % 2 == 0 && N != 2) N = N / 2;

  return N == 2;
}

/* Fast fourier transform, FFT*/
comp_array FFT(comp_array A)
{
  size_t N = A.size();

  if (N == 1) return A;
  /* Controls if the size is a power of 2*/
  if (!poweroftwo(N)) throw -1;

  comp_array even_part(N / 2), odd_part(N / 2);
  for (size_t i = 0; i < N / 2; ++i) {
    even_part[i] = A[2 * i];
    odd_part[i] = A[2 * i + 1];
  }

  comp_array res_ev = FFT(even_part);
  comp_array res_odd = FFT(odd_part);

  for (size_t i = 0; i < N / 2; ++i) {
    complx comp = polar(1.0, -2 * M_PI * i / N) * res_odd[i];
    A[i] = res_ev[i] + comp;
    A[i + N / 2] = res_ev[i] - comp;
  }

  return A;
}

/* Inverse Fast fourier transform, iFFT*/
comp_array iFFT(comp_array B)
{
  transform(begin(B), end(B), begin(B), [&](complx &c) { return conj(c); });
  B = FFT(B);
  transform(begin(B), end(B), begin(B), [&](complx &c) { return conj(c); });

  size_t N = B.size();

  for_each(begin(B), end(B), [&](complx &comp) {
    complx c(real(comp) / N, imag(comp) / N);
    comp = c;
  });

  return B;
}