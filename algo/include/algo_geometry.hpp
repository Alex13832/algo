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
/// 2021-02-06 Rotating calipers, minimum bounding box.
///

#ifndef ALGORITHM_GEOMETRY_GEOMETRY_ALGORITHMS_HPP_
#define ALGORITHM_GEOMETRY_GEOMETRY_ALGORITHMS_HPP_

#include <cmath>
#include <utility>
#include <vector>

#include "algo_geometry_ds.hpp"

namespace algo::geometry {

/// \brief Returns the closest pair of points from a set of input 2D-points.
/// \param points Input points.
/// \return The two points that are closest to each other.
/// \link <a href="https://en.wikipedia.org/wiki/Closest_pair_of_points_problem">Closest pair of points, Wikipedia.</a>
Points ClosestPairOfPoints(const Points& points);

/// \brief Returns the convex hull of the input 2D-points. This implementation uses the Quickhull algorithm.
/// \param points Input points.
/// \return The convex hull of points.
/// \link <a href="https://en.wikipedia.org/wiki/Quickhull">Quickhull, Wikipedia.</a>
/// \link <a href="https://en.wikipedia.org/wiki/Convex_hull">Convex hull, Wikipedia.</a>
Polygon ConvexHull(Points points);

/// \brief Returns the arbitrarily oriented minimum rectangle around the input points.
/// \details No need to extract convex hull before this function.
/// \param points the input points to extract the minimum bbox from.
/// \return Minimum bounding box.
/// \link <a href="https://en.wikipedia.org/wiki/Rotating_calipers">Rotating calipers, Wikipedia.</a>
/// \link <a href="https://en.wikipedia.org/wiki/Minimum_bounding_box">Minimum bounding box, Wikipedia.</a>
Polygon MinimumBoundingBox(const Points& points);

/// \brief Computes the triangulation of a set of input 2D-points.
/// \param pts The input points.
/// \return The triangulation as a set of lines.
Edges Triangulate(Points& pts);

}// namespace algo::geometry

#endif//ALGORITHM_GEOMETRY_GEOMETRY_ALGORITHMS_HPP_
