///
/// \brief Data structures for geometry algorithms.
/// \author alex011235
/// \date 2021-02-07
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_geometry.hpp"

#include <cmath>
#include <utility>

namespace {

const auto x_comp = [](auto p1, auto p2) { return p1.X() < p2.X(); };
const auto y_comp = [](auto p1, auto p2) { return p1.Y() < p2.Y(); };

}// namespace

namespace algo::geometry {

// /////////////////////////////
// MARK: Point

Point::Point(double x, double y) : x_{x}, y_{y}
{}

void Point::Set(double x, double y)
{
  x_ = x;
  y_ = y;
}

bool Point::operator==(const Point& p) const
{
  return x_ == p.x_ && y_ == p.y_;
}

bool Point::operator!=(const Point& p) const
{
  return x_ != p.x_ || y_ != p.y_;
}
Point Point::operator-(const Point& p) const
{
  return Point{x_ - p.x_, y_ - p.y_};
}

Point Point::operator+(const Point& p) const
{
  return Point{x_ + p.x_, y_ + p.y_};
}

double Point::Dist(const Point& point) const
{
  return std::sqrt(std::pow(x_ - point.x_, 2) + std::pow(y_ - point.y_, 2));
}

Point Point::Normalize() const
{
  const auto magnitude = std::sqrt(x_ * x_ + y_ * y_);
  return Point{x_ / magnitude, y_ / magnitude};
}

double Point::X() const
{
  return x_;
}

double Point::Y() const
{
  return y_;
}

// /////////////////////////////
// MARK: Edge

Edge::Edge(const Point& pt1, const Point& pt2) : pt1_{pt1}, pt2_{pt2}
{
  if (pt1 == pt2) {
    throw std::invalid_argument("Points cannot be equal.");
  }
}

bool Edge::operator==(const Edge& e) const
{
  return ((pt1_ == e.pt1_) && (pt2_ == e.pt2_))
      || ((pt2_ == e.pt1_) && (pt1_ == e.pt2_));
}

namespace {

// Edge intersection
// http://jeffe.cs.illinois.edu/teaching/373/notes/x06-sweepline.pdf

constexpr auto CCW = [](const Point& p1, const Point& p2, const Point& p3) {
  return ((p3.Y() - p1.Y()) * (p2.X() - p1.X()))
      >= ((p2.Y() - p1.Y()) * (p3.X() - p1.X()));
};

}// namespace

bool Edge::Intersect(const Edge& edge) const
{
  auto p1 = pt1_;
  auto p2 = pt2_;
  auto p3 = edge.pt1_;
  auto p4 = edge.pt2_;

  bool a = (CCW(p1, p3, p4) != CCW(p2, p3, p4))
      && (CCW(p1, p2, p3) != CCW(p1, p2, p4));

  // Degeneracy, if two points are equal, they should not count as intersection
  auto b = p1 != p3;
  auto c = p1 != p4;
  auto d = p2 != p3;
  auto e = p2 != p4;
  auto f = p1 != p3;
  auto g = p3 != p4;

  return a && b && c && d && e && f && g;
}

double Edge::Dist(const Point& pt) const
{
  auto pt_max = pt2_;
  if (pt1_.X() > pt_max.X()) pt_max = pt1_;
  auto pt_min = pt1_;
  if (pt2_.X() < pt_min.X()) pt_min = pt2_;

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
  const auto x1 = pt1_.X();
  const auto x2 = pt2_.X();
  const auto y1 = pt1_.Y();
  const auto y2 = pt2_.Y();
  const auto A = 1;
  const auto B = (y1 - y2) / (x2 - x1);
  const auto C = x1 * (y2 - y1) / (x2 - x1) - y1;
  return std::abs(A * pt.X() + B * pt.Y() + C) / std::sqrt(A * A + B * B);
}

Point Edge::GetStart() const
{
  return pt1_;
}

Point Edge::GetEnd() const
{
  return pt2_;
}

int Edge::Location(const Point& pt) const
{
  auto temp = (pt2_.X() - pt1_.X()) * (pt.Y() - pt1_.Y())
      - (pt2_.Y() - pt1_.Y()) * (pt.X() - pt1_.X());
  return temp > 0 ? 1 : -1;
}

// /////////////////////////////
// MARK: Circle

Circle::Circle(const Point& point, double radius)
    : origin_{point},
      radius_{radius}
{}

double Circle::Area() const
{
  return radius_ * radius_ * M_PI;
}

bool Circle::IsInside(const Point& pt) const
{
  return origin_.Dist(pt) <= radius_;
}

Point Circle::Origin() const
{
  return origin_;
}

double Circle::Radius() const
{
  return radius_;
}

// /////////////////////////////
// MARK: Polygon

namespace {

/// \brief Calculates the center point of the points in pts.
constexpr auto CalcCenter = [](const std::vector<Point>& pts) {
  double x_sum{0.0};
  double y_sum{0.0};
  auto n = static_cast<double>(pts.size());
  for (const auto& pt : pts) {
    x_sum += pt.X();
    y_sum += pt.Y();
  }
  return Point{x_sum / n, y_sum / n};
};

}// namespace

Polygon::Polygon(const std::vector<Point>& points)
    : points_{points},
      center_{CalcCenter(points)} {};

size_t Polygon::EdgeCount()
{
  return points_.size() <= 2 ? (points_.size() - 1) : points_.size();
}

double Polygon::Area() const
{
  return 0.0;
}

Polygon Polygon::Rotate(double angle, const Point& center) const
{
  auto points = points_;

  for (auto& pt : points) {
    auto x = pt.X() - center.X();
    auto y = pt.Y() - center.Y();
    const auto tx = x;
    const auto sin_of_angle = std::sin(angle);
    const auto cos_of_angle = std::cos(angle);

    x = x * cos_of_angle - y * sin_of_angle;
    y = tx * sin_of_angle + y * cos_of_angle;
    x += center.X();
    y += center.Y();
    pt.Set(x, y);
  }
  return Polygon{points};
}

Polygon Polygon::Rotate(double angle) const
{
  return Rotate(angle, center_);
}

Point Polygon::GetCenter() const
{
  return center_;
}

Rectangle Polygon::BoundingRectangle() const
{
  auto x_min = std::numeric_limits<double>::max();
  auto y_min = std::numeric_limits<double>::max();
  double x_max{0.0};
  double y_max{0.0};

  // Find minimum a maximum values of coordinates.
  for (const Point& pt : points_) {
    if (pt.X() > x_max) x_max = pt.X();
    if (pt.Y() > y_max) y_max = pt.Y();
    if (pt.X() < x_min) x_min = pt.X();
    if (pt.Y() < y_min) y_min = pt.Y();
  }

  return Rectangle{{x_min, y_min}, x_max - x_min, y_max - y_min};
}

std::vector<Point> Polygon::GetPoints() const
{
  return points_;
}

Point Polygon::GetEdge(size_t i) const
{
  const auto index_next{(i + 1) % points_.size()};
  const auto pt1 = points_.at(i);
  const auto pt2 = points_.at(index_next);
  return pt2 - pt1;
}

// /////////////////////////////
// MARK: Triangle

Triangle::Triangle(const Point& pt1, const Point& pt2, const Point& pt3)
    : Polygon({pt1, pt2, pt3}),
      pt1_{points_.at(0)},
      pt2_{points_.at(1)},
      pt3_{points_.at(2)}
{
  if ((pt1_ == pt2_) || (pt2_ == pt3_) || (pt1_ == pt3_)) {
    throw std::invalid_argument("Two points may not be equal.");
  }
}

double Triangle::Area() const
{
  return std::abs((pt1_.X() * (pt2_.Y() - pt3_.Y())
                   + pt2_.X() * (pt3_.Y() - pt1_.Y())
                   + pt3_.X() * (pt1_.Y() - pt2_.Y()))
                  / 2.0);
}

bool Triangle::IsInside(const Point& pt) const
{
  if ((pt == pt1_) || (pt == pt2_) || (pt == pt3_)) {
    // pt is a corner point -> "inside" ?
    return true;
  }
  const auto area = Area();
  const auto area1 = Triangle(pt, pt2_, pt3_).Area();
  const auto area2 = Triangle(pt1_, pt, pt3_).Area();
  const auto area3 = Triangle(pt1_, pt2_, pt).Area();
  return area == (area1 + area2 + area3);
}

namespace {

auto angle = [](auto pt3, auto pt1, auto pt2) {
  return atan2(pt3.Y() - pt1.Y(), pt3.X() - pt1.X())
      - atan2(pt2.Y() - pt1.Y(), pt2.X() - pt1.X());
};

}

Circle Triangle::CircumCircle() const
{
  const auto x1 = pt1_.X();
  const auto y1 = pt1_.Y();
  const auto x2 = pt2_.X();
  const auto y2 = pt2_.Y();
  const auto x3 = pt3_.X();
  const auto y3 = pt3_.Y();

  const auto A = angle(pt3_, pt1_, pt2_);// P1
  const auto B = angle(pt1_, pt2_, pt3_);// P2
  const auto C = angle(pt2_, pt3_, pt1_);// P3

  const auto Ox = (x1 * sin(2 * A) + x2 * sin(2 * B) + x3 * sin(2 * C))
      / (sin(2 * A) + sin(2 * B) + sin(2 * C));
  const auto Oy = (y1 * sin(2 * A) + y2 * sin(2 * B) + y3 * sin(2 * C))
      / (sin(2 * A) + sin(2 * B) + sin(2 * C));

  const Point cc{Ox, Oy};
  const auto radius = cc.Dist(pt1_);

  return Circle{cc, radius};
}

// /////////////////////////////
// MARK: Rhombus

Rhombus::Rhombus(const Point& pt1, const Point& pt2, const Point& pt3,
                 const Point& pt4)
    : Polygon({pt1, pt2, pt3, pt4}),
      pt_a_{points_.at(0)},
      pt_b_{points_.at(1)},
      pt_c_{points_.at(2)},
      pt_d_{points_.at(3)}
{
  //  const auto ab = pt_a_.Dist(pt_b_);
  //  const auto bc = pt_b_.Dist(pt_c_);
  //  const auto cd = pt_c_.Dist(pt_d_);
  //  const auto da = pt_d_.Dist(pt_a_);
  //  if ((ab != bc) || (bc != cd) || (cd != da) || (da != ab)) {
  //    throw std::invalid_argument("Side lengths must be equal in a rhombus.");
  //  }
}

Rhombus::Rhombus(const std::vector<Point>& pts)
    : Rhombus(pts.at(0), pts.at(1), pts.at(2), pts.at(3))
{}

double Rhombus::Area() const
{
  const auto d1 = pt_b_.Dist(pt_d_);
  const auto d2 = pt_a_.Dist(pt_c_);
  return 0.5 * d1 * d2;
}

// /////////////////////////////
// MARK: Rectangle

Rectangle::Rectangle(const Point& pt1, double width, double height)
    : Polygon({pt1, Point{pt1.X() + width, pt1.Y()},
               Point{pt1.X() + width, pt1.Y() + height},
               Point{pt1.X(), pt1.Y() + height}}),
      pt_{points_.at(0)},
      width_{width},
      height_{height}
{}

double Rectangle::Area() const
{
  return std::abs(width_ * height_);
}

Point Rectangle::GetPoint() const
{
  return pt_;
}

double Rectangle::GetWidth() const
{
  return width_;
}

double Rectangle::GetHeight() const
{
  return height_;
}

// /////////////////////////////
// MARK: Grid

Grid::Grid(const std::vector<Point>& points) : points_{points}
{}

// /////////////////////////////
// MARK: Closest pair of points

namespace {

/// \brief Returns the closes pair of points, brute force. Only to be used on a very small set of points.
/// \param xp Input points.
/// \param yp Input points.
/// \return Closest pair of points.
std::pair<double, std::vector<Point>> ClosestPairBF(
    const std::vector<Point>& xp, const std::vector<Point>& yp)
{
  auto min_dist = std::numeric_limits<double>::max();
  Point xp_min{0.0, 0.0};
  Point yp_min{0.0, 0.0};

  for (const auto& px : xp) {
    for (const auto& py : yp) {

      if (!(px.X() == py.X() && px.Y() == py.Y())) {
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
std::pair<double, std::vector<Point>> ClosestPair(const std::vector<Point>& xp,
                                                  const std::vector<Point>& yp)
{
  auto N = static_cast<int>(xp.size());

  // Brute force if size <= 3
  if (N <= 3) return ClosestPairBF(xp, yp);

  std::vector<Point> x_left;
  std::vector<Point> x_right;
  std::vector<Point> y_left;
  std::vector<Point> y_right;

  std::copy(xp.begin(), xp.begin() + (N / 2), std::back_inserter(x_left));
  std::copy(xp.begin() + (N / 2), xp.end(), std::back_inserter(x_right));
  // Mid point on x-axis
  auto mid_x_pt = xp.at(N / 2);

  std::copy_if(yp.begin(), yp.end(), std::back_inserter(y_left),
               [&mid_x_pt](auto pt) { return pt.X() <= mid_x_pt.X(); });

  std::copy_if(yp.begin(), yp.end(), std::back_inserter(y_right),
               [&mid_x_pt](auto pt) { return pt.X() > mid_x_pt.X(); });

  // Recursive calls
  auto cL = ClosestPair(x_left, y_left);
  auto cR = ClosestPair(x_right, y_right);

  auto p_min = cL.first < cR.first ? cL.second : cR.second;
  auto dist_min = cL.first < cR.first ? cL.first : cR.first;

  std::vector<Point> ys;
  std::copy_if(xp.begin(), xp.end(), std::back_inserter(ys),
               [&dist_min, &mid_x_pt](auto pt) {
                 return std::abs(mid_x_pt.X() - pt.X()) < dist_min;
               });

  auto closest_dist = dist_min;
  auto closest_pair = p_min;

  for (size_t i = 0; i < ys.size(); ++i) {
    size_t k = i + 1;

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

}// namespace

std::pair<Point, Point> Grid::ClosestPairOfPoints()
{
  auto ptsx = points_;
  auto ptsy = points_;
  std::sort(ptsx.begin(), ptsx.end(), x_comp);
  std::sort(ptsy.begin(), ptsy.end(), y_comp);

  auto closest = ClosestPair(ptsx, ptsy);
  auto p1 = closest.second.front();
  auto p2 = closest.second.back();
  return std::make_pair(p1, p2);
}

// /////////////////////////////
// MARK: ConvexHull

namespace {

/// \brief Determines the distance between a point p and the line ln.
/// \param ln The line.
/// \param p The point.
/// \return Distance.
constexpr auto LDistance = [](const Edge& ln, const Point& p) {
  auto abx = ln.GetEnd().X() - ln.GetStart().X();
  auto aby = ln.GetEnd().Y() - ln.GetStart().Y();
  auto dist =
      abx * (ln.GetStart().Y() - p.Y()) - aby * (ln.GetStart().X() - p.X());
  return dist < 0 ? -1.0 * dist : dist;
};

int MaxEdgeDistanceIndex(const std::vector<Point>& pts, const Edge& edge)
{
  int ci{0};
  int k{0};
  double max_dist{0.0};

  for (const auto& p : pts) {
    auto curr_dist = LDistance(edge, p);
    if (curr_dist > max_dist) {
      max_dist = curr_dist;
      ci = k;
    }
    ++k;
  }
  return ci;
}

/// \brief Subroutine of Quickhull. Not to be accessible from outside of this file. Use ConvexHull.
void QuickHull(const Point& a, const Point& b, std::vector<Point>& pts,
               std::vector<Point>& conv_hull_pts)
{
  if (pts.empty()) return;

  if (pts.size() == 1) {
    conv_hull_pts.emplace_back(pts.front());
    pts.erase(pts.begin());
    return;
  }

  const auto max_edge_index = MaxEdgeDistanceIndex(pts, Edge{a, b});
  const auto point_at_max_index = pts.at(max_edge_index);

  conv_hull_pts.push_back(point_at_max_index);
  pts.erase(pts.begin() + max_edge_index);

  std::vector<Point> pts_a;
  std::vector<Point> pts_b;

  const Edge edge1{a, point_at_max_index};
  const Edge edge2{point_at_max_index, b};

  for (const auto& p : pts) {
    // Checking which side of edge p is.
    if (edge1.Location(p) == 1) pts_a.emplace_back(p);
    if (edge2.Location(p) == 1) pts_b.emplace_back(p);
  }

  // Recursive calls
  QuickHull(a, point_at_max_index, pts_a, conv_hull_pts);
  QuickHull(point_at_max_index, b, pts_b, conv_hull_pts);
}

}// namespace

Polygon Grid::ConvexHull()
{
  if (points_.size() < 3) return Polygon{Points{}};

  auto pts = points_;

  std::sort(pts.begin(), pts.end(), x_comp);

  // b and a with min and max x-coordinates respectively
  auto b = pts.front();
  auto a = pts.back();
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
  QuickHull(a, b, right, pts_ch);
  QuickHull(b, a, left, pts_ch);

  std::sort(pts_ch.begin(), pts_ch.end(), x_comp);
  return Polygon{pts_ch};
}

// /////////////////////////////
// MARK: MinBoundingBox

namespace {

/// Minimum bounding box, rotating calipers
/// https://github.com/Glissando/Rotating-Calipers

std::vector<Polygon> RotatingCalipers(Polygon convex_hull_pts)
{
  std::vector<Polygon> polygons;

  for (size_t i = 0; i < convex_hull_pts.EdgeCount(); i++) {
    auto edge = convex_hull_pts.GetEdge(i);
    auto angle1 = std::acos(edge.Normalize().Y());
    auto polygon1 = convex_hull_pts.Rotate(angle1);
    auto box = polygon1.BoundingRectangle();
    polygon1 = polygon1.Rotate(-angle1);
    auto center = polygon1.GetCenter();
    Polygon pg{box.GetPoints()};
    polygons.emplace_back(pg.Rotate(-angle1, center));
  }

  return polygons;
}

Polygon GetMinBox(const std::vector<Polygon>& polygons)
{

  auto iter = std::min_element(polygons.begin(), polygons.end(),
                               [](const auto& polygon1, const auto& polygon2) {
                                 const auto pts1 = polygon1.GetPoints();
                                 const Rhombus rhombus1{pts1};
                                 const auto pts2 = polygon2.GetPoints();
                                 const Rhombus rhombus2{pts2};
                                 return rhombus1.Area() < rhombus2.Area();
                               });
  return *iter;
}

}// namespace

Polygon Grid::MinBoundingBox()
{
  // The only other constraint is if all points are on the same line.
  if (points_.size() < 3) return Polygon{Points{}};

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
Circle CircleOf3(const Point& p1, const Point& p2, const Point& p3)
{
  const auto bx = p2.X() - p1.X();
  const auto by = p2.Y() - p1.Y();
  const auto cx = p3.X() - p1.X();
  const auto cy = p3.Y() - p1.Y();
  const auto b = bx * bx + by * by;
  const auto c = cx * cx + cy * cy;
  const auto d = bx * cy - by * cx;

  const auto mid_x = p1.X() + (cy * b - by * c) / (2.0 * d);
  const auto mid_y = p1.Y() + (bx * c - cx * b) / (2.0 * d);
  const Point center{mid_x, mid_y};
  const auto radius = center.Dist(p1);

  return {center, radius};
}

/// \brief Returns a circle out of either 1, 2 or 3 points.
/// \param pts Given points, |points| ≤ 3.
/// \return A circle.
Circle TrivialCircumcircle(std::vector<Point> pts)
{
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
    const auto diameter = p1.Dist(p2);
    return Circle{mid, diameter / 2.0};
  }
  // Last case, three points are on the circle
  return CircleOf3(pts.at(0), pts.at(1), pts.at(2));
}

/// \brief Runs the Welzl step of the minimum enclosing circle step.
/// \param pts Points to construct a circle around.
/// \param r Input plane.
/// \return A circle around the points in pts.
Circle Welzl(std::vector<Point> pts, std::vector<Point> r)
{
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

}// namespace

Circle Grid::MinEnclosingCircle() const
{
  std::vector<Point> r;
  return Welzl(points_, r);
}

// /////////////////////////////
// MARK: Triangulate

namespace {

/// \brief Sorts the input points lexicographically,
/// \param pts The input points.
void LexSortPoints(std::vector<Point>& pts)
{
  auto x = pts.front().X();
  std::vector<Point> pts2;
  std::vector<Point> pts_res;

  for (auto& pt : pts) {
    if (pt.X() != x) {
      std::sort(pts2.begin(), pts2.end(), x_comp);
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

}//namespace

std::vector<Edge> Grid::Triangulate() const
{
  auto pts = points_;
  LexSortPoints(pts);

  std::vector<Point> visited{pts.at(0), pts.at(1), pts.at(2)};
  bool intersection{false};

  // The three first points constructs a triangle.
  Edge l0{pts.at(0), pts.at(1)};
  Edge l1{pts.at(0), pts.at(2)};
  Edge l2{pts.at(1), pts.at(2)};
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
          break;// when something intersects
        }
      }

      if (!intersection) {
        Edge line{pt0, *pi};
        lines.emplace_back(line);
      }
      intersection = false;
    }
    visited.emplace_back(pt0);
  }

  return lines;
}

}// namespace algo::geometry
