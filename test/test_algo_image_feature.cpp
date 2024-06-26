///
/// \brief Unit tests for image feature algorithms.
/// \author alex011235
/// \date 2020-06-28
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <cstdint>
#include <vector>

#include "gtest/gtest.h"
#include "include/algo_image_basic.hpp"
#include "include/algo_image_feature.hpp"

namespace {
namespace img = algo::image;
namespace imgf = algo::image::feature;
}  // namespace

namespace {

img::Img GetCornerImg() {
  const std::vector<uint8_t> data{
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      92, 91, 92, 91, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 91,
      91, 91, 92, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 89, 89, 90, 89, 90, 90, 90, 90, 90, 90,
      90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 89, 90, 89, 90, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 92, 49, 21, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
      32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 32, 14, 66, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92,
      37, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  60, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  40, 65, 62, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 62, 26, 0,  63, 94, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  59, 98, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94,
      94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 93, 36, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      92, 42, 0,  56, 93, 89, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      90, 91, 89, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62,
      94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94,
      90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,
      62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57,
      94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35,
      0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,
      57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90,
      35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42,
      0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92,
      90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92,
      42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62,
      94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94,
      90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,
      62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57,
      94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35,
      0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,
      57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90,
      35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42,
      0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92,
      90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92,
      42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      92, 42, 0,  57, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 92, 90, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  57, 94, 90, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 90, 35, 0,  62, 94, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  56, 93, 89, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 90, 91, 89, 35, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 92, 42, 0,  58, 97, 93, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94,
      94, 94, 94, 92, 36, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 42, 0,  48, 80, 77, 78, 78,
      78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 76, 31, 0,  62, 94, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 39, 0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  11, 0,  62, 94, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 92, 39, 0,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
      1,  1,  1,  1,  1,  2,  0,  61, 94, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 83, 81, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 81, 86, 92,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 93, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94,
      94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 92, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91,
      91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91};

  return img::Img{data, img::Size{75, 47}};
}

[[maybe_unused]] img::Img FastImg1() {
  const std::vector<uint8_t> data{0, 0, 2, 2, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1,
                                  0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 2, 2, 0, 0};

  return img::Img{data, img::Size{8, 9}};
}

[[maybe_unused]] img::Img FastImg2() {
  const std::vector<uint8_t> data{0, 0, 2, 2, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1,
                                  0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  return img::Img{data, img::Size{7, 7}};
}

img::Img FastImgBrighter() {
  const std::vector<uint8_t> data{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      2, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0,
      2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0,
      0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0};

  return img::Img{data, img::Size{8, 34}};
}

}  // namespace

/////////////////////////////////////////////
/// Corners
/////////////////////////////////////////////

TEST(TestAlgoImage, TestCorners) {
  const img::Img corner_img{GetCornerImg()};
  const imgf::GaussWindowSettings g_win_set{img::Size{5, 5}, 1.0};
  img::Points pts{Corners(corner_img, 1e6, imgf::CornerDetType::kHarris, 8, 5, g_win_set)};
  EXPECT_FALSE(pts.empty());
  pts = Corners(corner_img, 1e2, imgf::CornerDetType::kShiTomasi, 8, 5, g_win_set);
  EXPECT_FALSE(pts.empty());
}

/////////////////////////////////////////////
/// FAST Corners
/////////////////////////////////////////////

TEST(TestAlgoImage, TestFastCorners) {
  const img::Img corner_img{FastImgBrighter()};
  const img::Points points{imgf::FASTCorners(corner_img, 0, 11)};
  EXPECT_GT(points.size(), 0);
}
