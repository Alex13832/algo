///
/// \brief Example source code for line detection.
/// \author alex011235
/// \date 2020-05-19
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

namespace {
constexpr int kThreshMin{10};
constexpr int kTreshMax{50};
constexpr int kNbrLines{6};
constexpr int kMinLineDist{5};
}// namespace

int main(int argc, char** argv)
{
  const std::string kFileName{"../testfiles/puzzle1.png"};

  cv::Mat imgc = cv::imread(kFileName);
  cv::Mat img;
  cv::cvtColor(imgc, img, COLOR_BGR2GRAY);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", imgc);

  Img im{MatToVec(img)};
  im = object::ExtractCannyEdges(im, kThreshMin, kTreshMax);
  cv::Mat img2 = ImGrayToMat(im);
  cv::imshow("Canny", img2);

  Lines lines{object::ExtractLines(im, kNbrLines, kMinLineDist, 10)};

  for (const auto& line : lines) {
    cv::line(imgc, cv::Point{line.p1.x, line.p1.y}, cv::Point{line.p2.x, line.p2.y}, cv::Scalar{255, 255, 0}, 2);
  }

  // Show result
  cv::imshow("Detected lines", imgc);
  cv::waitKey(0);
  return 0;
}
