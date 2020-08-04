Transform algorithms
======

This namespace (`algo::transform`) contains algorithms for data transforms.

## Fast Fourier transform, FFT and the inverse, IFFT

>A fast Fourier transform (FFT) is an algorithm that computes the discrete Fourier transform (DFT) of a sequence, or its inverse 
>(IDFT). Fourier analysis converts a signal from its original domain (often time or space) to a representation in the frequency 
>domain and vice versa. The DFT is obtained by decomposing a sequence of values into components of different frequencies. [Wikipedia](https://en.wikipedia.org/wiki/Fast_Fourier_transform)

```c++
FftTransf FFT(const FftTransf& A);
```

Returns the FFT transform of the input `A`. `FftTransf` is defined as `using FftTransf = std::valarray<std::complex<double>>`.

```c++
FftTransf IFFT(const FftTransf& B);
``` 

Returns the inverse of the FFT transform.

The lenght of the input array in `FFT` and `IFFT` must be a power of two. If the input is not a power of two, it can be fixed by appended
zeros so the length becomes a power of two.

Note that much time as been spent on testing these functions, therefore the correctness of these algorithms might not be 100%. The few
test cases found are however accurate and correct.

### Usage and example

```c++
#include "algo.hpp"

using namespace std;

...

FftTransf data{1.0, 4.0, 3.0, 2.0};
data = algo::transform::FFT(data);
data = algo::transform::IFFT(data);
```


