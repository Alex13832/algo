///
/// \brief Unit tests for geometry algorithms.
/// \author alex011235
/// \date 2020-04-27
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <algorithm>
#include <cmath>
#include <numeric>

#include "geometry_algorithms.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace algo::geometry;

// For sorting on x-priority.
struct x_comp_ {
  bool operator()(const Point p1, const Point p2) const
  {
    return p1.x < p2.x;
  }
};

TEST(test_geometry_qhull, test_empty)
{
  Points points{};
  Points qh{ConvexHull(points)};
  EXPECT_TRUE(qh.empty());
}

TEST(test_geometry_qhull, test_too_few_points)
{
  Points points{
      {0.174069, 0.526348},
      {0.502471, 0.523942}};
  Points qh{ConvexHull(points)};
  // There's no convex hull of two points.
  EXPECT_TRUE(qh.empty());
}

TEST(test_geometry_qhull, test_same_in_out)
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

TEST(test_geometry_qhull, test_simple_1)
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

TEST(test_geometry_qhull, test_simple_2)
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