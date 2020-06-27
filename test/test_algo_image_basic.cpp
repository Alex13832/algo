///
/// \brief Unit tests for image algorithms.
/// \author alex011235
/// \date 2020-05-18
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>

#include "gtest/gtest.h"
#include "include/algo.hpp"

using namespace algo::image;

/////////////////////////////////////////////
/// Ops
/////////////////////////////////////////////

TEST(test_algo_image, test_8_bit_ops)
{
  Data8 data{255, 0,
             0, 255};
  Img im{data, Size{2, 2}};

  im.Set(1, 0, 255);
  EXPECT_EQ(im.At(1, 0), 255);
  EXPECT_EQ(im[1], 255);
}

TEST(test_algo_image, test_float_ops)
{
  Dataf data{1.0, 0.0,
             0.0, 1.0};
  ImgF im{data, Size{2, 2}};

  im.Set(1, 0, 1.0);
  EXPECT_EQ(im.At(1, 0), 1.0);
  EXPECT_EQ(im[1], 1.0);
}

/////////////////////////////////////////////
/// Integral images
/////////////////////////////////////////////

TEST(test_algo_image, test_integral_image)
{
  Data8 data{31, 2, 4, 33, 5, 36,
             12, 26, 9, 10, 29, 25,
             13, 17, 21, 22, 20, 18,
             24, 23, 15, 16, 14, 19,
             30, 8, 28, 27, 11, 7,
             1, 35, 34, 3, 32, 6};

  Img im{data, Size{6, 6}};

  IntegralImage iimg{ImgToIntegralImage(im)};
  EXPECT_EQ(iimg.At(5, 5), 666);
}

TEST(test_algo_image, test_integral_sum)
{
  Data8 data{31, 2, 4, 33, 5, 36,
             12, 26, 9, 10, 29, 25,
             13, 17, 21, 22, 20, 18,
             24, 23, 15, 16, 14, 19,
             30, 8, 28, 27, 11, 7,
             1, 35, 34, 3, 32, 6};

  Img im{data, Size{6, 6}};
  IntegralImage iimg{ImgToIntegralImage(im)};

  uint32_t sm{IntegralBoxSum(iimg, Rectangle{1, 2, 4, 3})};
  EXPECT_EQ(sm, 111);
}

/////////////////////////////////////////////
/// Misc.
/////////////////////////////////////////////

TEST(test_algo_image, test_new_image_gray)
{
  Img im{NewImgGray(2, 2)};
  EXPECT_EQ(im.size.rows, 2);
  EXPECT_EQ(im.size.cols, 2);
  EXPECT_EQ(im.data[0], 0);
  EXPECT_EQ(im[0], 0);
}

TEST(test_algo_image, test_to_gray)
{
  // 3x3 color image
  Img3 img3{};
  img3.size.rows = 3;
  img3.size.cols = 3;

  img3.data[Red] = {50, 100, 100, 100, 100, 100, 100, 100, 100};
  img3.data[Green] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
  img3.data[Blue] = {150, 100, 100, 100, 100, 100, 100, 100, 100};

  Img img{ToGray(img3)};

  EXPECT_EQ(img.data[0], 90);
  EXPECT_EQ(img.data[1], 100);
}

TEST(test_algo_image, test_invert_pixels)
{
  Data8 data{255, 0,
             0, 255};
  Img im{data, Size{2, 2}};
  Img imi{InvertPixels(im)};

  EXPECT_EQ(imi.At(0, 0), 0);
  EXPECT_EQ(imi.At(1, 0), 255);
  EXPECT_EQ(imi.At(0, 1), 255);
  EXPECT_EQ(imi.At(1, 1), 0);
}

TEST(test_algo_image, test_flipx)
{
  Data8 data{255, 0,
             255, 0};
  Img im{data, Size{2, 2}};
  Img imi{FlipX(im)};

  EXPECT_EQ(imi.At(0, 0), 0);
  EXPECT_EQ(imi.At(1, 0), 255);
  EXPECT_EQ(imi.At(0, 1), 0);
  EXPECT_EQ(imi.At(1, 1), 255);
}

TEST(test_algo_image, test_flipy)
{
  Data8 data{255, 255,
             0, 0};
  Img im{data, Size{2, 2}};
  Img imi{FlipY(im)};

  EXPECT_EQ(imi.At(0, 0), 0);
  EXPECT_EQ(imi.At(1, 0), 0);
  EXPECT_EQ(imi.At(0, 1), 255);
  EXPECT_EQ(imi.At(1, 1), 255);
}

TEST(test_algo_image, test_max_of_not_equal_sizes)
{
  Data8 data1{255};
  Img im1{data1, Size{1, 1}};

  Data8 data2{254, 254,
              254, 254};
  Img im2{data2, Size{2, 2}};

  Img im3{MaxOf(im1, im2)};
  EXPECT_EQ(im3.size.cols, 1);
  EXPECT_EQ(im3.size.rows, 1);
  EXPECT_EQ(im3[0], 255);
}

TEST(test_algo_image, test_max_of)
{
  Data8 data1{255, 255,
              255, 255};
  Img im1{data1, Size{2, 2}};

  Data8 data2{254, 254,
              254, 254};
  Img im2{data2, Size{2, 2}};

  Img im3{MaxOf(im1, im2)};
  EXPECT_EQ(im3.At(0, 0), 255);
  EXPECT_EQ(im3.At(1, 0), 255);
  EXPECT_EQ(im3.At(0, 1), 255);
  EXPECT_EQ(im3.At(1, 1), 255);
}
