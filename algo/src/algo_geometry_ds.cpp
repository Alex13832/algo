///
/// \brief Data structures for geometry algorithms.
/// \author alex011235
/// \date 2021-02-07
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_geometry_ds.hpp"

namespace algo::geometry {

namespace {
constexpr double kDblMin{2.2250738585072014e-308};
constexpr double kDblMax{1.79769e+308};

/// \brief Calculates the center point of the points in pts.
constexpr auto CalcCenter = [](const Points& pts) {
  double x_sum{0.0};
  double y_sum{0.0};
  auto n = static_cast<double>(pts.size());
  for (const auto& pt : pts) {
    x_sum += pt.x;
    y_sum += pt.y;
  }
  return Point{x_sum / n, y_sum / n};
};

}// namespace

/////////////////////////////////////////////
/// Rectangle
/////////////////////////////////////////////

Rectangle::Rectangle(const double& x, const double& y, const double& width, const double& height)
    : width_{width},
      height_{height}
{
  pts_ = {{x, y}, {x + width, y}, {x + width, y + height}, {x, y + height}};
}

Polygon Rectangle::GetPolygon()
{
  return Polygon{pts_};
}

/////////////////////////////////////////////
/// Polygon
/////////////////////////////////////////////

Polygon::Polygon(const Points& points) : pts_{points},
                                         center_{CalcCenter(points)}
{
}

Point Polygon::GetEdge(const size_t& i)
{
  const size_t index_next{(i + 1) % pts_.size()};
  const Point pt1{pts_.at(i)};
  const Point pt2{pts_.at(index_next)};
  return pt2 - pt1;
}

size_t Polygon::EdgeCount()
{
  if (pts_.size() <= 2) {
    return pts_.size() - 1;
  }
  return pts_.size();
}

Polygon Polygon::Rotate(const double& angle)
{
  return Rotate(angle, center_);
}

Polygon Polygon::Rotate(const double& angle, const Point& center)
{
  Points points{pts_};
  for (Point& pt : points) {
    double x{pt.x - center.x};
    double y{pt.y - center.y};
    const double tx{x};
    const double sin_of_angle{std::sin(angle)};
    const double cos_of_angle{std::cos(angle)};
    x = x * cos_of_angle - y * sin_of_angle;
    y = tx * sin_of_angle + y * cos_of_angle;
    x += center.x;
    y += center.y;
    pt.x = x;
    pt.y = y;
  }
  return Polygon{points};
}

Rectangle Polygon::BoundingRectangle()
{
  double x_min{kDblMax}, y_min{kDblMax};
  double x_max{kDblMin}, y_max{kDblMin};

  // Find minimum an maximum values of coordinates.
  for (const Point& pt : pts_) {
    if (pt.x > x_max) {
      x_max = pt.x;
    }
    if (pt.y > y_max) {
      y_max = pt.y;
    }
    if (pt.x < x_min) {
      x_min = pt.x;
    }
    if (pt.y < y_min) {
      y_min = pt.y;
    }
  }
  return Rectangle{x_min, y_min, x_max - x_min, y_max - y_min};
}

Point Polygon::GetCenter() const
{
  return center_;
}

}// namespace algo::geometry
