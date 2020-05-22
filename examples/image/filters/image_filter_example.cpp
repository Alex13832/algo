///
/// \brief Example source code image filters.
/// \author alex011235
/// \date 2020-05-19
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <image_helpers.hpp>
#include <include/algo_image.hpp>
#include <map>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace algo::image;
using namespace std;

void ProcessFilters()
{
  cv::Mat img = cv::imread("testfiles/road.png", 0);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", img);

  std::map<string, FilterType> filters = {
      {"Sobel x", FilterType::SOBEL_X},
      {"Sobel y", FilterType::SOBEL_Y},
      {"Edge detect", FilterType::EDGE_DETECT},
      {"Smoothing", FilterType::SMOOTHING},
      {"Modest sharp", FilterType::SHARPEN_MODEST},
      {"Aggressive sharp", FilterType::SHARPEN_AGGRESSIVE},
      {"Gaussian blur", FilterType::GAUSSIAN_BLUR},
      {"Hard blur", FilterType::BLUR_HARD},
      {"Soft blur", FilterType::BLUR_SOFT},
      {"High pass", FilterType::HIGH_PASS},
      {"Emboss", FilterType::EMBOSS},
      {"Weighted average", FilterType::WEIGHTED_AVERAGE},
      {"Vertical dilation", FilterType::DILATION_VERTICAL},
      {"Horizontal dilation", FilterType::DILATION_HORIZONTAL},
      {"XY Dilation", FilterType::DILATION}};

  for (auto const& filter : filters) {
    Img im{MatToVec(img)};
    im = Convolve(im, filter.second);
    cv::Mat img2 = ImGrayToMat(im);
    cv::imshow(filter.first, img2);
  }

  cv::waitKey(0);
}

void ProcessFiltersColor()
{
  cv::Mat img = cv::imread("testfiles/lena_color.png");
  img.convertTo(img, CV_8UC3);
  cv::imshow("Original", img);

  std::map<string, FilterType> filters = {
      {"Sobel x", FilterType::SOBEL_X},
      {"Sobel y", FilterType::SOBEL_Y},
      {"Edge detect", FilterType::EDGE_DETECT},
      {"Smoothing", FilterType::SMOOTHING},
      {"Modest sharp", FilterType::SHARPEN_MODEST},
      {"Aggressive sharp", FilterType::SHARPEN_AGGRESSIVE},
      {"Gaussian blur", FilterType::GAUSSIAN_BLUR},
      {"Hard blur", FilterType::BLUR_HARD},
      {"Soft blur", FilterType::BLUR_SOFT},
      {"High pass", FilterType::HIGH_PASS},
      {"Emboss", FilterType::EMBOSS},
      {"Weighted average", FilterType::WEIGHTED_AVERAGE},
      {"Vertical dilation", FilterType::DILATION_VERTICAL},
      {"Horizontal dilation", FilterType::DILATION_HORIZONTAL},
      {"XY Dilation", FilterType::DILATION}};

  for (auto const& filter : filters) {
    Img3 im{Mat3ToVec(img)};
    im = Convolve3(im, filter.second);
    cv::Mat img2 = Im3ToMat(im);
    cv::imshow(filter.first, img2);
  }

  cv::waitKey(0);
}

void ProcessMedian()
{
  cv::Mat img = cv::imread("testfiles/lena_very_noisy.bmp", 0);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", img);

  Img im{MatToVec(img)};
  Img res{MedianFilter(im, 3, 3)};
  cv::Mat mat{ImGrayToMat(res)};
  cv::imshow("Result of median filter", mat);

  cv::waitKey(0);
}

void ProcessMedian3()
{
  cv::Mat img = cv::imread("testfiles/lena_noisy_color.png");
  img.convertTo(img, CV_8UC3);
  cv::imshow("Original", img);

  Img3 im{Mat3ToVec(img)};
  Img3 res{MedianFilter3(im, 6, 6)};
  cv::Mat mat{Im3ToMat(res)};
  cv::imshow("Result of median filter", mat);

  cv::waitKey(0);
}

void ProcessBinaryThreshold()
{
  cv::Mat img{cv::imread("testfiles/receipt.png", 0)};
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", img);

  Img im{MatToVec(img)};
  Img res1{threshold::Fixed(im, 120, true)};
  cv::Mat mat_res1{ImGrayToMat(res1)};
  cv::imshow("Result, cut white true", mat_res1);

  Img res2{threshold::Fixed(im, 120, false)};
  cv::Mat mat_res2{ImGrayToMat(res2)};
  cv::imshow("Result, cut white false", mat_res2);

  cv::waitKey(0);
}

void ProcessAdaptiveThreshold()
{
  cv::Mat img{cv::imread("testfiles/receipt.png", 0)};
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", img);

  Img im{MatToVec(img)};
  Img res1{threshold::Adaptive(im, 12, true)};
  cv::Mat mat_res1{ImGrayToMat(res1)};
  cv::imshow("Result, cut white true", mat_res1);

  Img res2{threshold::Adaptive(im, 12, false)};
  cv::Mat mat_res2{ImGrayToMat(res2)};
  cv::imshow("Result, cut white false", mat_res2);

  cv::waitKey(0);
}

int main(int argc, char** argv)
{
  ProcessFilters();
  //ProcessFiltersColor();
  //ProcessMedian();
  //ProcessMedian3();
  //ProcessBinaryThreshold();
  //ProcessAdaptiveThreshold();
  return 0;
}
