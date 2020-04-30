///
/// \brief Source file for data mining algorithms.
/// \author alex011235
/// \date 2020-04-30
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "data_mining_algorithms.hpp"

#include <chrono>
#include <cmath>
#include <random>

namespace algo::data_mining {

namespace {
constexpr double kDblMax{1.79769e+308};
}// namespace

/// \brief Returns a uniform random number between a and b.
/// \param a Lower bound.
/// \param b Upper Bound.
/// \return Random number between a and b.
double Uniform(const double& a, const double& b)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed);//Mersenne twister
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(generator);
}

/// \brief Returns the distance between two points.
/// \param p1 Point 1.
/// \param p2 Point 2.
/// \return The distance between p1 and p2.
double Distance(Point p1, Point p2)
{
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

/////////////////////////////////////////////
/// K-means
/////////////////////////////////////////////

Clusters KMeans(Points points, const std::int8_t& k)
{
  if (k > points.size() || k == 0 || points.empty()) {
    return Clusters{};
  }

  Centroids ctr(k);
  size_t N{points.size()};
  // Initialize random centroids
  std::generate(ctr.begin(), ctr.end(), [&points, &N]() {
    return Centroid{points[static_cast<int>(Uniform(0, N))], 0.0, 0.0, 0};
  });

  int converge_clusters{0}, converge{0};
  // Compute centroid locations
  while (converge_clusters < 1) {

    for (const auto& pt : points) {

      double dist_min{kDblMax};
      int cluster{0}, min_cluster{0};

      for (auto& ct : ctr) {
        double dist_curr{Distance(ct.p, pt)};

        if (dist_curr < dist_min) {
          dist_min = dist_curr;
          min_cluster = cluster;
        }
        cluster++;
      }

      ctr[min_cluster].mean_x += pt.x;
      ctr[min_cluster].mean_y += pt.y;
      ctr[min_cluster].size++;
    }

    for (auto& ct : ctr) {
      ct.mean_x /= ct.size;// New mean
      ct.mean_y /= ct.size;// New mean

      if (Point{ct.mean_x, ct.mean_y} == ct.p) { converge++; }

      // Update centroid location and reset the rest
      ct = {ct.mean_x, ct.mean_y, 0, 0.0, 0};
    }

    // Check if clusters has converged
    if (converge == k) { converge_clusters++; }
    converge = 0;
  }

  // Put the points in the correct cluster
  Clusters clusters(k);
  for (const auto& pt : points) {
    double dist_min{kDblMax};
    int cluster{0}, min_cluster{0};

    for (auto& ct : ctr) {
      double dist_curr{Distance(ct.p, pt)};

      if (dist_curr < dist_min) {
        dist_min = dist_curr;
        min_cluster = cluster;
      }
      cluster++;
    }
    clusters[min_cluster].emplace_back(pt);
  }

  return clusters;
}

}// namespace algo::data_mining