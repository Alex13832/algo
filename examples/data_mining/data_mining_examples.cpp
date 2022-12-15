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

namespace dm = algo::data_mining;

namespace {
auto S = [](auto x) { return std::to_string(x); };
}

void SaveData(const std::vector<dm::Point>& pts, const std::vector<int>& labels,
              const string& file_name)
{
  std::string header;
  for (size_t i = 0; i < pts[0].size(); i++) {
    header += "x" + S(i) + ",";
  }
  header += "label";

  vector<string> rows{header};

  for (size_t i = 0; i < pts.size(); i++) {

    std::string line;

    for (size_t j = 0; j < pts.at(i).size(); j++) {
      line += S(pts[i][j]) + ",";
    }
    line += S(labels.at(i));
    rows.emplace_back(line);
  }
  io::ToCsv(rows, file_name);
}

/// \brief Prints help information.
void PrintHelp()
{
  cout << "Algorithms: Density based spatial clustering <DBSCAN>, K-Means "
          "clustering <kmeans>, K-nearest-neighbors <KNN>."
       << endl;
}

int main(int argc, char* argv[])
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

  if (arg1 == "dbscan") {
    const string kFileNameIn{"./testfiles/dbscan_in1.csv"};
    const string kFileNameOut{"./testfiles/dbscan_out1.csv"};

    std::cout << "Running DBSCAN on " << kFileNameIn << std::endl;

    auto points = io::ReadDoubles(kFileNameIn);
    dm::Cluster miner{points};
    auto labels = miner.DbScan(dm::norms::Euclidean(), 0.2, 50);

    std::cout << labels.size() << " Labels from DBSCAN returned" << std::endl;

    SaveData(points, labels, kFileNameOut);
    return 0;
  }

  if (arg1 == "knn") {
    const string kFileNameInKnown{"./testfiles/knn_labeled2.csv"};
    const string kFileNameInUnknown{"./testfiles/knn_unlabeled2.csv"};
    const string kFileNameOut{"./testfiles/knn_out2.csv"};

    std::cout << "Running KNN" << std::endl;

    auto lines_known = io::ReadDoubles(kFileNameInKnown);

    std::vector<int> known_labels;
    std::vector<dm::Point> known_points;
    auto lines_unknown = io::ReadDoubles(kFileNameInUnknown);

    for (auto& lk : lines_known) {
      known_labels.emplace_back(static_cast<int>(lk.back()));
      lk.pop_back();
      known_points.emplace_back(lk);
    }

    std::cout << known_points.size() << " Points" << std::endl;

    dm::Classifier classifier{lines_unknown};
    auto labels = classifier.KNearestNeighbour(dm::norms::Manhattan(),
                                               known_points, known_labels, 3);
    SaveData(lines_unknown, labels, kFileNameOut);

    return 0;
  }

  if (arg1 == "kmeans") {
    const string kFileNameIn{"./testfiles/kmeans_in1.csv"};
    const string kFileNameOut{"./testfiles/kmeans_out1.csv"};
    const int kNbrClusters{4};

    std::cout << "Running KMeans" << std::endl;

    auto points = io::ReadDoubles(kFileNameIn);
    dm::Cluster miner{points};
    auto clusters = miner.KMeans(dm::norms::Euclidean(), kNbrClusters);

    std::cout << clusters.size() << " entries returned " << std::endl;

    SaveData(points, clusters, kFileNameOut);
    return 0;
  }
  return 0;
}
