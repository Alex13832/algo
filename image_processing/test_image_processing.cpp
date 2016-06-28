// Tests for image_processing
//
// Alexander Karlsson 2016-04-06

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

extern "C" {
#include "image_processing.h"
}
using namespace std;
using namespace cv;

// Converts an OpenCV Mat to a STL vector
vector<uint8_t> Mat_to_vector(Mat img)
{
      vector<uint8_t> pix(img.rows*img.cols,0);

      for (int i = 0; i < img.rows; ++i) {
            for (int j = 0; j < img.cols; ++j) {
                  uint8_t px = img.at<char>(i,j);
                  pix[i*img.cols + j] = px;
            }
      }

      return pix;
}

// Converts a STL vector to an OpenCV Mat
Mat vector_to_Mat(vector<uint8_t> vec, int rows, int cols)
{
      Mat img = Mat::zeros(rows, cols, CV_8UC1);

      for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                  img.at<char>(i,j) = (uint8_t)vec[i*cols + j];
            }
      }

      return img;
}

// Tests the convolution function
void test_convolve()
{
      Mat img = imread("input_images/lena.png",0);
      img.convertTo(img, CV_8UC1);

      vector<string> out_file_names = {   "sobel_x", "sobel_y", "edge_detect", "smoothing",
            "sharpen_modest", "sharepen_aggressive", "gaussian_blur", "blur_hard",
            "blur_soft", "high_pass", "emboss", "weighted_average" };

      vector<filter_t> filters  = { SOBEL_X, SOBEL_Y, EDGE_DETECT, SMOOTHING, SHARPEN_MODEST,
          SHARPEN_AGGRESSIVE, GAUSSIAN_BLUR, BLUR_HARD, BLUR_SOFT, HIGH_PASS, EMBOSS,
          WEIGHTED_AVERAGE};

      // Convert OpenCV Mat to vector
      vector<uint8_t> pix = Mat_to_vector(img);
      vector<uint8_t> result(img.rows*img.cols,0);

      for (unsigned i = 0; i < filters.size(); ++i) {
            // Call c-library
            convolve(&pix[0], &result[0], (int)img.rows, (int)img.cols, filters[i], 3);
            // Convert back to Mat
            Mat img_conv = vector_to_Mat(result, img.rows, img.cols);
            string filename = "images/lena_" + out_file_names[i] + ".png";
            imwrite(filename, img_conv);
      }

}

void test_adaptive_threshold()
{
      Mat img = imread("input_images/lena.png", 0);
      img.convertTo(img, CV_8UC1);

      vector<uint8_t> Im = Mat_to_vector(img);
      vector<uint8_t> data(img.rows*img.cols);

      adaptive_threshold(&Im[0], &data[0], img.rows, img.cols, 15, 0);
      Mat im_tr = vector_to_Mat(data, img.rows, img.cols);
      imwrite("images/lena_adaptive15.png", im_tr);


}

void test_median_filter()
{
    Mat img = imread("input_images/lena_very_noisy.bmp", 0);
    img.convertTo(img, CV_8UC1);

    vector<uint8_t> Im = Mat_to_vector(img);
    vector<uint8_t> data(img.rows*img.cols);

    median_filter(&Im[0], &data[0], img.rows, img.cols);
    Mat im_tr = vector_to_Mat(data, img.rows, img.cols);
    imwrite("images/lena_median.png", im_tr);
}

void test_rank_filter()
{
    Mat img = imread("input_images/lena.png", 0);
    img.convertTo(img, CV_8UC1);

    vector<uint8_t> Im = Mat_to_vector(img);
    vector<uint8_t> data(img.rows*img.cols);

    rank_filter(&Im[0], &data[0], img.rows, img.cols, 0);
    Mat im_tr = vector_to_Mat(data, img.rows, img.cols);
    imwrite("images/lena_rank0.png", im_tr);

    rank_filter(&Im[0], &data[0], img.rows, img.cols, 8);
    im_tr = vector_to_Mat(data, img.rows, img.cols);
    imwrite("images/lena_rank8.png", im_tr);

}

void test_detect_diff()
{
    Mat imRefMat = imread("input_images/lena.png");
    cvtColor(imRefMat, imRefMat, CV_BGR2GRAY);
    imRefMat.convertTo(imRefMat, CV_8UC1);

    Mat imCompMat = imread("input_images/grumpy_lena.png");
    cvtColor(imCompMat, imCompMat, CV_BGR2GRAY);
    imCompMat.convertTo(imCompMat, CV_8UC1);

    vector<uint8_t> ImRef = Mat_to_vector(imRefMat);
    vector<uint8_t> ImComp = Mat_to_vector(imCompMat);

    vector<uint8_t> diff(imRefMat.rows*imRefMat.cols);

    detect_diff(&ImRef[0], &ImComp[0], &diff[0], imRefMat.rows, imRefMat.cols);

    Mat im_tr = vector_to_Mat(diff, imRefMat.rows, imRefMat.cols);
    imwrite("images/lenas_diff.png", im_tr);
}

void test_template_matching()
{
    Mat im = imread("input_images/lena.png");
    cvtColor(im, im, CV_BGR2GRAY);
    im.convertTo(im, CV_8UC1);
    vector<uint8_t> im_vec = Mat_to_vector(im);

    Mat templ = imread("input_images/template.png");
    cvtColor(templ, templ, CV_BGR2GRAY);
    templ.convertTo(templ, CV_8UC1);
    vector<uint8_t> templ_vec = Mat_to_vector(templ);

    int besti, bestj;
    template_match(&im_vec[0], im.rows, im.cols, &templ_vec[0],
                    templ.rows, templ.cols, &besti, &bestj);

    cvtColor(im, im, CV_GRAY2RGB);

    Point2f pt;
    pt.x = besti+20 , pt.y = bestj+20;
    Scalar sc(0,255,255);
    circle(im, pt, 10, sc);

    imwrite("images/lena_template_match.png", im);
}


int main(int argc, char const *argv[])
{
      test_convolve();
      test_adaptive_threshold();
      test_median_filter();
      test_rank_filter();
      test_detect_diff();
      test_template_matching();
      return 0;
}
