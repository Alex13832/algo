///
/// \brief Data mining examples.
/// \author alex011235
/// \date 2020-02-28
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <iostream>
#include <string>

#include "algo.hpp"
#include "io.hpp"

void PrintHelp()
{
  std::cout << "Algorithms: Minimum spanning tree <mst>. Shortest path <sp>. "
               "Strongly connected components <scc>"
            << std::endl;
}

int main(int argc, char *argv[])
{
  if (argc < 1) {
    PrintHelp();
    return -1;
  }

  std::string arg1{argv[1]};

  if (arg1 == "h" || arg1 == "help" || arg1 == "-h" || arg1 == "--help") {
    PrintHelp();
    return 0;
  }

  std::cout << arg1 << std::endl;

  // TODO: Find out by parsing file
  std::string file_in;
  std::string file_out;

  // Minimum spanning tree
  if (arg1 == "mst") {
    file_in = "./plot/mst_network_in.csv";
    auto lines = io::ReadLines(file_in);
    auto graph = io::ReadUWG(lines);
    double minimum_weight{0.0};// out
    auto mst = graph.MinSpanningTreePrim(minimum_weight);
    auto nodes = mst.GetRaw();

    file_out = "./plot/mst_network_out.csv";
    io::ToCsv(nodes, lines, file_out);
  }

  // Shortest path
  if (arg1 == "sp") {
    file_in = "./plot/sp_network_in.csv";
    auto lines = io::ReadLines(file_in);
    auto graph = io::ReadUWG(lines);
    // Trial and error until you find something nice.
    auto nodes = graph.ShortestPathDijkstra(2, 99);

    file_out = "./plot/sp_network_out.csv";
    io::ToCsv(nodes, lines, file_out);
  }

  // Strongly connected components
  if (arg1 == "scc") {
    file_in = "./plot/scc_network_in.csv";
    auto lines = io::ReadLines(file_in);
    auto graph = io::ReadDG(lines);
    auto nodes = graph.StronglyConnectedComponentsKosaraju();

    file_out = "./plot/scc_network_out.csv";
    io::ToCsv(nodes, lines, file_out);
  }

  return 0;
}