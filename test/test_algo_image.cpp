///
/// \brief Unit tests for image algorithms.
/// \author alex011235
/// \date 2020-05-18
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>

#include "gtest/gtest.h"
#include "include/algo.hpp"

using namespace std;
using namespace algo::image;

/////////////////////////////////////////////
/// Fundamental functions
/////////////////////////////////////////////

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
/// Thresholding
/////////////////////////////////////////////

TEST(test_algo_image, test_binary_thresholding)
{
  Data8 data{0, 10, 20, 30,
             40, 50, 60, 70,
             80, 90, 100, 110,
             120, 130, 140, 150};

  Img im{data, Size{4, 4}};
  Img imt1{filter::threshold::Fixed(im, 90, true)};

  int ct1{static_cast<int>(std::count_if(imt1.data.begin(), imt1.data.end(), [](const uint8_t& x) { return x == 255; }))};
  EXPECT_EQ(ct1, 6);

  imt1 = {filter::threshold::Fixed(im, 90, false)};
  ct1 = static_cast<int>(std::count_if(imt1.data.begin(), imt1.data.end(), [](const uint8_t& x) { return x == 255; }));
  EXPECT_EQ(ct1, 10);
}
