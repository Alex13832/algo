///
/// \brief Example source code for KNN.
/// \author alex011235
/// \date 2020-05-01
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <fstream>
#include <include/algo.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace algo::data_mining;
using namespace algo::geometry;

/// \brief Reads the input data points.
/// \param file File to read.
/// \return Points.
LabeledPoints ReadLabeledData(const string& file)
{
  ifstream infile(file);
  string line;
  LabeledPoints pts;
  const string kDelim{","};

  // Skip "header"
  getline(infile, line);

  while (getline(infile, line)) {
    string data{line.begin(), line.end() - 1};

    size_t pos{0};
    std::string token;
    double x{0.0}, y{0.0};
    int i = 0;
    while ((pos = data.find(kDelim)) != std::string::npos) {
      token = data.substr(0, pos);
      data.erase(0, pos + kDelim.length());

      if (i == 0) {
        x = stod(token);
      } else {
        y = stod(token);
      }
      i++;
    }

    LabeledPoint lp{x, y, 0.0, data};
    pts.emplace_back(lp);
  }
  return pts;
}

Points ReadPoints(const string& file)
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

int main(int argc, char* argv[])
{
  LabeledPoints labeled_points{ReadLabeledData("../testfiles/knn_labeled2.csv")};
  Points points{ReadPoints("../testfiles/knn_unlabeled2.csv")};

  LabeledPoints classified_points{KNearestNeighbor(points, labeled_points, 5)};

  WriteToFile(classified_points, "../testfiles/knn_out2.csv");
  return 0;
}
