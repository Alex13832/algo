//
// Created by Alexander Karlsson on 2021-02-20.
//

#include "io.hpp"

#include <fstream>
#include <iostream>
#include <vector>

namespace io {

algo::geometry::Points ReadPointsFile(const std::string& file_name)
{
  std::ifstream infile(file_name);
  std::string line;
  algo::geometry::Points pts;

  // Skip "header"
  getline(infile, line);

  while (getline(infile, line)) {
    std::string s{line.begin(), line.end() - 2};

    size_t pos = s.find_first_of(',');

    std::string a{s.begin(), s.begin() + pos};
    std::string b{s.begin() + pos + 1, s.end()};

    algo::geometry::Point p{stod(s), stod(b)};

    pts.emplace_back(p);
  }
  return pts;
}

algo::data_mining::LabeledPoints ReadLabelPointsFile(const std::string& file_name)
{
  std::ifstream infile(file_name);
  std::string line;
  algo::data_mining::LabeledPoints pts;
  const std::string kDelim{","};

  // Skip "header"
  getline(infile, line);

  while (getline(infile, line)) {
    std::string data{line.begin(), line.end() - 1};

    size_t pos{0};
    std::string token;
    double x{0.0}, y{0.0};
    int i = 0;
    while ((pos = data.find(kDelim)) != std::string::npos) {
      token = data.substr(0, pos);
      data.erase(0, pos + kDelim.length());

      if (i == 0) {
        x = stod(token);
      } else {
        y = stod(token);
      }
      i++;
    }

    algo::data_mining::LabeledPoint lp{x, y, 0.0, data};
    pts.emplace_back(lp);
  }
  return pts;
}

void ToCsv(const std::vector<std::string>& rows, const std::string& file_name)
{
  std::ofstream file;
  file.open(file_name);

  for (const auto& row : rows) {
    file << row << '\n';
  }
  file.close();
}

void ToCsv(const algo::geometry::Points& points, const algo::geometry::Points& all, const std::string& file_name)
{
  std::string header{"x, y, Label"};
  std::vector<std::string> rows{header};

  for (auto p : all) {
    std::string row{std::to_string(p.x) + "," + std::to_string(p.y) + ",1"};
    rows.emplace_back(row);
  }
  for (auto p : points) {
    std::string row{std::to_string(p.x) + "," + std::to_string(p.y) + ",2"};
    rows.emplace_back(row);
  }
  ToCsv(rows, file_name);
}

std::pair<algo::graph::Graph, std::vector<DataLine>> ReadGraph(const std::string& file,
                                                               int nbr_nodes,
                                                               bool connect_random_edge,
                                                               float connect_probability)
{
  std::ifstream infile(file);
  std::string line;
  algo::graph::Graph graph{algo::graph::NewGraph(nbr_nodes)};
  const std::string kDelim{","};
  std::vector<DataLine> lines;

  // Skip "header"
  getline(infile, line);

  while (getline(infile, line)) {
    std::string data{line.begin(), line.end()};

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

        if (connect_random_edge) {
          if (algo::math::random_num::cont::Random() < connect_probability) {
            MakeEdge(graph, ln.node1, ln.node2);
          } else {
            MakeDirEdge(graph, ln.node1, ln.node2);
          }
        } else {
          MakeEdge(graph, ln.node1, ln.node2, ln.w);
        }
        break;
      }
      i++;
    }
  }
  return make_pair(graph, lines);
}

void ToCsv(const algo::graph::Graph& graph, const std::vector<io::DataLine>& lines, const std::string& file_name)
{
  const std::string kHeader{"Node1, Node2, W, X0, Y0, X1, Y1"};
  std::vector rows{kHeader};

  for (size_t i = 0; i < graph.size(); ++i) {
    for (auto cell : graph[i]) {

      for (auto line : lines) {
        if (static_cast<size_t>(line.node1) == i && line.node2 == cell.node) {
          std::string row{
              std::to_string(i) + "," + std::to_string(cell.node) + "," + std::to_string(line.w)
                  + "," + std::to_string(line.x0) + "," + std::to_string(line.y0) + "," + std::to_string(line.x1) + ","
                  + std::to_string(line.y1)};
          rows.emplace_back(row);
        }
      }
    }
  }
  ToCsv(rows, file_name);
}

void ToCsv(const algo::graph::Nodes& nodes, const std::vector<io::DataLine>& lines, const std::string& filename)
{
  const std::string kHeader{"Node,X,Y"};
  std::vector<std::string> rows{kHeader};

  for (auto node : nodes) {
    for (auto line : lines) {
      if (line.node1 == node) {
        std::string row{std::to_string(node) + "," + std::to_string(line.x0) + "," + std::to_string(line.y0)};
        rows.emplace_back(row);
        break;
      } else if (line.node2 == node) {
        std::string row{std::to_string(node) + "," + std::to_string(line.x1) + "," + std::to_string(line.y1)};
        rows.emplace_back(row);
        break;
      }
    }
  }
  ToCsv(rows, filename);
}

void ToCsv(const algo::graph::NodeMat& node_mat, const std::vector<io::DataLine>& lines, const std::string& file_name)
{
  const std::string kHeader{"Node,X,Y,Component"};
  std::vector<std::string> rows{kHeader};

  int comp_counter{0};
  for (const auto& nodes : node_mat) {
    comp_counter++;

    for (auto node : nodes) {
      for (auto line : lines) {

        if (line.node1 == node) {
          const std::string kRow{
              std::to_string(node) + ',' + std::to_string(line.x0) + ',' + std::to_string(line.y0) + ','
                  + std::to_string(comp_counter)};
          rows.emplace_back(kRow);
          break;
        } else if (line.node2 == node) {
          const std::string kRow{
              std::to_string(node) + ',' + std::to_string(line.x1) + ',' + std::to_string(line.y1) + ','
                  + std::to_string(comp_counter)};
          rows.emplace_back(kRow);
          break;
        }
      }
    }
  }
  ToCsv(rows, file_name);
}

}// namespace io
