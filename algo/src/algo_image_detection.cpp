///
/// \brief Source code for image object detection algorithms.
/// \author alex011235
/// \date 2020-05-24
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "algo_image_detection.hpp"

#include <cmath>

#include "algo_image_filter.hpp"
#include "algo_image_transform.hpp"

namespace algo::image::detect {

/////////////////////////////////////////////
/// Canny
/////////////////////////////////////////////

Img CannyEdge(const Img& im, const int& threshold_min, const int& threshold_max)
{
  const int kNPixels{im.size.rows * im.size.cols};
  // Smooth with Gaussian kernel
  Img img{Convolve(im, filter::KernelType::GAUSSIAN_BLUR)};
  // Intensity gradients
  Img gx{Convolve(im, filter::KernelType::SOBEL_X)};
  Img gy{Convolve(im, filter::KernelType::SOBEL_Y)};

  // Magnitude
  Img gm{im};
  Img th{Data8(kNPixels, 0), im.size};

  for (int i = 0; i < kNPixels; i++) {
    gm[i] = std::hypot(gx[i], gy[i]);
    double theta = std::atan2(gy[i], gx[i]) * 180 / M_PI;
    // Round theta to 135, 90, 45 or 0.
    th[i] = static_cast<int>(std::round(theta * (5.0 / M_PI) + 5)) % 5;
  }

  // Non-maximum suppression
  Img np{gm};
  Img thr_edges{Data8(kNPixels, 0), im.size};

  for (int x = 0; x < im.size.cols; x++) {
    for (int y = 0; y < im.size.rows; y++) {
      if (x == 0 || y == 0 || x == im.size.cols || y == im.size.rows) {
        np.Set(x, y, 0);
        continue;
      }

      int dir{th.At(x, y) % 4};
      int n{np.At(x, y)};
      // Check neighbors.
      // Horizontal
      if (dir == 0 && (n < gm.At(x - 1, y) || n < gm.At(x + 1, y))) {
        np.Set(x, y, 0);
      }
      // Diagonal
      if (dir == 1 && (n < gm.At(x + 1, y - 1) || n < gm.At(x - 1, y + 1))) {
        np.Set(x, y, 0);
      }
      // Vertical
      if (dir == 2 && (n < gm.At(x, y - 1) || n < gm.At(x, y + 1))) {
        np.Set(x, y, 0);
      }
      // Diagonal
      if (dir == 3 && (n < gm.At(x - 1, y - 1) || n < gm.At(x + 1, y + 1))) {
        np.Set(x, y, 0);
      }
      // Give each p(x,y) +1 if over thresholds.
      if (np.At(x, y) > threshold_max) {
        thr_edges.Set(x, y, 1);
      }
      if (np.At(x, y) > threshold_min) {
        thr_edges.Set(x, y, thr_edges.At(x, y) + 1);
      }
    }
  }

  // Tracking by hysteresis
  Img res{Data8(kNPixels, 0), im.size};

  for (int x = 0; x < im.size.cols; x++) {
    for (int y = 0; y < im.size.rows; y++) {

      if (thr_edges.At(x, y) == 0) continue;

      if (thr_edges.At(x, y) == 2) {
        res.Set(x, y, 255);
        continue;
      }

      if (thr_edges.At(x, y) == 1) {
        // There's a strong edge in the 8-neighborhood of x,y
        if (thr_edges.At(x - 1, y - 1) == 2
            || thr_edges.At(x, y - 1) == 2
            || thr_edges.At(x + 1, y - 1) == 2
            || thr_edges.At(x - 1, y) == 2
            || thr_edges.At(x + 1, y) == 2
            || thr_edges.At(x - 1, y + 1) == 2
            || thr_edges.At(x, y + 1) == 2
            || thr_edges.At(x + 1, y + 1) == 2) {

          res.Set(x, y, 255);
        }
      }
    }
  }

  return res;
}

/////////////////////////////////////////////
/// Hough lines
/////////////////////////////////////////////

struct h_comp {
  bool operator()(const HLine l1, const HLine l2) const
  {
    return l1.sum > l2.sum;
  }
} h_comp;

namespace {
constexpr int kMaxNbrLines{1000};
// Lambda for computing distance in alpha-d-plane
constexpr auto DistComp = [](HLine l1, HLine l2) {
  return std::sqrt(std::pow(l1.dist - l2.dist, 2) + std::pow(l1.alpha - l2.alpha, 2));
};
}// namespace

Lines LinesHough(const Img& im, const int& n, const int& min_line_dist, const int& min_line_sep)
{
  // Simple improvement.
  Img imh{Convolve(im, filter::KernelType::EMBOSS)};// WEIGHTED_AVERAGE is ok.
  imh = transform::HoughLines(imh);
  Hlines all_lines;

  for (int alpha = 0; alpha < im.size.cols; alpha++) {
    for (int d = 0; d < im.size.rows; d++) {
      if (imh.At(alpha, d) == 0 || d < min_line_dist) continue;
      all_lines.emplace_back(HLine{d, alpha % 360, imh.At(alpha, d)});
    }
  }

  std::sort(all_lines.begin(), all_lines.end(), h_comp);
  std::vector<bool> skips(std::min(kMaxNbrLines, static_cast<int>(all_lines.size())), false);

  // Filter lines that are too close
  for (size_t i = 0; i < skips.size(); i++) {
    for (size_t j = i + 1; j < skips.size(); j++) {
      if (DistComp(all_lines[i], all_lines[j]) < min_line_sep) {
        skips[j] = true;
      }
    }
  }

  Hlines filtered;
  for (size_t i = 0; i < skips.size(); i++) {
    if (!skips[i]) {
      filtered.emplace_back(all_lines[i]);
    }
  }

  Hlines hlines(filtered.begin(), filtered.begin() + std::min(n, static_cast<int>(filtered.size())));
  Lines lines;
  // Convert to coordinates in the xy-plane.
  // https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_lines/hough_lines.html#code
  for (const auto& line : hlines) {
    const double a{cos(line.alpha * M_PI / 180.0)};
    const double b{sin(line.alpha * M_PI / 180.0)};
    const double x{a * line.dist};
    const double y{b * line.dist};
    // Lines don't have end-points.
    const int x1{static_cast<int>(round(x + 10000 * (-b)))};
    const int y1{static_cast<int>(round(y + 10000 * (a)))};
    const int x2{static_cast<int>(round(x - 10000 * (-b)))};
    const int y2{static_cast<int>(round(y - 10000 * (a)))};

    Line line1{Point{x1, y1}, Point{x2, y2}};
    lines.emplace_back(line1);
  }
  return lines;
}

/////////////////////////////////////////////
/// Corner detection
/////////////////////////////////////////////

namespace {
/// \brief Checks the 8-neighborhood if the other values are less than loc_m, the center value.
constexpr auto CheckNeighborhood = [](const std::vector<double>& R, auto n_cols, auto x, auto y, auto loc_m) {
  return (R[(y - 1) * n_cols + x - 1] >= loc_m)
      && (R[y * n_cols + (x - 1)] >= loc_m)
      && (R[(y + 1) * n_cols + (x - 1)] >= loc_m)
      && (R[(y - 1) * n_cols + x] >= loc_m)
      && (R[(y + 1) * n_cols + x] >= loc_m)
      && (R[(y - 1) * n_cols + (x + 1)] >= loc_m)
      && (R[y * n_cols + x + 1] >= loc_m)
      && (R[(y + 1) * n_cols + (x + 1)] >= loc_m);
};

struct Corner {
  Point pt;
  double cornerness;
};

struct c_comp {
  bool operator()(const Corner c1, const Corner c2) const
  {
    return c1.cornerness > c2.cornerness;
  }
} h_comp;

}// namespace

Points Corners(const Img& im, const int& threshold, const CornerDetType& det_type, const GaussWindowSettings& g_win_set)
{
  // http://dept.me.umn.edu/courses/me5286/vision/Notes/2015/ME5286-Lecture8.pdf
  // Compute derivatives
  Img imm{filter::GaussianBlur(im, g_win_set.size, g_win_set.sigma)};
  imm = filter::Convolve(imm, filter::KernelType::EMBOSS);
  imm = filter::Convolve(imm, filter::KernelType::WEIGHTED_AVERAGE);
  const Img Ix{Convolve(imm, filter::KernelType::SOBEL_X)};
  const Img Iy{Convolve(imm, filter::KernelType::SOBEL_Y)};

  const int kNCols{im.size.cols};
  const int kNRows{im.size.rows};

  Points points;
  std::vector<double> r_val(kNCols * kNRows, 0.0);

  for (int x = 0; x < kNCols; x++) {
    for (int y = 0; y < kNRows; y++) {
      const int eig1{Ix.At(x, y) * Ix.At(x, y)};
      const int eig2{Iy.At(x, y) * Iy.At(x, y)};
      const double m = eig1 * eig2 - 0.05 * (eig1 + eig2) * (eig1 + eig2);

      if (det_type == CornerDetType::kHarris && m > threshold) {
        // Handle Harris corner detector type
        r_val[y * kNCols + x] = m;
        points.emplace_back(Point{x, y});
      } else if (det_type == CornerDetType::kShiTomasi && std::min(eig1, eig2) > threshold) {
        // Handle Shi-Tomas corner detector type
        r_val[y * kNCols + x] = std::min(eig1, eig2);
        points.emplace_back(Point{x, y});
      }
    }
  }
  // Filter corners based on the neighborhood cornerness.
  Points final_pts;
  std::vector<Corner> corners;
  for (const auto& pt : points) {
    if (pt.x == 0 || pt.y == 0 || pt.x == kNCols || pt.y == kNRows) continue;

    double loc_m{r_val[pt.y * kNCols + pt.y]};
    // If weak neighbor found, don't include current point(x,y) in result.
    if (CheckNeighborhood(r_val, kNCols, pt.x, pt.y, loc_m)) {
      final_pts.emplace_back(pt);
      corners.emplace_back(Corner{pt, loc_m});
    }
  }
  return final_pts;
}

}// namespace algo::image::detect
