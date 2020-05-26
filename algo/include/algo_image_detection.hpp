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

namespace algo::image::detect {

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
/// \param l1 Canny edge image.
/// \param l2 Number of lines to get.
/// \param min_line_dist Minimum line distance, good for skipping small "lines".
/// \param min_line_sep Minimum distance between detected lines, good for remove lines too close to each other.
/// \return A list of lines.
Lines LinesHough(const Img& l1, const int& l2, const int& min_line_dist, const int& min_line_sep = 10);

}// namespace algo::image::detect

#endif//ALGO_ALGO_INCLUDE_ALGO_IMAGE_DETECTION_HPP_
