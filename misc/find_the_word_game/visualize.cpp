// File for visualizing the found words
// Thie file uses the OpenCV library.
// Alexander Karlsson
#include <cmath>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void visualize(vector< vector<char> > chars, vector< vector<int> > found)
{
      // Figure out the size
      size_t height = chars.size();
      size_t width = chars[0].size();

      // Give it a size proportional to tbe number of chars
      Mat im = Mat::ones(height*50, width*50, CV_8UC3 );

      // Put different colors on row/column/diagonal words

      for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                  stringstream ss;
                  string s;
                  ss << chars[i][j];
                  ss >> s;

                  if (found[i][j] == 1)
                        putText(im, s, Point2f(20+j*50,30+i*50), 0, FONT_HERSHEY_PLAIN,  Scalar(255,0,0,255), 2);
                  else if (found[i][j] == 2)
                        putText(im, s, Point2f(20+j*50,30+i*50), 0, FONT_HERSHEY_PLAIN,  Scalar(0,255,0,255), 2);
                  else if (found[i][j] == 3)
                        putText(im, s, Point2f(20+j*50,30+i*50), 0, FONT_HERSHEY_PLAIN,  Scalar(0,0,255,255), 2);
                  else
                        putText(im, s, Point2f(20+j*50,30+i*50), 0, FONT_HERSHEY_PLAIN,  Scalar(255,255,255,255), 2);
            }
      }

      imshow("asf", im);
      waitKey(0);
 }
