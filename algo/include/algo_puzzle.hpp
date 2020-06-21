///
/// \brief Header for puzzle algorithms.
/// \author alex011235
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
/// Change list:
/// 2016-10-16 Sudoku backtracking algorithm
///

#ifndef ALGO_ALGO_INCLUDE_ALGO_PUZZLE_HPP_
#define ALGO_ALGO_INCLUDE_ALGO_PUZZLE_HPP_

#include <array>
#include <vector>

/////////////////////////////////////////////
/// Sudoku
/////////////////////////////////////////////

namespace algo::puzzle::sudoku {

namespace {
constexpr int grid_size{9};
}

using Grid = std::array<std::array<int, grid_size>, grid_size>;

/// \brief Solves a Sudoku puzzle.
/// \param grid The input to solve.
/// \return If possible to solve, a solved instance, otherwise same as input.
Grid Solve(const Grid& grid);

}// namespace algo::puzzle::sudoku

#endif//ALGO_ALGO_INCLUDE_ALGO_PUZZLE_HPP_
