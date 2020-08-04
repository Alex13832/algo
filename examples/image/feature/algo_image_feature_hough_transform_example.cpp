///
/// \brief Example source code for Hough transform.
/// \author alex011235
/// \date 2020-06-06 SWE national day :)
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

#include "algo.hpp"
#include "image_helpers.hpp"

using namespace algo::image;
using namespace std;
using namespace cv;

int main()
{
  const std::string kFileName{"../testfiles/road10.png"};

  cv::Mat imgc = cv::imread(kFileName);
  cv::Mat img;
  cv::cvtColor(imgc, img, COLOR_BGR2GRAY);
  img.convertTo(img, CV_8UC1);
  cv::imshow("Original", imgc);

  Img im{MatToVec(img)};
  im = object::ExtractCannyEdges(im);
  im = feature::HoughTransform(im);
  cv::Mat img2 = ImGrayToMat(im);
  cv::imshow("Canny", img2);

  cv::waitKey(0);
  return 0;
}
