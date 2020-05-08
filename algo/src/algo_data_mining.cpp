///
/// \brief Source file for data mining algorithms.
/// \author alex011235
/// \date 2020-04-30
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "algo_data_mining.hpp"

#include <chrono>
#include <cmath>
#include <set>

#include "algo_math.hpp"

namespace algo::data_mining {

namespace {
constexpr double kDblMax{1.79769e+308};
}// namespace

/// \brief Returns the distance between two points.
/// \param p1 Point 1.
/// \param p2 Point 2.
/// \return The distance between p1 and p2.
double Distance(geometry::Point p1, geometry::Point p2)
{
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

/////////////////////////////////////////////
/// K-means
/////////////////////////////////////////////

Clusters KMeans(geometry::Points points, const std::int8_t& k)
{
  if (k > points.size() || k == 0 || points.empty()) {
    return Clusters{};
  }

  Centroids ctr(k);
  size_t N{points.size()};
  // Initialize random centroids
  std::generate(ctr.begin(), ctr.end(), [&points, &N]() {
    return Centroid{points[static_cast<int>(math::random_num::cont::Uniform(0, N))], 0.0, 0.0, 0};
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

      if (geometry::Point{ct.mean_x, ct.mean_y} == ct.p) { converge++; }

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

/////////////////////////////////////////////
/// KNN
/////////////////////////////////////////////

// For comparing distances
struct LPointDistComp {
  bool operator()(const LabeledPoint& p1, const LabeledPoint& p2) const
  {
    return p1.dist < p2.dist;
  }
};

LabeledPoints KNearestNeighbor(const geometry::Points& unlabeled_data, LabeledPoints& labeled_data, const std::uint8_t& k)
{
  if (k > unlabeled_data.size() || k == 0 || unlabeled_data.empty() || labeled_data.empty()) {
    return LabeledPoints{};
  }

  std::set<std::string> labels;
  LabeledPoints ret_labeled;

  for (auto point : unlabeled_data) {

    for (auto& ld : labeled_data) {
      ld.dist = Distance(point, {ld.x, ld.y});
      labels.insert(ld.label);
    }

    std::sort(labeled_data.begin(), labeled_data.end(), LPointDistComp());
    std::string label_to_use;
    int max_count{0};

    for (const auto& label : labels) {
      int count = std::count_if(labeled_data.begin(), labeled_data.begin() + k, [&label](const LabeledPoint& lp) {
        return lp.label == label;
      });

      if (count > max_count) {
        max_count = count;
        label_to_use = label;
      }
    }

    ret_labeled.emplace_back(LabeledPoint{point.x, point.y, 0.0, label_to_use});
  }

  return ret_labeled;
}

}// namespace algo::data_mining