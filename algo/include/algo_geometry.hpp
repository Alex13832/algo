///
/// \brief Source file for geometry algorithms.
/// \author alex011235
/// \date 2020-04-27
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
/// Change list:
/// 2015-06-04 Triangulation of 2D-points
/// 2015-06-25 Quickhull, convex hull of 2D-points
/// 2015-06-28 Closest pair of 2D-points
/// 2021-02-06 Rotating calipers
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

  bool operator==(const Line& e) const
  {
    Point p_1 = e.a, p_2 = e.b;
    return (p_1 == a) && (p_2 == b);
  }
};

using Points = std::vector<Point>;
using Lines = std::vector<Line>;

struct Polygon {
  Points pts;

  /// \brief Makes a polygon of a set of points with convex hull.
  /// \param points The points to extract a polygon from.
  void MakePolygonWithConvexHull(const Points& points);

  /// \brief Returns the number of edges in the polygon.
  /// \return The number of edges in the polygon.
  size_t NbrEdges();
};

struct Rectangle {
  Points pts;

  /// \brief Makes a bounding rectangle of the points in the input polygon.
  /// \note This is not the minimum bounding box.
  /// \param polygon The points in this to construct a polygon.
  void BoundingRectangle(const Polygon& polygon);
};

// //////////////////////////////////////////
//  Closest pair of points
// //////////////////////////////////////////

/// \brief Returns the closest pair of points from a set of input 2D-points.
/// \param points Input points.
/// \return The two points that are closest to each other.
/// \link <a href="https://en.wikipedia.org/wiki/Closest_pair_of_points_problem">Closest pair of points, Wikipedia.</a>
Points ClosestPairOfPoints(const Points& points);

// //////////////////////////////////////////
//  Quickhull
// //////////////////////////////////////////

/// \brief Returns the convex hull of the input 2D-points. This implementation uses the Quickhull algorithm.
/// \param points Input points.
/// \return The convex hull of points.
/// \link <a href="https://en.wikipedia.org/wiki/Quickhull">Quickhull, Wikipedia.</a>
/// \link <a href="https://en.wikipedia.org/wiki/Convex_hull">Convex hull, Wikipedia.</a>
Points ConvexHull(Points points);

// //////////////////////////////////////////
//  Rotating calipers
// //////////////////////////////////////////

// TODO: Add functions for rotating calipers and minimum bounding box.

// //////////////////////////////////////////
//  Triangulation of points
// //////////////////////////////////////////

/// \brief Computes the triangulation of a set of input 2D-points.
/// \param pts The input points.
/// \return The triangulation as a set of lines.
Lines Triangulate(Points& pts);

}// namespace algo::geometry

#endif//ALGORITHM_GEOMETRY_GEOMETRY_ALGORITHMS_HPP_
