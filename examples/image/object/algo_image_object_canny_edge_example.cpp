///
/// \brief Example source code for detection of Hough lines.
/// \author alex011235
/// \date 2020-06-05
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <image_helpers.hpp>
#include <include/algo.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

using namespace algo::image;
using namespace std;
using namespace cv;

namespace {
constexpr int kThreshMin{30};
constexpr int kTreshMax{90};
constexpr int kNbrLines{25};
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

  cv::waitKey(0);
  return 0;
}
