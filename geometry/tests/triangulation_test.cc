#include "../triangulation.cc"
#include "../../matplotlibcpp.h"
#include <iostream>
#include <fstream>
/** -----------------------------------------------------------
* Tests for triangulation.cc 
* The test is not a proof. Use the plot to visually "verify". 
* -triangulation.cc outputs one of several possible 
* triangualtions, though the same triangulation is calculated
* for the same input.
* Alexander Karlsson, 2015-06-04
* ------------------------------------------------------------- */
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>
#include <ctime>        
#include <cstdlib>     
using namespace std;
namespace plt = matplotlibcpp;

/* Lexicographical sort */
void lexisort(vector<point>& pts) {
	int x = pts[0].x;
	vector<point> pts2;
	vector<point> pts_res;

	for(size_t i = 0; i < pts.size(); ++i) {
		
		
		if (pts[i].x != x) {
			sort(pts2.begin(),pts2.end(),y_comp());
			for(size_t k = 0; k < pts2.size(); ++k) {
				pts_res.push_back(pts2[k]);
			}

			pts2.clear();
			x = pts[i].x;
		}

		pts2.push_back(pts[i]);
	}

	if (pts2.size() > 0) {
		for(auto p: pts2) {
			pts_res.push_back(p);
		}
	}

	pts = pts_res;
}

int myrandom (int i) { return std::rand()%i;}

/* Read data point from a file */
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

int main(int argc, const char *argv[]) {
	vector<point> pts;
	string filename;

	if (argc == 3) {
		string str = argv[1];	
		if (str == "-f") {
			filename = argv[2];
			pts = read_file(filename);
		
		} else if (str == "-r") {
			
			string r = argv[2];
			int randi = stoi(r);
			std::srand ( unsigned ( std::time(0) ) );

			vector<int> Xp(randi),Yp(randi);
			iota(Xp.begin(),Xp.end(),1);
			iota(Yp.begin(),Yp.end(),1);
			random_shuffle(Xp.begin(),Xp.end(),myrandom);
			random_shuffle(Yp.begin(),Yp.end(),myrandom);


			for(size_t k = 0; k < Xp.size(); ++k) {
				point p;
				p.x = Xp[k];
				p.y = Yp[k];
				pts.push_back(p);
			}
		} else {
			cout << "Fileusage: " << endl;
			cout << "-f <filename>" << endl;
			cout << "-r <integer>" << endl;
			return 0;
		}
	
	} else {
		cout << "Fileusage: " << endl;
		cout << "-f <filename> [Input file]" << endl;
		cout << "-r <integer> [Size on random example]" << endl;
		return 0;
	}


	sort(pts.begin(),pts.end(),x_comp());
	lexisort(pts);
	vector<edge> connected = triangulation(pts);

	int x_max = 0, y_max = 0;
	vector<int> X,Y;
	for (auto E: connected) {
		point p1 = E.p1, p2 = E.p2;

		int x1 = p1.x, y1 = p1.y; 
		int x2 = p2.x, y2 = p2.y; 
		if (x1 > x_max) x_max = x1;
		if (y1 > y_max) y_max = y1;
		if (x2 > x_max) x_max = x2;
		if (y2 > y_max) y_max = y2;

		X.push_back(x1);
		Y.push_back(y1);
		X.push_back(x2);
		Y.push_back(y2);
	
		plt::plot(X,Y,"k-");
		plt::plot(X,Y,"go");

		X.pop_back();
		Y.pop_back();	
		X.pop_back();
		Y.pop_back();	
	}

	plt::xlim(0, x_max+2);
	plt::ylim(0, y_max+2);
	plt::show();
}