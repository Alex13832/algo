///
/// \brief Source file for geometry algorithms.
/// \author alex011235
/// \date 2020-04-27
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_geometry.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

namespace algo::geometry {

namespace {
constexpr double kDblMin{2.2250738585072014e-308};
constexpr double kDblMax{1.79769e+308};

// For sorting on x-priority.
struct x_comp {
  bool operator()(const Point p1, const Point p2) const
  {
    return p1.x < p2.x;
  }
};

// For sorting on y-priority.
struct y_comp {
  bool operator()(const Point p1, const Point p2) const
  {
    return p1.y < p2.y;
  }
};

/// \brief Determines which side of a line a point is located.
/// \param ln The line.
/// \param p The point.
/// \return 1 if above/right, -1 below/left.
constexpr auto Location = [](const Edge& ln, const Point& pt) {
  double temp{(ln.b.x - ln.a.x) * (pt.y - ln.a.y) - (ln.b.y - ln.a.y) * (pt.x - ln.a.x)};
  if (temp > 0) {
    return 1;
  }
  return -1;
};

/// \brief Determines the distance between a point p and the line ln.
/// \param ln The line.
/// \param p The point.
/// \return Distance.
constexpr auto LDistance = [](const Edge& ln, const Point& p) {
  double abx{ln.b.x - ln.a.x};
  double aby{ln.b.y - ln.a.y};
  double dist{abx * (ln.a.y - p.y) - aby * (ln.a.x - p.x)};
  if (dist < 0) {
    return -1.0 * dist;
  }
  return dist;
};

/// \brief Returns the distance between two points.
/// \param p1 Point 1.
/// \param p2 Point 2.
/// \return The distance between p1 and p2.
constexpr auto PDistance = [](const Point& p1, const Point& p2) {
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
};

///\brief Checks if the given point p is inside the circle.
constexpr auto InsideCircle = [](const Circle& circle, const Point& p) {
  return PDistance(circle.center, p) <= circle.radius;
};

///\brief Computes the area of the four points in pts.
constexpr auto AreaPolyRect = [](const Points& pts) {
  Point p1 = pts.at(0);
  Point p2 = pts.at(1);
  Point p3 = pts.at(2);
  Point p4 = pts.at(3);

  double sum = p1.x * p2.y - p1.y * p2.x + p2.x * p3.y - p2.y * p3.x + p3.x * p4.y - p4.y * p3.x + p4.x * p1.y - p4.x * p1.x;
  return std::abs(sum / 2.0);
};

}// namespace

/////////////////////////////////////////////
/// Quickhull
/////////////////////////////////////////////

/// \brief Subroutine of Quickhull. Not to be accessible from outside of this file. Use ConvexHull.
/// This is the divide and conquer step in Quickhull.
/// \param a Point.
/// \param b Point.
/// \param pts Points.
/// \param pts_ch Output.
void QuickHull(Point a, Point b, Points& pts, Points& pts_ch)
{
  if (pts.empty()) {
    return;
  } else if (pts.size() == 1) {
    pts_ch.emplace_back(pts[0]);
    pts.erase(pts.begin());
    return;
  } else {

    // Determine max-distance from line
    Point c{};
    int ci{0}, k{0};
    double max_dist{kDblMin};

    for (auto p : pts) {
      double curr_dist{LDistance(Edge{a, b}, p)};
      if (curr_dist > max_dist) {
        max_dist = curr_dist;
        c = p;
        ci = k;
      }
      ++k;
    }

    pts_ch.push_back(c);
    pts.erase(pts.begin() + ci);

    Points A, B;
    std::for_each(pts.begin(), pts.end(), [&](Point p) {
      if (Location(Edge{a, c}, p) == 1) A.emplace_back(p);
      if (Location(Edge{c, b}, p) == 1) B.emplace_back(p);
    });

    // Recursive calls
    QuickHull(a, c, A, pts_ch);
    QuickHull(c, b, B, pts_ch);
  }
}

Polygon ConvexHull(Points points)
{
  if (points.empty()) {
    return Polygon{points};
  }
  if (points.size() < 3) {
    // Too few points.
    return Polygon{Points{}};
  }
  std::sort(points.begin(), points.end(), x_comp());
  // b and a with min and max x-coordinates respectively
  Point b{points[0]};
  Point a{points[points.size() - 1]};
  Points pts_ch;
  pts_ch.emplace_back(a);
  pts_ch.emplace_back(b);
  points.erase(points.begin());
  points.erase(points.end() - 1);

  Points left, right;

  // Determine which side of line (a,b)
  std::for_each(points.begin(), points.end(), [&](Point p) {
    Location(Edge{a, b}, p) == -1 ? left.emplace_back(p) : right.emplace_back(p);
  });

  // Call qhull with two sets
  QuickHull(a, b, right, pts_ch);
  QuickHull(b, a, left, pts_ch);

  std::sort(pts_ch.begin(), pts_ch.end(), x_comp());
  return Polygon{pts_ch};
}

/////////////////////////////////////////////
/// Closest pair of points
/////////////////////////////////////////////

/// \brief Returns the closes pair of points, brute force. Only to be used on a very small set of points.
/// \param xp Input points.
/// \param yp Input points.
/// \return Closest pair of points.
std::pair<double, Points> ClosestPairBF(const Points& xp, const Points& yp)
{
  double min_dist{kDblMax};
  Point xp_min{}, yp_min{};

  for (auto px : xp) {
    for (auto py : yp) {

      if (!(px.x == py.x && px.y == py.y)) {
        if (PDistance(px, py) < min_dist) {
          min_dist = PDistance(px, py);
          xp_min = px;
          yp_min = py;
        }
      }
    }
  }

  return std::make_pair(min_dist, Points{xp_min, yp_min});
}

/// \brief Divide and conquer algorithm to find the closest pair of points.
/// \param xp Set of points.
/// \param yp Set of points.
/// \return The min distance and the two closest points.
std::pair<double, Points> ClosestPair(const Points& xp, const Points& yp)
{
  int N = xp.size();

  // Brute force if size <= 3
  if (N <= 3) { return ClosestPairBF(xp, yp); }

  Points xL, xR, yL, yR;
  std::copy(xp.begin(), xp.begin() + (N / 2), std::back_inserter(xL));
  std::copy(xp.begin() + (N / 2), xp.end(), std::back_inserter(xR));
  // Mid point on x-axis
  Point xmid{xp.at(N / 2)};

  std::copy_if(yp.begin(), yp.end(), std::back_inserter(yL), [&xmid](Point p) {
    return p.x <= xmid.x;
  });

  std::copy_if(yp.begin(), yp.end(), std::back_inserter(yR), [&xmid](Point p) {
    return p.x > xmid.x;
  });

  // Recursive calls
  std::pair<double, Points> cL{ClosestPair(xL, yL)};
  std::pair<double, Points> cR{ClosestPair(xR, yR)};

  Points p_min{cL.first < cR.first ? cL.second : cR.second};
  double dist_min{cL.first < cR.first ? cL.first : cR.first};

  Points ys;
  std::copy_if(xp.begin(), xp.end(), std::back_inserter(ys), [&dist_min, &xmid](Point p) {
    return std::abs(xmid.x - p.x) < dist_min;
  });

  double closest_dist{dist_min};
  Points closest_pair{p_min};

  for (size_t i = 0; i < ys.size(); ++i) {
    size_t k = i + 1;

    while (k < ys.size() && ((ys[k].y - ys[i].y) < dist_min)) {
      if (PDistance(ys[k], ys[i]) < closest_dist) {
        closest_dist = PDistance(ys[k], ys[i]);
        closest_pair = {ys[k], ys[i]};
      }
      k++;
    }
  }

  return std::make_pair(closest_dist, closest_pair);
}

Points ClosestPairOfPoints(const Points& points)
{
  Points ptsx{points};
  Points ptsy{points};
  std::sort(ptsx.begin(), ptsx.end(), x_comp());
  std::sort(ptsy.begin(), ptsy.end(), y_comp());

  std::pair<double, Points> closest{ClosestPair(ptsx, ptsy)};
  return closest.second;
}

/////////////////////////////////////////////
/// Minimum bounding box, rotating calipers
/// https://github.com/Glissando/Rotating-Calipers
/////////////////////////////////////////////

Polygon MinimumBoundingBox(const Points& points)
{
  if (points.size() < 3) {
    // The only other constraint is if all points are on the same line.
    return Polygon{Points{}};
  }

  Polygon polygon{ConvexHull(points)};
  std::vector<Polygon> polygons;

  // Rotating calipers step
  for (size_t i = 0; i < polygon.EdgeCount(); i++) {
    Point edge{polygon.GetEdge(i)};
    const double angle{std::acos(edge.Normalize().y)};
    Polygon polygon1{polygon.Rotate(angle)};
    Rectangle box{polygon1.BoundingRectangle()};
    polygon1 = polygon1.Rotate(-angle);
    Point center{polygon1.GetCenter()};
    polygons.emplace_back(box.GetPolygon().Rotate(-angle, center));
  }
  double min_area{kDblMax};
  Polygon min_bbox{{}};

  // Get minimal enclosing rectangle
  for (Polygon poly : polygons) {
    if (AreaPolyRect(poly.GetPoints()) < min_area) {
      min_area = AreaPolyRect(poly.GetPoints());
      min_bbox = poly;
    }
  }
  return min_bbox;
}

/////////////////////////////////////////////
/// Minimum bounding circle
/////////////////////////////////////////////

/// \brief Makes a circle out of the the given points located on the radius.
/// \param p1 Point 1.
/// \param p2 Point 2.
/// \param p3 Point 3.
/// \return A circle of p1, p2, p3.
Circle CircleOf3(Point p1, Point p2, Point p3)
{
  const double bx{p2.x - p1.x};
  const double by{p2.y - p1.y};
  const double cx{p3.x - p1.x};
  const double cy{p3.y - p1.y};
  const double b{bx * bx + by * by};
  const double c{cx * cx + cy * cy};
  const double d{bx * cy - by * cx};

  Point center{Point{(cy * b - by * c) / (2.0 * d), (bx * c - cx * b) / (2.0 * d)}};
  center.x += p1.x;
  center.y += p1.y;
  const double radius{PDistance(center, p1)};
  return {center, radius};
}

/// \brief Returns a circle out of either 1, 2 or 3 points.
/// \param pts Given points, |points| ≤ 3.
/// \return A circle.
Circle TrivialCircumcircle(Points pts)
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
    Point p1 = pts.at(0);
    Point p2 = pts.at(1);
    const Point mid{(p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0};
    const double diameter{PDistance(p1, p2)};
    return Circle{mid, diameter / 2.0};
  }
  // Last case, three points are on the circle
  return CircleOf3(pts.at(0), pts.at(1), pts.at(2));
}

/// \brief Runs the Welzl step of the minimum enclosing circle step.
/// \param pts Points to construct a circle around.
/// \param r Input plane.
/// \return A circle around the points in pts.
Circle Welzl(Points pts, Points r)
{
  if (pts.empty() || r.size() == 3) {
    return TrivialCircumcircle(r);
  }
  size_t index = std::rand() % pts.size();
  Point p{pts.at(index)};
  pts.erase(pts.begin() + index);
  Circle circle{Welzl(pts, r)};

  if (InsideCircle(circle, p)) {
    return circle;
  }
  r.emplace_back(p);
  return Welzl(pts, r);
}

Circle MinimumEnclosingCircle(Points& pts)
{
  Points r;
  return Welzl(pts, r);
}

/////////////////////////////////////////////
/// Triangulation of points
/////////////////////////////////////////////

/// ------------------------------------------------------------------
/// Functions for determining if two line segments intersect.
/// Implemented according to
/// http://jeffe.cs.illinois.edu/teaching/373/notes/x06-sweepline.pdf
/// ------------------------------------------------------------------

namespace {

constexpr auto CCW = [](const Point& p1, const Point& p2, const Point& p3) {
  return ((p3.y - p1.y) * (p2.x - p1.x)) >= ((p2.y - p1.y) * (p3.x - p1.x));
};

constexpr auto SegmentIntersect = [](Point p1, Point p2, Point p3, Point p4) {
  bool a = (CCW(p1, p3, p4) != CCW(p2, p3, p4))
      && (CCW(p1, p2, p3) != CCW(p1, p2, p4));

  // Degeneracy, if two points are equal, they should not count as intersection
  bool b{p1 != p3};
  bool c{p1 != p4};
  bool d{p2 != p3};
  bool e{p2 != p4};
  bool f{p1 != p3};
  bool g{p3 != p4};

  return a && b && c && d && e && f && g;
};

/// \brief Sorts the input points lexicographically,
/// \param pts The input points.
void LexSortPoints(Points& pts)
{
  double x{pts[0].x};
  Points pts2;
  Points pts_res;

  for (auto& pt : pts) {
    if (pt.x != x) {
      std::sort(pts2.begin(), pts2.end(), y_comp());
      std::copy(pts2.begin(), pts2.end(), std::back_inserter(pts_res));
      pts2.clear();
      x = pt.x;
    }

    pts2.push_back(pt);
  }

  if (!pts2.empty()) {
    std::copy(pts2.begin(), pts2.end(), std::back_inserter(pts_res));
  }

  pts = pts_res;
}

}//namespace

Edges Triangulate(Points& pts)
{
  LexSortPoints(pts);

  Points visited{pts[0], pts[1], pts[2]};
  bool intersection{false};

  // The three first points constructs a triangle.
  Edge l0{pts[0], pts[1]};
  Edge l1{pts[0], pts[2]};
  Edge l2{pts[1], pts[2]};
  Edges lines{l0, l1, l2};

  // From this point add points to the only triangulate incrementally.
  for (size_t i = 3; i < pts.size(); ++i) {
    Point& p0{pts[i]};

    // Target point pi
    for (auto pi = visited.rbegin(); pi != visited.rend(); ++pi) {

      // Verify that the segment p0-pi doesn't intersect e
      for (auto e = lines.rbegin(); e != lines.rend(); ++e) {
        Point pk = e->a;
        Point pj = e->b;

        if (SegmentIntersect(p0, *pi, pj, pk)) {
          intersection = true;
          break;// as soon as something intersects
        }
      }

      if (!intersection) {
        Edge line{p0, *pi};
        lines.emplace_back(line);
      }
      intersection = false;
    }
    visited.emplace_back(p0);
  }

  return lines;
}

}// namespace algo::geometry
