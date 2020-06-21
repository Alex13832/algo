///
/// \brief Example source code for closes pair of points.
/// \author alex011235
/// \date 2020-04-29
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <fstream>
#include <iostream>
#include <string>

#include "include/algo.hpp"

using namespace std;
using namespace algo::geometry;

/// \brief Reads the input data points.
/// \param file File to read.
/// \return Points.
Points ReadFile(const string& file)
{
  ifstream infile(file);
  string line;
  Points pts;

  // Skip "header"
  getline(infile, line);

  while (getline(infile, line)) {
    string s{line.begin(), line.end() - 2};

    size_t pos = s.find_first_of(',');

    string a{s.begin(), s.begin() + pos};
    string b{s.begin() + pos + 1, s.end()};

    Point p{stod(s), stod(b)};
    pts.emplace_back(p);
  }
  return pts;
}

/// \brief Writes points to a csv-file.
/// \param points The closest pair of points.
/// \param all The raw data.
/// \param filename
void WriteToFile(const Points& points, const Points& all, const string& filename)
{
  ofstream file;
  file.open(filename);

  file << "x"
       << ","
       << "y"
       << ","
       << "Label" << '\n';

  for (auto p : all) {
    file << p.x << "," << p.y << ",1" << '\n';// All
  }
  for (auto p : points) {
    file << p.x << "," << p.y << ",2" << '\n';// Closest pair
  }

  file.close();
}

int main()
{
  Points points{ReadFile("../testfiles/closest_pair_in2.csv")};

  Points cp{ClosestPairOfPoints(points)};

  WriteToFile(cp, points, "../testfiles/closest_pair_out2.csv");
  return 0;
}