///
/// \brief Unit tests for puzzle algorithms.
/// \author alex011235
/// \date 2020-05-02
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <algorithm>

#include "gtest/gtest.h"
#include "include/algo.hpp"

using namespace std;
using namespace algo::puzzle::sudoku;

/////////////////////////////////////////////
/// Sudoku
/////////////////////////////////////////////

TEST(test_algo_puzzle, soduku_difficult)
{
  Grid correct{{{5, 8, 1, 6, 7, 2, 4, 3, 9},
                {7, 9, 2, 8, 4, 3, 6, 5, 1},
                {3, 6, 4, 5, 9, 1, 7, 8, 2},
                {4, 3, 8, 9, 5, 7, 2, 1, 6},
                {2, 5, 6, 1, 8, 4, 9, 7, 3},
                {1, 7, 9, 3, 2, 6, 8, 4, 5},
                {8, 4, 5, 2, 1, 9, 3, 6, 7},
                {9, 1, 3, 7, 6, 8, 5, 2, 4},
                {6, 2, 7, 4, 3, 5, 1, 9, 8}}};

  Grid grid{{{0, 0, 0, 6, 0, 0, 4, 0, 0},
             {7, 0, 0, 0, 0, 3, 6, 0, 0},
             {0, 0, 0, 0, 9, 1, 0, 8, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 5, 0, 1, 8, 0, 0, 0, 3},
             {0, 0, 0, 3, 0, 6, 0, 4, 5},
             {0, 4, 0, 2, 0, 0, 0, 6, 0},
             {9, 0, 3, 0, 0, 0, 0, 0, 0},
             {0, 2, 0, 0, 0, 0, 1, 0, 0}}};

  Grid solved{Solve(grid)};

  EXPECT_TRUE(equal(correct.begin(), correct.end(), solved.begin()));
}

TEST(test_algo_puzzle, sudoku_extreme)
{
  Grid correct{{{4, 5, 2, 1, 6, 7, 8, 3, 9},
                {7, 1, 9, 2, 8, 3, 4, 6, 5},
                {6, 8, 3, 4, 9, 5, 1, 2, 7},
                {9, 2, 8, 3, 4, 6, 7, 5, 1},
                {1, 6, 5, 9, 7, 8, 3, 4, 2},
                {3, 7, 4, 5, 2, 1, 6, 9, 8},
                {2, 9, 6, 7, 1, 4, 5, 8, 3},
                {5, 4, 7, 8, 3, 2, 9, 1, 6},
                {8, 3, 1, 6, 5, 9, 2, 7, 4}}};

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
  EXPECT_TRUE(equal(correct.begin(), correct.end(), solved.begin()));
}

TEST(test_algo_puzzle, sudoky_invalid_row)
{
  Grid grid{{{0, 0, 2, 1, 0, 0, 0, 0, 9},
             {0, 1, 0, 0, 8, 0, 0, 6, 0},
             {0, 3, 3, 0, 0, 0, 0, 0, 7},
             {9, 0, 0, 0, 0, 0, 7, 0, 0},
             {0, 6, 0, 0, 7, 0, 0, 4, 0},
             {0, 0, 4, 0, 0, 0, 0, 0, 8},
             {2, 0, 0, 0, 0, 0, 5, 0, 0},
             {0, 4, 0, 0, 3, 0, 0, 1, 0},
             {8, 0, 0, 0, 0, 9, 2, 0, 0}}};

  Grid solved{Solve(grid)};

  EXPECT_TRUE(equal(grid.begin(), grid.end(), solved.begin()));
}

TEST(test_algo_puzzle, sudoku_invalid_column)
{
  Grid grid{{{0, 0, 2, 1, 0, 9, 0, 0, 9},
             {0, 1, 0, 0, 8, 0, 0, 6, 0},
             {0, 0, 3, 0, 0, 0, 0, 0, 7},
             {9, 0, 0, 0, 0, 0, 7, 0, 0},
             {0, 6, 0, 0, 7, 0, 0, 4, 0},
             {0, 0, 4, 0, 0, 0, 0, 0, 8},
             {2, 0, 0, 0, 0, 0, 5, 0, 0},
             {0, 4, 0, 0, 3, 0, 0, 1, 0},
             {8, 0, 0, 0, 0, 9, 2, 0, 0}}};

  Grid solved{Solve(grid)};

  EXPECT_TRUE(equal(grid.begin(), grid.end(), solved.begin()));
}

TEST(test_algo_puzzle, sudokU_invalid_cell)
{
  Grid grid{{{0, 0, 2, 1, 0, 0, 6, 0, 9},
             {0, 1, 0, 0, 8, 0, 0, 6, 0},
             {0, 0, 3, 0, 0, 0, 0, 0, 7},
             {9, 0, 0, 0, 0, 0, 7, 0, 0},
             {0, 6, 0, 0, 7, 0, 0, 4, 0},
             {0, 0, 4, 0, 0, 0, 0, 0, 8},
             {2, 0, 0, 0, 0, 0, 5, 0, 0},
             {0, 4, 0, 0, 3, 0, 0, 1, 0},
             {8, 0, 0, 0, 0, 9, 2, 0, 0}}};

  Grid solved{Solve(grid)};

  EXPECT_TRUE(equal(grid.begin(), grid.end(), solved.begin()));
}
