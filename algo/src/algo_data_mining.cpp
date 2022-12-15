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
#include <numeric>
#include <queue>
#include <set>

#include "algo_math.hpp"

namespace algo::data_mining {

// //////////////////////////////////////////
// MARK: Data structures

/// \brief Represents a centroid in  for K-Means.
struct Centroid {

  /// \brief Adds data to centroid mean.
  /// \param pt Data array.
  void AddToMean(const Point& pt)
  {
    if (mean_.empty()) {
      mean_.resize(pt.size());
    }
    std::transform(pt.begin(), pt.end(), mean_.begin(), mean_.begin(),
                   std::plus<>());
    size_++;
  }

  /// \brief Computes the mean.
  void ComputeMean()
  {
    if (size_ == 0) return;
    for (auto& pt : mean_) {
      pt /= static_cast<double>(size_);
    }
  }

  /// \brief Checks if mean is equal to point.
  /// \return true if equal.
  bool PointEqualToMean()
  {
    return std::equal(mean_.begin(), mean_.end(), point_.begin());
  }

  /// \brief Sets the point to the centroid's mean values.
  void SetPointToMean()
  {
    std::copy(mean_.begin(), mean_.end(), point_.begin());
    std::fill(mean_.begin(), mean_.end(), 0);
    size_ = 0;
  }

  Point point_;
  Point mean_;
  size_t size_{0};
};

// MARK: Norm functions

std::function<double(Point, Point)> norms::Manhattan()
{
  return [](Point p1, Point p2) {
    if (p1.size() != p2.size()) {
      return std::numeric_limits<double>::max();
    }
    double abs_sum{0.0};
    for (size_t i = 0; i < p1.size(); i++) {
      abs_sum += std::abs(p1.at(i) - p2.at(i));
    }
    return abs_sum;
  };
}

std::function<double(Point, Point)> norms::Euclidean()
{
  return [](Point p1, Point p2) {
    if (p1.size() != p2.size()) {
      return std::numeric_limits<double>::max();
    }
    double sq_sum{0.0};
    for (size_t i = 0; i < p1.size(); i++) {
      sq_sum += std::pow(p1.at(i) - p2.at(i), 2);
    }
    return std::sqrt(sq_sum);
  };
}

// //////////////////////////////////////////
// MARK: KMeans

namespace {

/// \brief Generates random centroids for the KMeans algorithm.
/// \param points To sample random points from.
/// \param num_centroids The number of centroids to generate.
/// \return num_centroids Centroids.
std::vector<Centroid> GenerateRandCentroids(const std::vector<Point> points,
                                            size_t num_centroids)
{
  std::vector<Centroid> ctr(num_centroids);
  auto N = points.size();
  // Initialize random centroids
  std::generate(ctr.begin(), ctr.end(), [&]() {
    const auto num_d = static_cast<double>(N);
    const auto random_index =
        static_cast<int>(math::random_num::cont::Uniform(0, num_d));
    return Centroid{points.at(random_index), {}, 0};
  });

  return ctr;
}

/// \brief Checks which centroid is closest to point.
/// \param point The point of interest.
/// \param centroids The Centroids.
/// \param norm_func Norm function.
/// \return The index that indicates which centroid is closest to point.
int FindClosestCentroid(const Point& point,
                        const std::vector<Centroid>& centroids,
                        const std::function<double(Point, Point)>& norm_func)
{
  auto dist_min = std::numeric_limits<double>::max();
  int cluster{0};
  int min_cluster{0};

  for (auto& ct : centroids) {
    auto dist_curr = norm_func(ct.point_, point);

    if (dist_curr < dist_min) {
      dist_min = dist_curr;
      min_cluster = cluster;
    }
    cluster++;
  }

  return min_cluster;
}

/// \brief Assigns and index to each point in points to indicate which
/// centroid point belongs to.
/// \param points All points to assign indices for.
/// \param centroids Centroids to compare points with.
/// \param norm_func Norm function.
/// \return A vector of cluster indices.
std::vector<int> MakeClusters(
    const std::vector<Point>& points, const std::vector<Centroid>& centroids,
    const std::function<double(Point, Point)>& norm_func)
{
  std::vector<int> clusters;
  for (const auto& pt : points) {
    auto min_cluster = FindClosestCentroid(pt, centroids, norm_func);
    clusters.emplace_back(min_cluster);
  }
  return clusters;
}

}// namespace

std::vector<int> Cluster::KMeans(
    const std::function<double(Point, Point)>& norm_func, size_t k) const
{
  if (k >= size_ || k == 0) {
    return {};
  }
  auto centroids = GenerateRandCentroids(points_, k);
  size_t converge{0};

  while (converge != k) {
    converge = 0;

    // For each point, find the closest centroid.
    for (const auto& pt : points_) {
      auto centroid_index = FindClosestCentroid(pt, centroids, norm_func);
      centroids.at(centroid_index).AddToMean(pt);
    }

    // For each centroid, compute mean and check convergence.
    for (auto& centroid : centroids) {
      centroid.ComputeMean();
      if (centroid.PointEqualToMean()) converge++;
      centroid.SetPointToMean();
    }
  }
  return MakeClusters(points_, centroids, norm_func);
}

namespace {
struct LabeledPoint {
  size_t index{0}; ///< Index to a point in some vector.
  int label{-1};   ///< Label, an integer. No strings!
  double dist{0.0};///< Distance if needed.
};
}//namespace

// //////////////////////////////////////////
// MARK: DbScan

namespace {

constexpr int kUndefined{-2};
constexpr int kNoise{-1};

/// \brief Returns the indices for the points that are inside the distance <
/// eps from labeled_points.
/// \param norm_func For computing distance.
/// \param points Contains the points.
/// \param labeled_points Contains labels and indices.
/// \param labeled_point The main point of interest.
/// \param eps The maximum distance between two points for index inclusion.
/// \return Indices that fulfills description above.
std::queue<size_t> RangeQuery(
    const std::function<double(Point, Point)>& norm_func,
    const std::vector<Point>& points,
    const std::vector<LabeledPoint>& labeled_points, LabeledPoint labeled_point,
    double eps)
{
  std::queue<size_t> labels;
  for (size_t i = 0; i < labeled_points.size(); i++) {
    const auto idx_0 = labeled_point.index;
    const auto idx_1 = labeled_points.at(i).index;
    if (idx_0 == idx_1) continue;// Skip self.

    const auto distance = norm_func(points.at(idx_0), points.at(idx_1));
    if (distance < eps) labels.push(i);
  }
  return labels;
}

/// \brief Copies the indices from labeled points.
/// \param labeled_pts For each point, there's an index.
/// \return Indices.
std::vector<int> GetLabels(const std::vector<LabeledPoint>& labeled_pts)
{
  std::vector<int> labels;
  labels.reserve(labeled_pts.size());
  for (const auto& lp : labeled_pts)
    labels.emplace_back(lp.label);
  return labels;
}

}// namespace

std::vector<int> Cluster::DbScan(
    const std::function<double(Point, Point)>& norm_func, double eps,
    size_t min_points) const
{
  if ((min_points >= size_) || (min_points == 0) || points_.empty()
      || (eps <= 0.0))
  {
    return {};
  }
  std::vector<LabeledPoint> labeled_pts;
  labeled_pts.resize(size_);
  for (size_t i = 0; i < size_; i++) {
    labeled_pts.at(i) = LabeledPoint{i, kUndefined, 0.0};
  }
  int cluster_count{0};
  // DBSCAN algorithm
  for (size_t idx = 0; idx < labeled_pts.size(); idx++) {
    if (labeled_pts.at(idx).label != kUndefined) {
      continue;
    }
    auto neighbours =
        RangeQuery(norm_func, points_, labeled_pts, labeled_pts.at(idx), eps);

    if (neighbours.size() < min_points) {
      labeled_pts.at(idx).label = kNoise;
      continue;
    }
    cluster_count++;
    labeled_pts.at(idx).label = cluster_count;

    while (!neighbours.empty()) {
      auto& lpt = labeled_pts.at(neighbours.front());
      neighbours.pop();

      if (lpt.label == kNoise) {
        lpt.label = cluster_count;
      }
      if (lpt.label == kUndefined) {
        lpt.label = cluster_count;
        auto neighbours_n =
            RangeQuery(norm_func, points_, labeled_pts, lpt, eps);

        if (neighbours_n.size() >= min_points) {
          while (!neighbours_n.empty()) {
            auto nb_idx = neighbours_n.front();
            neighbours_n.pop();
            labeled_pts.at(nb_idx).label = cluster_count;
            neighbours.push(nb_idx);
          }
        }
      }
    }
  }
  return GetLabels(labeled_pts);
}

// //////////////////////////////////////////
// MARK: KNN

std::vector<int> Classifier::KNearestNeighbour(
    const std::function<double(Point, Point)>& norm_func,
    const std::vector<Point>& known_points,
    const std::vector<int>& known_labels, size_t k) const
{
  if ((k > size_) || (k == 0) || known_points.empty() || known_labels.empty()
      || (known_points.size() != known_labels.size()))
  {
    return {};
  }

  std::vector<LabeledPoint> classified;
  for (size_t i = 0; i < known_points.size(); i++) {
    classified.emplace_back(LabeledPoint{i, known_labels.at(i), 0.0});
  }

  std::set<int> labels;
  std::vector<int> ret_labeled;

  for (const auto& point : points_) {

    for (auto& ld : classified) {
      ld.dist = norm_func(point, known_points.at(ld.index));
      labels.insert(ld.label);
    }
    std::sort(classified.begin(), classified.end(),
              [](auto p1, auto p2) { return p1.dist < p2.dist; });

    int label_to_use;
    long max_count{0L};

    for (const auto& label : labels) {
      auto count = std::count_if(
          classified.begin(), classified.begin() + static_cast<long>(k),
          [&label](const LabeledPoint& lp) { return lp.label == label; });

      if (count > max_count) {
        max_count = count;
        label_to_use = label;
      }
    }

    ret_labeled.emplace_back(label_to_use);
  }

  return ret_labeled;
}

}// namespace algo::data_mining
