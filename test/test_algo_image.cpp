///
/// \brief Unit tests for image algorithms.
/// \author alex011235
/// \date 2020-05-18
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>

#include "gtest/gtest.h"
#include "include/algo_image.hpp"

using namespace std;
using namespace algo::image;

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