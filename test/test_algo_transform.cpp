///
/// \brief Unit tests for transform algorithms.
/// \author alex011235
/// \date 2020-04-22
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <iostream>

#include "algo.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace algo::transform;

constexpr auto kTolerance = std::numeric_limits<float>::epsilon();

/////////////////////////////////////////////
/// FFT tests
/////////////////////////////////////////////

TEST(test_algo_transform, fft_ifft_trivial_1)
{
  FftTransf data{1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0};
  auto itransf = IFFT(FFT(data));

  for (size_t i = 0; i < data.size(); i++) {
    EXPECT_NEAR(data[i].real(), itransf[i].real(), kTolerance);
    EXPECT_NEAR(data[i].imag(), itransf[i].imag(), kTolerance);

    if (i < 4) {
      EXPECT_NEAR(itransf[i].real(), 1, kTolerance);
    } else {
      EXPECT_NEAR(itransf[i].real(), 0, kTolerance);
    }
  }
}

TEST(test_algo_transform, fft_ifft_trivial_2)
{
  FftTransf data{1.0, 4.0, 3.0, 2.0};
  data = FFT(data);

  EXPECT_NEAR(data[0].real(), 10, kTolerance);
  EXPECT_NEAR(data[0].imag(), 0, kTolerance);
  EXPECT_NEAR(data[1].real(), -2, kTolerance);
  EXPECT_NEAR(data[1].imag(), -2, kTolerance);
  EXPECT_NEAR(data[2].real(), -2, kTolerance);
  EXPECT_NEAR(data[2].imag(), 0, kTolerance);
  EXPECT_NEAR(data[3].real(), -2, kTolerance);
  EXPECT_NEAR(data[3].imag(), 2, kTolerance);

  data = IFFT(data);
  EXPECT_NEAR(data[0].real(), 1.0, kTolerance);
  EXPECT_NEAR(data[0].imag(), 0.0, kTolerance);
  EXPECT_NEAR(data[1].real(), 4.0, kTolerance);
  EXPECT_NEAR(data[1].imag(), 0.0, kTolerance);
  EXPECT_NEAR(data[2].real(), 3.0, kTolerance);
  EXPECT_NEAR(data[2].imag(), 0.0, kTolerance);
  EXPECT_NEAR(data[3].real(), 2.0, kTolerance);
  EXPECT_NEAR(data[3].imag(), 0.0, kTolerance);
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
  auto transf = IFFT(data);
  EXPECT_EQ(transf.size(), 0);
}

TEST(test_algo_transform, fft_empty)
{
  FftTransf data{};
  auto transf = FFT(data);
  EXPECT_EQ(transf.size(), 0);
}

TEST(test_algo_transform, ifft_empty)
{
  FftTransf data{};
  auto transf = IFFT(data);
  EXPECT_EQ(transf.size(), 0);
}
