///
/// \brief Geometry examples.
/// \author alex011235
/// \date 2020-02-27
/// \link <a href=https://github.com/alex011235/algo>Algo, Github</a>
///

#include <iostream>

#include "algo.hpp"
#include "io.hpp"

using namespace std;
using namespace algo::geometry;

const auto TS = [](auto x) { return to_string(x); };

void WriteToFile(const Circle& circle, const string& file_name)
{
  string header{"x,y,radius"};
  string row{TS(circle.Origin().X()) + "," + TS(circle.Origin().Y()) + ","
             + TS(circle.Radius()) + '\n'};
  vector<string> rows{header, row};
  io::ToCsv(rows, file_name);
}

void WriteToFile(const std::vector<Edge>& lines, const string& file_name)
{
  string header{"x1,y1,x2,y2"};
  vector<string> rows{header};

  for (const auto& line : lines) {
    string row{TS(line.GetStart().X()) + "," + TS(line.GetStart().Y()) + ","
               + TS(line.GetEnd().X()) + "," + TS(line.GetEnd().Y())};
    rows.emplace_back(row);
  }
  io::ToCsv(rows, file_name);
}

void PrintHelp()
{
  cout << "Algorithms: Closest pair of points <cpp>, Convex hull <ch>, Minimum "
          "bounding box <mbbox>, "
          "Minimum enclosing circle <mec>, <triangulate>."
       << endl;
}

int main(int argc, char* argv[])
{
  if (argc < 2) {
    PrintHelp();
    return -1;
  }
  const string arg1{argv[1]};

  if (arg1 == "h" || arg1 == "help" || arg1 == "-h" || arg1 == "--help") {
    PrintHelp();
    return 0;
  }

  // Closest pair of points
  if (arg1 == "cpp") {
    const string kFileNameIn{"./testfiles/closest_pair_in1.csv"};
    const string kFileNameOut{"./testfiles/closest_pair_out1.csv"};
    auto points = io::ReadPointsFile(kFileNameIn);
    Grid grid{points};
    auto cp = grid.ClosestPairOfPoints();
    std::vector<Point> ch_pts{cp.first, cp.second};
    io::ToCsv(ch_pts, points, kFileNameOut);
  }

  // Convex hull
  if (arg1 == "ch") {
    const string kFileNameIn{"./testfiles/convex_hull_in1.csv"};
    const string kFileNameOut{"./testfiles/convex_hull_out11.csv"};
    auto points = io::ReadPointsFile(kFileNameIn);
    Grid grid{points};
    auto qh = grid.ConvexHull();
    io::ToCsv(qh.GetPoints(), points, kFileNameOut);
  }

  // Minimum bounding box
  if (arg1 == "mbbox") {
    const string kFileNameIn{"./testfiles/mbbox_in1.csv"};
    const string kFileNameOut{"./testfiles/mbbox_out1.csv"};
    auto points = io::ReadPointsFile(kFileNameIn);
    Grid grid{points};
    auto mbbox = grid.MinBoundingBox();
    io::ToCsv(mbbox.GetPoints(), points, kFileNameOut);
  }

  // Minimum enclosing circle
  if (arg1 == "mec") {
    const string kFileNameIn{"./testfiles/convex_hull_in1.csv"};
    const string kFileNameOut{"./testfiles/mec_out1.csv"};
    auto points = io::ReadPointsFile(kFileNameIn);
    Grid grid{points};
    auto mec = grid.MinEnclosingCircle();
    WriteToFile(mec, kFileNameOut);
  }

  // Enclosing triangle
  if (arg1 == "etri") {
    const string kFileNameIn{"./testfiles/convex_hull_in1.csv"};
    const string kFileNameOut{"./testfiles/etri_out1.csv"};
    auto points = io::ReadPointsFile(kFileNameIn);
    Grid grid{points};
    auto mec = grid.MinEnclosingCircle();
    auto triangle = mec.EnclosingTriangle();
    auto tri_points = triangle.GetPoints();
    tri_points.emplace_back(tri_points.front());
    io::ToCsv(tri_points, points, kFileNameOut);
  }

  // Triangulate
  if (arg1 == "tri") {
    const string kFileNameIn{"./testfiles/closest_pair_in1.csv"};
    const string kFileNameOut{"./testfiles/triangulate_out.csv"};
    auto points = io::ReadPointsFile(kFileNameIn);
    Grid grid{points};
    auto lines = grid.Triangulate();
    WriteToFile(lines, kFileNameOut);
  }

  return 0;
}
