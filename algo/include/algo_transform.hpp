///
/// \brief Header for string algorithms.
/// \author alex011235
/// \date 2020-04-19
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2015-08-12 FFT and iFFT
///

#ifndef ALGORITHM_TRANSFORM_TRANSFORM_ALGORITHMS_HPP_
#define ALGORITHM_TRANSFORM_TRANSFORM_ALGORITHMS_HPP_

#include <cmath>
#include <complex>
#include <valarray>

namespace algo::transform {

using FftTransf = std::valarray<std::complex<double>>;

/// \brief Computes the discrete Fourier transform (DFT) of the input sequence A. FFT converts the input
/// usually from the time domain to frequency domain. The length of the input must be a power of two.
/// \param A input to transform.
/// \return Signal in frequency domain.
/// \link <a href=https://en.wikipedia.org/wiki/Fast_Fourier_transform">FFT, Wikipedia.</a>
FftTransf FFT(const FftTransf& A);

/// \brief Computes the inverse FTT (discrete fourier transform) using the FFT transform. The input
/// sequence length must be a power of two.
/// \param B Sequence to transform.
/// \note B = IFFT(FFT(B))
/// \return Inverse FFT sequence.
/// \link <a href=https://en.wikipedia.org/wiki/Fast_Fourier_transform">FFT, Wikipedia.</a>
FftTransf IFFT(const FftTransf& B);

}// namespace algo::transform

#endif//ALGORITHM_TRANSFORM_TRANSFORM_ALGORITHMS_HPP_
