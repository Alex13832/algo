///
/// \brief Example source code for MST.
/// \author alex011235
/// \date 2020-05-01
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <fstream>
#include <include/algo_graph.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace algo::graph;

Graph ReadGraph(const string& file)
{
  ifstream infile(file);
  string line;
  Graph graph{NewGraph(200)};
  const string kDelim{","};

  // Skip "header"
  getline(infile, line);

  while (getline(infile, line)) {
    string data{line.begin(), line.end()};

    size_t pos{0};
    std::string token;
    int node0, node1;
    double w;

    int i = 0;
    while ((pos = data.find(kDelim)) != std::string::npos) {
      token = data.substr(0, pos);
      data.erase(0, pos + kDelim.length());

      if (i == 0) {
        node0 = stoi(token);
      } else if (i == 1) {
        node1 = stoi(token);
      } else if (i == 2) {
        w = stod(token);
      } else {

        MakeEdge(graph, node0, node1, w);
        i = 0;
        break;
      }

      i++;
    }
  }
  return graph;
}

void WriteToFile(const Graph& graph, const string& filename)
{
  ofstream file;
  file.open(filename);

  // Header
  file << "Node1"
       << ", "
       << "Node2"
       << '\n';

  for (size_t i = 0; i < graph.size(); ++i) {
    for (auto cell : graph[i]) {
      file << i << "," << cell.node << '\n';
    }
  }

  file.close();
}

int main()
{
  Graph graph_in{ReadGraph("testfiles/mst_network_in.csv")};

  double minimum_weight{0.0};
  Graph mstg{MinimumSpanningTree(graph_in, 0, minimum_weight)};

  WriteToFile(mstg, "testfiles/mst_network_out.csv");
  return 0;
}
