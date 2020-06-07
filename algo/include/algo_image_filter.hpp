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
  SOBEL_X,            /// Horizontal edge detection.
  SOBEL_Y,            /// Vertical edge detection.
  EDGE_DETECT,        /// Edge detection all-directions
  SMOOTHING,          /// Simple image smoothing.
  SHARPEN_MODEST,     /// Simple image sharpen.
  SHARPEN_AGGRESSIVE, /// Sharpens image.
  GAUSSIAN_BLUR,      /// Approximated. See `GaussianBlur` for better kernel.
  BLUR_HARD,          /// Image blur.
  BLUR_SOFT,          /// Image blur.
  HIGH_PASS,          /// High pass filter.
  EMBOSS,             /// Enhances edges.
  WEIGHTED_AVERAGE,   /// Filters with average.
  DILATION_HORIZONTAL,/// "Smears" image horizontally. *
  DILATION_VERTICAL,  /// "Smears" image vertically. *
  DILATION            /// "Smears" image in all directions. *
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

// //////////////////////////////////////////
//  Thresholding
// //////////////////////////////////////////

namespace threshold {

/// \brief Changes all data less than and greater than threshold to 0 and 255 respectively.
/// \param im Input image.
/// \param threshold Fixed value 0-255.
/// \param cut_white Flip values to 255 or 0.
/// \return A new image.
Img Fixed(const Img& im, const uint8_t& threshold, const bool& cut_white);

/// \brief Computes the adaptive threshold of the input image. The thresholding decision is based on the mean value of the
/// chose region size, e.g. 10x10 pixels (region_size^2).
/// \param im Input image.
/// \param region_size The region size to base the threshold decision on.
/// \param cut_white Flip values to 255 or 0.
/// \return A new image.
Img Adaptive(const Img& im, const int& region_size, const bool& cut_white);

}// namespace threshold

}// namespace algo::image::filter

#endif//ALGO_ALGO_INCLUDE_ALGO_IMAGE_FILTER_HPP_
