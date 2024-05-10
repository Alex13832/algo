///
/// \brief Unit tests for image algorithms.
/// \author alex011235
/// \date 2020-05-18
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <cstdint>
#include <vector>

#include "gtest/gtest.h"
#include "include/algo_image_basic.hpp"

namespace {
namespace img = algo::image;
}  // namespace

/////////////////////////////////////////////
/// Ops
/////////////////////////////////////////////

TEST(TestAlgoImage, Test8BitOps) {
  const std::vector<uint8_t> data{255, 0, 0, 255};
  img::Img im{data, img::Size{2, 2}};

  im.Set(1, 0, 255);
  EXPECT_EQ(im.At(1, 0), 255);
  EXPECT_EQ(im[1], 255);
}

TEST(TestAlgoImage, TestFloatOps) {
  const std::vector<float> data{1.0, 0.0, 0.0, 1.0};
  img::ImgF im{data, img::Size{2, 2}};

  im.Set(1, 0, 1.0);
  EXPECT_EQ(im.At(1, 0), 1.0);
  EXPECT_EQ(im[1], 1.0);
}

/////////////////////////////////////////////
/// Integral images
/////////////////////////////////////////////

TEST(TestAlgoImage, TestIntegralImage) {
  const std::vector<uint8_t> data{31, 2,  4,  33, 5,  36, 12, 26, 9,  10, 29, 25, 13, 17, 21, 22, 20, 18,
                                  24, 23, 15, 16, 14, 19, 30, 8,  28, 27, 11, 7,  1,  35, 34, 3,  32, 6};

  const img::Img im{data, img::Size{6, 6}};

  const img::IntegralImage iimg{ImgToIntegralImage(im)};
  EXPECT_EQ(iimg.At(5, 5), 666);
}

TEST(TestAlgoImage, TestIntegralSum) {
  const std::vector<uint8_t> data{31, 2,  4,  33, 5,  36, 12, 26, 9,  10, 29, 25, 13, 17, 21, 22, 20, 18,
                                  24, 23, 15, 16, 14, 19, 30, 8,  28, 27, 11, 7,  1,  35, 34, 3,  32, 6};

  const img::Img im{data, img::Size{6, 6}};
  const img::IntegralImage iimg{ImgToIntegralImage(im)};

  uint32_t const sm{IntegralBoxSum(iimg, img::Rectangle{1, 2, 4, 3})};
  EXPECT_EQ(sm, 111);
}

/////////////////////////////////////////////
/// Misc.
/////////////////////////////////////////////

TEST(TestAlgoImage, TestNewImageGray) {
  img::Img im{img::NewImgGray(2, 2)};
  EXPECT_EQ(im.size.rows, 2);
  EXPECT_EQ(im.size.cols, 2);
  EXPECT_EQ(im.data[0], 0);
  EXPECT_EQ(im[0], 0);
}

TEST(TestAlgoImage, TestToGray) {
  // 3x3 color image
  img::Img3 img3{};
  img3.size.rows = 3;
  img3.size.cols = 3;

  img3.data[img::Red] = {50, 100, 100, 100, 100, 100, 100, 100, 100};
  img3.data[img::Green] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
  img3.data[img::Blue] = {150, 100, 100, 100, 100, 100, 100, 100, 100};

  img::Img img{ToGray(img3)};

  EXPECT_EQ(img.data[0], 90);
  EXPECT_EQ(img.data[1], 100);
}

TEST(TestAlgoImage, TestInvertPixels) {
  const std::vector<uint8_t> data{255, 0, 0, 255};
  const img::Img im{data, img::Size{2, 2}};
  const img::Img imi{InvertPixels(im)};

  EXPECT_EQ(imi.At(0, 0), 0);
  EXPECT_EQ(imi.At(1, 0), 255);
  EXPECT_EQ(imi.At(0, 1), 255);
  EXPECT_EQ(imi.At(1, 1), 0);
}

TEST(TestAlgoImage, TestFlipx) {
  const std::vector<uint8_t> data{255, 0, 255, 0};
  const img::Img im{data, img::Size{2, 2}};
  const img::Img imi{FlipX(im)};

  EXPECT_EQ(imi.At(0, 0), 0);
  EXPECT_EQ(imi.At(1, 0), 255);
  EXPECT_EQ(imi.At(0, 1), 0);
  EXPECT_EQ(imi.At(1, 1), 255);
}

TEST(TestAlgoImage, TestFlipy) {
  const std::vector<uint8_t> data{255, 255, 0, 0};
  const img::Img im{data, img::Size{2, 2}};
  const img::Img imi{FlipY(im)};

  EXPECT_EQ(imi.At(0, 0), 0);
  EXPECT_EQ(imi.At(1, 0), 0);
  EXPECT_EQ(imi.At(0, 1), 255);
  EXPECT_EQ(imi.At(1, 1), 255);
}

TEST(TestAlgoImage, TestMaxOfNotEqualSizes) {
  const std::vector<uint8_t> data1{255};
  const img::Img im1{data1, img::Size{1, 1}};

  const std::vector<uint8_t> data2{254, 254, 254, 254};
  const img::Img im2{data2, img::Size{2, 2}};

  img::Img im3{MaxOf(im1, im2)};
  EXPECT_EQ(im3.size.cols, 1);
  EXPECT_EQ(im3.size.rows, 1);
  EXPECT_EQ(im3[0], 255);
}

TEST(TestAlgoImage, TestMaxOf) {
  const std::vector<uint8_t> data1{255, 255, 255, 255};
  const img::Img im1{data1, img::Size{2, 2}};

  const std::vector<uint8_t> data2{254, 254, 254, 254};
  const img::Img im2{data2, img::Size{2, 2}};

  const img::Img im3{MaxOf(im1, im2)};
  EXPECT_EQ(im3.At(0, 0), 255);
  EXPECT_EQ(im3.At(1, 0), 255);
  EXPECT_EQ(im3.At(0, 1), 255);
  EXPECT_EQ(im3.At(1, 1), 255);
}
