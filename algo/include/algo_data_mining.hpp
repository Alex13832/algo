///
/// \brief Source file for data mining algorithms.
/// \author alex011235
/// \date 2020-04-30
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
/// Change list:
/// 2015-08-14 KNN
/// 2015-08-16 K-means
/// 2020-07-19 DBSCAN
/// 2022-12-28 Make algorithms handle multi dimensional data.
///

#pragma once

#include <cstddef>
#include <functional>
#include <vector>

namespace algo::data_mining {

/// Could be ANY kind of data, 1D, 2D, ND, feature-vectors, R-G-B values etc.
using Datum = std::vector<double>;

namespace norms {

// All functions work for N dimensions.

/// \brief Returns a function for computing L1, Manhattan or Taxicab norm.
/// \return L1 Norm function.
std::function<double(Datum, Datum)> Manhattan();

/// \brief Returns a function for computing L2, Euclidean norm.
/// \return L2 Norm function.
std::function<double(Datum, Datum)> Euclidean();

}  // namespace norms

class Miner {
 protected:
  explicit Miner(const std::vector<Datum>& data)
      : data_{data}, size_{data.size()} {};

  std::vector<Datum> data_;
  size_t size_;
};

class Cluster : public Miner {
 public:
  explicit Cluster(const std::vector<Datum>& data) : Miner(data){};

  /// \brief Runs the KMeans algorithm and returns a vector of int,
  /// representing each datum's cluster index.
  /// \details This algorithm does not guarantee to find the optimum result.
  /// It could be good to run KMeans several times.
  /// \param norm_func Norm function, such as Euclidean norm. Can take
  /// predefined or custom made function.
  /// \param k Number of clusters.
  /// \return A vector of cluster indices.
  std::vector<int> KMeans(const std::function<double(Datum, Datum)>& norm_func,
                          size_t k) const;

  /// \brief Runs the DBSCAN algorithm and returns a vector of labels
  /// representing each datums's cluster index.
  /// \param norm_func Norm function, such as Euclidean norm. Can take
  /// predefined or custom made function.
  /// \param eps The maximum distance between two neighbor data.
  /// \param min_nbr The minimum number of neighbors within the distance eps
  /// that a datum must have.
  /// \return A vector of cluster indices.
  std::vector<int> DbScan(const std::function<double(Datum, Datum)>& norm_func,
                          double eps, size_t min_nbr) const;
};

class Classifier : public Miner {
 public:
  explicit Classifier(const std::vector<Datum>& data) : Miner(data){};

  /// \brief Runs the K nearest neighbour (KNN) algorithm and returns a
  /// vector of int, representing each datum's label.
  /// \param norm_func Norm function, such as Euclidean norm. Can take
  /// predefined or custom made function.
  /// \param known_data Data that belong to a known label in known_labels.
  /// \param known_labels Known labels for known_data.
  /// \param k Number of neighbours to check.
  /// \return A vector of labels.
  std::vector<int> KNearestNeighbour(
      const std::function<double(Datum, Datum)>& norm_func,
      const std::vector<Datum>& known_data,
      const std::vector<int>& known_labels, size_t k) const;
};

}  // namespace algo::data_mining
