Greedy algorithms
================
Several algorithms in this library may be considered as greedy. The reason that an algorithm ends up here is that it doesn't
have a clear category. For instance, Prim's algorithm for finding the minimum spanning tree in a graph has been placed in graph 
algorithms, since it's a graph algorithm. 

## Stable matching
>In mathematics, economics, and computer science, the stable marriage problem (also stable matching problem or SMP) is the 
>problem of finding a stable matching between two equally sized sets of elements given an ordering of preferences for each 
>element. [Wikipedia](https://en.wikipedia.org/wiki/Stable_marriage_problem)

The algorithm that finds the stable matching in this library is the [Gale-Shapley algorithm](https://en.wikipedia.org/wiki/Gale–Shapley_algorithm).

```cpp
std::vector<Match> StableMatching(Prefs men_pref, Prefs women_pref);
```

Returns a stable matching between `men_pref` and `women_pref`. This could generalized to any preferences, e.g. students'
 university prefences and the university student preferences and not only to men and women. Since the literature use
 men and women, this piece of code also does so.

An input of men's and women's preferences

![e](https://private.codecogs.com/gif.latex?%5Clarge%20%5Cbegin%7Bmatrix%7D%202%20%26%204%20%26%201%20%26%203%20%5C%5C%203%20%26%201%20%26%204%20%26%202%20%5C%5C%202%20%26%203%20%26%201%20%26%204%20%5C%5C%204%20%26%201%20%26%203%20%26%202%20%5Cend%7Bmatrix%7D) 

and

![e](https://private.codecogs.com/gif.latex?%5Clarge%20%5Cbegin%7Bmatrix%7D%202%20%26%201%20%26%204%20%26%203%20%5C%5C%204%20%26%203%20%26%201%20%26%202%20%5C%5C%201%20%26%204%20%26%203%20%26%202%20%5C%5C%202%20%26%201%20%26%204%20%26%203%20%5Cend%7Bmatrix%7D)  

respectively, where each line corresponds to one person's preferences, would result in the stable matching 

![e](https://private.codecogs.com/gif.latex?%5Clarge%20%5Cleft%20%5C%7B%20%281%2C4%29%2C%20%282%2C3%29%2C%20%283%2C2%29%2C%20%284%2C1%29%20%5Cright%20%5C%7D).

### Usage

```cpp
#include <algo_greedy.hpp>

using namespace algo::greedy;
using nameppace std;

...

Prefs mens{{2, 4, 1, 3},
           {3, 1, 4, 2},
           {2, 3, 1, 4},
           {4, 1, 3, 2}};

Prefs wmns{{2, 1, 4, 3},
           {4, 3, 1, 2},
           {1, 4, 3, 2},
           {2, 1, 4, 3}};

std::vector<Match> matches{StableMatching(mens, wmns)};
```

