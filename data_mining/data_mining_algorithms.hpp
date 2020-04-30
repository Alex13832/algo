///
/// \brief Source file for data mining algorithms.
/// \author alex011235
/// \date 2020-04-30
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2015-08-16 K-means
///

#ifndef ALGORITHM_DATA_MINING_DATA_MINING_ALGORITHMS_HPP_
#define ALGORITHM_DATA_MINING_DATA_MINING_ALGORITHMS_HPP_

#include <vector>

namespace algo::data_mining {

struct Point {
  double x, y;
  bool operator==(const Point& p) const
  {
    return x == p.x && y == p.y;
  }
};

struct Centroid {
  Point p;
  double mean_x, mean_y;
  size_t size;
};

using Centroids = std::vector<Centroid>;
using Points = std::vector<Point>;
using Clusters = std::vector<Points>;

/////////////////////////////////////////////
/// K-means
/////////////////////////////////////////////

/// \brief Returns the clusters of K-means. Each cluster i in 1...i...k contains a set of points.
/// \param k Number of clusters.
/// \return Clusters. If k is greated the points.size() it will return an empty object.
/// \link <a href="https://en.wikipedia.org/wiki/K-means_clustering">K-means, Wikipedia.</a>
Clusters KMeans(Points points, const std::int8_t& k);

}// namespace algo::data_mining

#endif//ALGORITHM_DATA_MINING_DATA_MINING_ALGORITHMS_HPP_
