///
/// \brief Source file for greedy algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///
/// Change list:
/// 2015-06-17 Gale-Shapley, Stable marriage.
///

#include "algo_greedy.hpp"

#include <algorithm>

namespace algo::greedy {

std::vector<Match> StableMatching(Prefs men_pref, Prefs women_pref)
{
  size_t couples{men_pref[0].size()};
  std::vector<int> engaged_men(couples, false);
  std::vector<int> engaged_women(couples, false);

  int m1{0};
  bool man_free{true};

  // Algorithm: while there is a man who is not engaged and has not proposed to every woman on his list.
  while (man_free) {
    int w{men_pref[m1].front()};
    men_pref[m1].erase(men_pref[m1].begin());

    if (engaged_women[w - 1] == 0) {
      engaged_women[w - 1] = m1 + 1;
      engaged_men[m1] = w;
    } else {
      int m2{engaged_women[w - 1] - 1};

      auto pref1 = std::find(women_pref[w - 1].begin(), women_pref[w - 1].end(), m1 + 1);
      auto pref2 = std::find(women_pref[w - 1].begin(), women_pref[w - 1].end(), m2 + 1);

      if (pref1 < pref2) {
        engaged_men[m1] = w;
        engaged_women[w - 1] = m1 + 1;
        engaged_men[m2] = 0;
      }
    }

    for (size_t i = 0; i < engaged_men.size(); ++i)
      if (engaged_men[i] == 0) m1 = i;

    if (find(engaged_men.begin(), engaged_men.end(), 0) == engaged_men.end())
      man_free = false;
  }

  // Copy pairs of matched men and women.
  std::vector<Match> out;
  int man{1};
  for (const auto &woman : engaged_men) {
    out.emplace_back(std::make_pair(man, woman));
    man++;
  }

  return out;
}
}// namespace algo::greedy
