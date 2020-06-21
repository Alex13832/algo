///
/// \brief Example source code image filters.
/// \author alex011235
/// \date 2020-05-19
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <image_helpers.hpp>
#include <include/algo.hpp>
#include <map>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace algo::image;
using namespace algo::image::filter;
using namespace std;

namespace {
string testfile_path() { return "../testfiles/"; };
}// namespace

void RunKernelConvolutions()
{
  cv::Mat img = cv::imread(testfile_path() + "lena.png", 0);
  img.convertTo(img, CV_8UC1);
  cv::resize(img, img, cv::Size{250, 250});
  cv::imshow("Original", img);
  // Simple
  std::map<string, KernelType> filters = {
      {"Sobel x", KernelType::SOBEL_X},
      {"Sobel y", KernelType::SOBEL_Y},
      {"Edge detect", KernelType::EDGE_DETECT},
      {"Emboss", KernelType::EMBOSS},
      {"Smoothing", KernelType::SMOOTHING},
      {"Modest sharp", KernelType::SHARPEN_MODEST},
      {"Aggressive sharp", KernelType::SHARPEN_AGGRESSIVE},
      {"Gaussian blur", KernelType::GAUSSIAN_BLUR},
      {"Hard blur", KernelType::BLUR_HARD},
      {"Soft blur", KernelType::BLUR_SOFT},
      {"High pass", KernelType::HIGH_PASS},
      {"Weighted average", KernelType::WEIGHTED_AVERAGE},
  };

  for (auto const& filter : filters) {
    Img im{MatToVec(img)};
    im = Convolve(im, filter.second);
    cv::Mat img2 = ImGrayToMat(im);
    cv::imshow(filter.first, img2);
  }

  Img im{MatToVec(img)};
  Img im_edge{Convolve(im, algo::image::filter::KernelType::EDGE_DETECT)};
  im_edge = threshold::Fixed(im_edge, 50, true);

  // Looks better with edge detection applied before these filters.
  cv::imshow("edge", ImGrayToMat(im_edge));
  Img im_dil_x{Convolve(im_edge, algo::image::filter::KernelType::DILATION_HORIZONTAL)};
  cv::imshow("dilation x", ImGrayToMat(im_dil_x));
  Img im_dil_y{Convolve(im_edge, algo::image::filter::KernelType::DILATION_VERTICAL)};
  cv::imshow("dilation_y", ImGrayToMat(im_dil_y));
  Img im_dil_xy{Convolve(im_edge, algo::image::filter::KernelType::DILATION)};
  cv::imshow("dilation_xy", ImGrayToMat(im_dil_xy));

  cv::waitKey(0);
}

void RunColorKernelConvolutions()
{
  cv::Mat img = cv::imread(testfile_path() + "lena_color.png");
  img.convertTo(img, CV_8UC3);
  cv::resize(img, img, cv::Size{250, 250});
  cv::imshow("Original", img);

  std::map<string, KernelType> filters = {
      {"Sobel x", KernelType::SOBEL_X},
      {"Sobel y", KernelType::SOBEL_Y},
      {"Edge detect", KernelType::EDGE_DETECT},
      {"Smoothing", KernelType::SMOOTHING},
      {"Modest sharp", KernelType::SHARPEN_MODEST},
      {"Aggressive sharp", KernelType::SHARPEN_AGGRESSIVE},
      {"Gaussian blur", KernelType::GAUSSIAN_BLUR},
      {"Hard blur", KernelType::BLUR_HARD},
      {"Soft blur", KernelType::BLUR_SOFT},
      {"High pass", KernelType::HIGH_PASS},
      {"Emboss", KernelType::EMBOSS},
      {"Weighted average", KernelType::WEIGHTED_AVERAGE},
  };

  for (auto const& filter : filters) {
    Img3 im{Mat3ToVec(img)};
    im = Convolve3(im, filter.second);
    cv::Mat img2 = Im3ToMat(im);
    cv::imshow(filter.first, img2);
  }

  cv::waitKey(0);
}

void RunGaussianBlurExample()
{
  cv::Mat img = cv::imread(testfile_path() + "lena.png", 0);
  img.convertTo(img, CV_8UC1);
  cv::resize(img, img, cv::Size{250, 250});
  cv::imshow("Original", img);
  Img im{MatToVec(img)};

  Img imgb1{GaussianBlur(im, Size{5, 5}, 1.0)};
  cv::imshow("Gaussian blur 5 5 1.0", ImGrayToMat(imgb1));
  Img imgb2{GaussianBlur(im, Size{5, 5}, 1.5)};
  cv::imshow("Gaussian blur 5 5 1.5", ImGrayToMat(imgb2));
  Img imgb3{GaussianBlur(im, Size{11, 11}, 1.0)};
  cv::imshow("Gaussian blur 11 11 1.0", ImGrayToMat(imgb3));
  Img imgb4{GaussianBlur(im, Size{11, 11}, 1.5)};
  cv::imshow("Gaussian blur 11 11 1.5", ImGrayToMat(imgb4));
  cv::waitKey(0);
}

void RunMedianExample()
{
  cv::Mat img = cv::imread(testfile_path() + "lena_very_noisy.bmp", 0);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", img);

  Img im{MatToVec(img)};
  Img res{MedianFilter(im, 4, 4)};
  cv::Mat mat{ImGrayToMat(res)};
  cv::imshow("Result of median filter", mat);

  cv::waitKey(0);
}

void RunMedian3Example()
{
  cv::Mat img = cv::imread(testfile_path() + "lena_noisy_color.png");
  img.convertTo(img, CV_8UC3);
  cv::imshow("Original", img);

  Img3 im{Mat3ToVec(img)};
  Img3 res{MedianFilter3(im, 4, 4)};
  cv::Mat mat{Im3ToMat(res)};
  cv::imshow("Result of median filter", mat);

  cv::waitKey(0);
}

void RunBinaryThresholdExample()
{
  cv::Mat img{cv::imread(testfile_path() + "receipt.png", 0)};
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

void RunAdaptiveThresholdExample()
{
  cv::Mat img{cv::imread(testfile_path() + "receipt.png", 0)};
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", img);

  Img im{MatToVec(img)};
  Img res1{threshold::Adaptive(im, 13, true)};
  cv::Mat mat_res1{ImGrayToMat(res1)};
  cv::imshow("Result, cut white true", mat_res1);

  Img res2{threshold::Adaptive(im, 13, false)};
  cv::Mat mat_res2{ImGrayToMat(res2)};
  cv::imshow("Result, cut white false", mat_res2);

  cv::waitKey(0);
}

int main(int argc, char** argv)
{
  //RunKernelConvolutions();
  //RunColorKernelConvolutions();
  //RunGaussianBlurExample();
  //RunMedianExample();
  //RunMedian3Example();
  //RunBinaryThresholdExample();
  RunAdaptiveThresholdExample();
  return 0;
}
