///
/// \brief Unit tests for geometry data structures.
/// \author alex011235
/// \date 2021-02-07
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"
#include "include/algo_geometry.hpp"

namespace {
namespace geo = algo::geometry;
constexpr float kPi{3.14159265358979323846264338327950288};
constexpr float kSqrt2{1.41421356237309504880168872420969808};
}  // namespace

// /////////////////////////////
// MARK: Helpers

TEST(Helpers, SortCounterClockwise3Points) {
  const std::vector<geo::Point> pts{{0, 0}, {1, 1}, {2, 0}};
  const std::vector<geo::Point> pts_expected{{0, 0}, {2, 0}, {1, 1}};
  auto pts_sorted = geo::helpers::SortCounterClockWise(pts);

  EXPECT_EQ(pts_sorted.size(), pts_expected.size());
  for (size_t i = 0; i < pts_sorted.size(); i++) {
    EXPECT_EQ(pts_sorted.at(i), pts_expected.at(i));
  }
}

TEST(Helpers, SortCounterClockwise6Points) {
  const std::vector<geo::Point> pts{{11, 7}, {1, 4}, {8, 9},
                                    {2, 1},  {3, 7}, {9, 2}};
  const std::vector<geo::Point> pts_expected{{2, 1}, {9, 2}, {11, 7},
                                             {8, 9}, {3, 7}, {1, 4}};
  auto pts_sorted = geo::helpers::SortCounterClockWise(pts);

  EXPECT_EQ(pts_sorted.size(), pts_expected.size());
  for (size_t i = 0; i < pts_sorted.size(); i++) {
    EXPECT_EQ(pts_sorted.at(i), pts_expected.at(i));
  }
}

// /////////////////////////////
// MARK: Point

TEST(Point, EqualsOp) {
  const geo::Point pt1{1, 1};
  const geo::Point pt2{1, 1};
  EXPECT_TRUE(pt1 == pt2);
}

TEST(Point, NotEqualsOp) {
  const geo::Point pt1{0, 1};
  const geo::Point pt2{1, 1};
  EXPECT_TRUE(pt1 != pt2);
}

TEST(Point, SubtractOp) {
  const geo::Point pt1{1, 1};
  const geo::Point pt2{1, 1};
  const geo::Point pt3 = pt1 - pt2;
  EXPECT_EQ(pt3.X(), 0);
  EXPECT_EQ(pt3.Y(), 0);
}

TEST(Point, AddOp) {
  const geo::Point pt1{1, 1};
  const geo::Point pt2{1, 1};
  const geo::Point pt3 = pt1 + pt2;
  EXPECT_EQ(pt3.X(), 2);
  EXPECT_EQ(pt3.Y(), 2);
}

TEST(Point, Dist) {
  geo::Point pt1{6, 7};
  geo::Point pt2{3, 3};
  EXPECT_EQ(pt1.Dist(pt2), 5.0);

  pt1 = {-6, -7};
  pt2 = {-3, -3};
  EXPECT_EQ(pt1.Dist(pt2), 5.0);

  pt1 = {0, 0};
  pt2 = {0, 0};
  EXPECT_EQ(pt1.Dist(pt2), 0.0);
}

TEST(Point, Normalize) {
  const geo::Point pt1{3, 4};
  auto pt2 = pt1.Normalize();
  EXPECT_EQ(pt2.X(), 3.0 / 5.0);
  EXPECT_EQ(pt2.Y(), 4.0 / 5.0);
}

TEST(Point, NormalizePointInOrigin) {
  const geo::Point pt1{0, 0};
  auto pt2 = pt1.Normalize();
  EXPECT_EQ(pt2.X(), 0);
  EXPECT_EQ(pt2.Y(), 0);
}

// /////////////////////////////
// MARK: Edge

TEST(Edge, Constructor) {
  EXPECT_THROW(new geo::Edge({0, 0}, {0, 0}), std::invalid_argument);
  EXPECT_THROW(new geo::Edge({0.0, 0.0}, {0.0, 0.0}), std::invalid_argument);
  EXPECT_NO_THROW(new geo::Edge({0, 0}, {1, 0}));
  EXPECT_NO_THROW(new geo::Edge({0.0, 0.0}, {1.0, 0.0}));
}

TEST(Edge, EqualsOperator) {
  const geo::Point pt1{1, 2};
  const geo::Point pt2{1, 2};
  const geo::Point pt3{1, 1.9999};
  EXPECT_TRUE(pt1 == pt1);
  EXPECT_TRUE(pt2 == pt2);
  EXPECT_TRUE(pt1 == pt2);
  EXPECT_FALSE(pt1 == pt3);
}

TEST(Edge, IntersectA) {
  const geo::Edge e1{{0, 0}, {4, 0}};
  const geo::Edge e2{{2, 2}, {2, -2}};
  EXPECT_TRUE(e1.Intersect(e2));
}

TEST(Edge, IntersectB) {
  auto noise = std::numeric_limits<float>::epsilon();
  const geo::Edge e1{{0, 0}, {4, 0}};
  const geo::Edge e2{{0 + noise, 2}, {0 + noise, -2}};
  EXPECT_TRUE(e1.Intersect(e2));
}

TEST(Edge, IntersectC) {
  auto noise = std::numeric_limits<float>::epsilon();
  const geo::Edge e1{{0, 0}, {4, 0}};
  const geo::Edge e2{{4 - noise, 2}, {4 - noise, -2}};
  EXPECT_TRUE(e1.Intersect(e2));
}

TEST(Edge, IntersectD) {
  const geo::Edge e1{{0, 0}, {4, 0}};
  const geo::Edge e2{{0, 2}, {0, -2}};
  EXPECT_FALSE(e1.Intersect(e2));
}

TEST(Edge, IntersectE) {
  auto noise = std::numeric_limits<float>::epsilon();
  const geo::Edge e1{{0, 0}, {4 - noise * 2, 0}};
  const geo::Edge e2{{4 + noise, 2}, {4 + noise, -2}};
  EXPECT_FALSE(e1.Intersect(e2));
}

TEST(Edge, IntersectF) {
  // Parallel
  const geo::Edge e1{{0, 0}, {4, 0}};
  const geo::Edge e2{{0, -1}, {4, -1}};
  EXPECT_FALSE(e1.Intersect(e2));
}

TEST(Edge, EqualsOpA) {
  const geo::Edge e1{{0, 0}, {1, 0}};
  const geo::Edge e2{{0, 0}, {1, 0}};
  const geo::Edge e3{{0, 0}, {2, 0}};
  EXPECT_TRUE(e1 == e2);
  EXPECT_FALSE(e1 == e3);

  const geo::Edge e5{{1, 1}, {3, 3}};
  const geo::Edge e6{{3, 3}, {1, 1}};
  EXPECT_TRUE(e5 == e6);
}

TEST(Edge, DistA) {
  const geo::Edge edge1{{2, 2}, {8, 2}};
  EXPECT_EQ(edge1.Dist({4, 4}), 2);
  const geo::Edge edge2{{2, 2}, {8, 4}};
  EXPECT_NEAR(edge2.Dist({6, 6}), std::sqrt(10) * 4.0 / 5.0,
              std::numeric_limits<float>::epsilon());
}

TEST(Edge, DistB) {
  // p1 is outside bounds, should compute distance to (4,0).
  const geo::Edge e1{{0, 0}, {4, 0}};
  const geo::Point p1{8, 3};
  EXPECT_EQ(e1.Dist(p1), 5.0);
}

TEST(Edge, DistC) {
  // p1 is outside bounds, should compute distance to (0,0).
  const geo::Edge e1{{0, 0}, {4, 0}};
  const geo::Point p1{-4, 3};
  EXPECT_EQ(e1.Dist(p1), 5.0);
}

// /////////////////////////////
// MARK: Circle

TEST(Edge, Location) {
  const geo::Edge e1{{0, 0}, {5, 0}};

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
  const geo::Edge e2{{0, 0}, {0, 5}};

  // On the line
  EXPECT_EQ(e2.Location({0, 3}), -1);
  // To the right
  EXPECT_EQ(e2.Location({2, 2}), -1);
  // To the left
  EXPECT_EQ(e2.Location({-2, 2}), 1);
}

TEST(Circle, Area) {
  const geo::Circle circle{{0, 0}, 5};
  EXPECT_NEAR(circle.Area(), 5 * 5 * kPi, 0.001);
}

TEST(Circle, IsInside) {
  const geo::Circle circle{{0, 0}, 1};  // Unit circle
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

// /////////////////////////////
// MARK: Polygon

TEST(Polygon, LessThanThreePoints) {
  const std::vector<geo::Point> pts{{0, 0}, {2, 0}};
  EXPECT_THROW(geo::Polygon{pts}, std::invalid_argument);
  const geo::Points pts_empty{};
  EXPECT_THROW(geo::Polygon{pts_empty}, std::invalid_argument);
}

TEST(Polygon, AreaOfFive) {
  const std::vector<geo::Point> pts{{3, 1}, {7, 2}, {4, 4}, {8, 5}, {1, 6}};
  const geo::Polygon polygon{pts};
  const double area{polygon.Area()};
  EXPECT_EQ(area, 16.5);
}

TEST(Polygon, GetEdges) {
  const std::vector<geo::Point> pts{{3, 1}, {7, 2}, {4, 4}, {8, 5}, {1, 6}};
  const geo::Polygon polygon{pts};
  const auto edges = polygon.GetEdges();

  for (size_t i = 0; i < pts.size() - 1; i++) {
    const geo::Edge& e{edges.at(i)};
    EXPECT_EQ(e.GetStart(), pts.at(i));
    EXPECT_EQ(e.GetEnd(), pts.at(i + 1));
  }
  const geo::Edge& e{edges.back()};
  EXPECT_EQ(e.GetStart(), pts.back());
  EXPECT_EQ(e.GetEnd(), pts.front());
}

TEST(Polygon, GetCenter) {
  const geo::Points pts{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
  const geo::Polygon polygon{pts};
  const geo::Point p{polygon.GetCenter()};
  EXPECT_EQ(p.X(), 0.0);
  EXPECT_EQ(p.Y(), 0.0);
}

TEST(Polygon, BoundingRectangleA) {
  const std::vector<geo::Point> pts{{0, 0}, {5, 0}, {5, 5}, {0, 5}, {1, 2},
                                    {2, 3}, {0, 3}, {2, 5}, {5, 4}};
  const geo::Polygon polygon{pts};
  auto rect = polygon.BoundingRectangle();
  EXPECT_EQ(rect.GetWidth(), 5.0);
  EXPECT_EQ(rect.GetHeight(), 5.0);
  EXPECT_EQ(rect.GetPoint().X(), 0.0);
  EXPECT_EQ(rect.GetPoint().Y(), 0.0);
}

TEST(Polygon, BoundingRectangleB) {
  const geo::Points pts{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}, {0, 0}};
  const geo::Polygon polygon{pts};
  auto rect = polygon.BoundingRectangle();
  EXPECT_EQ(rect.Area(), 4.0);
}

TEST(Polygon, Rotate) {
  const geo::Points pts{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
  const geo::Polygon pn1{pts};
  const geo::Polygon pn2{pn1.Rotate(kPi / 4.0)};  // 45 degrees
  const geo::Points pts2{pn2.GetPoints()};

  const double thr{0.0001};
  EXPECT_GE(pts2.at(0).X(), -thr);
  EXPECT_LE(pts2.at(0).X(), thr);
  EXPECT_GE(pts2.at(0).Y(), kSqrt2 - thr);
  EXPECT_LE(pts2.at(0).Y(), kSqrt2 + thr);

  EXPECT_GE(pts2.at(1).X(), -kSqrt2 - thr);
  EXPECT_LE(pts2.at(1).X(), -kSqrt2 + thr);
  EXPECT_GE(pts2.at(1).Y(), -thr);
  EXPECT_LE(pts2.at(1).Y(), thr);

  EXPECT_GE(pts2.at(2).X(), -thr);
  EXPECT_LE(pts2.at(2).X(), thr);
  EXPECT_GE(pts2.at(2).Y(), -kSqrt2 - thr);
  EXPECT_LE(pts2.at(2).Y(), -kSqrt2 + thr);

  EXPECT_GE(pts2.at(3).X(), kSqrt2 - thr);
  EXPECT_LE(pts2.at(3).X(), kSqrt2 + thr);
  EXPECT_GE(pts2.at(3).Y(), -thr);
  EXPECT_LE(pts2.at(3).Y(), thr);
}

// /////////////////////////////
// MARK: Triangle

TEST(Triangle, Constructor) {
  EXPECT_THROW(new geo::Triangle({0, 1}, {0, 0}, {0, 0}),
               std::invalid_argument);
  EXPECT_THROW(new geo::Triangle({0, 0}, {0, 1}, {0, 0}),
               std::invalid_argument);
  EXPECT_THROW(new geo::Triangle({0, 0}, {0, 0}, {0, 1}),
               std::invalid_argument);
  EXPECT_THROW(new geo::Triangle({0, 0}, {0, 0}, {0, 0}),
               std::invalid_argument);
  EXPECT_NO_THROW(new geo::Triangle({0, 0}, {4, 0}, {2, 2}));
}

TEST(Triangle, GetEdges) {
  const geo::Point pt1{0, 0};
  const geo::Point pt2{2, 0};
  const geo::Point pt3{1, 1};

  const geo::Triangle triangle{pt1, pt2, pt3};
  const auto edges = triangle.GetEdges();
  const auto& e1 = edges.at(0);
  const auto& e2 = edges.at(1);
  const auto& e3 = edges.at(2);

  EXPECT_EQ(e1.GetStart(), pt1);
  EXPECT_EQ(e1.GetEnd(), pt2);
  EXPECT_EQ(e2.GetStart(), pt2);
  EXPECT_EQ(e2.GetEnd(), pt3);
  EXPECT_EQ(e3.GetStart(), pt3);
  EXPECT_EQ(e3.GetEnd(), pt1);
}

TEST(Triangle, Area) {
  const geo::Triangle triangle1{{0, 0}, {5, 0}, {5, 10}};
  EXPECT_EQ(triangle1.Area(), 25.0);
  const geo::Triangle triangle2{{0, 0}, {-5, 0}, {-5, -10}};
  EXPECT_EQ(triangle2.Area(), 25.0);
}

TEST(Triangle, IsInside) {
  const geo::Triangle triangle{{0, 0}, {3, 0}, {3, 3}};
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

TEST(Triangle, HasEdgeA) {
  const geo::Triangle triangle{{0, 0}, {1, 0}, {1, 1}};
  const geo::Edge e1{{0, 0}, {1, 0}};
  const geo::Edge e2{{1, 0}, {0, 0}};
  const geo::Edge e3{{0, 0}, {1, 1}};
  const geo::Edge e4{{1, 1}, {0, 0}};
  const geo::Edge e5{{1, 0}, {1, 1}};
  const geo::Edge e6{{1, 1}, {1, 0}};
  EXPECT_TRUE(triangle.HasEdge(e1));
  EXPECT_TRUE(triangle.HasEdge(e2));
  EXPECT_TRUE(triangle.HasEdge(e3));
  EXPECT_TRUE(triangle.HasEdge(e4));
  EXPECT_TRUE(triangle.HasEdge(e5));
  EXPECT_TRUE(triangle.HasEdge(e6));
}

TEST(Triangle, HasEdgeB) {
  const geo::Triangle triangle{{0, 0}, {1, 0}, {1, 1}};
  const geo::Edge e1{{0, 0}, {2, 0}};
  const geo::Edge e2{{2, 0}, {0, 0}};
  const geo::Edge e3{{0, 0}, {2, 2}};
  const geo::Edge e4{{2, 2}, {0, 0}};
  const geo::Edge e5{{0, 0}, {2, 2}};
  const geo::Edge e6{{2, 2}, {1, 0}};
  EXPECT_FALSE(triangle.HasEdge(e1));
  EXPECT_FALSE(triangle.HasEdge(e2));
  EXPECT_FALSE(triangle.HasEdge(e3));
  EXPECT_FALSE(triangle.HasEdge(e4));
  EXPECT_FALSE(triangle.HasEdge(e5));
  EXPECT_FALSE(triangle.HasEdge(e6));
}

TEST(Triangle, CircumCircle) {
  const geo::Triangle triangle{{0, 0}, {4, 0}, {0, 5}};
  auto circle = triangle.CircumCircle();
  auto origin = circle.Origin();
  auto ox = origin.X();
  auto oy = origin.Y();
  EXPECT_NEAR(ox, 2.0, std::numeric_limits<float>::epsilon());
  EXPECT_NEAR(oy, 2.5, std::numeric_limits<float>::epsilon());
  EXPECT_TRUE(circle.IsInside({2, 2.5}));
}

TEST(Triangle, EqualsOp) {
  const geo::Point pt1{0, 0};
  const geo::Point pt2{2, 0};
  const geo::Point pt3{2, 3};
  const geo::Triangle tr0{pt1, pt2, pt3};

  const geo::Triangle tr1{pt1, pt2, pt3};
  EXPECT_TRUE(tr0 == tr1);

  const geo::Triangle tr2{pt3, pt1, pt2};
  EXPECT_TRUE(tr0 == tr2);

  const geo::Triangle tr3{pt2, pt3, pt1};
  EXPECT_TRUE(tr0 == tr3);
}

TEST(Triangle, Rotate) {
  const geo::Triangle triangle{{0, 0}, {6, 0}, {6, 6}};
  auto poly = triangle.Rotate(90.0 * kPi / 180.0, geo::Point{0, 0});
  auto pts = poly.GetPoints();

  EXPECT_EQ(pts.at(0).X(), 0.0);
  EXPECT_EQ(pts.at(0).Y(), 0.0);

  EXPECT_NEAR(pts.at(1).X(), 0.0, 0.001);
  EXPECT_NEAR(pts.at(1).Y(), 6.0, 0.001);

  EXPECT_NEAR(pts.at(2).X(), -6.0, 0.001);
  EXPECT_NEAR(pts.at(2).Y(), 6.0, 0.001);
}

TEST(Triangle, CircumCircleA) {
  const geo::Triangle triangle{{0, 0}, {4, 0}, {0, 5}};
  auto circle = triangle.CircumCircle();
  auto origin = circle.Origin();
  auto ox = origin.X();
  auto oy = origin.Y();
  EXPECT_NEAR(ox, 2.0, std::numeric_limits<float>::epsilon());
  EXPECT_NEAR(oy, 2.5, std::numeric_limits<float>::epsilon());
  EXPECT_TRUE(circle.IsInside({2, 2.5}));
}

TEST(Triangle, CircumCircleB) {
  const geo::Triangle triangle{{-1, 1}, {5, 1}, {3, 5}};
  auto circle = triangle.CircumCircle();
  EXPECT_NEAR(circle.Origin().X(), 2.0, std::numeric_limits<float>::epsilon());
  EXPECT_NEAR(circle.Origin().Y(), 2.0, std::numeric_limits<float>::epsilon());
  EXPECT_NEAR(circle.Radius(), sqrt(10), std::numeric_limits<float>::epsilon());
}

// /////////////////////////////
// MARK: Rhombus

TEST(Rhombus, AreaA) {
  const geo::Rhombus rhombus{{-1, 4}, {-5, 2}, {-1, 0}, {3, 2}};
  EXPECT_EQ(rhombus.Area(), 16.0);
}

TEST(Rhombus, AreaB) {
  const geo::Rhombus rhombus{{0, 0}, {4, 0}, {4, 4}, {0, 4}};
  EXPECT_NEAR(rhombus.Area(), 16.0, std::numeric_limits<float>::epsilon());
}

TEST(Rhombus, TrickyCasesPass) {
  // Generated with ChatGPT
  // This rhombus has vertices that do not form a straight horizontal or
  // vertical line, making it a bit tricky to visualize its shape at first
  // glance.
  EXPECT_NO_THROW(new geo::Rhombus({-1, 0}, {3, 2}, {-1, 4}, {-5, 2}));
  // Although this rhombus has relatively simple coordinates, its shape may be
  // tricky to visualize due to the arrangement of its vertices not forming a
  // perfect square.
  EXPECT_NO_THROW(new geo::Rhombus({0, 0}, {2, -1}, {4, 0}, {2, 1}));
  // The vertices of this rhombus are not arranged in a strictly clockwise or
  // anticlockwise manner, which can make it challenging to visualize its shape
  // without careful examination.
  EXPECT_NO_THROW(new geo::Rhombus({1, 2}, {2, 5}, {-1, 6}, {-2, 3}));
}

TEST(Rhombus, TrickyCasesFail) {
  // Generated with ChatGPT
  // Although it has equal diagonals, the sides are not equal in length, so it
  // is not a rhombus.
  EXPECT_THROW(new geo::Rhombus({1, 1}, {3, 4}, {7, 4}, {5, 1}),
               std::invalid_argument);
  // Although it has opposite sides parallel, the sides are not equal in length,
  // so it is not a rhombus.
  EXPECT_THROW(new geo::Rhombus({0, 0}, {2, 1}, {4, 0}, {3, -1}),
               std::invalid_argument);
}

// /////////////////////////////
// MARK: Rectangle

TEST(Rectangle, Area) {
  const geo::Rectangle rectangle{{0, 0}, 4, 5};
  EXPECT_EQ(rectangle.Area(), 20.0);
}

// /////////////////////////////
// MARK: Closest pair of points

TEST(Grid, ClosestPairOfPointsA) {
  const geo::Point correct1{0.351138, 0.478224};
  const geo::Point correct2{0.365551, 0.491458};

  const geo::Points points{{0.162745, 0.676737}, {0.578652, 0.674331},
                           {0.201865, 0.252038}, {0.609536, 0.232788},
                           {0.351138, 0.478224}, {0.365551, 0.491458}};

  const geo::Grid grid{points};
  auto closest = grid.ClosestPairOfPoints();

  EXPECT_EQ(closest.first, correct1);
  EXPECT_EQ(closest.second, correct2);
}

TEST(Grid, ClosestPairOfPointsB) {
  const geo::Point correct1{0.67851, 0.466192};
  const geo::Point correct2{0.684687, 0.457771};

  const geo::Points points{
      {0.313048, 0.872845}, {0.141126, 0.64305},   {0.137008, 0.380771},
      {0.211130, 0.197898}, {0.534384, 0.14857},   {0.731013, 0.190679},
      {0.842196, 0.434912}, {0.802047, 0.71644},   {0.623948, 0.881267},
      {0.352168, 0.728471}, {0.248191, 0.575676},  {0.280105, 0.383178},
      {0.509677, 0.312194}, {0.692923, 0.324225},  {0.716601, 0.56966},
      {0.633214, 0.671925}, {0.413936, 0.591316},  {0.402612, 0.44213},
      {0.586887, 0.448146}, {0.678510, 0.466192},  {0.684687, 0.457771},
      {0.165834, 0.813892}, {0.0999475, 0.747721}, {0.0597981, 0.6238},
      {0.0515624, 0.44213}, {0.0824465, 0.29896},  {0.098918, 0.217148},
      {0.194659, 0.17143},  {0.310989, 0.0655556}, {0.382023, 0.243616},
      {0.459233, 0.048712}, {0.751603, 0.0234466}, {0.516883, 0.801861},
      {0.471587, 0.740502}, {0.501441, 0.635832},  {0.530266, 0.683956},
      {0.517913, 0.718846}, {0.554974, 0.764565},  {0.681599, 0.763362},
      {0.634243, 0.810283}, {0.586887, 0.893298},  {0.597182, 0.951047},
      {0.539532, 0.92097},  {0.442761, 0.875251},  {0.544679, 0.564848},
      {0.526149, 0.529958}, {0.506589, 0.475817},  {0.500412, 0.44213},
      {0.487029, 0.396412}, {0.475704, 0.359115},  {0.474675, 0.289335}};

  const geo::Grid grid{points};
  auto closest = grid.ClosestPairOfPoints();

  EXPECT_EQ(closest.first, correct1);
  EXPECT_EQ(closest.second, correct2);
}

// /////////////////////////////
// MARK: ConvexHull

// Convex hull will fail because of too few input points.
TEST(Grid, ConvexHullFailB) {
  const geo::Points points{{0.174069, 0.526348}, {0.502471, 0.523942}};
  const geo::Grid grid{points};
  EXPECT_THROW(grid.ConvexHull(), std::invalid_argument);
}

namespace {

// const auto kXComp = [](auto p1, auto p2) { return p1.X() < p2.X(); };

}  // namespace

TEST(Grid, ConvexHullThreePoints) {
  geo::Points points{
      {0.174069, 0.526348},
      {0.502471, 0.523942},
      {0.339814, 0.297757},
  };

  points = geo::helpers::SortCounterClockWise(points);

  const geo::Grid grid{points};
  auto qh = grid.ConvexHull();
  auto qhpts = qh.GetPoints();

  EXPECT_EQ(points.size(), qhpts.size());
  EXPECT_TRUE(std::equal(points.begin(), points.end(), qhpts.begin()));
}

TEST(Grid, ConvexHullA) {
  const geo::Points points{{0.15348, 0.355506},
                           {0.2904, 0.354303},
                           {0.156568, 0.220757},
                           {0.292459, 0.224367},
                           {0.223484, 0.291741}};

  geo::Points correct{{0.15348, 0.355506},
                      {0.2904, 0.354303},
                      {0.156568, 0.220757},
                      {0.292459, 0.224367}};

  correct = geo::helpers::SortCounterClockWise(correct);

  const geo::Grid grid{points};
  auto qh = grid.ConvexHull();
  auto qhpts = qh.GetPoints();

  EXPECT_EQ(qhpts.size(), correct.size());
  EXPECT_TRUE(equal(qhpts.begin(), qhpts.end(), correct.begin()));
}

TEST(Grid, ConvexHullB) {
  const geo::Points points{
      {0.453056, 0.0932272}, {0.110242, 0.454161}, {0.749544, 0.410849},
      {0.402612, 0.779002},  {0.194659, 0.682753}, {0.21216, 0.179851},
      {0.682628, 0.203914},  {0.651744, 0.699597}, {0.319491, 0.532932},
      {0.299839, 0.460095},  {0.215062, 0.426786}, {0.298793, 0.411578},
      {0.237734, 0.405535},  {0.519017, 0.397239}, {0.483573, 0.370813},
      {0.553512, 0.304346},  {0.338087, 0.309805}, {0.321325, 0.264039},
      {0.478283, 0.63017},   {0.338503, 0.591417}, {0.441968, 0.497185},
      {0.404723, 0.553411},  {0.492701, 0.530521}, {0.541202, 0.5114},
      {0.559772, 0.450984},  {0.244139, 0.471237}, {0.310989, 0.68155},
      {0.180246, 0.55041},   {0.176128, 0.313397}, {0.342903, 0.144961},
      {0.564239, 0.150977},  {0.690864, 0.321819}, {0.668216, 0.568457},
      {0.502471, 0.712831}};

  geo::Points correct{{0.453056, 0.0932272}, {0.110242, 0.454161},
                      {0.749544, 0.410849},  {0.402612, 0.779002},
                      {0.194659, 0.682753},  {0.21216, 0.179851},
                      {0.682628, 0.203914},  {0.651744, 0.699597}};

  correct = geo::helpers::SortCounterClockWise(correct);

  const geo::Grid grid{points};
  auto qh = grid.ConvexHull();
  auto qhpts = qh.GetPoints();

  EXPECT_EQ(qhpts.size(), correct.size());
  EXPECT_TRUE(equal(qhpts.begin(), qhpts.end(), correct.begin()));
}

// /////////////////////////////
// MARK: MinBoundingBox

TEST(Grid, MinBoundingBoxConstraints) {
  const geo::Points pts{{0, 0}, {1, 1}};
  const geo::Grid grid{pts};
  EXPECT_THROW(grid.MinBoundingBox(), std::invalid_argument);
}

TEST(Grid, MinBoundingBoxSimple) {
  const geo::Points pts{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}, {0.5, 0.5}};
  const geo::Grid grid{pts};
  auto polygon = grid.MinBoundingBox();
  EXPECT_EQ(polygon.GetPoints().size(), 4);
}

// /////////////////////////////
// MARK: MinEnclosingCircle

TEST(Grid, MinEnclosingCircleEmpty) {
  const geo::Points pts{};
  const geo::Grid grid{pts};
  auto circle = grid.MinEnclosingCircle();

  EXPECT_EQ(circle.Radius(), 0.0);
  EXPECT_EQ(circle.Origin().X(), 0.0);
  EXPECT_EQ(circle.Origin().Y(), 0.0);
}

TEST(Grid, MinEnclosingCircleOnePoint) {
  const geo::Points pts{{1, 1}};
  const geo::Grid grid{pts};
  auto circle = grid.MinEnclosingCircle();

  EXPECT_EQ(circle.Radius(), 0.0);
  EXPECT_EQ(circle.Origin().X(), 1.0);
  EXPECT_EQ(circle.Origin().Y(), 1.0);
}

TEST(Grid, MinEnclosingCircleTheePoints) {
  const geo::Points pts{{0, 0}, {0, 1}, {1, 0}};
  const geo::Grid grid{pts};
  auto circle = grid.MinEnclosingCircle();

  EXPECT_EQ(circle.Radius(), std::sqrt(0.5));
  EXPECT_EQ(circle.Origin().X(), 0.5);
  EXPECT_EQ(circle.Origin().Y(), 0.5);
}

TEST(Grid, MinEnclosingCircleFivePoints) {
  const geo::Points pts{{5, -2}, {-3, -2}, {-2, 5}, {1, 6}, {0, 2}};
  const geo::Grid grid{pts};
  auto circle = grid.MinEnclosingCircle();

  EXPECT_EQ(circle.Radius(), 5);
  EXPECT_EQ(circle.Origin().X(), 1);
  EXPECT_EQ(circle.Origin().Y(), 1);
}

// /////////////////////////////
// MARK: Triangulate

TEST(Grid, TriangulateSimple) {
  const geo::Points points{{0.112301, 0.440927},
                           {0.339814, .723659},
                           {0.614683, .516723},
                           {0.414966, .294147}};
  const geo::Grid grid{points};
  auto lines = grid.Triangulation();
  EXPECT_EQ(lines.size(), 5);
}

// /////////////////////////////
// MARK: DelaunayTriangulation

TEST(Grid, DelaunayTriangulationEmpty) {
  const geo::Points points{};
  const geo::Grid grid{points};
  auto de_tri = grid.DelaunayTriangulation();
  EXPECT_TRUE(de_tri.empty());
}

TEST(Grid, DelaunayTriangulationMinimum) {
  const geo::Points points{{0.0, 0.0}, {4.0, 0.0}, {2.0, 2.0}};
  const geo::Grid grid{points};
  auto de_tri = grid.DelaunayTriangulation();
  EXPECT_EQ(de_tri.size(), 3);
}

TEST(Grid, DelaunayTriangulationA) {
  const geo::Points points{{0.22863140896245457, 0.9077353149327672},
                           {0.09068227694792083, 0.6923779193205944},
                           {0.1534800161485668, 0.27249115357395604},
                           {0.4633508276140493, 0.2135385704175513},
                           {0.657920872022608, 0.08841472045293697},
                           {0.8236657246669358, 0.18466383581033252},
                           {0.8669035123132822, 0.6069568294409058},
                           {0.7783689947517157, 0.8463765038924275},
                           {0.5652684699232943, 0.9029228591648973},
                           {0.436584578118692, 0.6899716914366596},
                           {0.2728986677432378, 0.5648478414720453},
                           {0.4314372224465079, 0.3915994338287332},
                           {0.6970407751312071, 0.3422717622080679},
                           {0.7021881308033912, 0.6105661712668082},
                           {0.5817400080742834, 0.745314932767162}};

  const geo::Grid grid{points};
  auto de_tri = grid.DelaunayTriangulation();
  EXPECT_EQ(de_tri.size(), 33);
}

TEST(Grid, DelaunayTriangulationB) {
  const geo::Points points{{2, 3}, {5, 8}, {9, 1}, {4, 6}, {7, 4},
                           {1, 9}, {6, 2}, {3, 5}, {8, 7}, {5, 5}};
  const geo::Grid grid{points};
  auto de_tri = grid.DelaunayTriangulation();
  EXPECT_EQ(de_tri.size(), 21);
}
