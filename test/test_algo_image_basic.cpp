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

TEST(test_algo_image, test_new_image_gray)
{
  Img im{NewImgGray(2, 2)};
  EXPECT_EQ(im.size.rows, 2);
  EXPECT_EQ(im.size.cols, 2);
  EXPECT_EQ(im.data[0], 0);
  EXPECT_EQ(im[0], 0);
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
