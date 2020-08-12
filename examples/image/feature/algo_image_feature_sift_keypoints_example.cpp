///
/// \brief Example source code for detection of corners.
/// \author alex011235
/// \date 2020-05-27
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <string>

#include "algo.hpp"
#include "image_helpers.hpp"

using namespace algo::image;
using namespace std;

int main()
{
  const std::string kFileName{"../testfiles/butterfly.png"};

  cv::Mat imgc = cv::imread(kFileName);
  cv::Mat img;
  cv::cvtColor(imgc, img, cv::COLOR_BGR2GRAY);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", imgc);

  // Check what OpenCV will output
  cv::Ptr<cv::Feature2D> f2d = cv::xfeatures2d::SIFT::create();
  std::vector<cv::KeyPoint> keypoints;
  f2d->detect(img, keypoints);
  std::cout << "OpenCV nbr points " << keypoints.size() << std::endl;

  // This repo's SIFT output:
  Img im{MatToVec(img)};
  Points points = feature::SiftKeypoints(im);

  std::cout << "Framework nbr points " << points.size() << std::endl;
  cv::Mat mat = imgc.clone();

  for (const auto& pt : points) {
    cv::circle(imgc, cv::Point{pt.x, pt.y}, 3, cv::Scalar{255, 255, 0}, 1);
  }

  for (const auto& kp : keypoints) {
    cv::circle(mat, cv::Point{(int) kp.pt.x, (int) kp.pt.y}, 3, cv::Scalar{0, 255, 255}, 1);
  }

  // Show result
  cv::imshow("SIFT", imgc);
  cv::imshow("SIFT cv", mat);
  cv::waitKey(0);
  return 0;
}
