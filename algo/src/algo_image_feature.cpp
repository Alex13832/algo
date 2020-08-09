///
/// \brief Source code for image feature algorithms.
/// \author alex011235
/// \date 2020-05-23
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_image_feature.hpp"

#include <algorithm>
#include <array>
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
  int d_max = std::sqrt(kNCols * kNCols + kNRows * kNRows);
  const int kAlphaMax{360};
  // All white from start.
  Img himg{Data8(d_max * kAlphaMax, 255), Size{d_max, kAlphaMax}};

  // Run through edge detector
  for (int x = 0; x < kNCols; x++) {
    for (int y = 0; y < kNRows; y++) {
      if (im.At(x, y) == 0) continue;// Not an edge-pixel.

      for (int alpha = 0; alpha < kAlphaMax; alpha++) {
        int d = LineFunc(x, y, alpha);
        d = std::max(static_cast<int>(d), 0);
        if (himg.At(alpha, d) > 0) {
          himg.Set(alpha, d, himg.At(alpha, d) - 1);// Vote
        }
      }
    }
  }
  Img im_inv{InvertPixels(himg)};
  return im_inv;// Better for finding maximums.
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
///\brief For sorting corners on cornerness value.
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
    for (size_t i = 0; i < corner_pts.size() - 1; i++) {
      for (size_t j = i + 1; j < corner_pts.size(); j++) {
        if (Euclidean(corner_pts[i], corner_pts[j]) < min_dist * min_dist) {// Avoid computing sqrt.
          skips[j] = true;
        }
      }
    }

    Points pts;
    for (size_t i = 0; i < skips.size(); i++) {
      if (!skips[i]) {
        pts.emplace_back(corner_pts[i]);
      }
    }
    corner_pts = pts;
  }
  return corner_pts;
}

/////////////////////////////////////////////
/// FAST Corners
/////////////////////////////////////////////

namespace {
// These points will be used to get the circumference on the Bresenham disc.
constexpr std::array<Point, 16> bresenham{{{3, 0}, {3, -1}, {2, -2}, {1, -3}, {0, -3}, {-1, -3}, {-2, -2}, {-3, -1}, {-3, 0}, {-3, 1}, {-2, 2}, {-1, 3}, {0, 3}, {1, 3}, {2, 2}, {3, 1}}};

///\brief Returns a counter for how many pixels that are darker and brighter (+- pixel_thr) than the candidate pixel (x,y).
// If the pixels are not continuous, the counter(s) will be reset.
constexpr auto CornerMeasure = [](const Img& im, auto x, auto y, auto count_thr, auto pixel_thr) {
  int dark_count{0};  // Counter to check how many pixels that are darker then the centre pixel on the Bresenham circle.
  int bright_count{0};// Counter for brighter.

  for (const auto& p : bresenham) {
    int xp{x + p.x};
    int yp{y + p.y};

    if (im.At(x, y) + pixel_thr < im.At(xp, yp)) {
      bright_count++;
    } else if (bright_count < count_thr) {// This means that the pixels are not continuous.
      bright_count = 0;
    }
    if (im.At(x, y) - pixel_thr > im.At(xp, yp)) {
      dark_count++;
    } else if (dark_count < count_thr) {// This means that the pixels are not continuous.
      dark_count = 0;
    }
  }
  return dark_count > count_thr || bright_count > count_thr;
};

}// namespace

Points FASTCorners(const Img& im, const int& intensity_threshold, const int& corner_threshold)
{
  Points points;
  for (int i = 3; i < im.size.cols - 3; i++) {
    for (int j = 3; j < im.size.rows - 3; j++) {
      if (CornerMeasure(im, i, j, corner_threshold, intensity_threshold)) {
        points.emplace_back(Point{i, j});
      }
    }
  }
  return points;
}

/////////////////////////////////////////////
/// SIFT Keypoints
/////////////////////////////////////////////

namespace {

std::vector<Img> DoGPyramid(const Img& img)
{
  std::vector<Img> pyramid; // DoG images.
  float sigma{1.6};         // Starting value for std in DoG.
  const int kNbrGaussian{5};// Per octave, 4*4=16 images, (subtraction between two consecutive pairs).
  const int kNbrOctaves{4}; // Number of levels in pyramid.

  Img gaussian_prev{algo::image::filter::GaussianBlur(img, Size{3, 3}, M_SQRT2 * sigma)};
  // Generates the pyramid.
  for (int i = 0; i < kNbrOctaves; i++) {
    for (int j = 0; j < kNbrGaussian; j++) {
      Img gaussian_next{algo::image::filter::GaussianBlur(gaussian_prev, Size{3, 3}, M_SQRT2 * sigma)};
      pyramid.emplace_back(algo::image::Subtract(gaussian_next, gaussian_prev));
      gaussian_prev = gaussian_next;
    }
    sigma *= 2.0;
  }
  return pyramid;
}

// b == below, m == middle, a == above
constexpr auto IsMaximum = [](const Img& b, const Img& m, const Img& a, auto x, auto y) {
  uint8_t cp{m.At(x, y)};// cp = centre-pixel (save space).
  const int xn{x - 1}, xp{x + 1}, yn{y - 1}, yp{y + 1};
  // Check that the centre pixel is larger than all its 26 neighbors.
  return m.At(xn, yn) > cp && m.At(xn, y) > cp && m.At(xn, yp) > cp && m.At(x, yn) > cp
      && m.At(x, yp) > cp && m.At(xp, yn) > cp && m.At(xp, y) > cp && m.At(xp, yp) > cp
      && b.At(xn, yn) > cp && b.At(xn, y) > cp && b.At(xn, yp) > cp && b.At(x, yn) > cp
      && b.At(x, y) > cp && b.At(x, yp) > cp && b.At(xp, yn) > cp && b.At(xp, y) > cp
      && b.At(xp, yp) > cp && a.At(xn, yn) > cp && a.At(xn, y) > cp && a.At(xn, yp) > cp
      && a.At(x, yn) > cp && a.At(x, y) > cp && a.At(x, yp) > cp && a.At(xp, yn) > cp
      && a.At(xp, y) > cp && a.At(xp, yp) > cp;
};

// b == below, m == middle, a == above
constexpr auto IsMinimum = [](const Img& b, const Img& m, const Img& a, auto x, auto y) {
  uint8_t cp{m.At(x, y)};
  const int xn{x - 1}, xp{x + 1}, yn{y - 1}, yp{y + 1};
  // Check that the centre pixel is smaller than all its 26 neighbors.
  return m.At(xn, yn) < cp && m.At(xn, y) < cp && m.At(xn, yp) < cp && m.At(x, yn) < cp
      && m.At(x, yp) < cp && m.At(xp, yn) < cp && m.At(xp, y) < cp && m.At(xp, yp) < cp
      && b.At(xn, yn) < cp && b.At(xn, y) < cp && b.At(xn, yp) < cp && b.At(x, yn) < cp
      && b.At(x, y) < cp && b.At(x, yp) < cp && b.At(xp, yn) < cp && b.At(xp, y) < cp
      && b.At(xp, yp) < cp && a.At(xn, yn) < cp && a.At(xn, y) < cp && a.At(xn, yp) < cp
      && a.At(x, yn) < cp && a.At(x, y) < cp && a.At(x, yp) < cp && a.At(xp, yn) < cp
      && a.At(xp, y) < cp && a.At(xp, yp) < cp;
};

Points GetExtrema(const std::vector<Img>& pyramid, const Img& img)
{
  Size size{pyramid[0].size};
  Points extrema;
  // Check (close to) every pixel, this might take some time...
  for (int i = 1; i < size.cols - 1; i++) {
    for (int j = 1; j < size.rows - 1; j++) {

      for (int p = 0; p < pyramid.size() - 2; p++) {
        // Check for extrema points
        if (IsMaximum(pyramid[p], pyramid[p + 1], pyramid[p + 2], i, j) || IsMinimum(pyramid[p], pyramid[p + 1], pyramid[p + 2], i, j)) {
          extrema.emplace_back(Point{i, j});
        }
      }
    }
  }
  return extrema;
}

}// namespace

Points SiftKeypoints(const Img& img)
{
  Img imh{Convolve(img, filter::KernelType::EMBOSS)};// ?
  std::vector<Img> pyramid{DoGPyramid(imh)};
  Points extrema{GetExtrema(pyramid, imh)};
  Points extrema_no_low_contrast;

  for (const auto& pt : extrema) {
    if (pyramid[0].At(pt.x, pt.y) > 240) {
      extrema_no_low_contrast.emplace_back(pt);
    }
  }

  const Img Ix1{filter::Convolve(pyramid[0], filter::KernelType::SOBEL_X)};
  const Img Ix2{FlipX(filter::Convolve(FlipX(pyramid[0]), filter::KernelType::SOBEL_X))};
  const Img Ix{MaxOf(Ix1, Ix2)};
  const Img Iy1{filter::Convolve(pyramid[0], filter::KernelType::SOBEL_Y)};
  const Img Iy2{FlipY(filter::Convolve(FlipY(pyramid[0]), filter::KernelType::SOBEL_Y))};
  const Img Iy{MaxOf(Iy1, Iy2)};

  Points points;

  for (const auto& pt : extrema_no_low_contrast) {
    const double kEig1 = Ix.At(pt.x, pt.y) * Ix.At(pt.x, pt.y);
    const double kEig2 = Iy.At(pt.x, pt.y) * Iy.At(pt.x, pt.y);
    if ((kEig1 / kEig2) > 100.0) {
      points.emplace_back(pt);
    }
  }

  // TODO: Discard low-contrast keypoints.
  // TODO: Eliminate edge responses.

  return points;
}

}// namespace algo::image::feature
