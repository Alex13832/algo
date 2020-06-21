///
/// \brief Example source code for strongly connected components.
/// \author alex011235
/// \date 2020-05-17
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <cmath>
#include <fstream>
#include <include/algo.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace algo::graph;
using namespace algo::math::random_num::cont;

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

        if (Random() < 0.2) {// Play with this
          MakeEdge(graph, ln.node1, ln.node2);
        } else {
          MakeDirEdge(graph, ln.node1, ln.node2);
        }

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
void WriteToFile(const NodeMat& node_mat, const vector<DataLine>& lines, const string& filename)
{
  ofstream file;
  file.open(filename);

  // Header
  file << "Node,"
       << "x,"
       << "y,"
       << "Component"
       << '\n';

  int comp_counter{0};
  for (const auto& nodes : node_mat) {
    comp_counter++;

    for (auto node : nodes) {
      for (auto line : lines) {

        if (line.node1 == node) {
          file << node << ',' << line.x0 << ',' << line.y0 << ',' << comp_counter << '\n';
          break;
        } else if (line.node2 == node) {
          file << node << ',' << line.x1 << ',' << line.y1 << ',' << comp_counter << '\n';
          break;
        }
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

  pair<Graph, vector<DataLine>> graph_lines{ReadGraph("testfiles/scc_data_in.csv", nbr_nodes)};
  Graph graph_in{graph_lines.first};

  // Kosaraju
  NodeMat nodes{StrConnComponents(graph_in)};

  WriteToFile(nodes, graph_lines.second, "testfiles/scc_data_out.csv");
  return 0;
}
