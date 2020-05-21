///
/// \brief Source code for image helpers.
/// \author alex011235
/// \date 2020-05-21
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
#include <include/algo_image.hpp>
#include <map>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#ifndef ALGO_EXAMPLES_IMAGE_FILTERS_IMAGE_HELPERS_HPP_
#define ALGO_EXAMPLES_IMAGE_FILTERS_IMAGE_HELPERS_HPP_

algo::image::Img MatToVec(const cv::Mat& img);

algo::image::Img3 Mat3ToVec(const cv::Mat& img);

cv::Mat ImGrayToMat(const algo::image::Img& im);

cv::Mat Im3ToMat(const algo::image::Img3& im);

#endif//ALGO_EXAMPLES_IMAGE_FILTERS_IMAGE_HELPERS_HPP_
