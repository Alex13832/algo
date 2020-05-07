///
/// \brief Unit tests for geometry algorithms.
/// \author alex011235
/// \date 2020-04-27
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <algorithm>

#include "gtest/gtest.h"
#include "include/algo_geometry.hpp"

using namespace std;
using namespace algo::geometry;

// For sorting on x-priority.
struct x_comp_ {
  bool operator()(const Point p1, const Point p2) const
  {
    return p1.x < p2.x;
  }
};

/////////////////////////////////////////////
/// Quickhull
/////////////////////////////////////////////

TEST(test_algo_geometry_qhull, test_empty)
{
  Points points{};
  Points qh{ConvexHull(points)};
  EXPECT_TRUE(qh.empty());
}

TEST(test_algo_geometry_qhull, test_too_few_points)
{
  Points points{
      {0.174069, 0.526348},
      {0.502471, 0.523942}};
  Points qh{ConvexHull(points)};
  // There's no convex hull of two points.
  EXPECT_TRUE(qh.empty());
}

TEST(test_algo_geometry_qhull, test_same_in_out)
{
  Points points{
      {0.174069, 0.526348},
      {0.502471, 0.523942},
      {0.339814, 0.297757},
  };
  Points qh{ConvexHull(points)};
  sort(points.begin(), points.end(), x_comp_());
  EXPECT_EQ(points.size(), qh.size());
  EXPECT_TRUE(equal(points.begin(), points.end(), qh.begin()));
}

TEST(test_algo_geometry_qhull, test_simple_1)
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

  sort(correct.begin(), correct.end(), x_comp_());

  Points qh{ConvexHull(points)};

  EXPECT_EQ(qh.size(), correct.size());
  EXPECT_TRUE(equal(qh.begin(), qh.end(), correct.begin()));
}

TEST(test_algo_geometry_qhull, test_simple_2)
{
  Points points{{0.453056, 0.0932272},
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

  Points correct{{0.453056, 0.0932272},
                 {0.110242, 0.454161},
                 {0.749544, 0.410849},
                 {0.402612, 0.779002},
                 {0.194659, 0.682753},
                 {0.21216, 0.179851},
                 {0.682628, 0.203914},
                 {0.651744, 0.699597}};

  sort(correct.begin(), correct.end(), x_comp_());

  Points qh{ConvexHull(points)};

  EXPECT_EQ(qh.size(), correct.size());
  EXPECT_TRUE(equal(qh.begin(), qh.end(), correct.begin()));
}

/////////////////////////////////////////////
/// Closest pair of points
/////////////////////////////////////////////

TEST(test_algo_geometry_closest_pair_of_points, test_simple_1)
{
  Points correct{{0.351138, 0.478224},
                 {0.365551, 0.491458}};

  Points points{{0.162745, 0.676737},
                {0.578652, 0.674331},
                {0.201865, 0.252038},
                {0.609536, 0.232788},
                {0.351138, 0.478224},
                {0.365551, 0.491458}};

  Points closest{ClosestPairOfPoints(points)};

  EXPECT_TRUE(equal(closest.begin(), closest.end(), correct.begin()));
}

TEST(test_algo_geometry_closest_pair_of_points, test_simple_2)
{
  Points correct{{0.67851, 0.466192},
                 {0.684687, 0.457771}};

  Points points{{0.313048, 0.872845},
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

  Points closest{ClosestPairOfPoints(points)};

  EXPECT_TRUE(equal(closest.begin(), closest.end(), correct.begin()));
}

/////////////////////////////////////////////
/// Triangulation of points
/////////////////////////////////////////////

TEST(test_algo_geometry_triangulate, test_timple)
{
  Points points{{0.112301, 0.440927},
                {0.339814, .723659},
                {0.614683, .516723},
                {0.414966, .294147}};

  Edges lines{Triangulate(points)};
  EXPECT_EQ(lines.size(), 5);
}
