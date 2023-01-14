///
/// \brief Data structures for geometry algorithms.
/// \author alex011235
/// \date 2021-02-07
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
/// Change list:
/// 2015-06-04 Triangulation of 2D-points
/// 2015-06-25 Quickhull, convex hull of 2D-points
/// 2015-06-28 Closest pair of 2D-points
/// 2021-02-06 Rotating calipers, minimum bounding box
/// 2021-01-18 Minimum enclosing circle
/// 2022-01-06 Object oriented design
///

#ifndef ALGO_ALGO_INCLUDE_ALGO_GEOMETRY_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_GEOMETRY_HPP_

#include <cmath>
#include <vector>

namespace algo::geometry {

// /////////////////////////////
// MARK: Point

class Point {

 public:
  Point(double x, double y);
  virtual ~Point() = default;

  /// \brief Updates the x and y coordinates.
  /// \param x Coordinate.
  /// \param y Coordinate.
  void Set(double x, double y);

  /// \brief == Operator overloading.
  /// \param p Other point.
  /// \return True if x == p.x and y == p.y
  bool operator==(const Point& p) const;

  /// \brief != Operator overloading.
  /// \param p Other point.
  /// \return x != p.x or y != p.y
  bool operator!=(const Point& p) const;

  /// \brief - Operator overloading.
  /// \param p Other point.
  /// \return Point(x - p.x, y - p.y)
  Point operator-(const Point& p) const;

  /// \brief + Operator overloading.
  /// \param p Other point.
  /// \return Point(x + p.x, y + p.y)
  Point operator+(const Point& p) const;

  /// \brief Returns the Euclidean distance between this point and p.
  /// \param point Other point.
  /// \return Euclidean distance.
  double Dist(const Point& point) const;

  /// \brief Normalizes the coordinates with the magnitude.
  /// \return Normalized point.
  Point Normalize() const;

  /// \brief Returns the value of the x-component.
  /// \return x.
  double X() const;

  /// \brief Returns the value of the y-component.
  /// \return
  double Y() const;

 protected:
  double x_;
  double y_;
};

// /////////////////////////////
// MARK: Edge

class Edge {
 public:
  Edge(const Point& pt1, const Point& pt2);
  virtual ~Edge() = default;

  /// \brief Equals operator overloading.
  /// \param e Other edge.
  /// \return true this this and other edges are equal.
  bool operator==(const Edge& e) const;

  /// \brief Checks if this edge and edge intersect.
  /// \details Note that the edges are not treated as continuing beyond their
  /// edge points.
  /// \param edge Other edge.
  /// \return true if there's an intersection.
  bool Intersect(const Edge& edge) const;

  /// \brief Returns the distance from this edge to the point pt.
  /// \param pt The point.
  /// \return Distance.
  double Dist(const Point& pt) const;

  /// \brief Returns the first edge point.
  /// \return Edge point.
  Point GetStart() const;

  /// \brief Returns the second edge point.
  /// \return Edge point.
  Point GetEnd() const;

  /// \brief Determines which side of a line a point is located.
  /// \param pt The point.
  /// \return 1 if above/right, -1 below/left,
  int Location(const Point& pt) const;

 private:
  Point pt1_;
  Point pt2_;
};

// /////////////////////////////
// MARK: Circle

class Triangle;

class Circle {

 public:
  Circle(const Point& point, double radius);
  virtual ~Circle() = default;

  /// \brief Calculates and returns the area of this circle.
  /// \return Area.
  double Area() const;

  /// \brief Checks if pt is inside this circle.
  /// \param pt The point.
  /// \return true if inside.
  bool IsInside(const Point& pt) const;

  /// \brief Returns an equal sided triangle that encloses the circle.
  /// \return A triangle.
  Triangle EnclosingTriangle() const;

  /// \brief Returns the origin of this circle.
  /// \return The origin.
  Point Origin() const;

  /// \brief Returns the radius of this circle.
  /// \return The radius.
  double Radius() const;

 private:
  Point origin_;
  double radius_;
};

class Rectangle;

// /////////////////////////////
// MARK: Polygon

class Polygon {

 public:
  explicit Polygon(const std::vector<Point>& points);
  virtual ~Polygon() = default;

  /// \brief Returns the number of edges in this polygon.
  /// \return The number of edges.
  size_t EdgeCount();

  /// \brief Rotates this polygon with an angle and around a point center.
  /// \param angle The rotation angle.
  /// \param center The point that the polygon will be rotated around.
  /// \return A rotated copy of this polygon.
  Polygon Rotate(double angle, const Point& center) const;

  /// \brief Rotates this polygon with an angle and around its center point.
  /// \param angle The rotation angle.
  /// \return A rotated copy of this polygon.
  Polygon Rotate(double angle) const;

  /// \brief Returns the center.
  /// \return Center.
  Point GetCenter() const;

  /// \brief Returns the bounding rectangle.
  /// \note Not the minimum bound rectangle.
  /// \return Bounding rectangle.
  Rectangle BoundingRectangle() const;

  /// \brief Returns the points of this polygon.
  /// \return Points.
  std::vector<Point> GetPoints() const;

  /// \brief Returns the i:th edge.
  /// \return The i:ith edge.
  Point GetEdge(size_t i) const;

 protected:
  std::vector<Point> points_;
  Point center_;

 private:
  /// \brief Calculates and returns the area.
  /// \return The area.
  virtual double Area() const;
};

// /////////////////////////////
// MARK: Triangle

class Triangle : public Polygon {
 public:
  Triangle(const Point& pt1, const Point& pt2, const Point& pt3);
  ~Triangle() override = default;

  /// \brief Calculates and returns the area.
  /// \return The area.
  double Area() const override;

  /// \brief Checks if pt is inside this triangle.
  /// \param pt The point.
  /// \return true if inside.
  bool IsInside(const Point& pt) const;

  /// \brief Returns a circum circle of this triangle.
  /// \return Circum circle.
  Circle CircumCircle() const;

 private:
  Point& pt1_;
  Point& pt2_;
  Point& pt3_;
};

// /////////////////////////////
// MARK: Rhombus

class Rhombus : public Polygon {
 public:
  Rhombus(const Point& pt1, const Point& pt2, const Point& pt3,
          const Point& pt4);
  explicit Rhombus(const std::vector<Point>& pts);
  ~Rhombus() override = default;

  /// \brief Calculates and returns the area.
  /// \return The area.
  double Area() const override;

 private:
  Point& pt_a_;
  Point& pt_b_;
  Point& pt_c_;
  Point& pt_d_;
};

// /////////////////////////////
// MARK: Rectangle

class Rectangle : public Polygon {
 public:
  Rectangle(const Point& pt1, double width, double height);
  ~Rectangle() override = default;

  /// \brief Calculates and returns the area.
  /// \return The area.
  double Area() const override;

  /// \brief Returns the input corner points.
  /// \return Corner point.
  Point GetPoint() const;

  /// Returns the width.
  /// \return Width.
  double GetWidth() const;

  /// \brief Returns the height.
  /// \return Height.
  double GetHeight() const;

 private:
  Point& pt_;
  double width_, height_;
};

// /////////////////////////////
// MARK: Grid

class Grid {
 public:
  explicit Grid(const std::vector<Point>& points);

  /// \brief Returns the two points that are closest in distance to each other.
  /// \return Closest pair of points.
  std::pair<Point, Point> ClosestPairOfPoints();

  /// \brief Returns the convex hull of this grid.
  /// \details Using quick hull algorithm.
  /// \return The polygon than makes the convex hull.
  Polygon ConvexHull();

  /// \brief Returns the minimum bounding box if this grid.
  /// \return Minimum bounding box.
  Polygon MinBoundingBox();

  /// \brief Returns the minimum enclosing circle.
  /// \return Minimum enclosing circle.
  Circle MinEnclosingCircle() const;

  /// \brief Returns a triangulation of this grid.
  /// \return A triangulation.
  std::vector<Edge> Triangulate() const;

 private:
  std::vector<Point> points_;
};

using Points = std::vector<Point>;

}// namespace algo::geometry

#endif//ALGO_ALGO_INCLUDE_ALGO_GEOMETRY_HPP_
