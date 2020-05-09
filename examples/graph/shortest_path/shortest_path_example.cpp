///
/// \brief Example source code for Dijkstra shortest path.
/// \author alex011235
/// \date 2020-05-08
/// \link <a href=https://github.com/alex011235/algorithm>Algorithm, Github</a>
///

#include <cmath>
#include <fstream>
#include <include/algo_graph.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace algo::graph;

struct DataLine {
  int node1, node2;
  double w, x0, y0, x1, y1;
};

/// \brief Raeds input file and makes a graph of the input points.
/// \param file The csv-file to read.
/// \param nbr_nodes How many nodes in the graph.
/// \return A new graph.
pair<Graph, vector<DataLine>> ReadGraph(const string& file, int nbr_nodes)
{
  ifstream infile(file);
  string line;
  Graph graph{NewGraph(nbr_nodes)};
  const string kDelim{","};
  vector<DataLine> lines;

  // Skip "header"
  getline(infile, line);

  while (getline(infile, line)) {
    string data{line.begin(), line.end()};

    size_t pos;
    std::string token;
    DataLine ln{};
    int i = 0;

    while ((pos = data.find(kDelim)) != std::string::npos) {
      token = data.substr(0, pos);
      data.erase(0, pos + kDelim.length());

      if (i == 0) {
        ln.node1 = stoi(token);
      } else if (i == 1) {
        ln.node2 = stoi(token);
      } else if (i == 2) {
        ln.w = stod(token);
      } else if (i == 3) {
        ln.x0 = stod(token);
      } else if (i == 4) {
        ln.y0 = stod(token);
      } else {
        ln.x1 = stod(token);
        ln.y1 = stod(data);
        lines.emplace_back(ln);
        MakeEdge(graph, ln.node1, ln.node2, ln.w);
        break;
      }
      i++;
    }
  }
  return make_pair(graph, lines);
}

/// \brief Writes result to file.
/// \param graph The graph to output to file.
/// \param lines Excess information from csv, that will be needed later in python for plotting edges etc.
/// \param filename The file name for the output.
void WriteToFile(const Nodes& nodes, const vector<DataLine>& lines, const string& filename)
{
  ofstream file;
  file.open(filename);

  // Header
  file << "Node"
       << ','
       << 'x'
       << ','
       << 'y'
       << '\n';

  for (auto node : nodes) {
    for (auto line : lines) {
      if (line.node1 == node) {
        file << node << ',' << line.x0 << ',' << line.y0 << '\n';
        break;
      } else if (line.node2 == node) {
        file << node << ',' << line.x1 << ',' << line.y1 << '\n';
        break;
      }
    }
  }
  file.close();
}

int main(int argc, char* argv[])
{
  if (argc != 2) {
    return -1;
  }

  int nbr_nodes{stoi(argv[1])};

  pair<Graph, vector<DataLine>> graph_lines{ReadGraph("testfiles/shortest_path_data_in.csv", nbr_nodes)};
  Graph graph_in{graph_lines.first};

  int min_source{0}, max_source{0};
  double max_dist{0};

  // Find points that are far away from each other.
  for (const auto& l1 : graph_lines.second) {
    for (const auto& l2 : graph_lines.second) {

      if (l1.node1 != l2.node1 && l1.node2 != l2.node2) {
        //double dist{(pow(l1.x0 - l2.x1, 2) + pow(l1.y0 - l2.y1, 2))};
        double dist{abs(l1.x0 - l2.x1)};

        if (dist > max_dist) {
          min_source = l1.node1;
          max_source = l2.node2;
          max_dist = dist;
        }
      }
    }
  }

  // Dijkstra
  Nodes nodes{ShortestPath(graph_in, min_source, max_source)};

  WriteToFile(nodes, graph_lines.second, "testfiles/shortest_path_data_out.csv");
  return 0;
}
