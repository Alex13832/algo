///
/// \brief Example source code for Quickhull.
/// \author alex011235
/// \date 2020-04-27
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <fstream>
#include <iostream>
#include <string>

#include "algo.hpp"

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
/// \param points The convex hull points.
/// \param all All points.
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
    file << p.x << ", " << p.y << ",1" << '\n';//Insed convex hull
  }
  for (auto p : points) {
    file << p.x << ", " << p.y << ",2" << '\n';//Convex hull
  }

  file.close();
}

int main()
{
  Points points{ReadFile("../testfiles/convex_hull_in2.csv")};

  Points qh{ConvexHull(points)};

  WriteToFile(qh, points, "../testfiles/convex_hull_out2.csv");

  return 0;
}