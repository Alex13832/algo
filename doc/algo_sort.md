Sorting algorithms
==============
Rather useless. These algorithms were implemented for learning purpose.

The algorithms are templates and should be easy to extend with new types.

|Algorithm|Can sort| Worst-case performance | Average performance |
|---|:---|:---:|:---:|
|`Bubble     `    |`unsigned, signed, double, std::string`       |![e](https://private.codecogs.com/gif.latex?n%5E2)                                                |![e](https://private.codecogs.com/gif.latex?n%5E2) |
|`Bucket     `    |`unsigned, signed, double`                    |![e](https://private.codecogs.com/gif.latex?n%5E2)                                                |![e](https://private.codecogs.com/gif.latex?O%5Cleft%20%28%20n%20&plus;%20%5Cfrac%7Bn%5E2%7D%7Bk%7D%20&plus;%20k%20%5Cright%20%29)|
|`Gnome      `    |`unsigned, signed, double, std::string`       |![e](https://private.codecogs.com/gif.latex?n%5E2)                                                |![e](https://private.codecogs.com/gif.latex?n%5E2)|
|`Heap       `    |`unsigned, signed, double, std::string`       |![e](https://private.codecogs.com/gif.latex?O%5Cleft%20%28%20n%20%5Clog%20n%20%5Cright%20%29)     |![e](https://private.codecogs.com/gif.latex?O%5Cleft%20%28%20n%20%5Clog%20n%20%5Cright%20%29) |
|`Insertion  `    |`unsigned, signed, double, std::string`       |![e](https://private.codecogs.com/gif.latex?n%5E2)                                                |![e](https://private.codecogs.com/gif.latex?n%5E2)|
|`Merge      `    |`unsigned, signed, double, std::string`       |![e](https://private.codecogs.com/gif.latex?O%5Cleft%20%28%20n%20%5Clog%20n%20%5Cright%20%29)     |![e](https://private.codecogs.com/gif.latex?O%5Cleft%20%28%20n%20%5Clog%20n%20%5Cright%20%29) |
|`Quick      `    |`unsigned, signed, double, std::string`       |![e](https://private.codecogs.com/gif.latex?n%5E2)                                                |![e](https://private.codecogs.com/gif.latex?O%5Cleft%20%28%20n%20%5Clog%20n%20%5Cright%20%29) |

### Usage
All sorting algorithms are used in the same manner, in this example the Merge sort algorithm will be demonstrated.

```cpp
#include <vector>

#include "algo.hpp"

using namespace std;

...

vector<int> numbers{1, 9, 10, 2, 1, 1, 3, 2, 1, 4, 40, 40, 1};
algo::sort::Merge(numbers);
```

### Experiment

Sort 50 000 integers and measure the execution time. Sorted from fastest to slowest. 

|Algorithm| Execution time [ms] (MacBook pro 2016)|
|---|---|
|`Heap       `    |`34.673` |
|`Quick      `    |`365.411` |
|`Merge      `    |`1013.26` |
|`Bucket     `    |`2539.16` |
|`Insertion  `    |`19924.5` |
|`Gnome      `    |`28286.9` |
|`Bubble     `    |`49086.7`|
