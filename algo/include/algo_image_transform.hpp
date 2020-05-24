///
/// \brief Header  for image transform algorithms.
/// \author alex011235
/// \date 2020-05-23
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2020-05-23 Hough transform
///

#ifndef ALGO_ALGO_INCLUDE_ALGO_IMAGE_TRANSFORM_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_IMAGE_TRANSFORM_HPP_

#include "algo_image_basic.hpp"

namespace algo::image::transform {

// //////////////////////////////////////////
//  Hough lines
// //////////////////////////////////////////

/// \brief Computes the Hough line transform.
/// \param im The input image.
/// \return An image/matrix with the line intersection vote.
Img HoughLines(const Img& im);

}//namespace algo::image::transform

#endif//ALGO_ALGO_INCLUDE_ALGO_IMAGE_TRANSFORM_HPP_
