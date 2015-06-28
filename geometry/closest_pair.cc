#include <iostream>
#include <vector>
#include <cmath>
#include "float.h"
using namespace std;

struct point {
	int x,y;
};

struct x_comp {
  bool operator() (const  point p1, const point p2) const
  {return p1.x < p2.x;}
};

struct y_comp {
  bool operator() (const  point p1, const point p2) const
  {return p1.y > p2.y;}
};

double dist(point p1, point p2) {
	cout << "p1x " << p1.x << " p1y " << p1.y << " p2x " << p2.x << " p2y " << p2.y <<endl;
	double c = pow((double)p1.x - (double)p2.x, 2) + pow((double)p1.y - (double)p2.y, 2);
	cout << "c " << sqrt(c) << endl;
	return sqrt(c); 
}

pair<double,pair<point,point>> closest_pair(vector<point> xp, vector<point> yp) {
	cout << "häst 1 " << endl;
	int N = xp.size();
	
	/* Brute force if size <= 3 */
	if (N <= 3) { 
		double min_dist = DBL_MAX;
		point xp_min;
		point yp_min;
		for (size_t i = 0; i < xp.size(); i++) {
			for (size_t j = 0; j < yp.size(); j++) {
				if(xp[i].x != yp[j].x && xp[i].y != yp[j].y){
					cout << " gurka " << endl;
					if (min_dist < dist(xp[i],yp[j])) {
						min_dist = dist(xp[i],yp[j]);
						xp_min = xp[i]; yp_min = yp[j];
					}
				}
			}	
		}
		cout << "häst2 " << endl;
		pair<point,point> pr(xp_min,yp_min);
		pair<double,pair<point,point>> pm(min_dist,pr);
		return pm;
	}
	
	cout << "häst 3 " << endl;
	vector<point> xL(ceil(N/2));
	vector<point> xR(ceil(N/2)+1);
	
	copy(xp.begin(), xp.begin()+ceil(N/2), xL.begin());
	copy(xp.begin()+ceil(N/2)+1, xp.end(), xR.begin());
	
	
	point xmid = xp[ceil(N/2)];
	vector<point> yL;
	vector<point> yR;
	cout << "häst 4 " << endl;
	
	for (size_t i = 0; i < yp.size(); ++i) {
		if (yp[i].x <= xmid.x) yL.push_back(yp[i]);
		if (yp[i].x > xmid.x) yR.push_back(yp[i]);
	}
	
	/* Recursive calls */	
	pair<double,pair<point,point>> cL = closest_pair(xL,yL);
	pair<double,pair<point,point>> cR = closest_pair(xR,yR);
	cout << "häst 5 " << endl;
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
	
	
	cout << "häst 6 " << endl;
	int Ns = ys.size();
	
	double closest_dist = dist_min;
	pair<point,point> closest_pair = p_min;
	
	for (size_t i = 0; i < Ns; ++i) {
		int k = i+1;
		
		while (k <= Ns && ((ys[k].y - ys[i].y) < dist_min)) {
			if (dist(ys[k],ys[i]) < closest_dist) {
				closest_dist = dist(ys[k],ys[i]);
				closest_pair = pair<point,point>(ys[k],ys[i]);
			}
			k++;
		
		}
	
	}
	
	pair<double,pair<point,point>> pm(closest_dist, closest_pair);
	return pm;
}


int main() {

	point p1;
	p1.x = 117;
	p1.y = 1900;
	
	point p2;
	p2.x = 211111;
	p2.y = 2;
	
	point p3;
	p3.x = 100;
	p3.y = 100;
	
	point p4;
	p4.x = 110;
	p4.y = 110;
	
	point p5;
	p5.x = 400;
	p5.y = 400;
	
	point p6;
	p6.x = 1234;
	p6.y = 8999;
	
	
	vector<point> points{p1,p2,p3,p4,p5};
	
	vector<point> px = points;
	vector<point> py = points;
	
	sort(px.begin(),px.end(),x_comp());
	sort(py.begin(),py.end(),y_comp());
	cout << "--------------"<< endl;
	for(auto pp: py) {
		cout <<pp.x << " ";
	}
	cout << endl;
	pair<double,pair<point,point>> closest = closest_pair(px,py);
	cout << closest.first << endl;
	
	


}