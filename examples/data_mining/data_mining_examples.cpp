///
/// \brief Data mining examples.
/// \author alex011235
/// \date 2020-02-27
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///
#include <iostream>
#include <string>

#include "algo.hpp"
#include "io.hpp"

using namespace algo::geometry;
using namespace algo::data_mining;
using namespace std;

/// \brief Saves labeled points to file.
/// \param labeled_points Points to save.
/// \param file_name The file name.
void SaveData(const LabeledPoints& labeled_points, const string& file_name)
{
  string header{"x, y, label"};
  vector<string> rows{header};

  for (auto& pt : labeled_points) {
    string row{to_string(pt.x) + "," + to_string(pt.y) + "," + pt.label};
    rows.emplace_back(row);
  }
  io::ToCsv(rows, file_name);
}

/// \brief Saves cluster data to file.
/// \param clusters Cluster data.
/// \param file_name The file name.
void SaveData(const Clusters& clusters, const string& file_name)
{
  string header{"x, y, cluster"};
  vector<string> rows{header};
  int cluster_index{0};

  for (auto& cluster : clusters) {
    for (auto pt : cluster) {
      string row{to_string(pt.x) + "," + to_string(pt.y) + "," + to_string(cluster_index)};
      rows.emplace_back(row);
    }
    cluster_index++;
  }
  io::ToCsv(rows, file_name);
}

/// \brief Prints help information.
void PrintHelp()
{
  cout
      << "Algorithms: Density based spatial clustering <DBSCAN>, K-Means clustering <kmeans>, K-nearest-neighbors <KNN>."
      << endl;
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    PrintHelp();
    return -1;
  }
  const string arg1{argv[1]};

  if (arg1 == "h" || arg1 == "help" || arg1 == "-h" || arg1 == "--help") {
    PrintHelp();
    return 0;
  }

  if (arg1 == "DBSCAN") {
    const string kFileNameIn{"./testfiles/dbscan_in1.csv"};
    const string kFileNameOut{"./testfiles/dbscan_out1.csv"};
    const DistFunc kDistFunc{DistFunc::Euclidean};
    const double kEps{0.1};
    const int kMinPts{50};

    Points points{io::ReadPointsFile(kFileNameIn)};
    LabeledPoints labeled_points{DBSCAN(points, kDistFunc, kEps, kMinPts)};
    SaveData(labeled_points, kFileNameOut);
    return 0;
  }

  if (arg1 == "KNN") {
    const string kFileNameInKnown{"./testfiles/knn_labeled1.csv"};
    const string kFileNameInUnknown{"./testfiles/knn_unlabeled1.csv"};
    const string kFileNameOut{"./testfiles/knn_out1.csv"};
    const int kNbrClusters{3};

    LabeledPoints labeled_points{io::ReadLabelPointsFile(kFileNameInKnown)};
    Points points{io::ReadPointsFile(kFileNameInUnknown)};
    LabeledPoints classified_points{KNearestNeighbor(points, labeled_points, kNbrClusters)};
    SaveData(classified_points, kFileNameOut);
    return 0;
  }

  if (arg1 == "kmeans") {
    const string kFileNameIn{"./testfiles/kmeans_in2.csv"};
    const string kFileNameOut{"./testfiles/kmeans_out2.csv"};
    const int kNbrClusters{3};

    Points points{io::ReadPointsFile(kFileNameIn)};
    Clusters clusters{KMeans(points, kNbrClusters)};
    SaveData(clusters, kFileNameOut);
    return 0;
  }
  return 0;
}
