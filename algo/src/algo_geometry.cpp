///
/// \brief Source file for geometry algorithms.
/// \author alex011235
/// \date 2020-04-27
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_geometry.hpp"

#include <algorithm>
#include <cmath>

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
constexpr auto Location = [](const Line& ln, const Point& pt) {
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
constexpr auto LDistance = [](const Line& ln, const Point& p) {
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
  return sqrt((double) pow(p1.x - p2.x, 2) + (double) pow(p1.y - p2.y, 2));
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
      double curr_dist{LDistance(Line{a, b}, p)};
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
      if (Location(Line{a, c}, p) == 1) A.emplace_back(p);
      if (Location(Line{c, b}, p) == 1) B.emplace_back(p);
    });

    // Recursive calls
    QuickHull(a, c, A, pts_ch);
    QuickHull(c, b, B, pts_ch);
  }
}

Points ConvexHull(Points points)
{
  if (points.empty()) {
    return points;
  }
  if (points.size() < 3) {
    // Too few points.
    return Points{};
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
    Location(Line{a, b}, p) == -1 ? left.emplace_back(p) : right.emplace_back(p);
  });

  // Call qhull with two sets
  QuickHull(a, b, right, pts_ch);
  QuickHull(b, a, left, pts_ch);

  std::sort(pts_ch.begin(), pts_ch.end(), x_comp());
  return pts_ch;
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
    return abs(xmid.x - p.x) < dist_min;
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

Lines Triangulate(Points& pts)
{
  LexSortPoints(pts);

  Points visited{pts[0], pts[1], pts[2]};
  bool intersection{false};

  // The three first points constructs a triangle.
  Line l0{pts[0], pts[1]};
  Line l1{pts[0], pts[2]};
  Line l2{pts[1], pts[2]};
  Lines lines{l0, l1, l2};

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
        Line line{p0, *pi};
        lines.emplace_back(line);
      }
      intersection = false;
    }
    visited.emplace_back(p0);
  }

  return lines;
}

}// namespace algo::geometry
