///
/// \brief Source file for data mining algorithms.
/// \author alex011235
/// \date 2020-04-30
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_data_mining.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <queue>
#include <set>

#include "algo_math.hpp"

namespace algo::data_mining {

namespace {
constexpr double kDblMax{1.79769e+308};
// Euclidean distance
constexpr auto Dist2 = [](const geometry::Point& p1, const geometry::Point& p2) {
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
};

}// namespace

/////////////////////////////////////////////
/// K-means
/////////////////////////////////////////////

Clusters KMeans(geometry::Points points, const std::int8_t& k)
{
  if (k > static_cast<int>(points.size()) || k == 0 || points.empty()) {
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
        double dist_curr{Dist2(ct.p, pt)};

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
      ct = {{ct.mean_x, ct.mean_y}, 0, 0.0, 0};
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
      double dist_curr{Dist2(ct.p, pt)};

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

namespace {
// For comparing distances
struct LPointDistComp {
  bool operator()(const LabeledPoint& p1, const LabeledPoint& p2) const
  {
    return p1.dist < p2.dist;
  }
};
}//namespace

LabeledPoints KNearestNeighbor(const geometry::Points& unlabeled_data, LabeledPoints& labeled_data, const std::uint8_t& k)
{
  if (k > unlabeled_data.size() || k == 0 || unlabeled_data.empty() || labeled_data.empty()) {
    return LabeledPoints{};
  }

  std::set<std::string> labels;
  LabeledPoints ret_labeled;

  for (auto point : unlabeled_data) {

    for (auto& ld : labeled_data) {
      ld.dist = Dist2(point, {ld.x, ld.y});
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

/////////////////////////////////////////////
/// DBSCAN
/////////////////////////////////////////////

namespace {
constexpr auto Dist = [](DistFunc dist_func, const geometry::Point& pt1, const geometry::Point& pt2) {
  if (dist_func == DistFunc::Manhattan) {
    return std::abs(std::abs(pt1.x) + std::abs(pt1.y) - std::abs(pt2.x) + std::abs(pt2.y));
  }
  if (dist_func == DistFunc::Euclidean) {
    return Dist2(pt1, pt2);
  }
  return 0.0;
};

struct Neighbor {
  LabeledPoint pt;
  int idx;
};

using Neighbors = std::queue<Neighbor>;

/// \brief Finds the neighbours of pt in lpts that are within eps distance. Skips itself (pt) in the result.
/// \param lpts All the points to scan for neighbors.
/// \param dist_func The distance functions, e.g. L1, L2.
/// \param pt The main point that is the "center" when looking for neighbors.
/// \param eps The maximum distance between two neighbors.
/// \param skip_idx The index of pt in lpts, so it can be skipped.
/// \return All the quialified neighbors of pt in lpts.
Neighbors RangeQuery(const LabeledPoints& lpts, const DistFunc& dist_func, const LabeledPoint& pt, const double& eps)
{
  Neighbors neighbors;
  for (size_t idx = 0; idx < lpts.size(); idx++) {
    double dist{Dist(dist_func, {lpts[idx].x, lpts[idx].y}, {pt.x, pt.y})};
    if (dist < eps) {
      neighbors.push(Neighbor{lpts[idx], static_cast<int>(idx)});
    }
  }
  return neighbors;
}
}//namespace

LabeledPoints DBSCAN(const geometry::Points& points, const DistFunc& dist_func, const double& eps, const int& min_pts)
{
  LabeledPoints lpts;
  if (static_cast<size_t>(min_pts) >= points.size() || min_pts == 0 || points.empty() || eps <= 0.0) {
    return lpts;
  }
  for (const auto& pt : points) {
    lpts.emplace_back(LabeledPoint{pt.x, pt.y, 0.0, "undef"});
  }
  int cluster_count{0};
  // DBSCAN algorithm
  for (size_t idx = 0; idx < lpts.size(); idx++) {
    if (lpts[idx].label != "undef") {
      continue;
    }

    Neighbors neighbors{RangeQuery(lpts, dist_func, lpts[idx], eps)};
    if (neighbors.size() < static_cast<size_t>(min_pts)) {
      lpts[idx].label = "0";// Noise
      continue;
    }
    cluster_count++;
    lpts[idx].label = std::to_string(cluster_count);

    while (!neighbors.empty()) {
      Neighbor q{neighbors.front()};
      neighbors.pop();

      if (q.pt.label == "0") {// Noise
        lpts[q.idx].label = std::to_string(cluster_count);
      }
      if (q.pt.label == "undef") {
        lpts[q.idx].label = std::to_string(cluster_count);
        Neighbors neighbors_n{RangeQuery(lpts, dist_func, q.pt, eps)};

        if (neighbors_n.size() >= static_cast<size_t>(min_pts)) {
          while (!neighbors_n.empty()) {
            Neighbor nb{neighbors_n.front()};
            neighbors_n.pop();
            lpts[nb.idx].label = std::to_string(cluster_count);
            neighbors.push(nb);
          }
        }
      }
    }
  }
  return lpts;
}

}// namespace algo::data_mining
