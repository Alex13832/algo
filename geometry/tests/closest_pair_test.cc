/** ----------------------------------------------------
* Test case for closest_pair.cc. The data is generated
* with help of Matlab.
* Alexander Karlsson, 2015-06-28
* ------------------------------------------------------ */
#include "../closest_pair.cc"
#include "../../matplotlibcpp.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
namespace plt = matplotlibcpp;

/* Read the data points to be processed by closest_pair */
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

int main() {
	vector<point> pts = read_file("testfiles/closest_pair/closest_pair_test.txt");
	cout << pts.size() << endl;
	pair<double,pair<point,point>> cp = closest_pair_of_points(pts);

	vector<int> x,y,clx,cly;
	for(auto p: pts) {
		x.push_back(p.x);
		y.push_back(p.y);
	}

	clx.push_back(cp.second.first.x);
	clx.push_back(cp.second.second.x);
	cly.push_back(cp.second.first.y);
	cly.push_back(cp.second.second.y);
	
	cout << "Min distance: " << cp.first << endl;
	cout << "Point(1): " << cp.second.first.x << " " << cp.second.first.y << endl;
	cout << "Point(2): " << cp.second.second.x << " " << cp.second.second.y << endl;

	plt::plot(x, y, "ko");
	plt::plot(clx,cly,"ro");
	plt::xlim(0, 10000);
	plt::ylim(0, 10000);
	plt::show();
}

//Answer for closest_pair_test.txt is ~ 92.358