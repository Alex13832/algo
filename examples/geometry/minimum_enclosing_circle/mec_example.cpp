///
/// \brief Example source code for minimum enclosing circle.
/// \author alex011235
/// \date 2020-02-18
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

/// \brief Prints the result to a CSV-file.
/// \param circle The properties of this circle will be printed.
/// \param filename The filename to print to.
void WriteToFile(const Circle& circle, const string& filename)
{
  ofstream file;
  file.open(filename);

  file << "x"
       << ","
       << "y"
       << ","
       << "radius" << '\n';

  file << circle.center.x << ", " << circle.center.y << ", " << circle.radius << '\n';
  file.close();
}

int main()
{
  Points points{ReadFile("../testfiles/mbbox_in4.csv")};

  Circle mec{MinimumEnclosingCircle(points)};

  WriteToFile(mec, "../testfiles/mec_out4.csv");

  return 0;
}