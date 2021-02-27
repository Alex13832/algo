///
/// \brief Duplicated code may end up here.
/// \author alex011235
/// \date 2020-02-20
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#ifndef ALGO_EXAMPLES_COMMON_IO_HPP_
#define ALGO_EXAMPLES_COMMON_IO_HPP_

#include <string>
#include <vector>

#include "algo.hpp"

namespace io {

/// \brief Reads a csv file from the given file.
/// \param file_name The file to read.
/// \return Points.
algo::geometry::Points ReadPointsFile(const std::string& file_name);
/// \brief Reads labeled points from a csv file.
/// \details x, y, label
/// \param file_name The file to read.
/// \return LabeledPoints data structure.
algo::data_mining::LabeledPoints ReadLabelPointsFile(const std::string& file_name);

/// \brief Prints the entries in rows to a csv file.
/// \param rows The rows to save.
/// \param file_name The file name.
void ToCsv(const std::vector<std::string>& rows, const std::string& file_name);

/// \brief Writes points to a file.
/// \param points Gets a label 2.
/// \param all Gets a label 1.
/// \param file_name The file name to save.
void ToCsv(const algo::geometry::Points& points, const algo::geometry::Points& all, const std::string& file_name);

struct DataLine {
  int node1, node2;
  double w, x0, y0, x1, y1;
};

/// \brief Reads input points and makes a graph of them.
/// \param file File to parse.
/// \param nbr_nodes Size of graph, must be known.
/// \todo{alex011235} Remove nbr_nodes dependency, count nbr of lines in input file.
/// \return A new graph.
std::pair<algo::graph::Graph, std::vector<DataLine>> ReadGraph(const std::string& file,
                                                               int nbr_nodes,
                                                               bool connect_random_edge = false,
                                                               float connect_probability = 0.2);

/// \brief Prepares graph and data to rows for a csv file.
/// \param graph The graph to output to file.
/// \param lines Excess information from csv, that will be needed later in python for plotting edges etc.
/// \param file_name The file name for the output.
void ToCsv(const algo::graph::Graph& graph, const std::vector<io::DataLine>& lines, const std::string& file_name);

/// \brief Writes result to file.
/// \param graph The graph to output to file.
/// \param lines Excess information from csv, that will be needed later in python for plotting edges etc.
/// \param filename The file name for the output.
void ToCsv(const algo::graph::Nodes& nodes, const std::vector<io::DataLine>& lines, const std::string& filename);

/// \brief Writes result to file.
/// \param graph The graph to output to file.
/// \param lines Excess information from csv, that will be needed later in python for plotting edges etc.
/// \param file_name The file name for the output.
void ToCsv(const algo::graph::NodeMat& node_mat, const std::vector<io::DataLine>& lines, const std::string& file_name);

}// namespace io

#endif//ALGO_EXAMPLES_COMMON_IO_HPP_
