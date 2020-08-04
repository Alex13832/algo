///
/// \brief Example source code for DBSCAN.
/// \author alex011235
/// \date 2020-07-21
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <fstream>
#include <iostream>
#include <string>

#include "algo.hpp"

using namespace std;
using namespace algo::data_mining;
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

void WriteToFile(const LabeledPoints& labeled_points, const string& filename)
{
  ofstream file;
  file.open(filename);

  // Header
  file << "x"
       << ","
       << "y"
       << ","
       << "Label" << '\n';

  for (auto& pt : labeled_points) {
    file << pt.x << "," << pt.y << "," << pt.label << '\n';
  }

  file.close();
}

int main()
{
  Points points{ReadFile("../testfiles/dbscan_in2.csv")};
  LabeledPoints labeled_points{DBSCAN(points, DistFunc::Euclidean, 0.1, 50)};
  WriteToFile(labeled_points, "../testfiles/dbscan_out1.csv");
  return 0;
}
