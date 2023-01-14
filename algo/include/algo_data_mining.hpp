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

#ifndef ALGORITHM_DATA_MINING_DATA_MINING_ALGORITHMS_HPP_
#define ALGORITHM_DATA_MINING_DATA_MINING_ALGORITHMS_HPP_

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "algo_geometry.hpp"

namespace algo::data_mining {

/// Could be ANY kind of data, 1D, 2D, ND, feature-vectors, R-G-B values etc.
using Point = std::vector<double>;

namespace norms {

// All functions work for N dimensions.

/// \brief Returns a function for computing L1, Manhattan or Taxicab norm.
/// \return L1 Norm function.
std::function<double(Point, Point)> Manhattan();

/// \brief Returns a function for computing L2, Euclidean norm.
/// \return L2 Norm function.
std::function<double(Point, Point)> Euclidean();

}// namespace norms

class Miner {
 protected:
  explicit Miner(const std::vector<Point>& points)
      : points_{points},
        size_{points.size()} {};

  std::vector<Point> points_;
  size_t size_;
};

class Cluster : public Miner {

 public:
  explicit Cluster(const std::vector<Point>& points) : Miner(points){};

  /// \brief Runs the KMeans algorithm and returns a vector of int,
  /// representing each point's cluster index.
  /// \details This algorithm does not guarantee to find the optimum result.
  /// It could be good to run KMeans several times.
  /// \param norm_func Norm function, such as Euclidean norm. Can take
  /// predefined or custom made function.
  /// \param k Number of clusters.
  /// \return A vector of cluster indices.
  std::vector<int> KMeans(const std::function<double(Point, Point)>& norm_func,
                          size_t k) const;

  /// \brief Runs the DBSCAN algorithm and returns a vector of labels
  /// representing each point's cluster index.
  /// \param norm_func Norm function, such as Euclidean norm. Can take
  /// predefined or custom made function.
  /// \param eps The maximum distance between two neighbor points.
  /// \param min_pts The minimum number of neighbors within the distance eps
  /// that a point must have.
  /// \return A vector of cluster indices.
  std::vector<int> DbScan(const std::function<double(Point, Point)>& norm_func,
                          double eps, size_t min_points) const;
};

class Classifier : public Miner {
 public:
  explicit Classifier(const std::vector<Point>& points) : Miner(points){};

  /// \brief Runs the K nearest neighbour (KNN) algorithm and returns a
  /// vector of int, representing each point's label.
  /// \param norm_func Norm function, such as Euclidean norm. Can take
  /// predefined or custom made function.
  /// \param known_points Points that belong to a known label in known_labels.
  /// \param known_labels Known labels for known_points.
  /// \param k Number of neighbours to check.
  /// \return A vector of labels.
  std::vector<int> KNearestNeighbour(
      const std::function<double(Point, Point)>& norm_func,
      const std::vector<Point>& known_points,
      const std::vector<int>& known_labels, size_t k) const;
};

}// namespace algo::data_mining

#endif//ALGORITHM_DATA_MINING_DATA_MINING_ALGORITHMS_HPP_
