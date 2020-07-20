Data mining algorithms
===============

## Data structures 

|Data structure| Description | Example |
|:---|:---|:---|
|`Centroid`|Describes a centre of a cluster of points. ||
|`Centroids`|A list of centroids.||
|`Clusters`|A list of a list of data points for a cluster.||
|`LabeledPoint`|A data point with label.| `LabeledPoint p{1.0, 1.0, 2.0, "Label"};`|
|`LabeledPoints`|A list of labeled points.||

## K-Means Clustering

```cpp
Clusters KMeans(geometry::Points points, const std::int8_t& k);
```
Outputs `k` clusters. The input 2D-points in `points` will be clustered based on the nearest cluster centroid, using the Euclidean distance.

### Usage
Namespace(s) omitted. 
```cpp
#include <algo_data_mining.hpp>

using namespace algo::data_mining;
using namespace algo::geometry;

...

Points points{{0.212603, 0.553522},
              {0.194965, 0.527275},
              ...,
              {0.220029, 0.524992},
              {0.211675, 0.536404}};

Clusters clusters{KMeans(points, 3)};
```

### Examples
![Kmeans1](images/kmeans_1.png) ![Kmeans2](images/kmeans_2.png)

## K-nearest neighbors

```cpp
LabeledPoints KNearestNeighbor(const geometry::Points& unlabeled_data, LabeledPoints& labeled_data, const std::uint8_t& k);
```

Labels the points in `unlabeled_data` based on the `k` nearest neighbors in `labeled_data`. 


### Usage
Namespace(s) omitted.
 
```cpp
#include <algo_data_mining.hpp>

using namespace algo::data_mining;
using namespace algo::geometry;

...

Points unlabeled_data{
  {0.186546, 0.811486},// C1
  {0.266705, 0.872845},// C1
  ...,
  {0.660214, 0.214742},// C2
  {0.63523, 0.433708}  // C2
};

LabeledPoints labeled_points{
  {0.199039, 0.888485, 0.0, "C1"},
  {0.125126, 0.860814, 0.0, "C1"},
  ...,
  {0.632107, 0.296553, 0.0, "C2"},
  {0.539455, 0.348287, 0.0, "C2"}};

LabeledPoints classified{KNearestNeighbor(unlabeled_data, labeled_points, 2)};
```

### Examples
 `k = 5`.

![Knn-four-clusters](images/knn_in1.png) ![Knn-four-clusters](images/knn_out1.png)

![Knn-four-clusters](images/knn_in2.png) ![Knn-four-clusters](images/knn_out2.png)


## DBSCAN
>Density-based spatial clustering of applications with noise (DBSCAN) is a data clustering algorithm [...]. It is a 
>density-based clustering non-parametric algorithm: given a set of points in some space, it groups together points 
>that are closely packed together (points with many nearby neighbors), marking as outliers points that lie alone in 
>low-density regions.

```cpp
LabeledPoints DBSCAN(const geometry::Points& points, const DistFunc& dist_func, const float& eps, const int& min_pts);
```

Returns a list of two-dimensional points with an assigned label. Label "0" is equal to noise, or outlier. If the
label is greater than "0" then it is the assigned cluster number.

### Usage
Namespace(s) omitted.

```cpp
#include <algo.hpp>

using namespace algo::data_mining;
using namespace algo::geometry;

...

Points pts{
  {0.0428843, 0.967891},
  {0.0418432, 0.943829},
  {0.0564176, 0.928188},
  {0.0751562, 0.937813},
  {0.0720331, 0.963079},
  {0.0616228, 0.970297},
  {0.0564176, 0.953454},
  {0.0886895, 0.952251},
  {0.0793203, 0.982328},
  {0.0605818, 0.984735},
  {0.032474, 0.95586},
  {0.871543, 0.104055},
  {0.862174, 0.081196},
  {0.867379, 0.0547275},
  {0.903815, 0.0619462},
  {0.900692, 0.0908209},
  {0.889241, 0.0787898},
  {0.890282, 0.116086},
  {0.911102, 0.0884147},
  {0.885077, 0.05954},
  {0.0907716, 0.0980396},
  {0.917348, 0.972703}};

LabeledPoints lpts{DBSCAN(pts, DistFunc::Euclidean, 0.2, 3)};
```

### Examples

`DBSCAN(points, DistFunc::Euclidean, 0.1, 50)` 

![DBSCSAN-four-clusters](images/dbscan1.png) ![DBSCSAN-four-clusters](images/dbscan2.png)

![DBSCSAN-four-clusters](images/dbscan3.png) ![DBSCSAN-four-clusters](images/dbscan4.png)