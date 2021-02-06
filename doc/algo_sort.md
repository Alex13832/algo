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

Sort 50 000 integers and measure the execution time.

|Algorithm|Execution time [ms]||
|---|---|---|
|| MacBook pro 2016| MacBook Air M1 2020 |
|`Heap       `    |`34.7` | `1.8` |
|`Quick      `    |`365.4` | `3.3` |
|`Merge      `    |`1013.3` | `55.3` |
|`Bucket     `    |`2539.2` | `16.5` |
|`Insertion  `    |`19924.5` | `133.1` |
|`Gnome      `    |`28286.9` | `181.9` |
|`Bubble     `    |`49086.7`| `303.7` |
