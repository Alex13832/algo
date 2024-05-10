///
/// \brief Unit tests for image algorithms.
/// \author alex011235
/// \date 2020-06-27
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>
#include <cstdint>
#include <vector>

#include "gtest/gtest.h"
#include "include/algo_image_filter.hpp"

namespace {
namespace img = algo::image;
namespace filt = algo::image::filter;
}  // namespace

/////////////////////////////////////////////
/// Kernels and convolutions
/////////////////////////////////////////////

TEST(TestAlgoImage, TestKernels) {
  std::vector<uint8_t> const data{10,  20,  30,  40,   //
                                  50,  60,  70,  80,   //
                                  90,  100, 110, 120,  //
                                  130, 140, 150, 160};
  img::Img im{data, img::Size{4, 4}};

  const img::Data8_3 data3{data, data, data};
  const img::Img3 im3{data3, img::Size{4, 4}};

  const std::vector<filt::KernelType> kernels{
      filt::KernelType::SOBEL_X,
      filt::KernelType::SOBEL_Y,
      filt::KernelType::EDGE_DETECT,
      filt::KernelType::SMOOTHING,
      filt::KernelType::SHARPEN_MODEST,
      filt::KernelType::SHARPEN_AGGRESSIVE,
      filt::KernelType::GAUSSIAN_BLUR,
      filt::KernelType::BLUR_HARD,
      filt::KernelType::BLUR_SOFT,
      filt::KernelType::EMBOSS,
      filt::KernelType::WEIGHTED_AVERAGE,
      filt::KernelType::DILATION_VERTICAL,
      filt::KernelType::DILATION_HORIZONTAL,
      filt::KernelType::DILATION,
      filt::KernelType::HIGH_PASS,
  };

  for (const auto& kernel : kernels) {
    img::Img res{filt::Convolve(im, kernel)};
    EXPECT_FALSE(equal(im.data.begin(), im.data.end(), res.data.begin()));

    img::Img3 res3{filt::Convolve3(im3, kernel)};
    EXPECT_FALSE(equal(im.data.begin(), im.data.end(), res3.data.at(img::Red).begin()));
    EXPECT_FALSE(equal(im.data.begin(), im.data.end(), res3.data.at(img::Green).begin()));
    EXPECT_FALSE(equal(im.data.begin(), im.data.end(), res3.data.at(img::Blue).begin()));
  }
}

/////////////////////////////////////////////
/// Gaussian blur
/////////////////////////////////////////////

TEST(TestAlgoImage, TestGaussianBlurDimensions) {
  const std::vector<uint8_t> data{10, 20, 40, 50};
  const img::Img im{data, img::Size{3, 4}};

  EXPECT_EQ(filt::GaussianBlur(im, img::Size{3, 4}, 1.0).size.cols, 0);
  EXPECT_EQ(filt::GaussianBlur(im, img::Size{3, 4}, 1.0).size.rows, 0);
  EXPECT_EQ(filt::GaussianBlur(im, img::Size{4, 3}, 1.0).size.cols, 0);
  EXPECT_EQ(filt::GaussianBlur(im, img::Size{4, 3}, 1.0).size.rows, 0);
}

TEST(TestAlgoImage, TestGaussianBlurWindowSize) {
  const std::vector<uint8_t> data{10,  20,  30,  40,   //
                                  50,  60,  70,  80,   //
                                  90,  100, 110, 120,  //
                                  130, 140, 150, 160};
  const img::Img im{data, img::Size{4, 4}};

  EXPECT_EQ(filt::GaussianBlur(im, img::Size{3, 5}, 1.0).size.cols, 0);
  EXPECT_EQ(filt::GaussianBlur(im, img::Size{3, 5}, 1.0).size.rows, 0);
  EXPECT_EQ(filt::GaussianBlur(im, img::Size{5, 3}, 1.0).size.cols, 0);
  EXPECT_EQ(filt::GaussianBlur(im, img::Size{5, 3}, 1.0).size.rows, 0);
}

TEST(TestAlgoImage, TestGaussianBlur) {
  std::vector<uint8_t> data{10,  20,  30,  40,  1,  //
                            50,  60,  70,  80,  1,  //
                            90,  100, 110, 120, 1,  //
                            130, 140, 150, 160, 1,  //
                            130, 140, 150, 160, 1};
  const img::Img im{data, img::Size{4, 4}};

  img::Img img{filt::GaussianBlur(im, img::Size{3, 3}, 1.0)};
  EXPECT_FALSE(equal(data.begin(), data.end(), img.data.begin()));
}

/////////////////////////////////////////////
/// Median filters
/////////////////////////////////////////////

TEST(TestAlgoImage, TestMedianFilterWSize) {
  const img::Img im{{}, img::Size{2, 2}};
  const img::Img img{filt::MedianFilter(im, img::Size{2, 2})};
  EXPECT_TRUE(img.data.empty());
}

TEST(TestAlgoImage, TestMedianFilter) {
  std::vector<uint8_t> data{10,  20,  30,  40,   //
                            50,  60,  70,  80,   //
                            90,  100, 110, 120,  //
                            130, 140, 150, 160};
  const img::Img im{data, img::Size{4, 4}};
  img::Img img{filt::MedianFilter(im, img::Size{2, 2})};
  EXPECT_FALSE(equal(data.begin(), data.end(), img.data.begin()));
}

TEST(TestAlgoImage, TestMedianFilter3WSize) {
  const img::Img3 im{{}, img::Size{2, 2}};
  img::Img3 img{filt::MedianFilter3(im, img::Size{2, 2})};
  EXPECT_TRUE(img.data.at(img::Red).empty());
  EXPECT_TRUE(img.data.at(img::Green).empty());
  EXPECT_TRUE(img.data.at(img::Blue).empty());
}

TEST(TestAlgoImage, TestMedianFilter3) {
  std::vector<uint8_t> data{10,  20,  30,  40,   //
                            50,  60,  70,  80,   //
                            90,  100, 110, 120,  //
                            130, 140, 150, 160};
  const img::Data8_3 data3{data, data, data};
  const img::Img3 im3{data3, img::Size{3, 3}};

  img::Img3 img3{filt::MedianFilter3(im3, img::Size{2, 2})};
  EXPECT_FALSE(equal(data.begin(), data.end(), img3.data.at(img::Red).begin()));
  EXPECT_FALSE(equal(data.begin(), data.end(), img3.data.at(img::Green).begin()));
  EXPECT_FALSE(equal(data.begin(), data.end(), img3.data.at(img::Blue).begin()));
}

/////////////////////////////////////////////
/// Thresholding
/////////////////////////////////////////////

TEST(TestAlgoImage, TestFixedThresholding) {
  const std::vector<uint8_t> data{0,   10,  20,  30,   //
                                  40,  50,  60,  70,   //
                                  80,  90,  100, 110,  //
                                  120, 130, 140, 150};

  const img::Img im{data, img::Size{4, 4}};
  img::Img imt1{filt::threshold::Fixed(im, 90, true)};

  int ct1{
      static_cast<int>(std::count_if(imt1.data.begin(), imt1.data.end(), [](const uint8_t& x) { return x == 255; }))};
  EXPECT_EQ(ct1, 6);

  imt1 = {filt::threshold::Fixed(im, 90, false)};
  ct1 = static_cast<int>(std::count_if(imt1.data.begin(), imt1.data.end(), [](const uint8_t& x) { return x == 255; }));
  EXPECT_EQ(ct1, 10);
}

TEST(TestAlgoImage, TestAdaptiveThresholdingRegionSize) {
  const std::vector<uint8_t> data{10, 20,  //
                                  40, 50};
  const img::Img im{data, img::Size{2, 2}};
  const img::Img img{filt::threshold::Adaptive(im, 2, true)};
  EXPECT_TRUE(img.data.empty());
}

TEST(TestAlgoImage, TestAdaptiveThresholding) {
  std::vector<uint8_t> data{10,  20,  30,  40,   //
                            50,  60,  70,  80,   //
                            90,  100, 110, 120,  //
                            130, 140, 150, 160};
  const img::Img im{data, img::Size{4, 4}};
  img::Img img{filt::threshold::Adaptive(im, 2, false)};
  EXPECT_FALSE(equal(data.begin(), data.end(), img.data.begin()));
}
