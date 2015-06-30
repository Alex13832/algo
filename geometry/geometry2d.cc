#include <iostream>
using namespace std;

struct point {
	int x, y;
};

struct x_comp {
  bool operator() (const  point p1, const point p2) const
  {return p1.x < p2.x;}
};

struct y_comp {
	bool operator() (const  point p1, const point p2) const
  {return p1.y < p2.y;}
};

/** ------------------------------------------------------------------
* Functions for determining if two line segments intersect.
* Implementerd according to
* http://jeffe.cs.illinois.edu/teaching/373/notes/x06-sweepline.pdf
*/

bool ccw(point p1, point p2, point p3) {
	return ((p3.y-p1.y) * (p2.x-p1.x)) > ((p2.y-p1.y) * (p3.x-p1.x));
}

bool segment_intersect(point p1, point p2, point p3, point p4) {
	return (ccw(p1,p3,p4) != ccw(p2,p3,p4)) 
		&& (ccw(p1,p2,p3) != ccw(p1,p2,p4));
}

/* -------------------------------------------------------------------*/