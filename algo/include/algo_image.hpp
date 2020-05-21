///
/// \brief Header for image algorithms.
/// \author alex011235
/// \date 2020-05-18
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
///

#include <array>
#include <vector>

#ifndef ALGO_ALGO_INCLUDE_ALGO_IMAGE_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_IMAGE_HPP_

namespace algo::image {

// //////////////////////////////////////////
//  Image data
// //////////////////////////////////////////

constexpr uint8_t Red{0};
constexpr uint8_t Green{1};
constexpr uint8_t Blue{2};

using Data8 = std::vector<uint8_t>;  // For grayscale images.
using Data32 = std::vector<uint32_t>;// For integral images.
using Data8_3 = std::array<Data8, 3>;// For color images.

struct Size {
  int rows, cols;
};

struct Point {
  int x, y;
};

struct Box {
  int x, y, width, height;
};

struct Img3 {// Color
  Data8_3 data;
  Size size{};
};

struct Img {// Grayscale
  Data8 data;
  Size size{};

  /// \brief Returns the value at x, y.
  /// \param x Coordinate x-value.
  /// \param y Coordinate y-value.
  /// \return The value at x, y.
  [[nodiscard]] uint8_t At(const int& x, const int& y) const;
};

struct IntegralImage {
  Data32 data;
  Size size{};

  /// \brief Returns the value at x, y.
  /// \param x Coordinate x-value.
  /// \param y Coordinate y-value.
  /// \return The value at x, y.
  [[nodiscard]] uint32_t At(const int& x, const int& y) const;
};

// //////////////////////////////////////////
//  Fundamental functions
// //////////////////////////////////////////

/// \brief Returns a new grayscale image.
/// \param rows Number of rows.
/// \param cols Number of columns.
/// \return A new grayscale image.
Img NewImgGray(const int& rows, const int& cols);

/// \brief Converts a color image to a gray scale image.
/// \details `gray = 0.3 * red + 0.59 * green + 0.11 * blue`.
/// \param img3 Values to convert.
/// \return A new gray scale image.
Img ToGray(const Img3& img3);

// //////////////////////////////////////////
//  Filters
// //////////////////////////////////////////

enum class FilterType {
  SOBEL_X,
  SOBEL_Y,
  EDGE_DETECT,
  SMOOTHING,
  SHARPEN_MODEST,
  SHARPEN_AGGRESSIVE,
  GAUSSIAN_BLUR,
  BLUR_HARD,
  BLUR_SOFT,
  HIGH_PASS,
  EMBOSS,
  WEIGHTED_AVERAGE,
  DILATION_VERTICAL,
  DILATION_HORIZONTAL,
  DILATION
};

// //////////////////////////////////////////
//  Integral image
// //////////////////////////////////////////

/// \brief Computes and returns the integral image of im.
/// \param im The input image.
/// \return A new integral image.
/// \link <a href="https://en.wikipedia.org/wiki/Summed-area_table">Summed-area-table, Wikipedia.</a>
IntegralImage ImgToIntegralImage(const Img& im);

/// \brief Computes the sum of the rectangular patch.
/// \param img The input integral image.
/// \param pt_tl Point 1, top left.
/// \param pt_tr Point 2, top right.
/// \param pt_bl Point 3, bottom left.
/// \param pt_br Point 4, bottom right.
/// \return The sum.
uint32_t IntegralBoxSum(const IntegralImage& img, const Box& box);

// //////////////////////////////////////////
//  Convolutions
// //////////////////////////////////////////

/// \brief Performs the mathematical convolve operation with a chosen filter.
/// \param im Image to convolve.
/// \param filter_type The filter to use, see FilterType.
/// \return A grayscale image.
Img Convolve(const Img& im, FilterType filter_type);

/// \brief Performs convolution of color images.
/// \param im The image.
/// \param filter_type The filter to use, see Filtertype.
/// \return A new color image.
Img3 Convolve3(const Img3& im, FilterType filter_type);

// //////////////////////////////////////////
//  Median filters
// //////////////////////////////////////////

/// \brief Filters the input image with a median filter.
/// \details This filter will remove noise.
/// \param im The input image.
/// \param w_width Width of filter window.
/// \param w_height Height of filter window.
/// \return New median filtered image of im.
/// \link <a href="https://en.wikipedia.org/wiki/Median_filter">Median filter, Wikipedia.</a>
Img MedianFilter(const Img& im, const int& w_width, const int& w_height);

/// \brief Filters a color image with a median filter.
/// \note The result will become blurry for too large windows. Very noisy images will look better.
/// \param im Input color image.
/// \param w_width Width of filter window.
/// \param w_height Height of filter window.
/// \return A new median filtered image of im.
/// \link <a href="https://en.wikipedia.org/wiki/Median_filter">Median filter, Wikipedia.</a>
Img3 MedianFilter3(const Img3& im, const int& w_width, const int& w_height);

}// namespace algo::image

#endif//ALGO_ALGO_INCLUDE_ALGO_IMAGE_HPP_
