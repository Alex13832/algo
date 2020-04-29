///
/// \brief Example source code for closes pair of points.
/// \author alex011235
/// \date 2020-04-29
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <fstream>
#include <geometry_algorithms.hpp>
#include <iostream>
#include <string>

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
       << ", "
       << "y"
       << ", "
       << "Labels" << '\n';

  for (auto p : all) {
    file << p.x << ", " << p.y << ", Other" << '\n';
  }
  for (auto p : points) {
    file << p.x << ", " << p.y << ", Closest pair" << '\n';
  }

  file.close();
}

int main()
{
  Points points{ReadFile("testfiles/closest_pair_in.csv")};

  Points cp{ClosestPairOfPoints(points)};

  WriteToFile(cp, points, "testfiles/closest_pair_out.csv");
  return 0;
}