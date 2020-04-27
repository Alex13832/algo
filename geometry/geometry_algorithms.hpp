///
/// \brief Source file for geometry algorithms.
/// \author alex011235
/// \date 2020-04-27
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2015-06-04: Triangulation of 2D-points.
/// 2015-06-25: Quickhull, convex hull of 2D-points.
/// 2015-06-28: Closest pair of 2D-points.
///

#ifndef ALGORITHM_GEOMETRY_GEOMETRY_ALGORITHMS_HPP_
#define ALGORITHM_GEOMETRY_GEOMETRY_ALGORITHMS_HPP_

#include <vector>

namespace algo::geometry {

struct Point {
  double x, y;

  bool operator==(const Point& p) const
  {
    return x == p.x && y == p.y;
  }

  bool operator!=(const Point& p) const
  {
    return x != p.x || y != p.y;
  }
};

struct Line {
  Point a, b;
};

using Points = std::vector<Point>;

/////////////////////////////////////////////
/// Quickhull
/////////////////////////////////////////////

/// \brief Returns the convex hull of the input 2D-points. This implementation uses the Quickhull algorithm.
/// \param points Input points.
/// \return The convex hull of points.
/// \link <a href="https://en.wikipedia.org/wiki/Quickhull">Quickhull, Wikipedia.</a>
/// \link <a href="https://en.wikipedia.org/wiki/Convex_hull">Convex hull, Wikipedia.</a>
Points ConvexHull(Points points);

}// namespace algo::geometry

#endif//ALGORITHM_GEOMETRY_GEOMETRY_ALGORITHMS_HPP_
