///
/// \brief Header for image helpers.
/// \author alex011235
/// \date 2020-05-21
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "image_helpers.hpp"

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
Img3 Mat3ToVec(const cv::Mat& img)
{
  vector<cv::Mat> channels(3);
  cv::split(img, channels);
  Img3 img3{{}, Size{img.rows, img.cols}};

  for (size_t i = 0; i < channels.size(); ++i) {
    Img img_temp{MatToVec(channels[i])};
    img3.data[i] = img_temp.data;
  }
  return img3;
}

// Will not be available in source code
cv::Mat ImGrayToMat(const Img& im)
{
  cv::Mat img = cv::Mat::zeros(im.size.rows, im.size.cols, CV_8UC1);

  for (int x = 0; x < im.size.cols; x++) {
    for (int y = 0; y < im.size.rows; y++) {
      img.at<uint8_t>(y, x) = static_cast<uint8_t>(im.At(x, y));
    }
  }
  return img;
}

// Will not be available in source code
cv::Mat Im3ToMat(const Img3& im)
{
  cv::Mat img_r = cv::Mat::zeros(im.size.rows, im.size.cols, CV_8UC1);
  cv::Mat img_g = cv::Mat::zeros(im.size.rows, im.size.cols, CV_8UC1);
  cv::Mat img_b = cv::Mat::zeros(im.size.rows, im.size.cols, CV_8UC1);

  for (int i = 0; i < im.size.rows; ++i) {
    for (int j = 0; j < im.size.cols; ++j) {
      img_r.at<char>(i, j) = (uint8_t) im.data[Red][i * im.size.cols + j];
      img_g.at<char>(i, j) = (uint8_t) im.data[Green][i * im.size.cols + j];
      img_b.at<char>(i, j) = (uint8_t) im.data[Blue][i * im.size.cols + j];
    }
  }

  cv::Mat mat, channels[3];
  channels[0] = img_r;
  channels[1] = img_g;
  channels[2] = img_b;
  cv::merge(channels, 3, mat);
  return mat;
}