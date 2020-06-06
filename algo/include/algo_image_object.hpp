///
/// \brief Header  for image object detection algorithms.
/// \author alex011235
/// \date 2020-05-24
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2020-05-23 Canny edge
/// 2020-05-24 Hough line
/// 2020-05-27 Corners.
///

#ifndef ALGO_ALGO_INCLUDE_ALGO_IMAGE_OBJECT_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_IMAGE_OBJECT_HPP_

#include "algo_image_basic.hpp"

namespace algo::image::object {

// //////////////////////////////////////////
//  Canny edge
// //////////////////////////////////////////

/// \brief Detects the edges in the input image according to the Canny edge detection algorithm.
/// \param im The input image.
/// \return Detected edges in a new image.
/// \link <a href="https://en.wikipedia.org/wiki/Canny_edge_detector">Canny edge detector, Wikipedia.</a>
Img ExtractCannyEdges(const Img& im, const int& threshold_min = 31, const int& threshold_max = 91);

// //////////////////////////////////////////
//  Hough lines
// //////////////////////////////////////////

struct HLine {
  int dist, alpha;// Distance and line angle.
  int sum;
};

using Hlines = std::vector<HLine>;

/// \brief Finds the local maximums of transform::HoughTransform image.
/// \note For best results, use a Canny edge detector on the input image.
/// \param im Canny edge image.
/// \param n Number of lines to get.
/// \param min_line_dist Minimum line distance, good for skipping small "lines".
/// \param min_line_sep Minimum distance between detected lines, good for remove lines too close to each other.
/// \return A list of lines.
/// \link <a href="https://en.wikipedia.org/wiki/Hough_transform">Hough transform, Wikipedia.</a>
Lines ExtractLines(const Img& im, const int& n, const int& min_line_dist, const int& min_line_sep = 10);

}// namespace algo::image::object

#endif//ALGO_ALGO_INCLUDE_ALGO_IMAGE_OBJECT_HPP_
