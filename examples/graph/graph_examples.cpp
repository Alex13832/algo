///
/// \brief Data mining examples.
/// \author alex011235
/// \date 2020-02-28
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <string>

#include "algo.hpp"
#include "io.hpp"

void PrintHelp()
{
  std::cout
      << "Algorithms: Minimum spanning tree <mst>. Nearest neighbor <nn>. Shortest path <sp>. Strongly connected components <scc>"
      << std::endl;
}

int main(int argc, char *argv[])
{
  if (argc < 3) {
    PrintHelp();
    return -1;
  }

  std::string arg1{argv[1]};

  if (arg1 == "h" || arg1 == "help" || arg1 == "-h" || arg1 == "--help") {
    PrintHelp();
    return 0;
  }

  // TODO: Find out by parsing file
  const int kNbrNodes{std::stoi(argv[2])};
  const std::string kFileIn{"./testfiles/graph_data_in.csv"};

  // Minimum spanning tree
  if (arg1 == "mst") {
    const std::string kFileOut{"./testfiles/mst_network_out.csv"};

    std::pair<algo::graph::Graph, std::vector<io::DataLine>> graph_lines{io::ReadGraph(kFileIn, kNbrNodes)};
    algo::graph::Graph graph_in = graph_lines.first;

    double minimum_weight{0.0};// out
    algo::graph::Graph mst{MinSpanningTree(graph_in, 0, minimum_weight)};

    io::ToCsv(mst, graph_lines.second, kFileOut);
  }

  // Nearest neighbor
  if (arg1 == "nn") {
    const std::string kFileOut{"testfiles/nn_data_out.csv"};

    std::pair<algo::graph::Graph, std::vector<io::DataLine>> graph_lines{io::ReadGraph(kFileIn, kNbrNodes)};
    algo::graph::Graph graph_in{graph_lines.first};

    algo::graph::Nodes nodes{AllNodesPath(graph_in, 0)};// Nearest neighbor

    io::ToCsv(nodes, graph_lines.second, kFileOut);
  }

  // Shortest path
  if (arg1 == "sp") {
    const std::string kFileOut{"./testfiles/shortest_path_data_out.csv"};

    std::pair<algo::graph::Graph, std::vector<io::DataLine>> graph_lines{io::ReadGraph(kFileIn, kNbrNodes)};
    algo::graph::Graph graph_in{graph_lines.first};

    size_t a{rand() % graph_lines.second.size()};
    size_t b{rand() % graph_lines.second.size()};

    const size_t kSource{a < b ? a : b};
    const size_t kSize{a < b ? b : a};

    // Dijkstra
    algo::graph::Nodes nodes{ShortestPathDijkstra(graph_in, kSource, kSize)};

    io::ToCsv(nodes, graph_lines.second, kFileOut);
  }

  // Strongly connected components
  if (arg1 == "scc") {
    const std::string kFileOut{"./testfiles/scc_data_out.csv"};

    std::pair<algo::graph::Graph, std::vector<io::DataLine>> graph_lines{io::ReadGraph(kFileIn, kNbrNodes, true, 0.2)};
    algo::graph::Graph graph_in{graph_lines.first};

    // Kosaraju
    algo::graph::NodeMat nodes{StrConnComponents(graph_in)};

    io::ToCsv(nodes, graph_lines.second, kFileOut);
  }
  return 0;
}