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

#ifndef ALGO_ALGO_INCLUDE_ALGO_IMAGE_PROCESSING_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_IMAGE_PROCESSING_HPP_

namespace algo::image {

// //////////////////////////////////////////
//  Image data
// //////////////////////////////////////////

constexpr uint8_t Red{0};
constexpr uint8_t Green{1};
constexpr uint8_t Blue{2};

struct Size {
  int rows, cols;
};

using Data = std::vector<uint8_t>;// For grayscale images
using Data3 = std::array<Data, 3>;// For color images

struct Img {// Grayscale
  Data data;
  Size size{};
};

struct Img3 {// Color
  Data3 data;
  Size size{};
};

// //////////////////////////////////////////
//  Fundamental functions
// //////////////////////////////////////////

/// \brief
/// \param rows
/// \param cols
/// \return
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

/// \brief
/// \param im
/// \param filter_type
/// \return
Img Convolve(const Img& im, FilterType filter_type);

}// namespace algo::image

#endif//ALGO_ALGO_INCLUDE_ALGO_IMAGE_PROCESSING_HPP_
