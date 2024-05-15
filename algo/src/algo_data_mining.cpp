///
/// \brief Source file for data mining algorithms.
/// \author alex011235
/// \date 2020-04-30
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_data_mining.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <limits>
#include <queue>
#include <set>
#include <vector>

#include "algo_math.hpp"

namespace algo::data_mining {

// //////////////////////////////////////////
// MARK: Data structures

/// \brief Represents a centroid in  for K-Means.
struct Centroid {
  /// \brief Adds data to centroid mean.
  /// \param datum Data array.
  void AddToMean(const Datum& datum) {
    if (mean_.empty()) {
      mean_.resize(datum.size());
    }
    std::transform(datum.begin(), datum.end(), mean_.begin(), mean_.begin(),
                   std::plus<>());
    size_++;
  }

  /// \brief Computes the mean.
  void ComputeMean() {
    if (size_ == 0) return;
    for (auto& datum : mean_) {
      datum /= static_cast<double>(size_);
    }
  }

  /// \brief Checks if mean is equal to one datum.
  /// \return true if equal.
  bool DatumEqualToMean() {
    return std::equal(mean_.begin(), mean_.end(), datum_.begin());
  }

  /// \brief Sets the datum to the centroid's mean values.
  void SetDatumToMean() {
    std::copy(mean_.begin(), mean_.end(), datum_.begin());
    std::fill(mean_.begin(), mean_.end(), 0);
    size_ = 0;
  }

  Datum datum_;
  Datum mean_;
  size_t size_{0};
};

// MARK: Norm functions

std::function<double(Datum, Datum)> norms::Manhattan() {
  return [](Datum p1, Datum p2) {
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

std::function<double(Datum, Datum)> norms::Euclidean() {
  return [](Datum p1, Datum p2) {
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
/// \param data To sample random datum items from.
/// \param num_centroids The number of centroids to generate.
/// \return num_centroids Centroids.
std::vector<Centroid> GenerateRandCentroids(const std::vector<Datum> data,
                                            size_t num_centroids) {
  std::vector<Centroid> ctr(num_centroids);
  auto N = data.size();
  // Initialize random centroids
  std::generate(ctr.begin(), ctr.end(), [&]() {
    const auto num_d = static_cast<double>(N);
    const auto random_index =
        static_cast<int>(math::random_num::cont::Uniform(0, num_d));
    return Centroid{data.at(random_index), {}, 0};
  });

  return ctr;
}

/// \brief Checks which centroid is closest to the input datu,.
/// \param datum The datum of interest.
/// \param centroids The Centroids.
/// \param norm_func Norm function.
/// \return The index that indicates which centroid is closest to datum.
int FindClosestCentroid(const Datum& datum,
                        const std::vector<Centroid>& centroids,
                        const std::function<double(Datum, Datum)>& norm_func) {
  auto dist_min = std::numeric_limits<double>::max();
  int cluster{0};
  int min_cluster{0};

  for (const auto& ct : centroids) {
    auto dist_curr = norm_func(ct.datum_, datum);

    if (dist_curr < dist_min) {
      dist_min = dist_curr;
      min_cluster = cluster;
    }
    cluster++;
  }

  return min_cluster;
}

/// \brief Assigns and index to each datum in data to indicate which
/// centroid each datum belongs to.
/// \param data All data to assign indices for.
/// \param centroids Centroids to compare data with.
/// \param norm_func Norm function.
/// \return A vector of cluster indices.
std::vector<int> MakeClusters(
    const std::vector<Datum>& data, const std::vector<Centroid>& centroids,
    const std::function<double(Datum, Datum)>& norm_func) {
  std::vector<int> clusters;
  for (const auto& datum : data) {
    auto min_cluster = FindClosestCentroid(datum, centroids, norm_func);
    clusters.emplace_back(min_cluster);
  }
  return clusters;
}

}  // namespace

std::vector<int> Cluster::KMeans(
    const std::function<double(Datum, Datum)>& norm_func, size_t k) const {
  if (k >= size_ || k == 0) {
    return {};
  }
  auto centroids = GenerateRandCentroids(data_, k);
  size_t converge{0};

  while (converge != k) {
    converge = 0;

    // For each datum, find the closest centroid.
    for (const auto& datum : data_) {
      auto centroid_index = FindClosestCentroid(datum, centroids, norm_func);
      centroids.at(centroid_index).AddToMean(datum);
    }

    // For each centroid, compute mean and check convergence.
    for (auto& centroid : centroids) {
      centroid.ComputeMean();
      if (centroid.DatumEqualToMean()) converge++;
      centroid.SetDatumToMean();
    }
  }
  return MakeClusters(data_, centroids, norm_func);
}

namespace {
struct LabeledDatum {
  size_t index{0};   ///< Index to a datum in some vector.
  int label{-1};     ///< Label, an integer. No strings!
  double dist{0.0};  ///< Distance if needed.
};
}  // namespace

// //////////////////////////////////////////
// MARK: DbScan

namespace {

constexpr int kUndefined{-2};
constexpr int kNoise{-1};

/// \brief Returns the indices for the data that are inside the distance <
/// eps from labeled_data.
/// \param norm_func For computing distance.
/// \param data Contains the data.
/// \param labeled_data Contains labels and indices.
/// \param labeled_datum The main datum of interest.
/// \param eps The maximum distance between two data for index inclusion.
/// \return Indices that fulfills description above.
std::queue<size_t> RangeQuery(
    const std::function<double(Datum, Datum)>& norm_func,
    const std::vector<Datum>& data,
    const std::vector<LabeledDatum>& labeled_data, LabeledDatum labeled_datum,
    double eps) {
  std::queue<size_t> labels;
  for (size_t i = 0; i < labeled_data.size(); i++) {
    const auto idx_0 = labeled_datum.index;
    const auto idx_1 = labeled_data.at(i).index;
    if (idx_0 == idx_1) continue;  // Skip self.

    const auto distance = norm_func(data.at(idx_0), data.at(idx_1));
    if (distance < eps) labels.push(i);
  }
  return labels;
}

/// \brief Copies the indices from labeled_data.
/// \param labeled_data For each datum, there's an index.
/// \return Indices.
std::vector<int> GetLabels(const std::vector<LabeledDatum>& labeled_data) {
  std::vector<int> labels;
  labels.reserve(labeled_data.size());
  for (const auto& lp : labeled_data) labels.emplace_back(lp.label);
  return labels;
}

}  // namespace

std::vector<int> Cluster::DbScan(
    const std::function<double(Datum, Datum)>& norm_func, double eps,
    size_t min_nbr) const {
  if ((min_nbr >= size_) || (min_nbr == 0) || data_.empty() || (eps <= 0.0)) {
    return {};
  }
  std::vector<LabeledDatum> labeled_data;
  labeled_data.resize(size_);
  for (size_t i = 0; i < size_; i++) {
    labeled_data.at(i) = LabeledDatum{i, kUndefined, 0.0};
  }
  int cluster_count{0};
  // DBSCAN algorithm
  for (size_t idx = 0; idx < labeled_data.size(); idx++) {
    if (labeled_data.at(idx).label != kUndefined) {
      continue;
    }
    auto neighbours =
        RangeQuery(norm_func, data_, labeled_data, labeled_data.at(idx), eps);

    if (neighbours.size() < min_nbr) {
      labeled_data.at(idx).label = kNoise;
      continue;
    }
    cluster_count++;
    labeled_data.at(idx).label = cluster_count;

    while (!neighbours.empty()) {
      auto& labeled_datum = labeled_data.at(neighbours.front());
      neighbours.pop();

      if (labeled_datum.label == kNoise) {
        labeled_datum.label = cluster_count;
      }
      if (labeled_datum.label == kUndefined) {
        labeled_datum.label = cluster_count;
        auto neighbours_n =
            RangeQuery(norm_func, data_, labeled_data, labeled_datum, eps);

        if (neighbours_n.size() >= min_nbr) {
          while (!neighbours_n.empty()) {
            auto nb_idx = neighbours_n.front();
            neighbours_n.pop();
            labeled_data.at(nb_idx).label = cluster_count;
            neighbours.push(nb_idx);
          }
        }
      }
    }
  }
  return GetLabels(labeled_data);
}

// //////////////////////////////////////////
// MARK: KNN

std::vector<int> Classifier::KNearestNeighbour(
    const std::function<double(Datum, Datum)>& norm_func,
    const std::vector<Datum>& known_data, const std::vector<int>& known_labels,
    size_t k) const {
  if ((k > size_) || (k == 0) || known_data.empty() || known_labels.empty() ||
      (known_data.size() != known_labels.size())) {
    return {};
  }

  std::vector<LabeledDatum> classified;
  for (size_t i = 0; i < known_data.size(); i++) {
    classified.emplace_back(LabeledDatum{i, known_labels.at(i), 0.0});
  }

  std::set<int> labels;
  std::vector<int> ret_labeled;

  for (const auto& datum : data_) {
    for (auto& ld : classified) {
      ld.dist = norm_func(datum, known_data.at(ld.index));
      labels.insert(ld.label);
    }
    std::sort(classified.begin(), classified.end(),
              [](auto p1, auto p2) { return p1.dist < p2.dist; });

    int label_to_use;
    long max_count{0L};

    for (const auto& label : labels) {
      auto count = std::count_if(
          classified.begin(), classified.begin() + static_cast<long>(k),
          [&label](const LabeledDatum& lp) { return lp.label == label; });

      if (count > max_count) {
        max_count = count;
        label_to_use = label;
      }
    }

    ret_labeled.emplace_back(label_to_use);
  }

  return ret_labeled;
}

}  // namespace algo::data_mining
