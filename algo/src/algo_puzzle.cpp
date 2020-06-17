///
/// \brief Source file for puzzle algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include "algo_puzzle.hpp"

/////////////////////////////////////////////
/// Sudoku
/////////////////////////////////////////////

namespace algo::puzzle::sudoku {

namespace {

/// \brief Checks if a row is valid.
/// \param grid The grid to check.
/// \param row The row number.
/// \param num The number to compare.
/// \return True if valid, otherwise false.
constexpr auto RowValid = [](const Grid& grid, const int& row, const int& num) {
  for (size_t i = 0; i < grid_size; ++i) {
    if (grid[row][i] == num) {
      return false;
    }
  }
  return true;
};

/// \brief Checks if a column is valid.
/// \param grid The grid to check.
/// \param col The column number.
/// \param num The number to compare.
/// \return True if valid, otherwise false.
constexpr auto ColValid = [](const Grid& grid, const int& col, const int& num) {
  for (size_t i = 0; i < grid_size; ++i) {
    if (grid[i][col] == num) {
      return false;
    }
  }
  return true;
};

/// \brief Checks if a 3x3 cell is valid.
/// \param grid The grid to check.
/// \param row The column number.
/// \param col The row number.
/// \param num The number to compare.
/// \return True if valid, otherwise false.
constexpr auto CellValid = [](Grid grid, int row, int col, int num) {
  int r1{row - row % 3};
  int r2{r1 + 3};
  int c1{col - col % 3};
  int c2{c1 + 3};

  for (int i = r1; i < r2; ++i) {
    for (int j = c1; j < c2; ++j) {
      if (grid[i][j] == num) {
        return false;
      }
    }
  }
  return true;
};

/// \brief Solves the Sudoku puzzle recursively, and iteratively, starting from the top left corner.
/// \param grid The grid containing the puzzle.
/// \param x Column number.
/// \param y Row number
/// \return
bool SolvePriv(Grid& grid, int x, int y)
{
  while (x < grid_size && grid[x][y] != 0) {
    y++;
    if (y == grid_size) {
      x++;
      y = 0;
    }
  }
  if (x == grid_size) {
    return true;
  }

  for (size_t i = 1; i < grid_size + 1; i++) {
    if (RowValid(grid, x, i) && ColValid(grid, y, i) && CellValid(grid, x, y, i)) {
      grid[x][y] = i;

      if (SolvePriv(grid, x, y)) {
        return true;
      }
    }
  }

  grid[x][y] = 0;
  return false;
}

}//namespace

Grid Solve(const Grid& grid)
{
  Grid ret{grid};
  bool solved{SolvePriv(ret, 0, 0)};

  if (solved) {
    return ret;
  }

  return grid;
}

}// namespace algo::puzzle::sudoku
