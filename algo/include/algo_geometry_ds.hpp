///
/// \brief Data structures for geometry algorithms.
/// \author alex011235
/// \date 2021-02-07
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#ifndef ALGO_ALGO_INCLUDE_ALGO_GEOMETRY_DS_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_GEOMETRY_DS_HPP_

#include <cmath>
#include <vector>

namespace algo::geometry {

// //////////////////////////////////////////
//  Point data structure
// //////////////////////////////////////////

struct Point {
  double x;///< x-coordinate
  double y;///< y-coordinate.

  bool operator==(const Point& p) const
  {
    return x == p.x && y == p.y;
  }

  bool operator!=(const Point& p) const
  {
    return x != p.x || y != p.y;
  }

  Point operator-(const Point& p) const
  {
    return Point{x - p.x, y - p.y};
  }

  /// \brief Normalizes the coordinates with the magnitude.
  /// \return
  Point Normalize() const
  {
    double mag{std::sqrt(x * x + y * y)};
    return {x / mag, y / mag};
  }
};

using Points = std::vector<Point>;///< A list of points in a vector.

// //////////////////////////////////////////
//  Edge data structure
// //////////////////////////////////////////

struct Edge {
  Point a, b;

  bool operator==(const Edge& e) const
  {
    Point p_1 = e.a, p_2 = e.b;
    return (p_1 == a) && (p_2 == b);
  }
};

using Edges = std::vector<Edge>;///< A list of edges in a vector.

// //////////////////////////////////////////
//  Rectangle data structure
// //////////////////////////////////////////

class Polygon;

class Rectangle {
 public:
  Rectangle(const double& x, const double& y, const double& width, const double& height);

  /// \brief Returns the Polygon of this rectangle.
  /// \return A rectangle.
  Polygon GetPolygon();

  /// \brief Returns the area of this rectangle.
  /// \return The area.
  double Area() const { return width_ * height_; };

 private:
  double width_{}; ///< Width of rectangle.
  double height_{};///< Height of rectangle.
  Points pts_;     ///< The four coordinates of the polygon.
};

// //////////////////////////////////////////
//  Polygon structure
// //////////////////////////////////////////

class Polygon {
 public:
  explicit Polygon(const Points& points);

  Point GetEdge(const size_t& i);

  /// \brief Returns the points (coordinates) in this polygon.
  /// \return The points.
  Points GetPoints() { return pts_; };

  /// \brief Returns the number of edges in the polygon.
  /// \return The number of edges in the polygon.
  size_t EdgeCount();

  /// \brief Rotates the polygon with the input angle.
  /// \param angle The angle to rotate the polygon with.
  /// \return A rotated polygon.
  Polygon Rotate(const double& angle);

  /// \brief Rotates the polygon with the input angle.
  /// \param angle The angle to rotate the polygon with.
  /// \param center Center of polygon.
  /// \return
  Polygon Rotate(const double& angle, const Point& center);

  /// \brief Returns a bounding rectangle, oriented to the x-y-axis, enclosing the points in this polygon.
  /// \return Bounding rectangle.
  Rectangle BoundingRectangle();

  /// \brief Gets the center point of this rectangle.
  /// \return The center.
  Point GetCenter() const;

 private:
  Points pts_;    ///< The points that builds up the polygon.
  Point center_{};///< The center of the polygon.
};

// //////////////////////////////////////////
//  Circle data structure
// //////////////////////////////////////////

struct Circle {
  Point center;
  double radius;
};

}// namespace algo::geometry

#endif//ALGO_ALGO_INCLUDE_ALGO_GEOMETRY_DS_HPP_
