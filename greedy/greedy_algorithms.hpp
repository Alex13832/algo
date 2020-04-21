///
/// \brief Header for greedy algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2015-06-17 Gale-Shapley, Stable marriage/matching.
///

#ifndef ALGORITHM_GREEDY_GREEDY_ALGORITHMS_HPP_
#define ALGORITHM_GREEDY_GREEDY_ALGORITHMS_HPP_

#include <vector>

namespace algo {
namespace greedy {

using Match = std::pair<int, int>;
using Prefs = std::vector<std::vector<int>>;

/// \brief Returns a set of stable matchings of the input of preferred choices. The input needs to be
/// converted to numbers, e.g. man 1 prefers woman 2. The stable matching is computed with the
/// Gale-Shapley algorithm.
/// \param men_pref Men's preferred women.
/// \param women_pref Women's preferred men.
/// \return A list of matching pairs (m_0, w_0), ..., (m_n, w_n).
/// \link <a href="https://en.wikipedia.org/wiki/Stable_marriage_problem">Stable marriage problem, Wikipedia.</a>
/// \link <a href="https://en.wikipedia.org/wiki/Gale–Shapley_algorithm">Gale-Shapley, Wikipedia.</a>
/// \reference <a href="https://www.cs.cmu.edu/afs/cs.cmu.edu/academic/class/15251-f10/Site/Materials/Lectures/Lecture21/lecture21.pdf">
/// The Stable Marriage Problem, Structure and Algorithms, D. Gusfield, R. W. Irving, The MIT Press</a>
std::vector<Match> StableMatching(Prefs men_pref, Prefs women_pref);
}// namespace greedy
}// namespace algo

#endif//ALGORITHM_GREEDY_GREEDY_ALGORITHMS_HPP_
