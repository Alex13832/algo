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

struct Line {
  int node1, node2;
  double w, x0, y0, x1, y1;
};

pair<Graph, vector<Line>> ReadGraph(const string& file, int nbr_nodes)
{
  ifstream infile(file);
  string line;
  Graph graph{NewGraph(nbr_nodes)};
  const string kDelim{","};
  vector<Line> lines;

  // Skip "header"
  getline(infile, line);

  while (getline(infile, line)) {
    string data{line.begin(), line.end()};

    size_t pos;
    std::string token;
    Line ln{};
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

void WriteToFile(const Graph& graph, const vector<Line>& lines, const string& filename)
{
  ofstream file;
  file.open(filename);

  // Header
  file << "Node1"
       << ", "
       << "Node2"
       << ","
       << "W"
       << ","
       << "x0"
       << ","
       << "y0"
       << ","
       << "x1"
       << ","
       << "y1"
       << '\n';

  for (size_t i = 0; i < graph.size(); ++i) {
    for (auto cell : graph[i]) {

      for (auto line : lines) {
        if (line.node1 == i && line.node2 == cell.node) {
          file << i << "," << cell.node << "," << line.w << "," << line.x0 << "," << line.y0 << "," << line.x1 << "," << line.y1 << '\n';
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

  int nodes{stoi(argv[1])};

  pair<Graph, vector<Line>> graph_lines{ReadGraph("testfiles/mst_network_in.csv", nodes)};
  Graph graph_in = graph_lines.first;

  double minimum_weight{0.0};
  Graph mstg{MinimumSpanningTree(graph_in, 0, minimum_weight)};

  WriteToFile(mstg, graph_lines.second, "testfiles/mst_network_out.csv");
  return 0;
}
