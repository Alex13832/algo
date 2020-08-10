///
/// \brief Source code for basic image processing functions.
/// \author alex011235
/// \date 2020-05-18
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_image_basic.hpp"

#include <algorithm>

namespace algo::image {

/////////////////////////////////////////////
/// Image functions
/////////////////////////////////////////////

///////////////////////////////////
/// 8-bit image
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
/// Float image
///////////////////////////////////

float ImgF::At(const int& x, const int& y) const
{
  return data[y * size.cols + x];
}

void ImgF::Set(const int& x, const int& y, const float& value)
{
  data[y * size.cols + x] = value;
}

float& ImgF::operator[](int i)
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

  for (int i = 0; i < size; i++) {
    data[i] = 0.3 * img3.data[Red][i] + 0.59 * img3.data[Green][i] + 0.11 * img3.data[Blue][i];
  }

  Img img{data, img3.size};
  return img;
}

ImgF ToFloat(const Img& img)
{
  ImgF imf{Dataf(img.size.rows * img.size.cols, 0), img.size};

  for (int x = 0; x < img.size.cols; x++) {
    for (int y = 0; y < img.size.rows; y++) {
      imf.Set(x, y, img.At(img.size.cols - 1 - x, y) / 255.0);
    }
  }
  return imf;
}

Img InvertPixels(const Img& im)
{
  Img img{im};
  std::transform(img.data.begin(), img.data.end(), img.data.begin(), [](uint8_t x) {
    return std::max(255 - x, 0);
  });
  return img;
}

Img FlipX(const Img& im)
{
  Img img{Data8(im.size.rows * im.size.cols, 0), im.size};

  for (int x = 0; x < im.size.cols; x++) {
    for (int y = 0; y < im.size.rows; y++) {
      img.Set(x, y, im.At(im.size.cols - 1 - x, y));
    }
  }
  return img;
}

Img FlipY(const Img& im)
{
  Img img{Data8(im.size.rows * im.size.cols, 0), im.size};

  for (int x = 0; x < im.size.cols; x++) {
    for (int y = 0; y < im.size.rows; y++) {
      img.Set(x, y, im.At(x, im.size.rows - 1 - y));
    }
  }
  return img;
}

Img MaxOf(const Img& im1, const Img& im2)
{
  if (!(im1.size == im2.size)) {
    return im1;
  }
  Img img{Data8(im1.size.rows * im1.size.cols, 0), im1.size};

  for (int x = 0; x < im1.size.cols; x++) {
    for (int y = 0; y < im1.size.rows; y++) {
      int max_val = std::max(im1.At(x, y), im2.At(x, y));
      img.Set(x, y, max_val);
    }
  }
  return img;
}

Img Subtract(const Img& im1, const Img& im2)
{
  if (!(im1.size == im2.size)) {
    return im1;
  }
  Img img{Data8(im1.size.rows * im1.size.cols, 0), im1.size};

  for (int x = 0; x < im1.size.cols; x++) {
    for (int y = 0; y < im1.size.rows; y++) {
      uint8_t val = im1.At(x, y) - im2.At(x, y);
      if (val < 0) val = 0;
      if (val > 255) val = 255;
      img.Set(x, y, val);
    }
  }
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

      if (x == 0 && y == 0) {
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

}//namespace algo::image