Puzzle solving algorithms
=====================
## Sudoku solver

```cpp
Grid Solve(const Grid& grid); 
```
Takes an unsolved Sudoku puzzle and returns the result. Empty cells are marked as zero in the input.

 
### Usage
```cpp
#include "algo.hpp"

...  

Grid grid{{{0, 0, 2, 1, 0, 0, 0, 0, 9},
           {0, 1, 0, 0, 8, 0, 0, 6, 0},
           {0, 0, 3, 0, 0, 0, 0, 0, 7},
           {9, 0, 0, 0, 0, 0, 7, 0, 0},
           {0, 6, 0, 0, 7, 0, 0, 4, 0},
           {0, 0, 4, 0, 0, 0, 0, 0, 8},
           {2, 0, 0, 0, 0, 0, 5, 0, 0},
           {0, 4, 0, 0, 3, 0, 0, 1, 0},
           {8, 0, 0, 0, 0, 9, 2, 0, 0}}};

  Grid solved{algo::puzzle::sudoku::Solve(grid)};
```
