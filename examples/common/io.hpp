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
std::vector<algo::geometry::Point> ReadPointsFile(
    const std::string& file_name);

/// \brief Prints the entries in rows to a csv file.
/// \param rows The rows to save.
/// \param file_name The file name.
void ToCsv(const std::vector<std::string>& rows, const std::string& file_name);

/// \brief Writes points to a file.
/// \param points Gets a label 2.
/// \param all Gets a label 1.
/// \param file_name The file name to save.
void ToCsv(const std::vector<algo::geometry::Point>& points,
           const std::vector<algo::geometry::Point>& all,
           const std::string& file_name);

struct DataLine {
  int node1, node2;
  double w, x0, y0, x1, y1;
};

/// \brief Reads lines for graphs.
/// \param file Input file.
/// \return DataLines
std::vector<DataLine> ReadLines(const std::string& file);

/// \brief Reads whole lines of double values from a file.
/// \param file File to read from.
/// \return A vector<vector<double>>, each entry is a line (vector<double>).
std::vector<std::vector<double>> ReadDoubles(const std::string& file);

/// \brief Returns a directed graph based on the input.
/// \param lines Input lines.
/// \return A directed graph.
algo::graph::DirectedGraph ReadDG(const std::vector<DataLine>& lines);

/// \brief Returns an undirected graph based on the input.
/// \param lines Input lines.
/// \return An undirected graph.
algo::graph::UndirectedGraph ReadUG(const std::vector<DataLine>& lines);

/// \brief Returns an undirected graph based on the input.
/// \param lines Input lines.
/// \return An undirected graph.
algo::graph::UndirectedWeightedGraph ReadUWG(
    const std::vector<DataLine>& lines);

/// \brief Returns an undirected graph based on the input.
/// \param lines Input lines.
/// \return An undirected graph.
algo::graph::DirectedWeightedGraph ReadDWG(const std::vector<DataLine>& lines);

/// \brief Prepares graph and data to rows for a csv file.
/// \param graph The graph to output to file.
/// \param lines Excess information from csv, that will be needed later in python for plotting edges etc.
/// \param file_name The file name for the output.
void ToCsv(const algo::graph::RawGraph& graph,
           const std::vector<io::DataLine>& lines,
           const std::string& file_name);

/// \brief Writes result to file.
/// \param graph The graph to output to file.
/// \param lines Excess information from csv, that will be needed later in python for plotting edges etc.
/// \param filename The file name for the output.
void ToCsv(const algo::graph::Nodes& nodes,
           const std::vector<io::DataLine>& lines, const std::string& filename);

/// \brief Writes result to file.
/// \param graph The graph to output to file.
/// \param lines Excess information from csv, that will be needed later in python for plotting edges etc.
/// \param file_name The file name for the output.
void ToCsv(const algo::graph::NodeMat& node_mat,
           const std::vector<io::DataLine>& lines,
           const std::string& file_name);

}// namespace io

#endif//ALGO_EXAMPLES_COMMON_IO_HPP_
