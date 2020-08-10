///
/// \brief Header for basic image processing algorithms.
/// \author alex011235
/// \date 2020-05-18
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
/// Change list:
/// 2016-04-07 Thresholding
/// 2020-05-21 Integral image.
///

#include <array>
#include <vector>

#ifndef ALGO_ALGO_INCLUDE_ALGO_IMAGE_BASIC_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_IMAGE_BASIC_HPP_

namespace algo::image {

// //////////////////////////////////////////
//  Image data
// //////////////////////////////////////////

constexpr uint8_t Red{0};
constexpr uint8_t Green{1};
constexpr uint8_t Blue{2};

struct Point {
  int x, y;
};

struct Line {
  Point p1, p2;// Two points define a line in the xy-plane.
};

struct Size {
  int rows, cols;

  bool operator==(Size other) const { return rows == other.rows && cols == other.cols; }
};

struct Rectangle {
  int x, y, width, height;
};

using Data8 = std::vector<uint8_t>;  // For grayscale images.
using Data32 = std::vector<uint32_t>;// For integral images.
using Data8_3 = std::array<Data8, 3>;// For color images.
using Dataf = std::vector<float>;    // For float images.

using Lines = std::vector<Line>;
using Points = std::vector<Point>;

// //////////////////////////////////////////
//  Image types
// //////////////////////////////////////////

// ////////////////////////////////
//  Color image
// ////////////////////////////////

struct Img3 {
  Data8_3 data;
  Size size{};
};

// ////////////////////////////////
//  8-bit image
// ////////////////////////////////

struct Img {
  Data8 data;
  Size size{};

  /// \brief Returns the value at x, y.
  /// \param x Coordinate x-value.
  /// \param y Coordinate y-value.
  /// \return The value at x, y.
  [[nodiscard]] uint8_t At(const int& x, const int& y) const;

  /// \brief Sets the value at x, y to value.
  /// \param x X-coordinate.
  /// \param y Y-coordinate.
  /// \param value New value at coordinate.
  void Set(const int& x, const int& y, const uint8_t& value);

  /// \brief Operator overloading for quick access of data element.
  /// \param i Index.
  /// \return Value at index.
  uint8_t& operator[](int i);
};

// ////////////////////////////////
//  Float image
// ////////////////////////////////

struct ImgF {
  Dataf data;
  Size size{};

  /// \brief Returns the value at x, y.
  /// \param x Coordinate x-value.
  /// \param y Coordinate y-value.
  /// \return The value at x, y.
  [[nodiscard]] float At(const int& x, const int& y) const;

  /// \brief Sets the value at x, y to value.
  /// \param x X-coordinate.
  /// \param y Y-coordinate.
  /// \param value New value at coordinate.
  void Set(const int& x, const int& y, const float& value);

  /// \brief Operator overloading for quick access of data element.
  /// \param i Index.
  /// \return Value at index.
  float& operator[](int i);
};

// ////////////////////////////////
//  Integral image
// ////////////////////////////////

struct IntegralImage {
  Data32 data;
  Size size{};

  /// \brief Returns the value at x, y.
  /// \param x Coordinate x-value.
  /// \param y Coordinate y-value.
  /// \return The value at x, y.
  [[nodiscard]] uint32_t At(const int& x, const int& y) const;

  void Set(const int& x, const int& y, const uint32_t& value);
};

// //////////////////////////////////////////
//  Fundamental functions
// //////////////////////////////////////////

/// \brief Returns a new grayscale image.
/// \param rows Number of rows.
/// \param cols Number of columns.
/// \return A new grayscale image.
Img NewImgGray(const int& rows, const int& cols);

/// \brief Converts a color image to a gray scale image.
/// \details `gray = 0.3 * red + 0.59 * green + 0.11 * blue`.
/// \param img3 Values to convert.
/// \return A new gray scale image.
Img ToGray(const Img3& img3);

ImgF ToFloat(const Img& img);

/// \brief Inverts all the pixels in the input image, (255 - pixel value).
/// \param im The input image.
/// \return A new image.
Img InvertPixels(const Img& im);

/// \brief Arranges the pixels in im like a mirror, horizontally,
/// \param im The input image.
/// \return Mirrored image.
Img FlipX(const Img& im);

/// \brief Arrange the pixels in im like a mirror, vertically.
/// \param im The input image.
/// \return Mirrored image.
Img FlipY(const Img& im);

/// \brief Returns he maximum values of im1 and im2.
/// \details The sizes of im1 and im2 must match. If not, im1 is returned.
/// \param im1 Input image 1.
/// \param im2 Input image 2.
/// \return Max of all pixels (im1, im2).
Img MaxOf(const Img& im1, const Img& im2);

/// Subtracts im1 with im2.
/// \param im1 First image.
/// \param im2 Second image.
/// \return The subtracted result.
Img Subtract(const Img& im1, const Img& im2);

// //////////////////////////////////////////
//  Integral image
// //////////////////////////////////////////

/// \brief Computes and returns the integral image of im.
/// \param im The input image.
/// \return A new integral image.
/// \link <a href="https://en.wikipedia.org/wiki/Summed-area_table">Summed-area-table, Wikipedia.</a>
IntegralImage ImgToIntegralImage(const Img& im);

/// \brief Computes the sum of the rectangular patch.
/// \param img The input integral image.
/// \param pt_tl Point 1, top left.
/// \param pt_tr Point 2, top right.
/// \param pt_bl Point 3, bottom left.
/// \param pt_br Point 4, bottom right.
/// \return The sum.
uint32_t IntegralBoxSum(const IntegralImage& img, const Rectangle& box);

}// namespace algo::image

#endif//ALGO_ALGO_INCLUDE_ALGO_IMAGE_BASIC_HPP_
