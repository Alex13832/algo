///
/// \brief Source file for image algorithms.
/// \author alex011235
/// \date 2020-05-18
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "algo_image.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

namespace algo::image {

/////////////////////////////////////////////
/// Image functions
/////////////////////////////////////////////

///////////////////////////////////
/// 8-bit image.
///////////////////////////////////

uint8_t Img::At(const int& x, const int& y) const
{
  return data[y * size.cols + x];
}

void Img::Set(const int& x, const int& y, const uint8_t& value)
{
  data[y * size.cols + x] = value;
}

uint8_t& Img::operator[](int i)
{
  return data[i];
}

///////////////////////////////////
/// Float image
///////////////////////////////////

uint32_t ImgF::At(const int& x, const int& y) const
{
  return data[y * size.cols + x];
}

void ImgF::Set(const int& x, const int& y, const float& value)
{
  data[y * size.cols + x] = value;
}

float& ImgF::operator[](int i)
{
  return data[i];
}

///////////////////////////////////
/// Integral image
///////////////////////////////////

uint32_t IntegralImage::At(const int& x, const int& y) const
{
  return data[y * size.cols + x];
}

void IntegralImage::Set(const int& x, const int& y, const uint32_t& value)
{
  data[y * size.cols + x] = value;
}

/////////////////////////////////////////////
/// Fundamental functions
/////////////////////////////////////////////

Img NewImgGray(const int& rows, const int& cols)
{
  Img im;
  im.size.rows = rows;
  im.size.cols = cols;
  im.data = Data8(rows * cols, 0);
  return im;
}

Img ToGray(const Img3& img3)
{
  int size{img3.size.rows * img3.size.cols};
  Data8 data(size, 0);

  for (size_t i = 0; i < size; i++) {
    data[i] = 0.3 * img3.data[Red][i] + 0.59 * img3.data[Green][i] + 0.11 * img3.data[Blue][i];
  }

  Img img{data, img3.size};
  return img;
}

Img InvertPixels(const Img& im)
{
  Img img{im};
  std::transform(img.data.begin(), img.data.end(), img.data.begin(), [](uint8_t x) {
    return 255 - x;
  });
  return img;
}

/////////////////////////////////////////////
/// Integral images
/////////////////////////////////////////////

IntegralImage ImgToIntegralImage(const Img& im)
{
  IntegralImage img{Data32(im.size.rows * im.size.cols, 0), im.size};

  for (int x = 0; x < im.size.cols; x++) {
    for (int y = 0; y < im.size.rows; y++) {

      if (x == 0 & y == 0) {
        img.Set(x, y, im.At(0, 0));

      } else if (x == 0) {
        img.Set(x, y, img.At(0, y - 1) + im.At(x, y));

      } else if (y == 0) {
        img.Set(x, y, img.At(x - 1, y) + im.At(x, y));

      } else {
        uint32_t yy{img.At(x, y - 1)};
        uint32_t xx{img.At(x - 1, y)};
        uint32_t xy{img.At(x - 1, y - 1)};
        img.Set(x, y, -xy + yy + xx + im.At(x, y));
      }
    }
  }
  return img;
}

uint32_t IntegralBoxSum(const IntegralImage& img, const Rectangle& box)
{
  return img.At(box.x, box.y) + img.At(box.x + box.width - 1, box.y + box.height - 1) - img.At(box.x + box.width - 1, box.y) - img.At(box.x, box.y + box.height - 1);
}

/////////////////////////////////////////////
/// Filters
/////////////////////////////////////////////

namespace {

using Kernel = std::array<float, 9>;

constexpr Kernel kernel_sobel_x{-1.0 / 2.0, 0, 1.0 / 2.0, -2.0 / 2.0, 0, 2.0 / 2.0, -1.0 / 2.0, 0, 1.0 / 2.0};
constexpr Kernel kernel_sobel_y{-1.0 / 2.0, -2.0 / 2.0, -1.0 / 2.0, 0, 0, 0, 1.0 / 2.0, 2.0 / 2.0, 1.0 / 2.0};
constexpr Kernel kernel_edge{1.0, 0.0, -1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0};
constexpr Kernel kernel_smooth{1.0 / 13.0, 2.0 / 13.0, 1.0 / 13.0, 2.0 / 13.0, 4.0 / 13.0, 2.0 / 13.0, 1.0 / 13.0, 2.0 / 13.0, 1.0 / 13.0};
constexpr Kernel kernel_sharp_agg{0, -1.0, 0, -1.0, 5.0, -1.0, 0, -1.0, 0};
constexpr Kernel kernel_sharp_mod{-1.0 / 9.0, -1.0 / 9.0, -1.0 / 9.0, -1.0 / 9.0, 17.0 / 9.0, -1.0 / 9.0, -1.0 / 9.0, -1.0 / 9.0, -1.0 / 9.0};
constexpr Kernel kernel_gauss_blur{1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0, 2.0 / 16.0, 5.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0};
constexpr Kernel kernel_blur_hard{1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0};
constexpr Kernel kernel_blur_soft{0.0, 1.0 / 8.0, 0.0, 1.0 / 8.0, 1.0 / 2.0, 1.0 / 8.0, 0.0, 1.0 / 8.0, 0.0};
constexpr Kernel kernel_emboss{-2.0, -1.0, 0.0, -1.0, 1.0, 1.0, 0.0, 1.0, 2.0};
constexpr Kernel kernel_weighted{1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0, 2.0 / 16.0, 4.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0};
constexpr Kernel kernel_dilation_v{0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0};
constexpr Kernel kernel_dilation_h{0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
constexpr Kernel kernel_dilation{0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0};
constexpr Kernel kernel_high_pass{-1.0, -1.0, -1.0, -1.0, 8.0, -1.0, -1.0, -1.0, -1.0};
constexpr Kernel kernel_nothing{0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0};

Kernel GetKernel(const KernelType& filter_type)
{
  switch (filter_type) {
    case KernelType::SOBEL_X:
      return kernel_sobel_x;
    case KernelType::SOBEL_Y:
      return kernel_sobel_y;
    case KernelType::EDGE_DETECT:
      return kernel_edge;
    case KernelType::SMOOTHING:
      return kernel_smooth;
    case KernelType::SHARPEN_MODEST:
      return kernel_sharp_mod;
    case KernelType::SHARPEN_AGGRESSIVE:
      return kernel_sharp_agg;
    case KernelType::GAUSSIAN_BLUR:
      return kernel_gauss_blur;
    case KernelType::BLUR_HARD:
      return kernel_blur_hard;
    case KernelType::BLUR_SOFT:
      return kernel_blur_soft;
    case KernelType::EMBOSS:
      return kernel_emboss;
    case KernelType::WEIGHTED_AVERAGE:
      return kernel_weighted;
    case KernelType::DILATION_VERTICAL:
      return kernel_dilation_v;
    case KernelType::DILATION_HORIZONTAL:
      return kernel_dilation_h;
    case KernelType::DILATION:
      return kernel_dilation;
    case KernelType::HIGH_PASS:
      return kernel_high_pass;
  }
  return kernel_nothing;
}

}// namespace

/////////////////////////////////////////////
/// Convolutions
/////////////////////////////////////////////

Data8 ConvolvePriv(const Data8& im, size_t rows, size_t cols, KernelType filter_type)
{
  Data8 res(im.size(), 0);
  const Kernel filter{GetKernel(filter_type)};
  uint8_t dim{3U};
  uint8_t sz{static_cast<uint8_t>(dim >> 1U)};

  // Filtering window
  for (size_t i = sz; i < rows - sz; i++) {
    for (size_t j = sz; j < cols - sz; j++) {
      float sum = 0;
      for (uint8_t k = 0; k < dim; k++) {
        for (uint8_t m = 0; m < dim; m++) {
          // Multiply components
          auto im_num = static_cast<float>((im[(i + k - sz) * cols + (j + m - sz)]));
          float filt_num = filter[k * dim + m];
          sum += im_num * filt_num;
        }
      }
      // Check overflow
      if (sum < 0) sum = 0;
      if (sum > 255) sum = 255;

      res[i * cols + j] = sum;
    }
  }
  return res;
}

Img Convolve(const Img& im, KernelType filter_type)
{
  Img res{im};
  res.data = ConvolvePriv(res.data, im.size.rows, im.size.cols, filter_type);
  return res;
}

Img3 Convolve3(const Img3& im, KernelType filter_type)
{
  Img3 res{im};
  res.data[Red] = ConvolvePriv(res.data[Red], im.size.rows, im.size.cols, filter_type);
  res.data[Green] = ConvolvePriv(res.data[Green], im.size.rows, im.size.cols, filter_type);
  res.data[Blue] = ConvolvePriv(res.data[Blue], im.size.rows, im.size.cols, filter_type);
  return res;
}

/////////////////////////////////////////////
/// Median filters
/////////////////////////////////////////////

Data8 MedianFilterPriv(const Data8& im, const int& rows, const int& cols, const int& w_width, const int& w_height)
{
  Data8 res(rows * cols, 0);
  int edge_x{w_width / 2};
  int edge_y{w_height / 2};

  for (size_t x = 0; x < cols - edge_x; x++) {
    for (size_t y = 0; y < rows - edge_y; y++) {

      std::vector<int> window(w_height * w_height, 0);
      int i{0};

      for (size_t wx = 0; wx < w_width; wx++) {
        for (size_t wy = 0; wy < w_height; wy++) {
          window[i] = im[(y + wy - edge_y) * cols + (x + wx - edge_x)];
          i++;
        }
      }
      std::sort(window.begin(), window.end());
      res[y * cols + x] = window[w_width * w_height / 2];
    }
  }
  return res;
}

Img MedianFilter(const Img& im, const int& w_width, const int& w_height)
{
  Img res;
  res.data = MedianFilterPriv(im.data, im.size.rows, im.size.cols, w_width, w_height);
  res.size = im.size;
  return res;
}

Img3 MedianFilter3(const Img3& im, const int& w_width, const int& w_height)
{
  Img3 res;
  res.data[Red] = MedianFilterPriv(im.data[Red], im.size.rows, im.size.cols, w_width, w_height);
  res.data[Green] = MedianFilterPriv(im.data[Green], im.size.rows, im.size.cols, w_width, w_height);
  res.data[Blue] = MedianFilterPriv(im.data[Blue], im.size.rows, im.size.cols, w_width, w_height);
  res.size = im.size;
  return res;
}

/////////////////////////////////////////////
/// Thresholding
/////////////////////////////////////////////

namespace threshold {

Img Fixed(const Img& im, const uint8_t& threshold, const bool& cut_white)
{
  Img img{im};

  std::for_each(img.data.begin(), img.data.end(), [threshold, cut_white](uint8_t& x) {
    if (x > threshold) {
      x = cut_white ? 255 : 0;
    } else {
      x = cut_white ? 0 : 255;
    }
  });
  return img;
}

Img Adaptive(const Img& im, const int& region_size, const bool& cut_white)
{
  IntegralImage img{ImgToIntegralImage(im)};
  Img res{Data8(im.size.rows * im.size.cols, 0), im.size};

  const int kMargin{region_size / 2};

  for (int x = kMargin; x < im.size.cols - kMargin; x++) {
    for (int y = kMargin; y < img.size.rows - kMargin; y++) {

      Rectangle box{x - kMargin, y - kMargin, region_size, region_size};
      uint32_t box_sum{IntegralBoxSum(img, box)};
      uint32_t avg = box_sum / (region_size * region_size);

      if (im.At(x, y) > avg) {
        res.Set(x, y, 255);
      }
    }
  }

  if (!cut_white) {
    std::for_each(res.data.begin(), res.data.end(), [](uint8_t& x) { x = x == 0 ? 255 : 0; });
  }

  return res;
}

}// namespace threshold

/////////////////////////////////////////////
/// Transform
/////////////////////////////////////////////

namespace transform {

///////////////////////////////////
/// Hough transform
///////////////////////////////////

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

}// namespace transform

/////////////////////////////////////////////
/// Detection
/////////////////////////////////////////////

namespace detection {

///////////////////////////////////
/// Canny
///////////////////////////////////

Img CannyEdge(const Img& im, const int& threshold_min, const int& threshold_max)
{
  const int kNPixels{im.size.rows * im.size.cols};
  // Smooth with Gaussian kernel
  Img img{Convolve(im, KernelType::GAUSSIAN_BLUR)};
  // Intensity gradients
  Img gx{Convolve(img, KernelType::SOBEL_X)};
  Img gy{Convolve(img, KernelType::SOBEL_Y)};

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
      if (dir == 0) {// Horizontal
        if (n < gm.At(x - 1, y) || n < gm.At(x + 1, y)) {
          np.Set(x, y, 0);
        }
      }
      if (dir == 1) {// Diagonal
        if (n < gm.At(x + 1, y - 1) || n < gm.At(x - 1, y + 1)) {
          np.Set(x, y, 0);
        }
      }
      if (dir == 2) {// Vertical
        if (n < gm.At(x, y - 1) || n < gm.At(x, y + 1)) {
          np.Set(x, y, 0);
        }
      }
      if (dir == 3) {// Diagonal
        if (n < gm.At(x - 1, y - 1) || n < gm.At(x + 1, y + 1)) {
          np.Set(x, y, 0);
        }
      }
      // Keep edges > threshold_max
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
      }

      if (thr_edges.At(x, y) == 1) {
        if (thr_edges.At(x - 1, y - 1) == 2 || thr_edges.At(x, y - 1) == 2 || thr_edges.At(x + 1, y - 1) == 2 || thr_edges.At(x - 1, y) == 2 || thr_edges.At(x + 1, y) == 2 || thr_edges.At(x - 1, y + 1) == 2 || thr_edges.At(x, y + 1) == 2 || thr_edges.At(x + 1, y + 1) == 2) {
          res.Set(x, y, 255);
        }
      }
    }
  }

  return res;
}

///////////////////////////////////
/// Hough lines
///////////////////////////////////

struct h_comp {
  bool operator()(const HLine l1, const HLine l2) const
  {
    return l1.sum > l2.sum;
  }
} h_comp;

Lines DetectHoughLines(const Img& im, const int& n, const int& min_line_dist)
{
  Hlines all_lines;
  const Img imh{transform::HoughLines(im)};

  for (int x = 0; x < im.size.cols; x++) {
    for (int y = 0; y < im.size.rows; y++) {
      if (imh.At(x, y) == 0) continue;

      HLine line{y, x, imh.At(x, y)};

      if (line.dist < min_line_dist) continue;

      all_lines.emplace_back(line);
    }
  }

  std::sort(all_lines.begin(), all_lines.end(), h_comp);
  Hlines hlines;

  if (n < all_lines.size()) {
    std::copy_n(all_lines.begin(), n, std::back_inserter(hlines));
  } else {
    hlines = all_lines;
  }

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

}// namespace detection

}//namespace algo::image