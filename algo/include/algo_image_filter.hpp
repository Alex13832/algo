///
/// \brief Header for image filtering algorithms.
/// \author alex011235
/// \date 2020-05-18
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2016-04-04 Convolve
/// 2016-04-08 Median filter
///

#ifndef ALGO_ALGO_INCLUDE_ALGO_IMAGE_FILTER_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_IMAGE_FILTER_HPP_

#include "algo_image_basic.hpp"

namespace algo::image::filter {

// //////////////////////////////////////////
//  Kernels
// //////////////////////////////////////////

enum class KernelType {
  SOBEL_X,            /// \brief Edgde detection X-dir.
  SOBEL_Y,            /// \brief Edge detection Y-dir
  EDGE_DETECT,        /// \brief Edge detection all-directions
  SMOOTHING,          /// \brief Simple smoothing
  SHARPEN_MODEST,     /// \brief Simple sharpen
  SHARPEN_AGGRESSIVE, /// \brief
  GAUSSIAN_BLUR,      /// \brief Approximated! \see  #GaussianBlur for better kernel.
  BLUR_HARD,          /// \brief
  BLUR_SOFT,          /// \brief
  HIGH_PASS,          /// \brief
  EMBOSS,             /// \brief Makes edges thicker
  WEIGHTED_AVERAGE,   /// \brief
  DILATION_VERTICAL,  /// \brief Makes edges narrow
  DILATION_HORIZONTAL,/// \brief Makes edges narrow
  DILATION            /// \brief Makes edges narrow
};

// //////////////////////////////////////////
//  Convolutions
// //////////////////////////////////////////

/// \brief Performs the mathematical convolve operation with a chosen filter.
/// \param im Image to convolve.
/// \param filter_type The filter to use, see FilterType.
/// \return A grayscale image.
Img Convolve(const Img& im, KernelType filter_type);

/// \brief Performs convolution of color images.
/// \param im The image.
/// \param filter_type The filter to use, see Filtertype.
/// \return A new color image.
Img3 Convolve3(const Img3& im, KernelType filter_type);

// //////////////////////////////////////////
//  Gaussian blur
// //////////////////////////////////////////

Img GaussianBlur(const Img& im, const Size& size, const float& sigma);

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

}// namespace algo::image::filter

#endif//ALGO_ALGO_INCLUDE_ALGO_IMAGE_FILTER_HPP_
