/** ---------------------------------------------------
* Tests for the quickhull algorithm
* Alexander Karlsson, 2015-06-25 
* ----------------------------------------------------- */
#include "../quickhull.cc"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* Read the data points to be processed by quickhull */
vector<point> read_file(string file) {
	ifstream infile(file);
	string line;
	vector<point> pts;
	while (getline(infile, line)){	
		string s = line;
		string delimiter = " ";
		size_t pos = 0;
		string token;
		point p;
		while ((pos = s.find(delimiter)) != string::npos) {
		    	token = s.substr(0, pos);
			try {
				
				int num = stoi(token);
				p.x = num;

			} catch (std::invalid_argument&) { }
		    	s.erase(0, pos + delimiter.length());
		}

		try {
			int num = stoi(s);
			p.y = num;
		} catch (std::invalid_argument&) { }
		pts.push_back(p);
 		
	}
	return pts; 
}

/* Print resulting polygon to a file */
void write_to_file(vector<point> chull, string filename) {
	ofstream file;
	file.open(filename);

	for (auto p: chull) {
		file << p.x << " " << p.y << '\n';
	}

	file.close();
}


int main() {
	vector<point> pts = read_file("testfiles/convexhull/data.txt");
	sort(pts.begin(),pts.end(), point_comp());
	vector<point> convhull = quickhull(pts);
	write_to_file(convhull, "convex_hull_res.txt");
}