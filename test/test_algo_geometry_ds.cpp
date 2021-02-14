///
/// \brief Unit tests for geometry data structures.
/// \author alex011235
/// \date 2021-02-07
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>

#include "algo.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace algo::geometry;

/////////////////////////////////////////////
/// Point
/////////////////////////////////////////////

TEST(test_algo_geometry_ds, point_equals_operator)
{
  Point p1{1.0, 1.0};
  Point p2{1.0, 1.0};
  Point p3{1.0, 2.0};
  Point p4{2.0, 1.0};
  EXPECT_TRUE(p1 == p2);
  EXPECT_FALSE(p1 == p3);
  EXPECT_FALSE(p1 == p4);
}

TEST(test_algo_geometry_ds, points_not_equals_operator)
{
  Point p1{1.0, 1.0};
  Point p2{1.0, 1.0};
  Point p3{1.0, 2.0};
  Point p4{2.0, 1.0};
  EXPECT_TRUE(p1 != p3);
  EXPECT_TRUE(p1 != p4);
  EXPECT_FALSE(p1 != p2);
}

TEST(test_algo_geometry_ds, points_subtract_operator)
{
  Point p1{1.0, 1.0};
  Point p2{1.0, 1.0};
  Point p3{p1 - p2};
  EXPECT_EQ(p3.x, 0);
  EXPECT_EQ(p3.y, 0);
}

TEST(test_algo_geometry_ds, points_normalize)
{
  Point p{1.0, 1.0};
  Point pm{p.Normalize()};
  EXPECT_EQ(pm.x, 1.0 / std::sqrt(2));
  EXPECT_EQ(pm.y, 1.0 / std::sqrt(2));
}

/////////////////////////////////////////////
/// Edge
/////////////////////////////////////////////

TEST(test_algo_geometry_ds, edge_equals_operator)
{
  Point p1{0, 0};
  Point p2{1, 1};
  Point p3{2, 2};
  Edge e1{p1, p2};
  Edge e2{p1, p2};
  Edge e3{p1, p3};
  EXPECT_TRUE(e1 == e2);
  EXPECT_FALSE(e1 == e3);
}

/////////////////////////////////////////////
/// Rectangle
/////////////////////////////////////////////

TEST(test_algo_geometry_ds, rectangle_area)
{
  Rectangle r1{0, 0, 2, 2};
  EXPECT_EQ(r1.Area(), 4);
}

/////////////////////////////////////////////
/// Polygon
/////////////////////////////////////////////

TEST(test_algo_geometry_ds, polygon_rotate)
{
  const Points pts{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
  Polygon pn1{pts};
  Polygon pn2{pn1.Rotate(M_PI / 4.0)};// 45 degrees
  const Points pts2{pn2.GetPoints()};

  const double thr{0.00000001};
  EXPECT_GE(pts2.at(0).x, -thr);
  EXPECT_LE(pts2.at(0).x, thr);
  EXPECT_GE(pts2.at(0).y, M_SQRT2 - thr);
  EXPECT_LE(pts2.at(0).y, M_SQRT2 + thr);

  EXPECT_GE(pts2.at(1).x, -M_SQRT2 - thr);
  EXPECT_LE(pts2.at(1).x, -M_SQRT2 + thr);
  EXPECT_GE(pts2.at(1).y, -thr);
  EXPECT_LE(pts2.at(1).y, thr);

  EXPECT_GE(pts2.at(2).x, -thr);
  EXPECT_LE(pts2.at(2).x, thr);
  EXPECT_GE(pts2.at(2).y, -M_SQRT2 - thr);
  EXPECT_LE(pts2.at(2).y, -M_SQRT2 + thr);

  EXPECT_GE(pts2.at(3).x, M_SQRT2 - thr);
  EXPECT_LE(pts2.at(3).x, M_SQRT2 + thr);
  EXPECT_GE(pts2.at(3).y, -thr);
  EXPECT_LE(pts2.at(3).y, thr);
}

TEST(test_algo_geometry_ds, polygon_bounding_rectangle)
{
  Points pts{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}, {0, 0}};
  Polygon polygon{pts};
  Rectangle rect{polygon.BoundingRectangle()};
  EXPECT_EQ(rect.Area(), 4.0);
}

TEST(test_algo_geometry_ds, polygon_get_center)
{
  const Points pts{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
  Polygon polygon{pts};
  const Point p{polygon.GetCenter()};
  EXPECT_EQ(p.x, 0.0);
  EXPECT_EQ(p.y, 0.0);
}
