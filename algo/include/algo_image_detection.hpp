///
/// \brief Header  for image object detection algorithms.
/// \author alex011235
/// \date 2020-05-24
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2020-05-23 Canny edge detection
/// 2020-05-24 Hough line detection
///

#ifndef ALGO_ALGO_INCLUDE_ALGO_IMAGE_DETECTION_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_IMAGE_DETECTION_HPP_

#include "algo_image_basic.hpp"

namespace algo::image::detection {

struct HLine {
  int dist, alpha;// Distance and line angle.
  int sum;
};

using Hlines = std::vector<HLine>;

/// \brief Detects the edges in the input image according to the Canny edge detection algorithm.
/// \param im The input image.
/// \return Detected edges in a new image.
Img CannyEdge(const Img& im, const int& threshold_min = 31, const int& threshold_max = 91);

/// \brief Finds the local maximums of transform::HoughLines image.
/// \note For best results, use a Canny edge detector on the input image.
/// \param im Canny edge image.
/// \param n Number of lines to get.
/// \return A list of lines.
Lines DetectHoughLines(const Img& im, const int& n, const int& min_line_dist = 30);

}// namespace algo::image::detection

#endif//ALGO_ALGO_INCLUDE_ALGO_IMAGE_DETECTION_HPP_
