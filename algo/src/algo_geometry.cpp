///
/// \brief Data structures for computational geometry algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_geometry.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {
constexpr double kPi{3.14159265358979323846264338327950288};

constexpr size_t kMinPolygonPoints{3UL};
constexpr size_t kMinBoundingBoxPoints{3UL};
constexpr size_t kMinDelaunayTriangulationPoints{3UL};
constexpr size_t kMinConvexHullPoints{3UL};
constexpr size_t kMinClosestPairPoints{3UL};

constexpr auto kXComp = [](auto p1, auto p2) { return p1.X() < p2.X(); };
constexpr auto kYComp = [](auto p1, auto p2) { return p1.Y() < p2.Y(); };

}  // namespace

namespace algo::geometry {

std::vector<Point> helpers::SortCounterClockWise(
    const std::vector<Point>& pts) {
  std::vector<Point> points{pts};
  // Find point with lowest y-value
  double y_lowest{std::numeric_limits<double>::max()};
  Point pt_y_lowest{0.0, 0.0};

  for (const auto& pt : points) {
    if (pt.Y() < y_lowest) {
      y_lowest = pt.Y();
      pt_y_lowest = pt;
    }
  }

  const auto comp = [pt_y_lowest](const Point& p1, const Point& p2) {
    const double polar_p1{
        std::atan2(p1.Y() - pt_y_lowest.Y(), p1.X() - pt_y_lowest.X())};
    const double polar_p2{
        std::atan2(p2.Y() - pt_y_lowest.Y(), p2.X() - pt_y_lowest.X())};
    return polar_p1 < polar_p2;
  };

  std::sort(points.begin(), points.end(), comp);

  return points;
}

// /////////////////////////////
// MARK: Point

Point::Point(double x, double y) : x_{x}, y_{y} {}

void Point::Set(double x, double y) {
  x_ = x;
  y_ = y;
}

bool Point::operator==(const Point& p) const {
  return (x_ == p.x_) && (y_ == p.y_);
}

bool Point::operator!=(const Point& p) const {
  return (x_ != p.x_) || (y_ != p.y_);
}
Point Point::operator-(const Point& p) const {
  return Point{x_ - p.x_, y_ - p.y_};
}

Point Point::operator+(const Point& p) const {
  return Point{x_ + p.x_, y_ + p.y_};
}

double Point::Dist(const Point& point) const {
  return std::sqrt(std::pow(x_ - point.x_, 2) + std::pow(y_ - point.y_, 2));
}

Point Point::Normalize() const {
  const auto magnitude = std::sqrt(x_ * x_ + y_ * y_);
  if (magnitude == 0) {
    return Point{0, 0};
  }
  return Point{x_ / magnitude, y_ / magnitude};
}

double Point::X() const {
  return x_;
}

double Point::Y() const {
  return y_;
}

// /////////////////////////////
// MARK: Edge

Edge::Edge(const Point& pt1, const Point& pt2) : pt1_{pt1}, pt2_{pt2} {
  if (pt1 == pt2) {
    throw std::invalid_argument("Points are equal.");
  }
}

bool Edge::operator==(const Edge& e) const {
  return ((pt1_ == e.pt1_) && (pt2_ == e.pt2_)) or
         ((pt2_ == e.pt1_) && (pt1_ == e.pt2_));
}

namespace {

// Edge intersection
// http://jeffe.cs.illinois.edu/teaching/373/notes/x06-sweepline.pdf

}  // namespace

bool Edge::Intersect(const Edge& edge) const {
  const Point& p1{pt1_};
  const Point& p2{pt2_};
  const Point& p3{edge.pt1_};
  const Point& p4{edge.pt2_};

  const auto ccw = [](const Point& p1, const Point& p2, const Point& p3) {
    return ((p3.Y() - p1.Y()) * (p2.X() - p1.X())) >=
           ((p2.Y() - p1.Y()) * (p3.X() - p1.X()));
  };

  const bool is_ccw{(ccw(p1, p3, p4) != ccw(p2, p3, p4)) &&
                    (ccw(p1, p2, p3) != ccw(p1, p2, p4))};

  // Degeneracy, if two points are equal, they should not count as intersection
  const bool b{p1 != p3};
  const bool c{p1 != p4};
  const bool d{p2 != p3};
  const bool e{p2 != p4};
  const bool f{p1 != p3};
  const bool g{p3 != p4};

  return is_ccw && b && c && d && e && f && g;
}

double Edge::Dist(const Point& pt) const {
  Point pt_max{pt2_};
  if (pt1_.X() > pt_max.X()) {
    pt_max = pt1_;
  }
  auto pt_min = pt1_;
  if (pt2_.X() < pt_min.X()) {
    pt_min = pt2_;
  }

  // The x value of pt is larger than largest x, then the distance to the
  // line is the same as the distance to the right most coordinate.
  if (pt.X() > pt_max.X()) {
    return pt.Dist(pt_max);
  }
  // The x value of pt is smaller than smallest x, then the distance to the
  // line is the same as the distance to the left most coordinate.
  if (pt.X() < pt_min.X()) {
    return pt.Dist(pt_min);
  }

  // pt.x is withing bounds.
  const double x1{pt1_.X()};
  const double x2{pt2_.X()};
  const double y1{pt1_.Y()};
  const double y2{pt2_.Y()};
  const double a{1.0};
  const double b{(y1 - y2) / (x2 - x1)};
  const double c{x1 * (y2 - y1) / (x2 - x1) - y1};
  return std::abs(a * pt.X() + b * pt.Y() + c) / std::sqrt(a * a + b * b);
}

Point Edge::GetStart() const {
  return pt1_;
}

Point Edge::GetEnd() const {
  return pt2_;
}

int Edge::Location(const Point& pt) const {
  const double temp{(pt2_.X() - pt1_.X()) * (pt.Y() - pt1_.Y()) -
                    (pt2_.Y() - pt1_.Y()) * (pt.X() - pt1_.X())};
  return temp > 0.0 ? 1 : -1;
}

// /////////////////////////////
// MARK: Circle

Circle::Circle(Point point, double radius)
    : origin_{std::move(point)}, radius_{radius} {}

double Circle::Area() const {
  return radius_ * radius_ * kPi;
}

bool Circle::IsInside(const Point& pt) const {
  return origin_.Dist(pt) <= radius_;
}

Triangle Circle::EnclosingTriangle() const {
  // The distance from each corner point of the triangle to the point on
  // the triangle's base perpendicular to the origin.
  const double phi{radius_ / tan(30.0 * kPi / 180.0)};
  // The distance from the origin to each corner point.
  const double sigma{std::sqrt(std::pow(radius_, 2) + std::pow(phi, 2))};

  // An equal sided triangle of these points.
  const Point p1{(origin_.X() - phi), origin_.Y() - radius_};
  const Point p2{origin_.X() + phi, origin_.Y() - radius_};
  const Point p3{origin_.X(), origin_.Y() + sigma};

  return Triangle{p1, p2, p3};
}

Point Circle::Origin() const {
  return origin_;
}

double Circle::Radius() const {
  return radius_;
}

// /////////////////////////////
// MARK: Polygon

namespace {

inline Point CenterOfPoints(const std::vector<Point>& pts) {
  double x_sum{0.0};
  double y_sum{0.0};

  if (pts.empty()) {
    throw std::invalid_argument("Division by zero.");
  }

  auto n = static_cast<double>(pts.size());
  for (const auto& pt : pts) {
    x_sum += pt.X();
    y_sum += pt.Y();
  }
  return Point{x_sum / n, y_sum / n};
}

inline bool IsSortedCounterClockwise(const std::vector<Point>& pts) {
  // Skipping checks since that was done in constructor.
  // Get any three points.
  const Point& pt1{pts.at(0)};
  const Point& pt2{pts.at(1)};
  const Point& pt3{pts.at(2)};

  const double cross_product{(pt2.X() - pt1.X()) * (pt3.Y() - pt1.Y()) -
                             (pt3.X() - pt1.X()) * (pt2.Y() - pt1.Y())};

  return cross_product > 0.0;
}

inline bool AnyPointPairEqual(const std::vector<Point>& pts) {
  for (size_t i = 0; i < pts.size() - 1; i++) {
    if (pts.at(i) == pts.at(i + 1)) {
      return true;
    }
  }
  return pts.back() == pts.front();
}

}  // namespace

Polygon::Polygon(const std::vector<Point>& points)
    : points_{points}, center_{CenterOfPoints(points)} {
  if (points.size() < kMinPolygonPoints) {
    throw std::invalid_argument("Less than three points");
  }
  if (AnyPointPairEqual(points)) {
    throw ::std::invalid_argument("Contains equal point pairs.");
  }
  if (not IsSortedCounterClockwise(points)) {
    throw std::invalid_argument("Not sorted counter clockwise");
  }
};

size_t Polygon::EdgeCount() const {
  return points_.size() <= 2 ? (points_.size() - 1) : points_.size();
}

Point Polygon::GetEdge(const size_t i) const {
  const size_t index_next{(i + 1) % points_.size()};
  const Point pt1{points_.at(i)};
  const Point pt2{points_.at(index_next)};
  return pt2 - pt1;
}

std::vector<Edge> Polygon::GetEdges() const {
  std::vector<Edge> edges;
  for (size_t i = 0; i < points_.size() - 1; i++) {
    edges.emplace_back(points_.at(i), points_.at(i + 1));
  }
  edges.emplace_back(points_.back(), points_.front());
  return edges;
}

double Polygon::Area() const {
  double area{0.0};

  const auto det = [](const Point& p1, const Point& p2) {
    return p1.X() * p2.Y() - p1.Y() * p2.X();
  };

  for (size_t i = 0; i < points_.size() - 1; i++) {
    area += det(points_.at(i), points_.at(i + 1));
  }
  // Includes last point to first point, closed loop.
  area += det(points_.back(), points_.front());

  return area / 2.0;
}

Polygon Polygon::Rotate(const double angle, const Point& center) const {
  auto points = points_;

  for (auto& pt : points) {
    double x{pt.X() - center.X()};
    double y{pt.Y() - center.Y()};
    const double tx{x};

    x = tx * std::cos(angle) - y * std::sin(angle);
    y = tx * std::sin(angle) + y * std::cos(angle);
    x += center.X();
    y += center.Y();
    pt.Set(x, y);
  }
  return Polygon{points};
}

Polygon Polygon::Rotate(const double angle) const {
  return Rotate(angle, center_);
}

Point Polygon::GetCenter() const {
  return center_;
}

Rectangle Polygon::BoundingRectangle() const {
  auto x_min = std::numeric_limits<double>::max();
  auto y_min = std::numeric_limits<double>::max();
  double x_max{0.0};
  double y_max{0.0};

  // Find minimum a maximum values of coordinates.
  for (const Point& pt : points_) {
    x_max = std::max(pt.X(), x_max);
    y_max = std::max(pt.Y(), y_max);
    x_min = std::min(pt.X(), x_min);
    y_min = std::min(pt.Y(), y_min);
  }

  return Rectangle{{x_min, y_min}, x_max - x_min, y_max - y_min};
}

std::vector<Point> Polygon::GetPoints() const {
  return points_;
}

// /////////////////////////////
// MARK: Triangle

Triangle::Triangle(const Point& pt1, const Point& pt2, const Point& pt3)
    : Polygon({pt1, pt2, pt3}), pt1_{pt1}, pt2_{pt2}, pt3_{pt3} {}

bool Triangle::IsInside(const Point& pt) const {
  if ((pt == pt1_) || (pt == pt2_) || (pt == pt3_)) {
    // pt is a corner point -> "inside" ?
    return true;
  }

  const auto area_of_triangle = [](const Point& pt1, const Point& pt2,
                                   const Point& pt3) {
    return std::abs((pt1.X() * (pt2.Y() - pt3.Y()) +
                     pt2.X() * (pt3.Y() - pt1.Y()) +
                     pt3.X() * (pt1.Y() - pt2.Y())) /
                    2.0);
  };

  const double area0{Area()};
  const double area1{area_of_triangle(pt, pt2_, pt3_)};
  const double area2{area_of_triangle(pt1_, pt, pt3_)};
  const double area3{area_of_triangle(pt1_, pt2_, pt)};
  return area0 == (area1 + area2 + area3);
}

bool Triangle::HasEdge(const Edge& edge) const {
  if ((edge.GetStart() == pt1_) && (edge.GetEnd() == pt2_)) {
    return true;
  }
  if ((edge.GetStart() == pt1_) && (edge.GetEnd() == pt3_)) {
    return true;
  }
  if ((edge.GetStart() == pt2_) && (edge.GetEnd() == pt3_)) {
    return true;
  }
  if ((edge.GetStart() == pt2_) && (edge.GetEnd() == pt1_)) {
    return true;
  }
  if ((edge.GetStart() == pt3_) && (edge.GetEnd() == pt1_)) {
    return true;
  }
  if ((edge.GetStart() == pt3_) && (edge.GetEnd() == pt2_)) {
    return true;
  }
  return false;
}

Circle Triangle::CircumCircle() const {
  const double x1{pt1_.X()};
  const double y1{pt1_.Y()};
  const double x2{pt2_.X()};
  const double y2{pt2_.Y()};
  const double x3{pt3_.X()};
  const double y3{pt3_.Y()};

  const auto angle = [](const Point& pt3, const Point& pt1, const Point& pt2) {
    return atan2(pt3.Y() - pt1.Y(), pt3.X() - pt1.X()) -
           atan2(pt2.Y() - pt1.Y(), pt2.X() - pt1.X());
  };

  const double angle_a{angle(pt3_, pt1_, pt2_)};  // P1
  const double angle_b{angle(pt1_, pt2_, pt3_)};  // P2
  const double angle_c{angle(pt2_, pt3_, pt1_)};  // P3

  const double s_ox{
      (x1 * sin(2 * angle_a) + x2 * sin(2 * angle_b) + x3 * sin(2 * angle_c)) /
      (sin(2 * angle_a) + sin(2 * angle_b) + sin(2 * angle_c))};
  const double s_oy{
      (y1 * sin(2 * angle_a) + y2 * sin(2 * angle_b) + y3 * sin(2 * angle_c)) /
      (sin(2 * angle_a) + sin(2 * angle_b) + sin(2 * angle_c))};

  const Point cc{s_ox, s_oy};
  const double radius{cc.Dist(pt1_)};

  return Circle{cc, radius};
}

bool Triangle::operator==(const Triangle& tr) const {
  if ((pt1_ == tr.pt1_) && (pt2_ == tr.pt2_) && (pt3_ == tr.pt3_)) {
    return true;
  }
  if ((pt1_ == tr.pt3_) && (pt2_ == tr.pt1_) && (pt3_ == tr.pt2_)) {
    return true;
  }
  if ((pt1_ == tr.pt2_) && (pt2_ == tr.pt3_) && (pt3_ == tr.pt1_)) {
    return true;
  }
  return false;
}

// /////////////////////////////
// MARK: Rhombus

Rhombus::Rhombus(const Point& pt1, const Point& pt2, const Point& pt3,
                 const Point& pt4)
    : Polygon({pt1, pt2, pt3, pt4}) {
  const double ab{pt1.Dist(pt2)};
  const double bc{pt2.Dist(pt3)};
  const double cd{pt3.Dist(pt4)};
  const double da{pt4.Dist(pt1)};
  if ((ab != bc) || (bc != cd) || (cd != da) || (da != ab)) {
    throw std::invalid_argument("Side lengths not equal.");
  }
}

// /////////////////////////////
// MARK: Rectangle

Rectangle::Rectangle(const Point& pt1, double width, double height)
    : Polygon({pt1, Point{pt1.X() + width, pt1.Y()},
               Point{pt1.X() + width, pt1.Y() + height},
               Point{pt1.X(), pt1.Y() + height}}),
      width_{width},
      height_{height} {}

Point Rectangle::GetPoint() const {
  return points_.front();
}

double Rectangle::GetWidth() const {
  return width_;
}

double Rectangle::GetHeight() const {
  return height_;
}

// /////////////////////////////
// MARK: Grid

Grid::Grid(const std::vector<Point>& points) : points_{points} {}

// /////////////////////////////
// MARK: Closest pair of points

namespace {

/// \brief Returns the closes pair of points, brute force. Only to be used on a
/// very small set of points.
/// \param xp Input points.
/// \param yp Input points.
/// \return Closest pair of points.
std::pair<double, std::vector<Point>> ClosestPairBF(
    const std::vector<Point>& xp, const std::vector<Point>& yp) {
  auto min_dist = std::numeric_limits<double>::max();
  Point xp_min{0.0, 0.0};
  Point yp_min{0.0, 0.0};

  for (const auto& px : xp) {
    for (const auto& py : yp) {
      if (px.X() != py.X() || px.Y() != py.Y()) {
        if (px.Dist(py) < min_dist) {
          min_dist = px.Dist(py);
          xp_min = px;
          yp_min = py;
        }
      }
    }
  }

  return std::make_pair(min_dist, std::vector<Point>{xp_min, yp_min});
}

/// \brief Divide and conquer algorithm to find the closest pair of points.
/// \param xp Set of points.
/// \param yp Set of points.
/// \return The min distance and the two closest points.
// NOLINTNEXTLINE
std::pair<double, std::vector<Point>> ClosestPair(
    const std::vector<Point>& xp, const std::vector<Point>& yp) {
  // Brute force if size <= 3
  if (xp.size() <= kMinClosestPairPoints) {
    return ClosestPairBF(xp, yp);
  }
  auto n = static_cast<int>(xp.size());

  std::vector<Point> x_left;
  std::vector<Point> x_right;
  std::vector<Point> y_left;
  std::vector<Point> y_right;

  std::copy(xp.begin(), xp.begin() + (n / 2), std::back_inserter(x_left));
  std::copy(xp.begin() + (n / 2), xp.end(), std::back_inserter(x_right));
  // Mid point on x-axis
  const Point& mid_x_pt{xp.at(n / 2)};

  std::copy_if(yp.begin(), yp.end(), std::back_inserter(y_left),
               [&mid_x_pt](auto pt) { return pt.X() <= mid_x_pt.X(); });

  std::copy_if(yp.begin(), yp.end(), std::back_inserter(y_right),
               [&mid_x_pt](auto pt) { return pt.X() > mid_x_pt.X(); });

  // Recursive calls
  auto c_l = ClosestPair(x_left, y_left);
  auto c_r = ClosestPair(x_right, y_right);

  auto p_min = c_l.first < c_r.first ? c_l.second : c_r.second;
  const double dist_min{c_l.first < c_r.first ? c_l.first : c_r.first};

  std::vector<Point> ys;
  std::copy_if(xp.begin(), xp.end(), std::back_inserter(ys),
               [&dist_min, &mid_x_pt](auto pt) {
                 return std::abs(mid_x_pt.X() - pt.X()) < dist_min;
               });

  double closest_dist{dist_min};
  auto closest_pair = p_min;

  for (size_t i = 0; i < ys.size(); ++i) {
    size_t k{i + 1};

    while (k < ys.size() && ((ys.at(k).Y() - ys.at(i).Y()) < dist_min)) {
      if (ys.at(k).Dist(ys.at(i)) < closest_dist) {
        closest_dist = ys.at(k).Dist(ys.at(i));
        closest_pair = {ys[k], ys[i]};
      }
      k++;
    }
  }

  return std::make_pair(closest_dist, closest_pair);
}

}  // namespace

std::pair<Point, Point> Grid::ClosestPairOfPoints() const {
  auto ptsx = points_;
  auto ptsy = points_;
  std::sort(ptsx.begin(), ptsx.end(), kXComp);
  std::sort(ptsy.begin(), ptsy.end(), kYComp);

  const auto closest = ClosestPair(ptsx, ptsy);
  // Closest points in input:
  const Point& p1{closest.second.front()};
  const Point& p2{closest.second.back()};
  return std::make_pair(p1, p2);
}

// /////////////////////////////
// MARK: ConvexHull

namespace {

/// \brief Determines the distance between a point p and the line ln.
/// \param p The point.
/// \param ln The line.
/// \return Distance.
inline double DistanceToLine(const Point& p, const Edge& ln) {
  const double abx{ln.GetEnd().X() - ln.GetStart().X()};
  const double aby{ln.GetEnd().Y() - ln.GetStart().Y()};
  const double dist{abx * (ln.GetStart().Y() - p.Y()) -
                    aby * (ln.GetStart().X() - p.X())};
  return dist < 0 ? -1.0 * dist : dist;
}

inline int MaxEdgeDistanceIndex(const std::vector<Point>& pts,
                                const Edge& edge) {
  int ci{0};
  int k{0};
  double max_dist{0.0};

  for (const auto& p : pts) {
    const double curr_dist{DistanceToLine(p, edge)};
    if (curr_dist > max_dist) {
      max_dist = curr_dist;
      ci = k;
    }
    ++k;
  }
  return ci;
}

/// \brief Subroutine of Quickhull. Not to be accessible from outside of this
/// file. Use ConvexHull.
// NOLINTNEXTLINE
void QuickHull(const Point& a, const Point& b, std::vector<Point>& pts,
               std::vector<Point>& conv_hull_pts) {
  if (pts.empty()) {
    return;
  }

  if (pts.size() == 1) {
    conv_hull_pts.emplace_back(pts.front());
    pts.erase(pts.begin());
    return;
  }

  const int max_edge_index{MaxEdgeDistanceIndex(pts, Edge{a, b})};
  const Point point_at_max_index{pts.at(max_edge_index)};

  conv_hull_pts.push_back(point_at_max_index);
  pts.erase(pts.begin() + max_edge_index);

  std::vector<Point> pts_a;
  std::vector<Point> pts_b;

  const Edge edge1{a, point_at_max_index};
  const Edge edge2{point_at_max_index, b};

  for (const auto& p : pts) {
    // Checking which side of edge p is.
    if (edge1.Location(p) == 1) {
      pts_a.emplace_back(p);
    }
    if (edge2.Location(p) == 1) {
      pts_b.emplace_back(p);
    }
  }

  // Recursive calls
  QuickHull(a, point_at_max_index, pts_a, conv_hull_pts);
  QuickHull(point_at_max_index, b, pts_b, conv_hull_pts);
}

}  // namespace

Polygon Grid::ConvexHull() const {
  if (points_.size() < kMinConvexHullPoints) {
    throw std::invalid_argument("To few points in input.");
  }

  auto pts = points_;
  std::sort(pts.begin(), pts.end(), kXComp);

  // b and a with min and max x-coordinates respectively
  const Point b{pts.front()};
  const Point a{pts.back()};
  std::vector<Point> pts_ch{a, b};
  pts.erase(pts.begin());
  pts.erase(pts.end() - 1);

  std::vector<Point> left;
  std::vector<Point> right;

  const Edge edge{a, b};
  // Determine which side of line (a,b)
  for (const auto& pt : pts) {
    edge.Location(pt) == -1 ? left.emplace_back(pt) : right.emplace_back(pt);
  }

  // Call qhull with two sets
  QuickHull(a, b, right, pts_ch);  // NOLINT
  QuickHull(b, a, left, pts_ch);   // NOLINT

  pts_ch = helpers::SortCounterClockWise(pts_ch);
  return Polygon{pts_ch};
}

// /////////////////////////////
// MARK: MinBoundingBox

namespace {

/// Minimum bounding box, rotating calipers
/// https://github.com/Glissando/Rotating-Calipers

std::vector<Polygon> RotatingCalipers(const Polygon& convex_hull_pts) {
  std::vector<Polygon> polygons;

  for (size_t i = 0; i < convex_hull_pts.EdgeCount(); i++) {
    const Point edge{convex_hull_pts.GetEdge(i)};
    const double angle1{std::acos(edge.Normalize().Y())};
    auto polygon1 = convex_hull_pts.Rotate(angle1);
    const auto box = polygon1.BoundingRectangle();
    polygon1 = polygon1.Rotate(-angle1);
    const Point center{polygon1.GetCenter()};
    const Polygon pg{box.GetPoints()};
    polygons.emplace_back(pg.Rotate(-angle1, center));
  }

  return polygons;
}

Polygon GetMinBox(const std::vector<Polygon>& polygons) {
  auto iter = std::min_element(
      polygons.begin(), polygons.end(),
      [](const auto& polygon1, const auto& polygon2) {
        const auto pts1 = polygon1.GetPoints();
        const Rhombus rhombus1{pts1.at(0), pts1.at(1), pts1.at(2), pts1.at(3)};
        const auto pts2 = polygon2.GetPoints();
        const Rhombus rhombus2{pts2.at(0), pts2.at(1), pts2.at(2), pts2.at(3)};
        return rhombus1.Area() < rhombus2.Area();
      });
  return *iter;
}

}  // namespace

Polygon Grid::MinBoundingBox() const {
  // The only other constraint is if all points are on the same line.
  if (points_.size() < kMinBoundingBoxPoints) {
    throw std::invalid_argument("Too few points in input.");
  }

  auto convex_hull_pts = ConvexHull();
  auto polygons = RotatingCalipers(convex_hull_pts);

  return GetMinBox(polygons);
}

// /////////////////////////////
// MARK: MinEnclosingCircle

namespace {

/// \brief Makes a circle out of the the given points located on the radius.
/// \param p1 Point 1.
/// \param p2 Point 2.
/// \param p3 Point 3.
/// \return A circle of p1, p2, p3.
inline Circle CircleOf3(const Point& p1, const Point& p2, const Point& p3) {
  const double bx{p2.X() - p1.X()};
  const double by{p2.Y() - p1.Y()};
  const double cx{p3.X() - p1.X()};
  const double cy{p3.Y() - p1.Y()};
  const double b{bx * bx + by * by};
  const double c{cx * cx + cy * cy};
  const double d{bx * cy - by * cx};

  const double mid_x{p1.X() + (cy * b - by * c) / (2.0 * d)};
  const double mid_y{p1.Y() + (bx * c - cx * b) / (2.0 * d)};
  const Point center{mid_x, mid_y};
  const double radius{center.Dist(p1)};

  return {center, radius};
}

/// \brief Returns a circle out of either 1, 2 or 3 points.
/// \param pts Given points, |points| ≤ 3.
/// \return A circle.
inline Circle TrivialCircumcircle(std::vector<Point> pts) {
  if (pts.empty() || pts.size() > 3) {
    return Circle{{0, 0}, 0};
  }
  // Single point given
  if (pts.size() == 1) {
    return Circle{pts.front(), 0};
  }
  // Two points on the circle
  if (pts.size() == 2) {
    const Point p1 = pts.at(0);
    const Point p2 = pts.at(1);
    const Point mid{(p1.X() + p2.X()) / 2.0, (p1.Y() + p2.Y()) / 2.0};
    const double diameter{p1.Dist(p2)};
    return Circle{mid, diameter / 2.0};
  }
  // Last case, three points are on the circle
  return CircleOf3(pts.at(0), pts.at(1), pts.at(2));
}

/// \brief Runs the Welzl step of the minimum enclosing circle step.
/// \param pts Points to construct a circle around.
/// \param r Input plane.
/// \return A circle around the points in pts.
// NOLINTNEXTLINE
inline Circle Welzl(std::vector<Point> pts, std::vector<Point> r) {
  if (pts.empty() || r.size() == 3) {
    return TrivialCircumcircle(r);
  }
  auto index = std::rand() % pts.size();
  auto p = pts.at(index);
  pts.erase(pts.begin() + static_cast<long>(index));
  auto circle = Welzl(pts, r);

  if (circle.IsInside(p)) {
    return circle;
  }

  r.emplace_back(p);
  return Welzl(pts, r);
}

}  // namespace

Circle Grid::MinEnclosingCircle() const {
  const std::vector<Point> r;
  return Welzl(points_, r);
}

// /////////////////////////////
// MARK: Triangulate

namespace {

/// \brief Sorts the input points lexicographically,
/// \param pts The input points.
inline void LexSortPoints(std::vector<Point>& pts) {
  auto x = pts.front().X();
  std::vector<Point> pts2;
  std::vector<Point> pts_res;

  for (auto& pt : pts) {
    if (pt.X() != x) {
      std::sort(pts2.begin(), pts2.end(), kXComp);
      std::copy(pts2.begin(), pts2.end(), std::back_inserter(pts_res));
      pts2.clear();
      x = pt.X();
    }

    pts2.emplace_back(pt);
  }

  if (!pts2.empty()) {
    std::copy(pts2.begin(), pts2.end(), std::back_inserter(pts_res));
  }

  pts = pts_res;
}

}  // namespace

std::vector<Edge> Grid::Triangulation() const {
  auto pts = points_;
  LexSortPoints(pts);

  std::vector<Point> visited{pts.at(0), pts.at(1), pts.at(2)};
  bool intersection{false};

  // The three first points constructs a triangle.
  const Edge l0{pts.at(0), pts.at(1)};
  const Edge l1{pts.at(0), pts.at(2)};
  const Edge l2{pts.at(1), pts.at(2)};
  std::vector<Edge> lines{l0, l1, l2};

  // From this point add points to the only triangulate incrementally.
  for (size_t i = 3; i < pts.size(); ++i) {
    auto& pt0 = pts.at(i);

    // Target point pi
    for (auto pi = visited.rbegin(); pi != visited.rend(); ++pi) {
      const Edge edge1{pt0, *pi};

      // Verify that the segment p0-pi doesn't intersect e
      for (auto e = lines.rbegin(); e != lines.rend(); ++e) {
        if (edge1.Intersect(*e)) {
          intersection = true;
          break;  // when something intersects
        }
      }

      if (!intersection) {
        const Edge line{pt0, *pi};
        lines.emplace_back(line);
      }
      intersection = false;
    }
    visited.emplace_back(pt0);
  }

  return lines;
}

// /////////////////////////////
// MARK: DelaunayTriangulation

namespace {

/// \brief Returns all the edges from the triangles.
/// \param triangles Triangles.
/// \return All edges.
std::vector<Edge> TrianglesToEdges(const std::vector<Triangle>& triangles) {
  std::vector<Edge> all_edges;
  for (const auto& triangle : triangles) {
    auto edges = triangle.GetEdges();
    all_edges.emplace_back(edges.at(0));
    all_edges.emplace_back(edges.at(1));
    all_edges.emplace_back(edges.at(2));
  }
  return all_edges;
}

/// \brief Returns all edges that are not shared with no other triangle.
/// \param[in] triangles Triangles.
/// \return Edges.
std::vector<Edge> GetNonSharingEdges(const std::vector<Triangle>& triangles) {
  std::vector<Edge> polygon;
  for (const auto& triangle_i : triangles) {
    for (const auto& edge : triangle_i.GetEdges()) {
      bool sharing_edge{false};
      for (const auto& triangle_j : triangles) {
        if (triangle_i == triangle_j) {
          continue;
        }
        if (triangle_j.HasEdge(edge)) {
          sharing_edge = true;
          break;
        }
      }
      if (not sharing_edge) {
        polygon.emplace_back(edge);
      }
    }
  }
  return polygon;
}

/// \brief Removes triangles that are equal in triangulation and bad_triangles.
/// \param[in,out] triangulation Triangles.
/// \param[in] bad_triangles Triangles.
inline void RemoveEqualTriangles(std::vector<Triangle>& triangulation,
                                 const std::vector<Triangle>& bad_triangles) {
  auto iter = triangulation.begin();

  while (iter != triangulation.end()) {
    for (const auto& bt : bad_triangles) {
      iter = std::find_if(triangulation.begin(), triangulation.end(),
                          [bt](const Triangle& tri) { return tri == bt; });

      if (iter != triangulation.end()) {
        triangulation.erase(iter);
      }
    }
  }
}

/// \brief Removes the edges in the Delaunay triangulation that share a point
/// with the super triangle.
/// \param[in] del_edges Delaunay triangulation with super triangle around it.
/// \param[in] super_triangle Known super triangle.
inline void RemoveSuperVertices(std::vector<Edge>& del_edges,
                                const Triangle& super_triangle) {
  const auto st_vertices = super_triangle.GetPoints();
  auto iter = del_edges.begin();
  while (iter != del_edges.end()) {
    iter = std::find_if(
        del_edges.begin(), del_edges.end(), [st_vertices](const Edge& edge) {
          const auto get_start = edge.GetStart();
          const auto get_end = edge.GetEnd();
          return get_start == st_vertices.at(0) or
                 get_end == st_vertices.at(0) or
                 get_start == st_vertices.at(1) or
                 get_end == st_vertices.at(1) or
                 get_start == st_vertices.at(2) or get_end == st_vertices.at(2);
        });
    if (iter != del_edges.end()) {
      del_edges.erase(iter);
    }
  }
}

/// \brief Removes the duplicated edges.
/// \param edges Edges.
/// \return What's left.
inline std::vector<Edge> GetNonDuplicates(const std::vector<Edge>& edges) {
  std::vector<Edge> non_duplicates;

  for (const auto& e1 : edges) {
    auto iter = std::find_if(non_duplicates.begin(), non_duplicates.end(),
                             [e1](const Edge& e2) { return e1 == e2; });
    if (iter == non_duplicates.end()) {
      non_duplicates.emplace_back(e1);
    }
  }
  return non_duplicates;
}

}  // namespace

// Delaunay triangulation using the Bowyer–Watson algorithm
// https://en.wikipedia.org/wiki/Bowyer–Watson_algorithm

std::vector<Edge> Grid::DelaunayTriangulation() const {
  if (points_.size() < kMinDelaunayTriangulationPoints) {
    return {};
  }
  const auto super_triangle = MinEnclosingCircle().EnclosingTriangle();
  std::vector<Triangle> triangulation{super_triangle};

  for (const auto& pt : points_) {
    std::vector<Triangle> bad_triangles;

    for (const auto& triangle : triangulation) {
      if (triangle.CircumCircle().IsInside(pt)) {
        bad_triangles.emplace_back(triangle);
      }
    }
    // Get only edges that are not shared with any other bad triangle.
    const auto polygon = GetNonSharingEdges(bad_triangles);
    // Remove triangles in bad_triangles from triangulation
    RemoveEqualTriangles(triangulation, bad_triangles);
    // Make an ew triangle of edge and pt and put in triangulation.
    for (const auto& edge : polygon) {
      triangulation.emplace_back(pt, edge.GetStart(), edge.GetEnd());
    }
  }
  auto del_edges = TrianglesToEdges(triangulation);
  RemoveSuperVertices(del_edges, super_triangle);
  return GetNonDuplicates(del_edges);
}

}  // namespace algo::geometry
