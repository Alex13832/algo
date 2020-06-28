///
/// \brief Example source code for detection of corners.
/// \author alex011235
/// \date 2020-05-27
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <image_helpers.hpp>
#include <include/algo.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

using namespace algo::image;
using namespace std;

int main()
{
  const std::string kFileName{"../testfiles/puzzle1.png"};

  cv::Mat imgc = cv::imread(kFileName);
  cv::Mat img;
  cv::cvtColor(imgc, img, cv::COLOR_BGR2GRAY);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", imgc);

  Img im{MatToVec(img)};

  Points points{feature::Corners(im, 5e4, feature::CornerDetType::kHarris, 0, 2)};

  for (const auto& pt : points) {
    cv::circle(imgc, cv::Point{pt.x, pt.y}, 1, cv::Scalar{255, 255, 0}, 2);
  }

  // Show result
  cv::imshow("Detected corners", imgc);
  cv::waitKey(0);
  return 0;
}
