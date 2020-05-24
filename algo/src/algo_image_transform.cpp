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
/// Hough transform
/////////////////////////////////////////////

Img HoughLines(const Img& im)
{
  int n_rows{im.size.rows};
  int n_cols{im.size.cols};

  const int kDMax = std::sqrt(n_cols * n_cols + n_rows * n_rows);
  const int kAlphaMax{360};
  // All white from start.
  Img himg{Data8(kDMax * kAlphaMax, 255), Size{kDMax, kAlphaMax}};

  auto d_comp2 = [n_cols, n_rows](auto x, auto y, auto alpha) {
    return x * std::cos(alpha * M_PI / 180.0) + y * std::sin(alpha * M_PI / 180.0);
  };

  // Run through edge detector
  for (int x = 0; x < n_cols; x++) {
    for (int y = 0; y < n_rows; y++) {

      if (im.At(x, y) == 0) continue;// Not an edge-pixel.

      for (int alpha = 0; alpha < kAlphaMax; alpha++) {
        auto d = d_comp2(x, y, alpha);
        if (himg.At(alpha, d) > 0) {
          himg.Set(alpha, d, himg.At(alpha, d) - 1);// Vote
        }
      }
    }
  }

  return InvertPixels(himg);// Better for finding maximums.
}

}// namespace algo::image::transform