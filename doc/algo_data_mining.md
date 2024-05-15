Datum mining algorithms
===============

# Clustering algorithms

## K-Means Clustering

```cpp
std::vector<Datum> data{{1.1, 1.0}, {1.2, 1.1}, ...};
Cluster cluster{data};
size_t nbr_clusters{2};
auto clusters = cluster.KMeans(norms::Euclidean(), nbr_clusters);
```

Returns a list of integers that indicates which cluster each point belongs to.
A cluster index may be found at the same position in `data` and `clusters`.

KMeans can handle N dimensions.

### Examples

![Kmeans1](images/kmeans_1.png) ![Kmeans2](images/kmeans_2.png)

## DBSCAN

> Density-based spatial clustering of applications with noise (DBSCAN) is a data clustering algorithm [...]. It is a
> density-based clustering non-parametric algorithm: given a set of data in some space, it groups together data
> that are closely packed together (data with many nearby neighbors), marking as outliers data that lie alone in
> low-density regions.

```cpp
std::vector<Datum> data{{0.0428843, 0.967891}, {0.0418432, 0.943829}, ...;

// Min distance to neighbour data  
double epsiolon{0.2};
// Min number of data in a cluster
size_t min_data_in_cluster{3};

Cluster cluster{data};
auto clusters = cluster.DbScan(norms::Euclidean(), epsilon, min_data_in_cluster);
```

Returns a list of integers that indicates which cluster each point belongs to.
Noise is indicated with -1, which means, a cluster for that point was not found.

### Examples

![DBSCSAN-four-clusters](images/dbscan1.png) ![DBSCSAN-four-clusters](images/dbscan2.png)

![DBSCSAN-four-clusters](images/dbscan3.png) ![DBSCSAN-four-clusters](images/dbscan4.png)

# Classification algorithms

## K-nearest neighbours

```cpp
// Classify these, works with 1D ... ND
std::vector<Datum> unknown{{0.5}, {0.4}, {0.3}, {0.8}, {0.9}, {0.4},
                             {6.1}, {6.0}, {5.9}, {5.8}, {5.6}, {5.3}};

// Datum already known
std::vector<int> known_labels{2, 2, 2, 2, 2, 1, 1, 1, 1, 1};
std::vector<Datum> known_data{{5.11}, {6.14}, {4.95}, {7.45}, {5.67},
                              {0.33}, {0.39}, {0.45}, {0.66}, {0.57}};

Classifier classifier{unknown};
// How many neighbours to compare an unknown point with.
size_t nbr_neighbours{2};
auto classified = classifier.KNearestNeighbour(norms::Euclidean(),
                                               known_data, known_labels,
                                               nbr_neighbours);
```

Returns a list of classified labels for each point in `unknown`.
The algorithm needs a set of already known data and labels.

### Examples

`k = 5`.

![Knn-four-clusters](images/knn_in1.png) ![Knn-four-clusters](images/knn_out1.png)

![Knn-four-clusters](images/knn_in2.png) ![Knn-four-clusters](images/knn_out2.png)


