///
/// \brief Example source code image filters.
/// \author alex011235
/// \date 2020-05-19
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <include/algo_image.hpp>
#include <map>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace algo::image;
using namespace std;

// Will not be available in source code
Img MatToVec(const cv::Mat& img)
{
  Img im{NewImgGray(img.rows, img.cols)};

  for (int i = 0; i < img.rows; ++i) {
    for (int j = 0; j < img.cols; ++j) {
      uint8_t px = img.at<char>(i, j);
      im.data[i * img.cols + j] = px;
    }
  }
  return im;
}

// Will not be available in source code
cv::Mat ImGrayToMat(const Img& im)
{
  cv::Mat img = cv::Mat::zeros(im.size.rows, im.size.cols, CV_8UC1);

  for (int i = 0; i < im.size.rows; ++i) {
    for (int j = 0; j < im.size.cols; ++j) {
      img.at<char>(i, j) = (uint8_t) im.data[i * im.size.cols + j];
    }
  }

  return img;
}

void ProcessFilters()
{
  cv::Mat img = cv::imread("testfiles/lena.png", 0);
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

int main(int argc, char** argv)
{
  ProcessFilters();
  return 0;
}
