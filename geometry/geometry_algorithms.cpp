///
/// \brief Source file for geometry algorithms.
/// \author alex011235
/// \date 2020-04-27
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "geometry_algorithms.hpp"

namespace algo::geometry {

namespace {
constexpr double kDblMin{2.2250738585072014e-308};
}

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
int Location(Line ln, Point p)
{
  double temp{(ln.b.x - ln.a.x) * (p.y - ln.a.y) - (ln.b.y - ln.a.y) * (p.x - ln.a.x)};
  if (temp > 0) {
    return 1;
  }
  return -1;
}

/// \brief Determines the distance between a point p and the line ln.
/// \param ln The line.
/// \param p The point.
/// \return Distance.
double Distance(Line ln, Point p)
{
  double abx{ln.b.x - ln.a.x};
  double aby{ln.b.y - ln.a.y};
  double dist{abx * (ln.a.y - p.y) - aby * (ln.a.x - p.x)};
  if (dist < 0) {
    return -1.0 * dist;
  }
  return dist;
}

/////////////////////////////////////////////
/// Quickhull
/////////////////////////////////////////////

/// \brief Soubroutine of Quickhull. Not to be accessible from outside of this file. Use ConvexHull.
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
      double curr_dist{Distance(Line{a, b}, p)};
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

}// namespace algo::geometry
