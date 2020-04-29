///
/// \brief Example source code for triangulate.
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
/// \param points The convex hull points.
/// \param all All points.
/// \param filename
void WriteToFile(const Lines& lines, const string& filename)
{
  ofstream file;
  file.open(filename);

  file << "x1"
       << ", "
       << "y1"
       << ", "
       << "x2"
       << ","
       << "y2"
       << '\n';

  for (auto line : lines) {
    file << line.a.x << ", " << line.a.y << ", " << line.b.x << ", " << line.b.y << '\n';
  }

  file.close();
}

struct x_comp {
  bool operator()(const Point p1, const Point p2) const
  {
    return p1.x < p2.x;
  }
};

int main()
{
  Points points{ReadFile("testfiles/triangulate_in.csv")};

  Lines lines{Triangulate(points)};

  WriteToFile(lines, "testfiles/triangulate_out.csv");
  return 0;
}