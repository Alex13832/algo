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
constexpr std::array<Point, 32> bresenham{{{3, 0}, {3, -1}, {2, -2}, {1, -3}, {0, -3}, {-1, -3}, {-2, -2}, {-3, -1}, {-3, 0}, {-3, 1}, {-2, 2}, {-1, 3}, {0, 3}, {1, 3}, {2, 2}, {3, 1}, {3, 0}, {3, -1}, {2, -2}, {1, -3}, {0, -3}, {-1, -3}, {-2, -2}, {-3, -1}, {-3, 0}, {-3, 1}, {-2, 2}, {-1, 3}, {0, 3}, {1, 3}, {2, 2}, {3, 1}}};

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

constexpr auto DoGPyramid = [](const Img& img) {
  //std::vector<Img> pyramid;// DoG images.
  float sigma{1.6};// Starting value for std in DoG.
  float k = M_SQRT2;
  const int kNbrGaussian{4};
  const int kNbrOctaves{4};
  const Size kSize{3, 3};
  //Img rim{Data8(img.size.rows * img.size.cols, 0), img.size};
  std::vector<std::vector<int16_t>> pyramid;
  std::vector<int16_t> diff(img.size.cols * img.size.rows, 0);

  Img gaussian_prev{algo::image::filter::GaussianBlur(img, kSize, k * sigma)};
  // Generates the pyramid.
  for (int i = 0; i < kNbrOctaves; i++) {
    for (int j = 0; j < kNbrGaussian; j++) {
      Img gaussian_next{algo::image::filter::GaussianBlur(gaussian_prev, kSize, k * sigma)};

      for (size_t idx = 0; idx < gaussian_prev.data.size(); idx++) {
        diff[idx] = gaussian_next.data[idx] - gaussian_prev.data[idx];
      }
      pyramid.emplace_back(diff);
      gaussian_prev = gaussian_next;
    }
    sigma *= 2.0;
  }
  return pyramid;
};

// b == below, m == middle, a == above
constexpr auto IsExtrema = [](const std::vector<int16_t>& b, const std::vector<int16_t>& m, const std::vector<int16_t>& a, const Size& size, const auto& xx, const auto& yy) {
  const int c{size.cols};
  const int16_t cp{m[yy * c + xx]};
  const int xn{xx - 1}, xp{xx + 1}, yn{yy - 1}, yp{yy + 1};
  // Check that the centre pixel is smaller than all its 26 neighbors.
  bool is_mini = m[yn * c + xn] >= cp && m[yy * c + xn] >= cp && m[yp * c + xn] >= cp && m[yn * c + xx] >= cp
      && m[yp * c + xx] >= cp && m[yn * c + xp] >= cp && m[yy * c + xp] >= cp && m[yp * c + xp] >= cp
      && b[yn * c + xn] >= cp && b[yy * c + xn] >= cp && b[yp * c + xn] >= cp && b[yn * c + xx] >= cp
      && b[yy * c + xx] >= cp && b[yp * c + xx] >= cp && b[yn * c + xp] >= cp && b[yy * c + xp] >= cp
      && b[yp * c + xp] >= cp && a[yn * c + xn] >= cp && a[yy * c + xn] >= cp && a[yp * c + xn] >= cp
      && a[yn * c + xx] >= cp && a[yy * c + xx] >= cp && a[yp * c + xx] >= cp && a[yn * c + xp] >= cp
      && a[yy * c + xp] >= cp && a[yp * c + xp] >= cp && cp > 0;
  // Check that the centre pixel is larger than all its 26 neighbors.
  bool is_maxi = m[yn * c + xn] <= cp && m[yy * c + xn] <= cp && m[yp * c + xn] <= cp && m[yn * c + xx] <= cp
      && m[yp * c + xx] <= cp && m[yn * c + xp] <= cp && m[yy * c + xp] <= cp && m[yp * c + xp] <= cp
      && b[yn * c + xn] <= cp && b[yy * c + xn] <= cp && b[yp * c + xn] <= cp && b[yn * c + xx] <= cp
      && b[yy * c + xx] <= cp && b[yp * c + xx] <= cp && b[yn * c + xp] <= cp && b[yy * c + xp] <= cp
      && b[yp * c + xp] <= cp && a[yn * c + xn] <= cp && a[yy * c + xn] <= cp && a[yp * c + xn] <= cp
      && a[yn * c + xx] <= cp && a[yy * c + xx] <= cp && a[yp * c + xx] <= cp && a[yn * c + xp] <= cp
      && a[yy * c + xp] <= cp && a[yp * c + xp] <= cp && cp < 0;

  return is_mini || is_maxi;
};

using Mat = std::vector<std::vector<float>>;

/// \brief Computes the determinan of a 3x3 matrix.
// https://en.wikipedia.org/wiki/Determinant
constexpr auto determinant = [](const auto& M) {
  const float& a{M[0][0]};
  const float& b{M[0][1]};
  const float& c{M[0][2]};
  const float& d{M[1][0]};
  const float& e{M[1][1]};
  const float& f{M[1][2]};
  const float& g{M[2][0]};
  const float& h{M[2][1]};
  const float& i{M[2][2]};
  return a * e * i + b * f * g + c * d * h - c * e * g - b * d * i - a * f * h;
};

/// \brief Solves a 3x3 equation system by using Cramer's rule.
/// https://en.wikipedia.org/wiki/Cramer%27s_rule
constexpr auto SolveEq = [](const auto& H, const auto& d) {
  float detH = determinant(H);
  const Mat m1{{d[0], H[0][1], H[0][2]},
               {d[1], H[1][1], H[1][2]},
               {d[2], H[2][1], H[2][2]}};
  const float detM1{determinant(m1)};

  const Mat m2{{H[0][0], d[0], H[0][2]},
               {H[1][0], d[1], H[1][2]},
               {H[2][0], d[2], H[2][2]}};
  const float detM2{determinant(m2)};

  const Mat m3{{H[0][0], H[0][1], d[0]},
               {H[1][0], H[1][1], d[1]},
               {H[2][0], H[1][1], d[2]}};
  const float detM3{determinant(m3)};

  const float x{detM1 / detH};
  const float y{detM2 / detH};
  const float z{detM3 / detH};
  return std::vector<float>{x, y, z};
};

constexpr auto GetExtrema = [](std::vector<std::vector<int16_t>>& pyr, Size size) {
  Points extrema;
  // Check (close to) every pixel, this might take some time...
  for (int x = 1; x < size.cols - 1; x++) {
    for (int y = 1; y < size.rows - 1; y++) {
      for (auto it = pyr.begin(); it != (pyr.end() - 2); it++) {
        // Get three layers from the pyramid.
        const std::vector<int16_t>& prev{*it};
        const std::vector<int16_t>& mid{*(it + 1)};
        const std::vector<int16_t>& next{*(it + 2)};

        if (IsExtrema(prev, mid, next, size, x, y)) {
          // Check, next step: interpolation of nearby data for accurate position.
          // In other words: Compute offset from dDoG(x,y,sigma), using Taylor expansion, if > 0.5 then discard this point.
          // https://en.wikipedia.org/wiki/Scale-invariant_feature_transform

          const float deriv_scale = 0.5f;
          const float second_deriv_scale = 1.0f;
          const float cross_deriv_scale = 0.25f;
          int yy = y * size.cols;
          int c = size.cols;
          std::vector<float> dD{(float) (mid[yy + x + 1] - mid[yy + x - 1]) * deriv_scale,
                                (float) (mid[(y + 1) * c + x] - mid[(y - 1) * c + x]) * deriv_scale,
                                (float) (next[yy + x] - prev[yy + x]) * deriv_scale};

          float v2 = (float) mid[yy + x] * 2.0;

          float dxx = (float) (mid[yy + x + 1] + mid.at(yy + x - 1) - v2) * second_deriv_scale;
          float dyy = (float) (mid[(y + 1) * c + x] + mid[(y - 1) * c + x] - v2) * second_deriv_scale;
          float dss = (float) (next[yy + x] + prev[yy + x] - v2) * second_deriv_scale;
          float dxy = (float) (mid[(y + 1) * c + x + 1] - mid[(y + 1) * c + x - 1] - mid[(y - 1) * c + x + 1] + mid[(y - 1) * c + x - 1]) * cross_deriv_scale;
          float dxs = (float) (next[yy + x + 1] - next[yy + x - 1] - prev[yy + x + 1] - prev[yy + x - 1]) * cross_deriv_scale;
          float dys = (float) (next[(y + 1) * c + x] - next[(y - 1) * c + x] - prev[(y + 1) * c + x] + prev[(y - 1) * c + x]) * cross_deriv_scale;

          const Mat H{{dxx, dxy, dxs},
                      {dxy, dyy, dys},
                      {dxs, dys, dss}};

          std::vector<float> solved{SolveEq(H, dD)};

          if (std::abs(solved[0] > 0.3f && std::abs(solved[1]) > 0.3f && std::abs(solved[2]) > 0.3f)) {
            extrema.emplace_back(Point{x, y});
          }
        }
      }
    }
  }
  return extrema;
};

}// namespace

Points SiftKeypoints(const Img& img)
{
  Img imh{Convolve(img, filter::KernelType::HIGH_PASS)};
  std::vector<std::vector<int16_t>> pyramid{DoGPyramid(imh)};
  Points extrema{GetExtrema(pyramid, img.size)};
  Points extrema_no_low_contrast;

  //  for (const auto& pt : extrema) {
  //    if ((img.At(pt.x, pt.y)) > 10) {
  //      extrema_no_low_contrast.emplace_back(pt);
  //    }
  //  }
  //
  //  const Img Ix1{filter::Convolve(img, filter::KernelType::SOBEL_X)};
  //  const ImgF Ix{algo::image::ToFloat(Ix1)};
  //  const Img Iy1{filter::Convolve(img, filter::KernelType::SOBEL_Y)};
  //  const ImgF Iy{algo::image::ToFloat(Iy1)};
  //
  //  Points points;
  //  float eig_thr{.1};
  //
  //  for (const auto& pt : extrema_no_low_contrast) {
  //    const double kEig1{Ix.At(pt.x, pt.y) * Ix.At(pt.x, pt.y)};// Eigenvalues
  //    const double kEig2{Iy.At(pt.x, pt.y) * Iy.At(pt.x, pt.y)};// Eigenvalues
  //
  //    if (kEig1 > eig_thr && kEig2 > eig_thr) {
  //      points.emplace_back(pt);
  //    }
  //  }
  return extrema;
}

}// namespace algo::image::feature
