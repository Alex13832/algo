///
/// \brief Example source code for detection of corners.
/// \author alex011235
/// \date 2020-05-27
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <image_helpers.hpp>
#include <include/algo_image.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

using namespace algo::image;
using namespace std;
using namespace cv;

constexpr int kThreshMin{30};
constexpr int kTreshMax{90};
constexpr int kNbrLines{7};
constexpr int kMinLineDist{5};

int main(int argc, char** argv)
{
  const std::string kFileName{"testfiles/building.png"};

  cv::Mat imgc = cv::imread(kFileName);
  cv::Mat img;
  cv::cvtColor(imgc, img, COLOR_BGR2GRAY);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", imgc);
  cv::GaussianBlur(img, img, cv::Size{7, 7}, 0.95);
  Img im{MatToVec(img)};
  Points points{detect::Corners(im, 1e2, detect::CornerDetType::kShiTomasi)};

  for (const auto& pt : points) {
    //cv::drawMarker(imgc, cv::Point{pt.x, pt.y}, cv::Scalar{255, 255, 0}, MARKER_SQUARE);
    cv::circle(imgc, cv::Point{pt.x, pt.y}, 4, cv::Scalar{255, 255, 0}, 2);
  }

  // Show result
  cv::imshow("Detected corners", imgc);
  cv::waitKey(0);
  return 0;
}
