///
/// \brief Source code for basic image processing functions.
/// \author alex011235
/// \date 2020-05-18
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "algo_image_basic.hpp"

#include <algorithm>
#include <cmath>

namespace algo::image {

/////////////////////////////////////////////
/// Image functions
/////////////////////////////////////////////

///////////////////////////////////
/// 8-bit image.
///////////////////////////////////

uint8_t Img::At(const int& x, const int& y) const
{
  return data[y * size.cols + x];
}

void Img::Set(const int& x, const int& y, const uint8_t& value)
{
  data[y * size.cols + x] = value;
}

uint8_t& Img::operator[](int i)
{
  return data[i];
}

///////////////////////////////////
/// Integral image
///////////////////////////////////

uint32_t IntegralImage::At(const int& x, const int& y) const
{
  return data[y * size.cols + x];
}

void IntegralImage::Set(const int& x, const int& y, const uint32_t& value)
{
  data[y * size.cols + x] = value;
}

/////////////////////////////////////////////
/// Fundamental functions
/////////////////////////////////////////////

Img NewImgGray(const int& rows, const int& cols)
{
  Img im;
  im.size.rows = rows;
  im.size.cols = cols;
  im.data = Data8(rows * cols, 0);
  return im;
}

Img ToGray(const Img3& img3)
{
  int size{img3.size.rows * img3.size.cols};
  Data8 data(size, 0);

  for (size_t i = 0; i < size; i++) {
    data[i] = 0.3 * img3.data[Red][i] + 0.59 * img3.data[Green][i] + 0.11 * img3.data[Blue][i];
  }

  Img img{data, img3.size};
  return img;
}

Img InvertPixels(const Img& im)
{
  Img img{im};
  std::transform(img.data.begin(), img.data.end(), img.data.begin(), [](uint8_t x) {
    return 255 - x;
  });
  return img;
}

/////////////////////////////////////////////
/// Integral images
/////////////////////////////////////////////

IntegralImage ImgToIntegralImage(const Img& im)
{
  IntegralImage img{Data32(im.size.rows * im.size.cols, 0), im.size};

  for (int x = 0; x < im.size.cols; x++) {
    for (int y = 0; y < im.size.rows; y++) {

      if (x == 0 & y == 0) {
        img.Set(x, y, im.At(0, 0));

      } else if (x == 0) {
        img.Set(x, y, img.At(0, y - 1) + im.At(x, y));

      } else if (y == 0) {
        img.Set(x, y, img.At(x - 1, y) + im.At(x, y));

      } else {
        uint32_t yy{img.At(x, y - 1)};
        uint32_t xx{img.At(x - 1, y)};
        uint32_t xy{img.At(x - 1, y - 1)};
        img.Set(x, y, -xy + yy + xx + im.At(x, y));
      }
    }
  }
  return img;
}

uint32_t IntegralBoxSum(const IntegralImage& img, const Rectangle& box)
{
  return img.At(box.x, box.y) + img.At(box.x + box.width - 1, box.y + box.height - 1) - img.At(box.x + box.width - 1, box.y) - img.At(box.x, box.y + box.height - 1);
}

/////////////////////////////////////////////
/// Thresholding
/////////////////////////////////////////////

namespace threshold {

Img Fixed(const Img& im, const uint8_t& threshold, const bool& cut_white)
{
  Img img{im};

  std::for_each(img.data.begin(), img.data.end(), [threshold, cut_white](uint8_t& x) {
    if (x > threshold) {
      x = cut_white ? 255 : 0;
    } else {
      x = cut_white ? 0 : 255;
    }
  });
  return img;
}

Img Adaptive(const Img& im, const int& region_size, const bool& cut_white)
{
  IntegralImage img{ImgToIntegralImage(im)};
  Img res{Data8(im.size.rows * im.size.cols, 0), im.size};

  const int kMargin{region_size / 2};

  for (int x = kMargin; x < im.size.cols - kMargin; x++) {
    for (int y = kMargin; y < img.size.rows - kMargin; y++) {

      Rectangle box{x - kMargin, y - kMargin, region_size, region_size};
      uint32_t box_sum{IntegralBoxSum(img, box)};
      uint32_t avg = box_sum / (region_size * region_size);

      if (im.At(x, y) > avg) {
        res.Set(x, y, 255);
      }
    }
  }

  if (!cut_white) {
    std::for_each(res.data.begin(), res.data.end(), [](uint8_t& x) { x = x == 0 ? 255 : 0; });
  }

  return res;
}

}// namespace threshold

}//namespace algo::image