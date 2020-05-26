///
/// \brief Source code for image transform algorithms.
/// \author alex011235
/// \date 2020-05-23
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "algo_image_transform.hpp"

#include <cmath>

#include "algo_image_basic.hpp"

namespace algo::image::transform {

/////////////////////////////////////////////
/// Hough lines transform
/////////////////////////////////////////////

namespace {
// For computing d
constexpr auto LineFunc = [](auto x, auto y, auto alpha) {
  return x * std::cos(alpha * M_PI / 180.0) + y * std::sin(alpha * M_PI / 180.0);
};
}// namespace

Img HoughLines(const Img& im)
{
  const int kNRows{im.size.rows};
  const int kNCols{im.size.cols};
  const int kDMax = std::sqrt(kNCols * kNCols + kNRows * kNRows);
  const int kAlphaMax{360};
  // All white from start.
  Img himg{Data8(kDMax * kAlphaMax, 255), Size{kDMax, kAlphaMax}};

  // Run through edge detector
  for (int x = 0; x < kNCols; x++) {
    for (int y = 0; y < kNRows; y++) {
      if (im.At(x, y) == 0) continue;// Not an edge-pixel.

      for (int alpha = 0; alpha < kAlphaMax; alpha++) {
        auto d = LineFunc(x, y, alpha);
        if (himg.At(alpha, d) > 0) {
          himg.Set(alpha, d, himg.At(alpha, d) - 1);// Vote
        }
      }
    }
  }
  return InvertPixels(himg);// Better for finding maximums.
}

}// namespace algo::image::transform