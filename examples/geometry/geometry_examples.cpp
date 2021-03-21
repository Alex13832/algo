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

void WriteToFile(const Circle& circle, const string& file_name)
{
  string header{"x,y,radius"};
  string row{to_string(circle.center.x) + "," + to_string(circle.center.y) + "," + to_string(circle.radius) + '\n'};
  vector<string> rows{header, row};
  io::ToCsv(rows, file_name);
}

void WriteToFile(const Edges& lines, const string& file_name)
{
  string header{"x1,y1,x2,y2"};
  vector<string> rows{header};

  for (auto line : lines) {
    string row{to_string(line.a.x) + "," + to_string(line.a.y) + "," + to_string(line.b.x) + "," + to_string(line.b.y)};
    rows.emplace_back(row);
  }
  io::ToCsv(rows, file_name);
}

void PrintHelp()
{
  cout << "Algorithms: Closest pair of points <cpp>, Convex hull <ch>, Minimum bounding box <mbbox>, "
          "Minimum enclosing circle <mec>, <triangulate>."
       << endl;
}

int main(int argc, char *argv[])
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
    Points points{io::ReadPointsFile(kFileNameIn)};
    Points cp{ClosestPairOfPoints(points)};
    io::ToCsv(cp, points, kFileNameOut);
  }

  // Convex hull
  if (arg1 == "ch") {
    const string kFileNameIn{"./testfiles/convex_hull_in1.csv"};
    const string kFileNameOut{"./testfiles/convex_hull_out2.csv"};
    Points points{io::ReadPointsFile(kFileNameIn)};
    Polygon qh{ConvexHull(points)};
    io::ToCsv(qh.GetPoints(), points, kFileNameOut);
  }

  // Minimum bounding box
  if (arg1 == "mbbox") {
    const string kFileNameIn{"./testfiles/mbbox_in1.csv"};
    const string kFileNameOut{"./testfiles/mbbox_out1.csv"};
    Points points{io::ReadPointsFile(kFileNameIn)};
    Polygon mbbox{MinimumBoundingBox(points)};
    io::ToCsv(mbbox.GetPoints(), points, kFileNameOut);
  }

  // Minimum eclosing circle
  if (arg1 == "mec") {
    const string kFileNameIn{"./testfiles/mbbox_in1.csv"};
    const string kFileNameOut{"./testfiles/mec_out1.csv"};
    Points points{io::ReadPointsFile(kFileNameIn)};
    Circle mec{MinimumEnclosingCircle(points)};
    WriteToFile(mec, kFileNameOut);
  }

  // Triangulate
  if (arg1 == "triangulate") {
    const string kFileNameIn{"./testfiles/triangulate_in.csv"};
    const string kFileNameOut{"./testfiles/triangulate_out.csv"};
    Points points{io::ReadPointsFile(kFileNameIn)};
    Edges lines{Triangulate(points)};
    WriteToFile(lines, kFileNameOut);
  }

  return 0;
}
