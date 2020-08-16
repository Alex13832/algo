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
  const std::string kFileName{"../testfiles/skyscrapers.png"};

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
  feature::Keypoints keyp = feature::SiftKeypoints(im, 5, 5, 1.7, 20.0);
  std::vector<cv::KeyPoint> my_keyp;

  std::cout << "Framework nbr points " << keyp.size() << std::endl;
  cv::Mat mat = imgc.clone();

  for (const auto& pt : keyp) {
    //cv::circle(imgc, cv::Point{pt.x, pt.y}, pt.mag, cv::Scalar{255, 255, 0}, 1);
    my_keyp.emplace_back(cv::KeyPoint{cv::Point2f{(float) pt.x, (float) pt.y}, (float) pt.radius, (float) pt.angle});
  }

  cv::drawKeypoints(imgc, my_keyp, imgc, cv::Scalar{255, 255, 0}, cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  cv::drawKeypoints(mat, keypoints, mat, cv::Scalar{0, 255, 255}, cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

  // Show result
  cv::imshow("SIFT cv", mat);
  cv::imshow("SIFT", imgc);
  cv::waitKey(0);
  return 0;
}
