Data mining algorithms
===============

## Data structures 

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


