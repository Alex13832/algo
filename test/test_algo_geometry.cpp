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

// /////////////////////////////
// MARK: Point

TEST(Point, EqualsOp)
{
  Point pt1{1, 1};
  Point pt2{1, 1};
  EXPECT_TRUE(pt1 == pt2);
}

TEST(Point, NotEqualsOp)
{
  Point pt1{0, 1};
  Point pt2{1, 1};
  EXPECT_TRUE(pt1 != pt2);
}

TEST(Point, SubtractOp)
{
  Point pt1{1, 1};
  Point pt2{1, 1};
  Point pt3 = pt1 - pt2;
  EXPECT_EQ(pt3.X(), 0);
  EXPECT_EQ(pt3.Y(), 0);
}

TEST(Point, AddOp)
{
  Point pt1{1, 1};
  Point pt2{1, 1};
  Point pt3 = pt1 + pt2;
  EXPECT_EQ(pt3.X(), 2);
  EXPECT_EQ(pt3.Y(), 2);
}

TEST(Point, Dist)
{
  Point pt1{6, 7};
  Point pt2{3, 3};
  EXPECT_EQ(pt1.Dist(pt2), 5.0);

  pt1 = {-6, -7};
  pt2 = {-3, -3};
  EXPECT_EQ(pt1.Dist(pt2), 5.0);
}

TEST(Point, Normalize)
{
  Point pt1{3, 4};
  auto pt2 = pt1.Normalize();
  EXPECT_EQ(pt2.X(), 3.0 / 5.0);
  EXPECT_EQ(pt2.Y(), 4.0 / 5.0);
}

// /////////////////////////////
// MARK: Edge

TEST(Edge, Constructor)
{
  EXPECT_THROW(new Edge({0, 0}, {0, 0}), std::invalid_argument);
  EXPECT_THROW(new Edge({0.0, 0.0}, {0.0, 0.0}), std::invalid_argument);
  EXPECT_NO_THROW(new Edge({0, 0}, {1, 0}));
  EXPECT_NO_THROW(new Edge({0.0, 0.0}, {1.0, 0.0}));
}

TEST(Edge, IntersectA)
{
  Edge e1{{0, 0}, {4, 0}};
  Edge e2{{2, 2}, {2, -2}};
  EXPECT_TRUE(e1.Intersect(e2));
}

TEST(Edge, IntersectB)
{
  auto noise = std::numeric_limits<float>::epsilon();
  Edge e1{{0, 0}, {4, 0}};
  Edge e2{{0 + noise, 2}, {0 + noise, -2}};
  EXPECT_TRUE(e1.Intersect(e2));
}

TEST(Edge, IntersectC)
{
  auto noise = std::numeric_limits<float>::epsilon();
  Edge e1{{0, 0}, {4, 0}};
  Edge e2{{4 - noise, 2}, {4 - noise, -2}};
  EXPECT_TRUE(e1.Intersect(e2));
}

TEST(Edge, IntersectD)
{
  Edge e1{{0, 0}, {4, 0}};
  Edge e2{{0, 2}, {0, -2}};
  EXPECT_FALSE(e1.Intersect(e2));
}

TEST(Edge, IntersectE)
{
  auto noise = std::numeric_limits<float>::epsilon();
  Edge e1{{0, 0}, {4 - noise * 2, 0}};
  Edge e2{{4 + noise, 2}, {4 + noise, -2}};
  EXPECT_FALSE(e1.Intersect(e2));
}

TEST(Edge, IntersectF)
{
  // Parallel
  Edge e1{{0, 0}, {4, 0}};
  Edge e2{{0, -1}, {4, -1}};
  EXPECT_FALSE(e1.Intersect(e2));
}

TEST(Edge, EqualsOpA)
{
  Edge e1{{0, 0}, {1, 0}};
  Edge e2{{0, 0}, {1, 0}};
  Edge e3{{0, 0}, {2, 0}};
  EXPECT_TRUE(e1 == e2);
  EXPECT_FALSE(e1 == e3);

  Edge e5{{1, 1}, {3, 3}};
  Edge e6{{3, 3}, {1, 1}};
  EXPECT_TRUE(e5 == e6);
}

TEST(Edge, DistA)
{
  Edge edge1{{2, 2}, {8, 2}};
  EXPECT_EQ(edge1.Dist({4, 4}), 2);
  Edge edge2{{2, 2}, {8, 4}};
  EXPECT_NEAR(edge2.Dist({6, 6}), std::sqrt(10) * 4.0 / 5.0,
              std::numeric_limits<float>::epsilon());
}

TEST(Edge, DistB)
{
  // p1 is outside bounds, should compute distance to (4,0).
  Edge e1{{0, 0}, {4, 0}};
  Point p1{8, 3};
  EXPECT_EQ(e1.Dist(p1), 5.0);
}

TEST(Edge, DistC)
{
  // p1 is outside bounds, should compute distance to (0,0).
  Edge e1{{0, 0}, {4, 0}};
  Point p1{-4, 3};
  EXPECT_EQ(e1.Dist(p1), 5.0);
}

// /////////////////////////////
// MARK: Cicle

TEST(Edge, Location)
{
  Edge e1{{0, 0}, {5, 0}};

  // On the line
  EXPECT_EQ(e1.Location({4, 0}), -1);
  // Above the line
  EXPECT_EQ(e1.Location({4, 1}), 1);
  // Above, but outside x
  EXPECT_EQ(e1.Location({6, 1}), 1);
  EXPECT_EQ(e1.Location({-1, 1}), 1);
  // Below the line
  EXPECT_EQ(e1.Location({4, -1}), -1);
  EXPECT_EQ(e1.Location({6, -1}), -1);
  EXPECT_EQ(e1.Location({-1, -1}), -1);

  // Vertical line
  Edge e2{{0, 0}, {0, 5}};

  // On the line
  EXPECT_EQ(e2.Location({0, 3}), -1);
  // To the right
  EXPECT_EQ(e2.Location({2, 2}), -1);
  // To the left
  EXPECT_EQ(e2.Location({-2, 2}), 1);
}

TEST(Circle, Area)
{
  Circle circle{{0, 0}, 5};
  EXPECT_EQ(circle.Area(), 5 * 5 * M_PI);
}

TEST(Circle, IsInside)
{
  Circle circle{{0, 0}, 1};// Unit circle
  EXPECT_TRUE(circle.IsInside({0, 0}));
  EXPECT_TRUE(circle.IsInside({1, 0}));
  EXPECT_TRUE(circle.IsInside({0, 1}));
  EXPECT_TRUE(circle.IsInside({-1, 0}));
  EXPECT_TRUE(circle.IsInside({0, -1}));

  auto eps = std::numeric_limits<float>::epsilon();
  auto on_unit_circle_x = std::sqrt(3.0) / 2.0 - eps;
  auto on_unit_circle_y = 0.5 - eps;
  EXPECT_TRUE(circle.IsInside({on_unit_circle_x, on_unit_circle_y}));

  on_unit_circle_x = -std::sqrt(2.0) / 2.0 + eps;
  on_unit_circle_y = -std::sqrt(2.0) / 2.0 + eps;
  EXPECT_TRUE(circle.IsInside({on_unit_circle_x, on_unit_circle_y}));

  auto outside_x = -std::sqrt(2.0) / 2.0 - eps;
  auto outside_y = -std::sqrt(2.0) / 2.0 - eps;
  EXPECT_FALSE(circle.IsInside({outside_x, outside_y}));

  outside_x = std::sqrt(3.0) / 2.0 + eps;
  outside_y = 1.0 / 2.0 + eps;
  EXPECT_FALSE(circle.IsInside({outside_x, outside_y}));
}

TEST(Circle, CircumCircle)
{
  Triangle triangle{{0, 0}, {0, 5}, {4, 0}};
  auto circle = triangle.CircumCircle();
  auto origin = circle.Origin();
  auto ox = origin.X();
  auto oy = origin.Y();
  EXPECT_NEAR(ox, 2.0, std::numeric_limits<float>::epsilon());
  EXPECT_NEAR(oy, 2.5, std::numeric_limits<float>::epsilon());
  EXPECT_TRUE(circle.IsInside({2, 2.5}));
}

// /////////////////////////////
// MARK: Polygon

TEST(Polygon, GetCenter)
{
  Points pts{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
  Polygon polygon{pts};
  Point p{polygon.GetCenter()};
  EXPECT_EQ(p.X(), 0.0);
  EXPECT_EQ(p.Y(), 0.0);
}

TEST(Polygon, BoundingRectangleA)
{
  std::vector<Point> pts{{0, 0}, {5, 0}, {5, 5}, {0, 5}, {1, 2}, {2, 3}, {0, 3}, {2, 5}, {5, 4}};
  Polygon polygon{pts};
  auto rect = polygon.BoundingRectangle();
  EXPECT_EQ(rect.GetWidth(), 5.0);
  EXPECT_EQ(rect.GetHeight(), 5.0);
  EXPECT_EQ(rect.GetPoint().X(), 0.0);
  EXPECT_EQ(rect.GetPoint().Y(), 0.0);
}

TEST(Polygon, BoundingRectangleB)
{
  Points pts{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}, {0, 0}};
  Polygon polygon{pts};
  auto rect = polygon.BoundingRectangle();
  EXPECT_EQ(rect.Area(), 4.0);
}

TEST(Polygon, Rotate)
{
  Points pts{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
  Polygon pn1{pts};
  Polygon pn2{pn1.Rotate(M_PI / 4.0)};// 45 degrees
  Points pts2{pn2.GetPoints()};

  const double thr{0.00000001};
  EXPECT_GE(pts2.at(0).X(), -thr);
  EXPECT_LE(pts2.at(0).X(), thr);
  EXPECT_GE(pts2.at(0).Y(), M_SQRT2 - thr);
  EXPECT_LE(pts2.at(0).Y(), M_SQRT2 + thr);

  EXPECT_GE(pts2.at(1).X(), -M_SQRT2 - thr);
  EXPECT_LE(pts2.at(1).X(), -M_SQRT2 + thr);
  EXPECT_GE(pts2.at(1).Y(), -thr);
  EXPECT_LE(pts2.at(1).Y(), thr);

  EXPECT_GE(pts2.at(2).X(), -thr);
  EXPECT_LE(pts2.at(2).X(), thr);
  EXPECT_GE(pts2.at(2).Y(), -M_SQRT2 - thr);
  EXPECT_LE(pts2.at(2).Y(), -M_SQRT2 + thr);

  EXPECT_GE(pts2.at(3).X(), M_SQRT2 - thr);
  EXPECT_LE(pts2.at(3).X(), M_SQRT2 + thr);
  EXPECT_GE(pts2.at(3).Y(), -thr);
  EXPECT_LE(pts2.at(3).Y(), thr);
}

// /////////////////////////////
// MARK: Triangle

TEST(Triangle, Constructor)
{
  EXPECT_THROW(new Triangle({0, 1}, {0, 0}, {0, 0}), std::invalid_argument);
  EXPECT_THROW(new Triangle({0, 0}, {0, 1}, {0, 0}), std::invalid_argument);
  EXPECT_THROW(new Triangle({0, 0}, {0, 0}, {0, 1}), std::invalid_argument);
  EXPECT_THROW(new Triangle({0, 0}, {0, 0}, {0, 0}), std::invalid_argument);
  EXPECT_NO_THROW(new Triangle({0, 0}, {4, 0}, {2, 2}));
}

TEST(Triangle, Area)
{
  Triangle triangle1{{0, 0}, {5, 0}, {5, 10}};
  EXPECT_EQ(triangle1.Area(), 25.0);
  Triangle triangle2{{0, 0}, {-5, 0}, {-5, -10}};
  EXPECT_EQ(triangle2.Area(), 25.0);
}

TEST(Triangle, IsInside)
{
  Triangle triangle{{0, 0}, {3, 0}, {3, 3}};
  // INSIDE
  EXPECT_TRUE(triangle.IsInside({0, 0}));
  EXPECT_TRUE(triangle.IsInside({1, 1}));
  EXPECT_TRUE(triangle.IsInside({2, 2}));
  EXPECT_TRUE(triangle.IsInside({3, 3}));
  EXPECT_TRUE(triangle.IsInside({3, 0}));

  // OUTSIDE
  EXPECT_FALSE(triangle.IsInside({-1, -1}));
  EXPECT_FALSE(triangle.IsInside({2, 4}));
  EXPECT_FALSE(triangle.IsInside({-1, 2}));
  EXPECT_FALSE(triangle.IsInside({4, 4}));
}

TEST(Triangle, Rotate)
{
  Triangle triangle{{0, 0}, {6, 0}, {6, 6}};
  auto poly = triangle.Rotate(90.0 * M_PI / 180.0, Point{0, 0});
  auto pts = poly.GetPoints();

  EXPECT_EQ(pts.at(0).X(), 0.0);
  EXPECT_EQ(pts.at(0).Y(), 0.0);

  EXPECT_NEAR(pts.at(1).X(), 0.0, std::numeric_limits<float>::epsilon());
  EXPECT_EQ(pts.at(1).Y(), 6.0);

  EXPECT_EQ(pts.at(2).X(), -6.0);
  EXPECT_EQ(pts.at(2).Y(), 6.0);
}

// /////////////////////////////
// MARK: Rhombus

TEST(Rhombus, AreaA)
{
  Rhombus rhombus{{-1, 4}, {-5, 2}, {-1, 0}, {3, 2}};
  EXPECT_EQ(rhombus.Area(), 16.0);
}

TEST(Rhombus, AreaB)
{
  Rhombus rhombus{{0, 0}, {0, 4}, {4, 4}, {4, 0}};
  EXPECT_NEAR(rhombus.Area(), 16.0, std::numeric_limits<float>::epsilon());
}

TEST(Rectangle, Area)
{
  Rectangle rectangle{{0, 0}, 4, 5};
  EXPECT_EQ(rectangle.Area(), 20.0);
}

// /////////////////////////////
// MARK: Closest pair of points

TEST(Grid, ClosestPairOfPointsA)
{
  Point correct1{0.351138, 0.478224};
  Point correct2{0.365551, 0.491458};

  Points points{{0.162745, 0.676737}, {0.578652, 0.674331}, {0.201865, 0.252038}, {0.609536, 0.232788}, {0.351138, 0.478224}, {0.365551, 0.491458}};

  Grid grid{points};
  auto closest = grid.ClosestPairOfPoints();

  EXPECT_EQ(closest.first, correct1);
  EXPECT_EQ(closest.second, correct2);
}

TEST(Grid, ClosestPairOfPointsB)
{
  Point correct1{0.67851, 0.466192};
  Point correct2{0.684687, 0.457771};

  Points points{
      {0.313048, 0.872845},
      {0.141126, 0.64305},
      {0.137008, 0.380771},
      {0.211130, 0.197898},
      {0.534384, 0.14857},
      {0.731013, 0.190679},
      {0.842196, 0.434912},
      {0.802047, 0.71644},
      {0.623948, 0.881267},
      {0.352168, 0.728471},
      {0.248191, 0.575676},
      {0.280105, 0.383178},
      {0.509677, 0.312194},
      {0.692923, 0.324225},
      {0.716601, 0.56966},
      {0.633214, 0.671925},
      {0.413936, 0.591316},
      {0.402612, 0.44213},
      {0.586887, 0.448146},
      {0.678510, 0.466192},
      {0.684687, 0.457771},
      {0.165834, 0.813892},
      {0.0999475, 0.747721},
      {0.0597981, 0.6238},
      {0.0515624, 0.44213},
      {0.0824465, 0.29896},
      {0.098918, 0.217148},
      {0.194659, 0.17143},
      {0.310989, 0.0655556},
      {0.382023, 0.243616},
      {0.459233, 0.048712},
      {0.751603, 0.0234466},
      {0.516883, 0.801861},
      {0.471587, 0.740502},
      {0.501441, 0.635832},
      {0.530266, 0.683956},
      {0.517913, 0.718846},
      {0.554974, 0.764565},
      {0.681599, 0.763362},
      {0.634243, 0.810283},
      {0.586887, 0.893298},
      {0.597182, 0.951047},
      {0.539532, 0.92097},
      {0.442761, 0.875251},
      {0.544679, 0.564848},
      {0.526149, 0.529958},
      {0.506589, 0.475817},
      {0.500412, 0.44213},
      {0.487029, 0.396412},
      {0.475704, 0.359115},
      {0.474675, 0.289335}};

  Grid grid{points};
  auto closest = grid.ClosestPairOfPoints();

  EXPECT_EQ(closest.first, correct1);
  EXPECT_EQ(closest.second, correct2);
}

// /////////////////////////////
// MARK: ConvexHull

// Convex hull will fail because of empty set of input points.
TEST(Grid, ConvexHullFailA)
{
  Points points{};
  Grid grid{points};
  auto qh = grid.ConvexHull();
  EXPECT_TRUE(qh.GetPoints().empty());
}

// Convex hull will fail because of too few input points.
TEST(Grid, ConvexHullFailB)
{
  Points points{{0.174069, 0.526348}, {0.502471, 0.523942}};
  Grid grid{points};
  auto qh = grid.ConvexHull();
  // There's no convex hull of two points.
  EXPECT_TRUE(qh.GetPoints().empty());
}

namespace {

const auto x_comp = [](auto p1, auto p2) { return p1.X() < p2.X(); };

}// namespace

TEST(Grid, ConvexHullThreePoints)
{
  Points points{
      {0.174069, 0.526348},
      {0.502471, 0.523942},
      {0.339814, 0.297757},
  };

  Grid grid{points};
  auto qh = grid.ConvexHull();
  auto qhpts = qh.GetPoints();
  std::sort(points.begin(), points.end(), x_comp);

  EXPECT_EQ(points.size(), qhpts.size());
  EXPECT_TRUE(std::equal(points.begin(), points.end(), qhpts.begin()));
}

TEST(Grid, ConvexHullA)
{
  Points points{{0.15348, 0.355506},
                {0.2904, 0.354303},
                {0.156568, 0.220757},
                {0.292459, 0.224367},
                {0.223484, 0.291741}};

  Points correct{{0.15348, 0.355506},
                 {0.2904, 0.354303},
                 {0.156568, 0.220757},
                 {0.292459, 0.224367}};

  std::sort(correct.begin(), correct.end(), x_comp);
  Grid grid{points};
  auto qh = grid.ConvexHull();
  auto qhpts = qh.GetPoints();

  EXPECT_EQ(qhpts.size(), correct.size());
  EXPECT_TRUE(equal(qhpts.begin(), qhpts.end(), correct.begin()));
}

TEST(Grid, ConvexHullB)
{
  Points points{
      {0.453056, 0.0932272},
      {0.110242, 0.454161},
      {0.749544, 0.410849},
      {0.402612, 0.779002},
      {0.194659, 0.682753},
      {0.21216, 0.179851},
      {0.682628, 0.203914},
      {0.651744, 0.699597},
      {0.319491, 0.532932},
      {0.299839, 0.460095},
      {0.215062, 0.426786},
      {0.298793, 0.411578},
      {0.237734, 0.405535},
      {0.519017, 0.397239},
      {0.483573, 0.370813},
      {0.553512, 0.304346},
      {0.338087, 0.309805},
      {0.321325, 0.264039},
      {0.478283, 0.63017},
      {0.338503, 0.591417},
      {0.441968, 0.497185},
      {0.404723, 0.553411},
      {0.492701, 0.530521},
      {0.541202, 0.5114},
      {0.559772, 0.450984},
      {0.244139, 0.471237},
      {0.310989, 0.68155},
      {0.180246, 0.55041},
      {0.176128, 0.313397},
      {0.342903, 0.144961},
      {0.564239, 0.150977},
      {0.690864, 0.321819},
      {0.668216, 0.568457},
      {0.502471, 0.712831}};

  Points correct{{0.453056, 0.0932272}, {0.110242, 0.454161}, {0.749544, 0.410849}, {0.402612, 0.779002}, {0.194659, 0.682753}, {0.21216, 0.179851}, {0.682628, 0.203914}, {0.651744, 0.699597}};

  std::sort(correct.begin(), correct.end(), x_comp);
  Grid grid{points};
  auto qh = grid.ConvexHull();
  auto qhpts = qh.GetPoints();

  EXPECT_EQ(qhpts.size(), correct.size());
  EXPECT_TRUE(equal(qhpts.begin(), qhpts.end(), correct.begin()));
}

// /////////////////////////////
// MARK: MinBoundingBox

TEST(Grid, MinBoundingBoxConstraints)
{
  Points pts{{0, 0}, {1, 1}};
  Grid grid{pts};
  auto polygon = grid.MinBoundingBox();
  EXPECT_EQ(polygon.GetPoints().size(), 0);
}

TEST(Grid, MinBoundingBoxSimple)
{
  const Points pts{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}, {0.5, 0.5}};
  Grid grid{pts};
  auto polygon = grid.MinBoundingBox();
  EXPECT_EQ(polygon.GetPoints().size(), 4);
}

// /////////////////////////////
// MARK: MinEnclosingCircle

TEST(Grid, MinEnclosingCircleEmpty)
{
  Points pts{};
  Grid grid{pts};
  auto circle = grid.MinEnclosingCircle();

  EXPECT_EQ(circle.Radius(), 0.0);
  EXPECT_EQ(circle.Origin().X(), 0.0);
  EXPECT_EQ(circle.Origin().Y(), 0.0);
}

TEST(Grid, MinEnclosingCircleOnePoint)
{
  Points pts{{1, 1}};
  Grid grid{pts};
  auto circle = grid.MinEnclosingCircle();

  EXPECT_EQ(circle.Radius(), 0.0);
  EXPECT_EQ(circle.Origin().X(), 1.0);
  EXPECT_EQ(circle.Origin().Y(), 1.0);
}

TEST(Grid, MinEnclosingCircleTheePoints)
{
  Points pts{{0, 0}, {0, 1}, {1, 0}};
  Grid grid{pts};
  auto circle = grid.MinEnclosingCircle();

  EXPECT_EQ(circle.Radius(), std::sqrt(0.5));
  EXPECT_EQ(circle.Origin().X(), 0.5);
  EXPECT_EQ(circle.Origin().Y(), 0.5);
}

TEST(Grid, MinEnclosingCircleFivePoints)
{
  Points pts{{5, -2}, {-3, -2}, {-2, 5}, {1, 6}, {0, 2}};
  Grid grid{pts};
  auto circle = grid.MinEnclosingCircle();

  EXPECT_EQ(circle.Radius(), 5);
  EXPECT_EQ(circle.Origin().X(), 1);
  EXPECT_EQ(circle.Origin().Y(), 1);
}

// /////////////////////////////
// MARK: Triangulate

TEST(Grid, TriangulateSimple)
{
  Points points{{0.112301, 0.440927},
                {0.339814, .723659},
                {0.614683, .516723},
                {0.414966, .294147}};
  Grid grid{points};
  auto lines = grid.Triangulate();
  EXPECT_EQ(lines.size(), 5);
}
