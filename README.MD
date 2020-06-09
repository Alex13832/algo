Algo
===============================
This repository contains implementations of various known algorithms from selected fields of algorithm design in computer science, 
mathematics, data mining and etc. A not so unrealistic goal is to have the source code 100% unit tested and a 100% code coverage. 


# Constraints

The algorithms are implemented **only** using the C++ standard library.

The examples in `examples/` may use additional libraries but should not be required when building the library itself.

# Resources

### Data
For generating and plotting data, the [Orange](https://orange.biolab.si) data mining tool is used. It's super easy to 
output a data set in csv format to play with. The result of the C++ algorithms may then be plotted with the 
same tool. Not a single line of code.

### Unit tests
The C++ code is tested with the [Google Test](https://github.com/google/googletest) framework.

# A brief overview

## Puzzle

### Sudoku solver

```cpp
Grid Solve(const Grid& grid); 
```

This algorithm needs very little explanation. It solves a Sudoku puzzle! There's a `9x9` structure `Grid` that will contain 
the puzzle. A `0` is an empty cell.
 
Example:
```cpp
using namespace algo::puzzle::sudoku;

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

  Grid solved{Solve(grid)};
```
