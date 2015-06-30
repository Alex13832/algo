/** ---------------------------------------------------------
* Implementation that finds the closest pair of points
* in the plane of some input set of points. Divide and 
* Conquer style. 
* Alexander Karlsson, 2015-06-28
* ----------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <cmath>
#include "float.h"
#include <algorithm>
#include "geometry2d.cc"
using namespace std;

double dist(point p1, point p2) {
	double c = pow((double)p1.x - (double)p2.x, 2) + pow((double)p1.y - (double)p2.y, 2);
	return sqrt(c); 
}

/* Divide and Conquer algorithm that finds the cloest pair of points  */
pair<double,pair<point,point>> closest_pair(vector<point>& xp, vector<point>& yp) {
	int N = xp.size();
	
	/* Brute force if size <= 3 */
	if (N <= 3) { 
		double min_dist = DBL_MAX;
		point xp_min, yp_min;

		for (auto px: xp) {
			for (auto py: yp) {

				if(!(px.x == py.x && px.y == py.y)){
					if (dist(px,py) < min_dist) {
						min_dist = dist(px,py);
						xp_min = px; yp_min = py;
					}
				}
			}	
		}

		pair<point,point> pr(xp_min,yp_min);
		return pair<double,pair<point,point>>(min_dist,pr);
	}
	
	vector<point> xL(ceil(N/2)), xR(ceil(N/2)), yL, yR;
	
	copy(xp.begin(), xp.begin()+ceil(N/2), xL.begin());
	copy(xp.begin()+ceil(N/2), xp.end(), xR.begin());
	point xmid = xp[ceil(N/2)];
	
	for (size_t i = 0; i < yp.size(); ++i) {
		if (yp[i].x <= xmid.x) yL.push_back(yp[i]);
		else yR.push_back(yp[i]);
	}

	/* Recursive calls */	
	pair<double,pair<point,point>> cL = closest_pair(xL,yL), cR = closest_pair(xR,yR);

	double dist_min = cR.first;
	pair<point,point> p_min = cR.second;
	
	if (cL.first < cR.first) {
		dist_min = cL.first;
		p_min = cL.second;
	}
	
	vector<point> ys;
	for (size_t i = 0; i < xp.size(); ++i) {
		if (abs(xmid.x - xp[i].x) < dist_min) ys.push_back(xp[i]);
	}

	double closest_dist = dist_min;
	pair<point,point> closest_pair = p_min;
	
	for (size_t i = 0; i < ys.size(); ++i) {
		size_t k = i+1;
		
		while (k < ys.size() && ((ys[k].y - ys[i].y) < dist_min)) {
			if (dist(ys[k],ys[i]) < closest_dist) {
				closest_dist = dist(ys[k],ys[i]);
				closest_pair = pair<point,point>(ys[k],ys[i]);
			}
			k++;
		}
	}
	
	return pair<double,pair<point,point>>(closest_dist, closest_pair);
}

/* Sort pts before finding the closest pair of points*/
 pair<double,pair<point,point>> closest_pair_of_points(vector<point> pts) {
 	vector<point> ptsx = pts;
 	vector<point> ptsy = pts;
 	sort(ptsx.begin(), ptsx.end(), x_comp());
 	sort(ptsy.begin(), ptsy.end(), y_comp());
 	return closest_pair(ptsx,ptsy);
 }