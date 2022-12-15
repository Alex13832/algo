//
// Created by Alexander Karlsson on 2021-02-20.
//

#include "io.hpp"

#include <fstream>
#include <iostream>
#include <vector>

using namespace algo::geometry;

namespace io {

std::vector<Point> ReadPointsFile(const std::string& file_name)
{
  std::ifstream infile(file_name);
  std::string line;
  std::vector<Point> pts;

  // Skip "header"
  getline(infile, line);

  while (getline(infile, line)) {
    std::string s{line.begin(), line.end() - 2};

    size_t pos = s.find_first_of(',');

    std::string a{s.begin(), s.begin() + pos};
    std::string b{s.begin() + pos + 1, s.end()};

    Point p{stod(s), stod(b)};

    pts.emplace_back(p);
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

void ToCsv(const std::vector<Point>& points, const std::vector<Point>& all,
           const std::string& file_name)
{
  std::string header{"x,y,Label"};
  std::vector<std::string> rows{header};

  for (const auto& p : all) {
    std::string row{std::to_string(p.X()) + "," + std::to_string(p.Y()) + ",1"};
    rows.emplace_back(row);
  }
  for (const auto& p : points) {
    std::string row{std::to_string(p.X()) + "," + std::to_string(p.Y()) + ",2"};
    rows.emplace_back(row);
  }
  ToCsv(rows, file_name);
}

std::vector<DataLine> ReadLines(const std::string& file)
{
  std::ifstream infile(file);
  std::string line;
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
        break;
      }
      i++;
    }
  }
  return lines;
}

std::vector<std::vector<double>> ReadDoubles(const std::string& file)
{
  std::ifstream infile(file);
  std::string line;
  const std::string kDelim{","};
  std::vector<std::vector<double>> lines;

  // Skip "header"
  getline(infile, line);

  while (getline(infile, line)) {
    std::string data{line.begin(), line.end()};

    size_t pos;
    std::string token;
    std::vector<double> line_d;

    while ((pos = data.find(kDelim)) != std::string::npos) {
      token = data.substr(0, pos);
      data.erase(0, pos + kDelim.length());
      auto token_d = std::stod(token);
      line_d.emplace_back(token_d);
    }
    if (!data.empty()) {
      auto token_d = std::stod(data);
      line_d.emplace_back(token_d);
    }
    lines.emplace_back(line_d);
  }
  return lines;
}

algo::graph::DirectedGraph ReadDG(const std::vector<DataLine>& lines)
{
  algo::graph::DirectedGraph dg{lines.size()};

  for (const auto& line : lines) {
    dg.InsertEdge(line.node1, line.node2);
  }

  return dg;
}

algo::graph::UndirectedGraph ReadUG(const std::vector<DataLine>& lines)
{
  algo::graph::UndirectedGraph ug{lines.size()};

  for (const auto& line : lines) {
    ug.InsertEdge(line.node1, line.node2);
  }

  return ug;
}

algo::graph::UndirectedWeightedGraph ReadUWG(const std::vector<DataLine>& lines)
{
  algo::graph::UndirectedWeightedGraph uwg{lines.size()};

  for (const auto& line : lines) {
    uwg.InsertEdge(line.node1, line.node2, line.w);
  }

  return uwg;
}

algo::graph::DirectedWeightedGraph ReadDWG(const std::vector<DataLine>& lines)
{
  algo::graph::DirectedWeightedGraph dwg{lines.size()};

  for (const auto& line : lines) {
    dwg.InsertEdge(line.node1, line.node2, line.w);
  }

  return dwg;
}

void ToCsv(const algo::graph::RawGraph& graph,
           const std::vector<io::DataLine>& lines, const std::string& file_name)
{
  const std::string kHeader{"Node1,Node2,W,X0,Y0,X1,Y1"};
  std::vector rows{kHeader};

  for (size_t i = 0; i < graph.size(); ++i) {
    for (auto cell : graph[i]) {

      for (auto line : lines) {
        if (static_cast<size_t>(line.node1) == i && line.node2 == cell.node) {
          std::string row{
              std::to_string(i) + "," + std::to_string(cell.node) + ","
              + std::to_string(line.w) + "," + std::to_string(line.x0) + ","
              + std::to_string(line.y0) + "," + std::to_string(line.x1) + ","
              + std::to_string(line.y1)};
          rows.emplace_back(row);
        }
      }
    }
  }
  ToCsv(rows, file_name);
}

void ToCsv(const algo::graph::Nodes& nodes,
           const std::vector<io::DataLine>& lines, const std::string& filename)
{
  const std::string kHeader{"Node,X,Y"};
  std::vector<std::string> rows{kHeader};

  for (auto node : nodes) {
    for (auto line : lines) {
      if (line.node1 == node) {
        std::string row{std::to_string(node) + "," + std::to_string(line.x0)
                        + "," + std::to_string(line.y0)};
        rows.emplace_back(row);
        break;
      } else if (line.node2 == node) {
        std::string row{std::to_string(node) + "," + std::to_string(line.x1)
                        + "," + std::to_string(line.y1)};
        rows.emplace_back(row);
        break;
      }
    }
  }
  ToCsv(rows, filename);
}

void ToCsv(const algo::graph::NodeMat& node_mat,
           const std::vector<io::DataLine>& lines, const std::string& file_name)
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
              std::to_string(node) + ',' + std::to_string(line.x0) + ','
              + std::to_string(line.y0) + ',' + std::to_string(comp_counter)};
          rows.emplace_back(kRow);
          break;
        } else if (line.node2 == node) {
          const std::string kRow{
              std::to_string(node) + ',' + std::to_string(line.x1) + ','
              + std::to_string(line.y1) + ',' + std::to_string(comp_counter)};
          rows.emplace_back(kRow);
          break;
        }
      }
    }
  }
  ToCsv(rows, file_name);
}

}// namespace io
