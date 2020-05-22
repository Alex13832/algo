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
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace algo::image;
using namespace std;

void ProcessFilters()
{
  cv::Mat img = cv::imread("testfiles/road4.png", 0);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", img);

  Img im{MatToVec(img)};
  im = transform::HoughLines(im);

  cv::Mat img2 = ImGrayToMat(im);

  detection::Hlines lines{detection::DetectHoughLines(im, 5)};

  cv::imshow("Result", img2);

  cv::waitKey(0);
}

int main(int argc, char** argv)
{
  ProcessFilters();

  return 0;
}
