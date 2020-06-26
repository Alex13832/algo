///
/// \brief Source code for image feature algorithms.
/// \author alex011235
/// \date 2020-05-23
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_image_feature.hpp"

#include <algorithm>
#include <cmath>

#include "algo_image_basic.hpp"
#include "algo_image_filter.hpp"

namespace algo::image::feature {

/////////////////////////////////////////////
/// Hough lines transform
/////////////////////////////////////////////

namespace {
// For computing d
constexpr auto LineFunc = [](auto x, auto y, auto alpha) {
  return x * std::cos(alpha * M_PI / 180.0) + y * std::sin(alpha * M_PI / 180.0);
};
}// namespace

Img HoughTransform(const Img& im)
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

/////////////////////////////////////////////
/// Corners
/////////////////////////////////////////////

namespace {
/// \brief Checks the 8-neighborhood if the other pixels are also corners.
constexpr auto NeighborsAreCorners = [](const std::vector<double>& R, auto n_cols, auto x, auto y, auto loc_m) {
  return (R[(y - 1) * n_cols + x - 1] >= loc_m)
      && (R[y * n_cols + (x - 1)] >= loc_m)
      && (R[(y + 1) * n_cols + (x - 1)] >= loc_m)
      && (R[(y - 1) * n_cols + x] >= loc_m)
      && (R[(y + 1) * n_cols + x] >= loc_m)
      && (R[(y - 1) * n_cols + (x + 1)] >= loc_m)
      && (R[y * n_cols + x + 1] >= loc_m)
      && (R[(y + 1) * n_cols + (x + 1)] >= loc_m);
};
/// \brief Compute the Euclidean distance between pt1 and pt2
constexpr auto Euclidean = [](const Point& pt1, const Point& pt2) {
  return (std::pow(pt1.x - pt2.x, 2) + std::pow(pt1.y - pt2.y, 2));
};

struct Corner {
  Point pt;
  double cornerness;
};
/// \brief For sorting corners on cornerness value.
struct c_comp {
  bool operator()(const Corner c1, const Corner c2) const
  {
    return c1.cornerness > c2.cornerness;
  }
} c_comp;

}// namespace

Points Corners(const Img& im, const int& threshold, const CornerDetType& det_type, const int& n_best, const int& min_dist, const GaussWindowSettings& g_win_set)
{
  // http://dept.me.umn.edu/courses/me5286/vision/Notes/2015/ME5286-Lecture8.pdf
  // Blur image with Gaussian, compute derivatives, do some tricks.
  Img imm{filter::GaussianBlur(im, g_win_set.size, g_win_set.sigma)};
  const Img Ix1{filter::Convolve(imm, filter::KernelType::SOBEL_X)};
  const Img Ix2{FlipX(filter::Convolve(FlipX(imm), filter::KernelType::SOBEL_X))};
  const Img Ix{MaxOf(Ix1, Ix2)};
  const Img Iy1{filter::Convolve(imm, filter::KernelType::SOBEL_Y)};
  const Img Iy2{FlipY(filter::Convolve(FlipY(imm), filter::KernelType::SOBEL_Y))};
  const Img Iy{MaxOf(Iy1, Iy2)};

  const int kNCols{im.size.cols};
  const int kNRows{im.size.rows};

  Points points;
  std::vector<double> r_val(kNCols * kNRows, 0.0);
  // Compute cornerness for all pixels.
  for (int x = 0; x < kNCols; x++) {
    for (int y = 0; y < kNRows; y++) {
      const int kEig1{Ix.At(x, y) * Ix.At(x, y)};
      const int kEig2{Iy.At(x, y) * Iy.At(x, y)};
      const double m = kEig1 * kEig2 - 0.05 * (kEig1 + kEig2) * (kEig1 + kEig2);

      if (det_type == CornerDetType::kHarris && m > threshold) {
        r_val[y * kNCols + x] = m;
        points.emplace_back(Point{x, y});
      } else if (det_type == CornerDetType::kShiTomasi && std::min(kEig1, kEig2) > threshold) {
        r_val[y * kNCols + x] = std::min(kEig1, kEig2);
        points.emplace_back(Point{x, y});
      }
    }
  }
  // Filter corners based on the neighborhood cornerness.
  Points corner_pts;
  std::vector<Corner> corners;
  for (const auto& pt : points) {
    if (pt.x == 0 || pt.y == 0 || pt.x == kNCols || pt.y == kNRows) continue;
    const double kLocM{r_val[pt.y * kNCols + pt.y]};
    // If weak neighbor found, don't include current point(x,y) in result.
    if (NeighborsAreCorners(r_val, kNCols, pt.x, pt.y, kLocM)) {
      corner_pts.emplace_back(pt);
      corners.emplace_back(Corner{pt, kLocM});
    }
  }
  // Get the n points with strongest cornerness value.
  if (n_best > 0) {
    std::sort(corners.begin(), corners.end(), c_comp);
    corner_pts.clear();
    const int kN = std::min(n_best, static_cast<int>(corners.size()));
    for (int i = 0; i < kN; i++) {
      corner_pts.emplace_back(corners.at(i).pt);
    }
  }
  // Get points that are not too close.
  if (min_dist > 0) {
    std::vector<bool> skips(corner_pts.size(), false);
    for (int i = 0; i < corner_pts.size() - 1; i++) {
      for (int j = i + 1; j < corner_pts.size(); j++) {
        if (Euclidean(corner_pts[i], corner_pts[j]) < min_dist * min_dist) {// Avoid computing sqrt.
          skips[j] = true;
        }
      }
    }

    Points pts;
    for (int i = 0; i < skips.size(); i++) {
      if (!skips[i]) {
        pts.emplace_back(corner_pts[i]);
      }
    }
    corner_pts = pts;
  }
  return corner_pts;
}

}// namespace algo::image::feature
