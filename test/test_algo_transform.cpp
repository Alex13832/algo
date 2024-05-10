///
/// \brief Unit tests for transform algorithms.
/// \author alex011235
/// \date 2020-04-22
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <cstddef>
#include <limits>

#include "gtest/gtest.h"
#include "include/algo_transform.hpp"

namespace {
namespace trf = algo::transform;
constexpr auto kTolerance = std::numeric_limits<float>::epsilon();
}  // namespace

/////////////////////////////////////////////
/// FFT tests
/////////////////////////////////////////////

// NOLINTNEXTLINE
TEST(TestAlgoTransform, FftIfftTrivial1) {
  const trf::FftTransf data{1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0};
  auto itransf = trf::IFFT(trf::FFT(data));

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

TEST(TestAlgoTransform, FftIfftTrivial2) {
  trf::FftTransf data{1.0, 4.0, 3.0, 2.0};
  data = trf::FFT(data);

  EXPECT_NEAR(data[0].real(), 10, kTolerance);
  EXPECT_NEAR(data[0].imag(), 0, kTolerance);
  EXPECT_NEAR(data[1].real(), -2, kTolerance);
  EXPECT_NEAR(data[1].imag(), -2, kTolerance);
  EXPECT_NEAR(data[2].real(), -2, kTolerance);
  EXPECT_NEAR(data[2].imag(), 0, kTolerance);
  EXPECT_NEAR(data[3].real(), -2, kTolerance);
  EXPECT_NEAR(data[3].imag(), 2, kTolerance);

  data = trf::IFFT(data);
  EXPECT_NEAR(data[0].real(), 1.0, kTolerance);
  EXPECT_NEAR(data[0].imag(), 0.0, kTolerance);
  EXPECT_NEAR(data[1].real(), 4.0, kTolerance);
  EXPECT_NEAR(data[1].imag(), 0.0, kTolerance);
  EXPECT_NEAR(data[2].real(), 3.0, kTolerance);
  EXPECT_NEAR(data[2].imag(), 0.0, kTolerance);
  EXPECT_NEAR(data[3].real(), 2.0, kTolerance);
  EXPECT_NEAR(data[3].imag(), 0.0, kTolerance);
}

TEST(TestAlgoTransform, FftNotPowOfTwo) {
  const trf::FftTransf data{1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
  const trf::FftTransf transf{trf::FFT(data)};
  EXPECT_EQ(transf.size(), 0);
}

TEST(TestAlgoTransform, IfftNotPowOfTwo) {
  const trf::FftTransf data{1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
  auto transf = trf::IFFT(data);
  EXPECT_EQ(transf.size(), 0);
}

TEST(TestAlgoTransform, FftEmpty) {
  const trf::FftTransf data{};
  auto transf = trf::FFT(data);
  EXPECT_EQ(transf.size(), 0);
}

TEST(TestAlgoTransform, IfftEmpty) {
  const trf::FftTransf data{};
  auto transf = trf::IFFT(data);
  EXPECT_EQ(transf.size(), 0);
}
