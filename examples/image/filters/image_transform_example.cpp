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
  cv::Mat imgc = cv::imread("testfiles/road6.png");
  cv::Mat img;
  cv::cvtColor(imgc, img, COLOR_BGR2GRAY);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", imgc);

  Img im{MatToVec(img)};

  Img imh = transform::HoughLines(im);
  cv::Mat img3 = ImGrayToMat(imh);
  cv::imshow("Hough", img3);

  detection::Hlines hlines{detection::DetectHoughLines(imh, 30)};

  for (const auto& line : hlines) {
    double a = cos(line.alpha * M_PI / 180.0);
    double b = sin(line.alpha * M_PI / 180.0);
    double x = a * line.dist;
    double y = b * line.dist;

    int x1 = cvRound(x + 1000 * (-b));
    int y1 = cvRound(y + 1000 * (a));
    int x2 = cvRound(x - 1000 * (-b));
    int y2 = cvRound(y - 1000 * (a));

    cv::line(imgc, cv::Point{x1, y1}, cv::Point{x2, y2}, cv::Scalar{255, 255, 0}, 3);
  }

  cv::imshow("Points", imgc);

  cv::waitKey(0);
}

int main(int argc, char** argv)
{
  ProcessFilters();

  return 0;
}
