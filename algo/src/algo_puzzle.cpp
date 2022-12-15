///
/// \brief Source file for puzzle algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include "algo_puzzle.hpp"

/////////////////////////////////////////////
/// Sudoku
/////////////////////////////////////////////

namespace algo::puzzle::sudoku {

namespace {

constexpr auto RowValid = [](const Grid& grid, int row, int num) {
  return std::none_of(grid[row].begin(), grid[row].end(),
                      [num](auto col) { return col == num; });
};

constexpr auto ColValid = [](const Grid& grid, int col, int num) {
  return std::none_of(grid.begin(), grid.end(),
                      [col, num](auto row) { return row[col] == num; });
};

constexpr auto CellValid = [](const Grid& grid, int row, int col, int num) {
  auto r1 = row - row % 3;
  auto r2 = r1 + 3;
  auto c1 = col - col % 3;
  auto c2 = c1 + 3;

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
  if (x == grid_size) return true;

  for (int i = 1; i < grid_size + 1; i++) {
    if (RowValid(grid, x, i) && ColValid(grid, y, i)
        && CellValid(grid, x, y, i))
    {
      grid[x][y] = i;

      if (SolvePriv(grid, x, y)) return true;
    }
  }

  grid[x][y] = 0;
  return false;
}

}//namespace

Grid Solve(const Grid& grid)
{
  Grid ret{grid};
  return SolvePriv(ret, 0, 0) ? ret : grid;
}

}// namespace algo::puzzle::sudoku
