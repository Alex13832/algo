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

Points Corners(const Img& im,
               int threshold,
               const CornerDetType& det_type,
               int n_best,
               int min_dist,
               const GaussWindowSettings& g_win_set)
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
constexpr std::array<Point, 32> bresenham
    {{{3, 0}, {3, -1}, {2, -2}, {1, -3}, {0, -3}, {-1, -3}, {-2, -2}, {-3, -1}, {-3, 0}, {-3, 1}, {-2, 2}, {-1, 3},
      {0, 3}, {1, 3}, {2, 2}, {3, 1}, {3, 0}, {3, -1}, {2, -2}, {1, -3}, {0, -3}, {-1, -3}, {-2, -2}, {-3, -1}, {-3, 0},
      {-3, 1}, {-2, 2}, {-1, 3}, {0, 3}, {1, 3}, {2, 2}, {3, 1}}};

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

Points FASTCorners(const Img& im, int intensity_threshold, int corner_threshold)
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

using Mat = std::vector<std::vector<float>>;

std::vector<Mat> gaussians;

constexpr auto DoGPyramid = [](const Img& img, auto nbr_octaves, auto nbr_gaussians) {
  //std::vector<Img> pyramid;// DoG images.
  float sigma{1.6};// Starting value for std in DoG.
  float k = M_SQRT2;
  const Size kSize{3, 3};
  std::vector<Mat> pyramid;
  Mat diff{static_cast<size_t>(img.size.rows), std::vector<float>(img.size.cols, 0)};
  Mat gaussian{static_cast<size_t>(img.size.rows), std::vector<float>(img.size.cols, 0)};

  Img gaussian_prev{algo::image::filter::GaussianBlur(img, kSize, k * sigma)};
  //Img gaussian_prev = algo::image::filter::Convolve(img, filter::KernelType::GAUSSIAN_BLUR);
  Img gaussian_next;
  // Generates the pyramid.
  for (int i = 0; i < nbr_octaves; i++) {
    for (int j = 0; j < nbr_gaussians; j++) {

      gaussian_next = algo::image::filter::GaussianBlur(gaussian_prev, kSize, k * sigma);
      //gaussian_next = algo::image::filter::Convolve(gaussian_prev, filter::KernelType::GAUSSIAN_BLUR);
      for (int y = kSize.rows; y < (img.size.rows - kSize.rows); y++) {
        for (int x = kSize.cols; x < (img.size.cols - kSize.cols); x++) {
          diff[y][x] = gaussian_prev.data[y * img.size.cols + x] - gaussian_next.data[y * img.size.cols + x];
          gaussian[y][x] = gaussian_prev.data[y * img.size.cols + x];
        }
      }
      gaussians.emplace_back(gaussian);
      pyramid.emplace_back(diff);
      gaussian_prev = gaussian_next;
    }
    sigma *= 2.0;
  }
  return pyramid;
};

// b == below, m == middle, a == above
constexpr auto IsExtrema = [](const Mat& b, const Mat& m, const Mat& a, const auto& xx, const auto& yy) {
  const float cp{m[yy][xx]};
  const int xn{xx - 1}, xp{xx + 1}, yn{yy - 1}, yp{yy + 1};
  // Check that the centre pixel is smaller than all its 26 neighbors.
  bool is_mini = m[yn][xn] >= cp && m[yy][xn] >= cp && m[yp][xn] >= cp && m[yn][xx] >= cp
      && m[yp][xx] >= cp && m[yn][xp] >= cp && m[yy][xp] >= cp && m[yp][xp] >= cp
      && b[yn][xn] >= cp && b[yy][xn] >= cp && b[yp][xn] >= cp && b[yn][xx] >= cp
      && b[yy][xx] >= cp && b[yp][xx] >= cp && b[yn][xp] >= cp && b[yy][xp] >= cp
      && b[yp][xp] >= cp && a[yn][xn] >= cp && a[yy][xn] >= cp && a[yp][xn] >= cp
      && a[yn][xx] >= cp && a[yy][xx] >= cp && a[yp][xx] >= cp && a[yn][xp] >= cp
      && a[yy][xp] >= cp && a[yp][xp] >= cp && cp;
  // Check that the centre pixel is larger than all its 26 neighbors.
  bool is_maxi = m[yn][xn] <= cp && m[yy][xn] <= cp && m[yp][xn] <= cp && m[yn][xx] <= cp
      && m[yp][xx] <= cp && m[yn][xp] <= cp && m[yy][xp] <= cp && m[yp][xp] <= cp
      && b[yn][xn] <= cp && b[yy][xn] <= cp && b[yp][xn] <= cp && b[yn][xx] <= cp
      && b[yy][xx] <= cp && b[yp][xx] <= cp && b[yn][xp] <= cp && b[yy][xp] <= cp
      && b[yp][xp] <= cp && a[yn][xn] <= cp && a[yy][xn] <= cp && a[yp][xn] <= cp
      && a[yn][xx] <= cp && a[yy][xx] <= cp && a[yp][xx] <= cp && a[yn][xp] <= cp
      && a[yy][xp] <= cp && a[yp][xp] <= cp && cp;

  return is_mini || is_maxi;
};

constexpr auto determinant = [](const float& a, const float& b, const float& c,
                                const float& d, const float& e, const float& f,
                                const float& g, const float& h, const float& i) {
  return a * e * i + b * f * g + c * d * h - c * e * g - b * d * i - a * f * h;
};

/// \brief Solves a 3x3 equation system by using Cramer's rule.
/// https://en.wikipedia.org/wiki/Cramer%27s_rule
inline void SolveEq(const Mat& H, const std::vector<float>& d, float& x, float& y, float& z)
{
  float detH{determinant(H[0][0], H[0][1], H[0][2], H[1][0], H[1][1], H[1][2], H[2][0], H[2][1], H[2][2])};
  float detm1{determinant(d[0], H[0][1], H[0][2], d[1], H[1][1], H[1][2], d[2], H[2][1], H[2][2])};
  float detm2{determinant(H[0][0], d[0], H[0][2], H[1][0], d[1], H[1][2], H[2][0], d[2], H[2][2])};
  float detm3{determinant(H[0][0], H[0][1], d[0], H[1][0], H[1][1], d[1], H[2][0], H[1][1], d[2])};
  x = detm1 / detH;
  y = detm2 / detH;
  z = detm3 / detH;
}

}// namespace

Keypoints SiftKeypoints(const Img& img, int nbr_gaussians, int nbr_octaves, float contrast_offset, float edge_threshold)
{
  std::vector<Mat> pyr{DoGPyramid(img, nbr_octaves, nbr_gaussians)};
  std::vector<float> d_deriv(3, 0);
  Keypoints keypoints;
  Mat hessian;

  const float kSc1St{0.5f}, kSc2Nd{1.0f}, kScXy{0.25f};
  const int kFrameLimit{10};
  float x1, x2, x3, v2, dxx, dyy, dss, dxy, dxs, dys;

  for (int x = kFrameLimit; x < img.size.cols - kFrameLimit; x++) {
    for (int y = kFrameLimit; y < img.size.rows - kFrameLimit; y++) {
      for (size_t i = 0; i < pyr.size() - 2; i++) {
        // Get three layers from the pyramid. pyr[i] = previous layer, pyr[i+1] current layer, pyr[i+2] next layer.

        if (IsExtrema(pyr[i], pyr[i + 1], pyr[i + 2], x, y)) {
          // Interpolation of nearby data for accurate position.
          // In other words: Compute offset from dDoG(x,y,sigma), using Taylor expansion, if > 0.5 then discard this point.
          // https://en.wikipedia.org/wiki/Scale-invariant_feature_transform
          d_deriv[0] = (pyr[i + 1][y][x + 1] - pyr[i + 1][y][x - 1]) * kSc1St;
          d_deriv[1] = (pyr[i + 1][y + 1][x] - pyr[i + 1][y - 1][x]) * kSc1St;
          d_deriv[2] = (pyr[i + 2][y][x] - pyr[i][y][x]) * kSc1St;

          v2 = pyr[i + 1][y][x] * 2.0f;
          dxx = (pyr[i + 1][y][x + 1] + pyr[i + 1][y][x - 1] - v2) * kSc2Nd;
          dyy = (pyr[i + 1][y + 1][x] + pyr[i + 1][y - 1][x] - v2) * kSc2Nd;
          dss = (pyr[i + 2][y][x] + pyr[i][y][x] - v2) * kSc2Nd;
          dxy = (pyr[i + 1][y + 1][x + 1] - pyr[i + 1][y + 1][x - 1] - pyr[i + 1][y - 1][x + 1]
              + pyr[i + 1][y - 1][x - 1]) * kScXy;
          dxs = (pyr[i + 2][y][x + 1] - pyr[i + 2][y][x - 1] - pyr[i][y][x + 1] - pyr[i][y][x - 1]) * kScXy;
          dys = (pyr[i + 2][y + 1][x] - pyr[i + 2][y - 1][x] - pyr[i][y + 1][x] + pyr[i][y - 1][x]) * kScXy;

          hessian = {{dxx, dxy, dxs},
                     {dxy, dyy, dys},
                     {dxs, dys, dss}};

          SolveEq(hessian, d_deriv, x1, x2, x3);

          // Discards low-contrast keypoints
          x1 = std::abs(x1);
          x2 = std::abs(x2);
          x3 = std::abs(x3);
          if (x1 < contrast_offset && x2 < contrast_offset && x3 < contrast_offset) {
            continue;
          }
          // Eliminate edge response
          double detH{dxx * dyy - dxy * dxy};// Determinant of H
          double trH{dxx + dyy};             // Trace of H
          if (detH == 0) {
            continue;
          }
          if (std::abs(trH * trH / detH) < edge_threshold) {
            continue;
          }
          Mat& L{gaussians[i]};
          // Radius assignment
          double rad{std::sqrt(std::pow(L[y][x + 1] - L[y][x - 1], 2) + std::pow(L[y + 1][x] - L[y - 1][x], 2)) / 2.0};
          // Angle assignment
          double theta{std::atan2(L[y + 1][x] - L[y - 1][x], L[y][x + 1] - L[y][x - 1]) * 180.0 / M_PI};
          keypoints.emplace_back(feature::Keypoint{x, y, rad, theta});
        }
      }
    }
  }
  return keypoints;
}

}// namespace algo::image::feature
