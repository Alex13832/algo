///
/// \brief Header  for image feature extraction algorithms.
/// \author alex011235
/// \date 2020-05-23
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
/// Change list:
/// 2020-05-19 Hough lines transform
/// 2020-05-26 Hough circles transform
///

#ifndef ALGO_ALGO_INCLUDE_ALGO_IMAGE_FEATURE_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_IMAGE_FEATURE_HPP_

#include "algo_image_basic.hpp"

namespace algo::image::feature {

// //////////////////////////////////////////
//  Hough transform
// //////////////////////////////////////////

/// \brief Computes the Hough line transform.
/// \param im The input image.
/// \return An image/matrix with the line intersection vote.
Img HoughTransform(const Img& im);

// //////////////////////////////////////////
//  Corner
// //////////////////////////////////////////

enum class CornerDetType {
  kHarris,
  kShiTomasi,
};

struct GaussWindowSettings {
  Size size;  // Window size
  float sigma;// Standard deviation of Gaussian kernel
};

/// \brief Finds the corners in the input image.
/// \details This algorithm is based on the Harris
/// \param im The input image.
/// \param threshold The threshold used by the Harris algorithm to sort out weak corners.
/// \param det_type Corner detection measure type, Harris or Shi-Tomasi.
/// \return Corners.
/// \link <a href="https://en.wikipedia.org/wiki/Corner_detection">Corner detection, Wikipedia.</a>
Points Corners(const Img& im, int threshold, const CornerDetType& det_type = CornerDetType::kHarris,
               int n_best = 0, int min_dist = 0,
               const GaussWindowSettings& g_win_set = {Size{7, 7}, 1.0});

// //////////////////////////////////////////
//  FAST Corner
// //////////////////////////////////////////

/// \brief Returns the corners found with the FAST (Features from an accelerated segment test) algorithm.
/// \param im Input image.
/// \param radius The digital disk radius.
/// \param corner_threshold Number of pixels that must be darker/brighter than the center pixel.
/// \return The FAST corners.
/// \link <a href="https://en.wikipedia.org/wiki/Features_from_accelerated_segment_test">FAST, Wikipedia.</a>
Points FASTCorners(const Img& im, int intensity_threshold, int corner_threshold = 11);

// //////////////////////////////////////////
//  SIFT Keypoints
// //////////////////////////////////////////

/// \brief Used to describe a SIFT keypoint.
struct Keypoint {
  int x;        /// < X-coordinate
  int y;        /// < Y-coordinate
  double radius;/// < Radius, sometimes called magnitude.
  double angle; /// < Angle in degrees.
};

/// \brief Used for storing keypoints.
using Keypoints = std::vector<Keypoint>;

/// \brief Retuns a list of SIFT keypoints, where each keypoint has a (x,y)-coordinate, radius and angle.
/// \param img Input image.
/// \param nbr_gaussians The number of gaussians in each octave-layer, 5 recommended.
/// \param nbr_octaves The number of octaves in DoG-pyramid, |DoG| = nbr_octaves * nbr_gaussians - 1, 5 recommended.
/// \param contrast_offset The contrast threshold that will discard keypoints at locations with lower value.
/// \param edge_threshold The edge threshold that will discard keypoints at edges with lower value.
/// \return The SIFT-keypoints [{x, y, radius, angle},...].
/// \note This function does NOT return the descriptors.
/// \note The input parameters may need to be changed depending on what kind of images is used and their size.
/// \link <a href="https://en.wikipedia.org/wiki/Scale-invariant_feature_transform">SIFT, Wikipedia.</a>
/// \link <a href="https://www.cs.ubc.ca/~lowe/papers/iccv99.pdf">Lowe 1999.</a>
/// \todo Add code for computing the descriptors.
/// \todo Unit test.
Keypoints SiftKeypoints(const Img& img,
                        int nbr_gaussians = 5,
                        int nbr_octaves = 5,
                        float contrast_offset = 1.7,
                        float edge_threshold = 20.0);

}// namespace algo::image::feature

#endif//ALGO_ALGO_INCLUDE_ALGO_IMAGE_FEATURE_HPP_
