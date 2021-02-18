Computational geometry
=============

## Data structures
Namespaces omitted

|Data structure| Description | Example |
|:---|:---|:---|
|`Point`        | 2D cartesian point.                   | `Point pt{1,2};` |
|`Points`       | For storing multiple points.          | `Points pts_{{1,1},...,{n,n}};` |
|`Edge`         | For connecting two points.            | `Edge line{Point{1,1}, Point{2,2}};`|
|`Edges`        | For storing multiple lines.           | `Edges lines{{{1,1},{2,2}},...,{{m,m},{n,n}}};`|
|`Polygon`      | An object constructed of `Points`     | `Polygon p{pts};` |
|`Rectangle`    | Constructed of x,y, width and height. | `Rectangle rect{0, 0, 1, 1};` |

## Closest pair of points

```cpp
Points ClosestPairOfPoints(const Points& points);
```
Returns the closest pair of points of the input set of 2D-points.

### Usage

```cpp
#include "algo.hpp"

using namespace algo::geometry;

...

Points points{{0.162745, 0.676737},
              {0.578652, 0.674331},
              {0.201865, 0.252038},
              {0.609536, 0.232788},
              {0.351138, 0.478224},
              {0.365551, 0.491458}};

Points closest{ClosestPairOfPoints(points)};
```

### Example

![Closest pair 1](images/closest_pair1.png) ![Closest pair 2](images/closest_pair2.png)

## Convex hull

The convex hull is the minimal polygon than contains all the input points. It's like a rubber band around the points.
This implementation is based on the quickhull algorithm.

[Quickhull, Wikipedia.](https://en.wikipedia.org/wiki/Quickhull)

```cpp
Points ConvexHull(Points points);
```

Returns the convex hull of `points`, the convex hull is in the returned `Points`.

### Usage

```cpp
#include "algo.hpp"

using namespace algo::geometry;

...

Points points{{0.15348, 0.355506},
              {0.2904, 0.354303},
              {0.156568, 0.220757},
              {0.292459, 0.224367},
              {0.223484, 0.291741}};

Points cp{ConvexHull(points)};
```

### Examples

![Convex hull example 1](images/convex_hull1.png) ![Convex hull example 2](images/convex_hull2.png)

## Minimum bounding box

```cpp
Points MinimumBoundingBox(Points points);
```

Returns the minimum bounding box of the input points. Note that it's not the same as bounding rectangle, which can be found by looking for the min and max coordinates of the input points. The minimum bounding box is the smallest enclosing rectangle around the input points, which means that the rectangle may be rotated.

This implementation is based on the concept of rotating calipers of a polygon. It starts by finding the convex hull of the input points and then iterates over each edge and rotates the polygon with the angle of the edge with respect to the y-axis and extracts the bounding rectangle each time. When all the rectangles are found, the one with smallest area is returned.

[Rotating calipers, Wikipedia.](https://en.wikipedia.org/wiki/Rotating_calipers)

### Usage

```cpp
#include "algo.hpp"

using namespace algo::geometry;

...

const Points pts{
  {0.416443, 0.33606},
  {0.660542, 0.594665},
  {0.493637, 0.804683},
  {0.282919, 0.607203},
  {0.467558, 0.604069}
};

Polygon mbbox{MinimumBoundingBox(pts)};
```

### Examples

Note that the axis should be adjusted when plotting, otherwise the resulting rectangle might look skew.

![mbbox1](images/mbbox1.png) ![mbbox1](images/mbbox2.png) ![mbbox1](images/mbbox3.png)

## Minimum enclosing circle

```cpp
Circle MinimumEnclosingCircle(Points& pts);
```

Returns the smallest circle around the points in `pts`.

[Smallest-circle problem](https://en.wikipedia.org/wiki/Smallest-circle_problem)

### Usage

```cpp
#include "algo.hpp"

using namespace algo::geometry;

...

Points pts{{5, -2},
           {-3, -2},
           {-2, 5},
           {1, 6},
           {0, 2}};

Circle circle{MinimumEnclosingCircle(pts)};
```

### Examples

![Mec1](images/mec1.png) ![Mec2](images/mec2.png)

![Mec3](images/mec3.png) ![Mec1](images/mec4.png)

## Triangulation of 2D-points

```cpp
Edges Triangulate(Points& pts_);
```

Triangulates the input points `pts_` and returns a set of pair of points in `Edges` where each pair connects two points with an edge.

### Usage

```cpp
#include "algo.hpp"

using namespace algo::geometry;

...

Points points{{0.112301, 0.440927},
              {0.339814, 0.723659},
              {0.614683, 0.516723},
              {0.414966, 0.294147}};

Edges lines{Triangulate(points)};
```

### Examples

![Triangulate in2](images/triangulate_out1.png) ![Triangulate in2](images/triangulate_out3.png)