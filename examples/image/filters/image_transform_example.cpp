///
/// \brief Example source code image transform.
/// \author alex011235
/// \date 2020-05-19
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

///
/// \brief Example source code image filters.
/// \author alex011235
/// \date 2020-05-22
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <image_helpers.hpp>
#include <include/algo_image.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace algo::image;
using namespace std;
using namespace cv;

void ProcessFilters()
{
  cv::Mat imgc = cv::imread("testfiles/sudoku.png");
  cv::Mat img;
  cv::cvtColor(imgc, img, COLOR_BGR2GRAY);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", imgc);

  Img im{MatToVec(img)};
  im = detection::CannyEdge(im, 30, 91);
  cv::Mat img2 = ImGrayToMat(im);
  cv::imshow("Canny", img2);

  Lines lines{detection::DetectHoughLines(im, 45, 40)};

  for (const auto& line : lines) {
    cv::line(imgc, cv::Point{line.p1.x, line.p1.y}, cv::Point{line.p2.x, line.p2.y}, cv::Scalar{255, 255, 0}, 2);
  }

  cv::imshow("Points", imgc);

  cv::waitKey(0);
}

int main(int argc, char** argv)
{
  ProcessFilters();

  return 0;
}
