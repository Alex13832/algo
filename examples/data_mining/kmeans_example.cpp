///
/// \brief Example source code for K-means.
/// \author alex011235
/// \date 2020-04-29
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <fstream>
#include <include/algo_data_mining.hpp>
#include <iostream>
#include <string>

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

/// \brief Writes points to a csv-file.
/// \param points The convex hull points.
/// \param all All points.
/// \param filename
void WriteToFile(const Clusters& clusters, const string& filename)
{
  ofstream file;
  file.open(filename);
  int clust{0};

  // Header
  file << "x"
       << ", "
       << "y"
       << ", "
       << "Cluster" << '\n';

  for (auto& cluster : clusters) {
    clust++;

    for (auto pt : cluster) {
      file << pt.x << ", " << pt.y << ", cluster " << std::to_string(clust) << '\n';
    }
  }

  file.close();
}

int main()
{
  Points points{ReadFile("testfiles/kmeans_in.csv")};

  Clusters clusters{KMeans(points, 3)};

  WriteToFile(clusters, "testfiles/kmeans_out.csv");
  return 0;
}
