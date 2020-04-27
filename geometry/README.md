Computational Geometry
===================================

## Closest Pair of Points
Finds the closest pair of points of some input set of points.


## Quickhull Algorithm
Finds the set of points that constructs the convex hull of some input data set of points.

[Quickhull, Wikipedia](https://en.wikipedia.org/wiki/Quickhull)

[Convex hull, Wikipedia](https://en.wikipedia.org/wiki/Convex_hull)

### Usage
```cpp
Points points{{0.15348, 0.355506},
            {0.2904, 0.354303},
            {0.156568, 0.220757},
            {0.292459, 0.224367},
            {0.223484, 0.291741}};

Points qh{ConvexHull(points)};
```

### Example
The example in `examples/geometry/qhull_example.cpp` outputs the following data shown in the image below. 
Note that the example does not plot it.

![PageRank](images/convexhull.png)

## Triangulation
This algorithm finds a triangulation of some input set of points.
See the example below.
