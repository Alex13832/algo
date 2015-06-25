/** ---------------------------------------------------------------
* Quickhull implementation. The algorithm finds the convex hull
* of some input set of points. 
* The quickhull function takes a vector<point> as input, point 
* is a struct.
* Alexander Karlsson, 2015-06-25
* ----------------------------------------------------------------- */ 
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <numeric>
using namespace std;

#define DBL_MIN 2.2250738585072014e-308

/* ------------------------------------------------------------- */
struct point {
	int x, y;
};

struct point_comp {
  bool operator() (const  point p1, const point p2) const
  {return p1.x < p2.x;}
};

/* Determines which side of a line a point is located */
int location(point a, point b, point p) {
	int temp = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
	if (temp > 0) {
		return 1;
	} 
	return -1;
}

/* Distance funtion */
int distance(point a, point b, point c) {
	int abx = b.x - a.x;
	int aby = b.y - a.y;
	int dist = abx*(a.y-c.y) - aby*(a.x-c.x);
	if (dist < 0) return -1*dist;
	return dist;
}

/* ------------------------------------------------------------- */
 
/* Subroutine of quickhull */
void qhull(point a, point b, vector<point>& pts, vector<point>& pts_ch) {
	if (pts.size()==0) {
		return; 
	} else if(pts.size() == 1) {
		pts_ch.push_back(pts[0]);
		pts.erase(pts.begin());
		return;
	} else {

		/* Determine max-distance from line */
		point c;
		int ci;
		int k = 0;
		double max_dist = DBL_MIN;
		for (auto p: pts) {
			if (distance(a,b,p) > max_dist) {
				max_dist = distance(a,b,p);
				c = p;
				ci = k;
			}
			++k;	 
		}

		pts_ch.push_back(c);
		pts.erase(pts.begin()+ci);

		vector<point> A, B;
		for (auto p: pts) {
			if (location(a,c,p) == 1) A.push_back(p);
			if (location(c,b,p) == 1) B.push_back(p);
		}

		/* Recursive calls */
		qhull(a,c,A,pts_ch);
		qhull(c,b,B,pts_ch);
	}
}	

/** Quickhull algorithm, returns the set of points that constructs the
 convex hull of the input set pts */
vector<point> quickhull(vector<point> pts) {
	/* b and a with min and max x-coordinates respectively */
	point b = pts[0];
	point a = pts[pts.size()-1];
	vector<point> pts_ch;
	pts_ch.push_back(a); pts_ch.push_back(b);
	pts.erase(pts.begin());
	pts.erase(pts.end()-1);


	vector<point> left, right;

	/* Determine which side of line (a,b) */
	for(auto p: pts) {
		if (location(a,b,p) == -1) left.push_back(p);
		else right.push_back(p);
	}

	/* Call qhull with two sets */
	qhull(a,b,right,pts_ch);
	qhull(b,a,left,pts_ch);

	return pts_ch;
}