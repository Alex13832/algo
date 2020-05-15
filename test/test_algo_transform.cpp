///
/// \brief Unit tests for transform algorithms.
/// \author alex011235
/// \date 2020-04-22
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <iostream>

#include "gtest/gtest.h"
#include "include/algo_transform.hpp"

using namespace std;
using namespace algo::transform;

/////////////////////////////////////////////
/// FFT tests
/////////////////////////////////////////////

TEST(test_algo_transform, fft_ifft_trivial_1)
{
  FftTransf data{1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0};
  FftTransf transf{FFT(data)};
  FftTransf itransf{IFFT(transf)};

  for (size_t i = 0; i < data.size(); i++) {
    EXPECT_EQ(static_cast<int>(data[i].real()), static_cast<int>(itransf[i].real()));
    EXPECT_EQ(static_cast<int>(data[i].imag()), static_cast<int>(itransf[i].imag()));

    if (i < 4) {
      EXPECT_EQ(static_cast<int>(itransf[i].real()), 1);
    } else {
      EXPECT_EQ(static_cast<int>(itransf[i].real()), 0);
    }
  }
}

TEST(test_algo_transform, fft_ifft_trivial_2)
{
  FftTransf data{1.0, 4.0, 3.0, 2.0};
  data = FFT(data);

  EXPECT_DOUBLE_EQ(data[0].real(), 10);
  EXPECT_DOUBLE_EQ(data[0].imag(), 0);
  EXPECT_DOUBLE_EQ(data[1].real(), -2);
  EXPECT_DOUBLE_EQ(data[1].imag(), -2);
  EXPECT_DOUBLE_EQ(data[2].real(), -2);
  EXPECT_DOUBLE_EQ(data[2].imag(), 0);
  EXPECT_DOUBLE_EQ(data[3].real(), -2);
  EXPECT_DOUBLE_EQ(data[3].imag(), 2);

  data = IFFT(data);
  EXPECT_DOUBLE_EQ(round(data[0].real()), 1.0);
  EXPECT_DOUBLE_EQ(round(data[0].imag()), 0.0);
  EXPECT_DOUBLE_EQ(round(data[1].real()), 4.0);
  EXPECT_DOUBLE_EQ(round(data[1].imag()), 0.0);
  EXPECT_DOUBLE_EQ(round(data[2].real()), 3.0);
  EXPECT_DOUBLE_EQ(round(data[2].imag()), 0.0);
  EXPECT_DOUBLE_EQ(round(data[3].real()), 2.0);
  EXPECT_DOUBLE_EQ(round(data[3].imag()), 0.0);
}

TEST(test_algo_transform, fft_not_pow_of_two)
{
  FftTransf data{1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
  FftTransf transf{FFT(data)};
  EXPECT_EQ(transf.size(), 0);
}

TEST(test_algo_transform, ifft_not_pow_of_two)
{
  FftTransf data{1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
  FftTransf transf{IFFT(data)};
  EXPECT_EQ(transf.size(), 0);
}

TEST(test_algo_transform, fft_empty)
{
  FftTransf data{};
  FftTransf transf{FFT(data)};
  EXPECT_EQ(transf.size(), 0);
}

TEST(test_algo_transform, ifft_empty)
{
  FftTransf data{};
  FftTransf transf{IFFT(data)};
  EXPECT_EQ(transf.size(), 0);
}
