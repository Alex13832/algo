#include <iostream>
using namespace std;

struct point {
	int x, y;
	vector<point> adj;

	bool operator==(const point& p) {
		return x == p.x && y == p.y;
	}

	bool operator!=(const point& p) {
		return x != p.x || y != p.y;
	}

};

struct edge {
	point p1, p2;

	bool operator==(const edge& e) {
		point p_1 = e.p1, p_2 = e.p2;
		return (p_1 == p1) && (p_2 == p2);
	}
};

struct x_comp {
  bool operator() (const  point p1, const point p2) const
  {return p1.x < p2.x;}
};

struct y_comp {
	bool operator() (const  point p1, const point p2) const
  {return p1.y < p2.y;}
};


// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(point p, point q, point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return true;
 
    return false;
}

/* Distance funtion */
double distance(point a, point b, point c) {
	int abx = b.x - a.x;
	int aby = b.y - a.y;
	double dist = (double)abx*((double)a.y-(double)c.y) - aby*((double)a.x-(double)c.x);
	if (dist < 0) return -1.0*dist;
	return dist;
}


/** ------------------------------------------------------------------
* Functions for determining if two line segments intersect.
* Implementerd according to
* http://jeffe.cs.illinois.edu/teaching/373/notes/x06-sweepline.pdf
*/

//0.01 small penalty
bool ccw(point p1, point p2, point p3) {
	return ((p3.y-p1.y) * (p2.x-p1.x)) >= ((p2.y-p1.y) * (p3.x-p1.x));
}

//p0 pi pk pj
bool segment_intersect(point p1, point p2, point p3, point p4) {
	bool a = (ccw(p1,p3,p4) != ccw(p2,p3,p4)) 
		&& (ccw(p1,p2,p3) != ccw(p1,p2,p4));

	/** Degeneracy, if two points are equal, they should not 
	//count as intersection */	
	bool b = p1 != p3;
	bool c = p1 != p4;
	bool d = p2 != p3;	
	bool e = p2 != p4;
	bool f = p1 != p3;
	bool g = p3 != p4;


	return a && b && c && d && e && f && g; 
	
}	
