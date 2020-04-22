///
/// \brief Unit tests for greedy algorithms.
/// \author alex011235
/// \date 2020-04-20
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "greedy_algorithms.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace algo::greedy;

namespace {
const std::string path{"../../test/testfiles/stable_match/"};
}

/// \brief Reads an input test files with preferred choices.
/// \param file The file to read.
/// \return A list of preferred choices.
Prefs ReadPrefFile(const std::string &file)
{
  ifstream infile;
  infile.open(file);
  Prefs prefs;

  while (!infile.eof()) {
    string line{};
    getline(infile, line);

    stringstream in(line);
    vector<int> a;
    int temp;
    while (in >> temp) {
      a.emplace_back(temp);
    }

    prefs.emplace_back(a);
  }
  infile.close();

  return prefs;
}

/// \brief Reads the correct matched pairs from a file.
/// \param file The file with the pairs.
/// \return A list of correct matched pairs.
vector<Match> ReadCorrect(const std::string &file)
{
  ifstream infile;
  infile.open(file);
  vector<Match> matches;

  while (!infile.eof()) {
    string line{};
    getline(infile, line);

    stringstream in(line);
    int m, w;
    in >> m;
    in >> w;
    matches.emplace_back(make_pair(m, w));
  }
  infile.close();

  return matches;
}

TEST(test_stable_matching, test_4)
{
  Prefs m_prefs{ReadPrefFile(path + "men4.txt")};
  Prefs w_prefs{ReadPrefFile(path + "women4.txt")};
  vector<Match> correct{ReadCorrect(path + "correct4.txt")};

  std::vector<Match> matches{StableMatching(m_prefs, w_prefs)};
  EXPECT_FALSE(matches.empty());
  EXPECT_TRUE(equal(correct.begin(), correct.end(), matches.begin()));
}

TEST(test_stable_matching, test_8)
{
  Prefs m_prefs{ReadPrefFile(path + "men8.txt")};
  Prefs w_prefs{ReadPrefFile(path + "women8.txt")};
  vector<Match> correct{ReadCorrect(path + "correct8.txt")};

  std::vector<Match> matches{StableMatching(m_prefs, w_prefs)};
  EXPECT_FALSE(matches.empty());
  EXPECT_TRUE(equal(correct.begin(), correct.end(), matches.begin()));
}
