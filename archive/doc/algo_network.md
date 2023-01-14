Network algorithms
=======

## PageRank
PageRank is an algorithm developed by Google and is a way to measure the importance of websites. The PageRank algorithm
implemented here is NOT what Google uses today, they use many algorithms to measure the importance of websites.
 This PageRank algorithm could perhaps be compared with the first version of Google's PageRank algorithm. The fundamental parts of PageRank
 might however be the same.
 
```c++
Arr PageRank(const Mat& W, const double& error, const double& damping = 0.85);
```
Returns a list of the ranks of each website in the input "web-matrix" `W`. The sum of the output is equal to one (summed probabilities).
The higher number in the output, the higher ranking of that website. 

`damping` is a concept that roughly means that a surfer eventually will stop clickling. [Wikipedia](https://en.wikipedia.org/wiki/PageRank)
describes it like this:
>The PageRank theory holds that an imaginary surfer who is randomly clicking on links will eventually stop clicking. 
>The probability, at any step, that the person will continue is a damping factor d. Various studies have tested different damping 
>factors, but it is generally assumed that the damping factor will be set around 0.85.

`error` is a threshold used in the PageRank algorihtm. The algorithm will continue until a computed L2-error is larger than `error`.

There is a function that can convert link counts of websites to a matrix with probabilities:

```c++
Mat MatTransition(const Mat& M, const Arr& deg);
```
Where `M` is the matrix with click counts, the content may look like this:

![mat](https://private.codecogs.com/gif.latex?%5Clarge%20%5Cbegin%7Bmatrix%7D%200%20%261%20%260%20%260%20%260%20%5C%5C%200%20%260%20%262%20%262%20%261%20%5C%5C%200%20%260%20%260%20%261%20%260%20%5C%5C%201%20%260%20%260%20%260%20%260%20%5C%5C%201%20%260%20%261%20%260%20%260%20%5Cend%7Bmatrix%7D)

There is one link from site 0 to site 1, two links from site 1 to 2 and so on.

`deg` is an array with the total number of links out from a site. For the matrix above, the content of `deg` will be:
 
 ![e](https://private.codecogs.com/gif.latex?%5Clarge%20%5Cleft%20%5B%201%2C5%2C1%2C1%2C2%20%5Cright%20%5D) .

### Usage and example
```c++
#include <vector>

#include "algo.hpp"

using namespace algo::network;
using namespace std;

...

Mat M{{0, 1, 0, 0, 0},
      {0, 0, 2, 2, 1},
      {0, 0, 0, 1, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 1, 0, 0}};

vector<int> deg{1, 5, 1, 1, 2};

Mat trans{(M, deg)};
Arr rank{PageRank(trans, 0.0001, 0.85)};

for (const auto& r: rank) {
  cout << r << " ";
}
cout << endl;
```

Output:
```text
0.250262 0.139853 0.139853 0.207724 0.262308
```