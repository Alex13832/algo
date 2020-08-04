Sequence algorithms
=======

The concept of sequence is a bit fuzzy. Shouldn't strings also be considered as sequnces? The algorithms in this section 
usually take a sequence of numbers e.g. ![2](https://private.codecogs.com/gif.latex?%5Csmall%20%5Cleft%20%5C%7B1%2C%202%20%2C3%2C%20%5Cdots%20%5Cright%20%5C%7D). 

## Longest increasing subsequence

```cpp
std::vector<T> LongestIncreasingSub(const std::vector<T>& seq);
```

Returns the sequence that is the longest increasing sub-sequence of `seq`. Assume that `seq` is 

![e](https://private.codecogs.com/gif.latex?%5Clarge%20%5Cleft%20%5C%7B2%2C3%2C%201%2C%202%20%2C3%2C4%20%2C3%2C2%20%5Cright%20%5C%7D)

`LongestIncreasingSub` will then return

![e](https://private.codecogs.com/gif.latex?%5Clarge%20%5Cleft%20%5C%7B1%2C%202%20%2C3%2C%204%20%5Cright%20%5C%7D).

### Usage
```cpp
#include <vector>

#include "algo.hpp"

using namespace algo::sequence;
using namespace std;

...

vector<int> in{1, 2, 3, 4, 5, 6, 5, 1, 2, 3, 4, 5, 6, 7, 8, 1};
vector<int> out{LongestIncreasingSub(in)}; // {1, 2, 3, 4, 5, 6, 7, 8}
```

## Max sub-array
```cpp
T MaxSubarray(const std::vector<T>& vec);
```
Returns the largest sum of any continuous subarray in `vec`.

If `vec` is equal to

![e](https://private.codecogs.com/gif.latex?%5Clarge%20%5Cleft%20%5C%7B5%2C%204%2C%201%2C%202%2C%203%2C%204%20%5Cright%20%5C%7D)

then `MaxSubarray` will return 10 since

![e](https://private.codecogs.com/gif.latex?%5Clarge%20%5Cleft%20%5C%7B1%2C%202%2C%203%2C%204%20%5Cright%20%5C%7D)

is the longest increasing subarray with sum 10.

### Usage
```cpp
#include <vector>

#include "algo.hpp"

using namespace algo::sequence;
using namespace std;

...

vector<int> vec{5, 4, 1, 2, 3, 4};
int max_sum{MaxSubarray(vec)}; // 10
```
