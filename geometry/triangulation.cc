/** --------------------------------------------------------------
* Implementation of an incremental triangulation algorithm.
* it takes a vector of points as input. On test-computer: slow
* for inputs larger than 10 000.
* Alexander Karlsson, 2015-06-04
* ---------------------------------------------------------------- */
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include "geometry2d.cc"
using namespace std;

/** Incremental triangulation algorithm 
 N.B. pts has to be lexicographical sorted.*/
vector<edge> triangulation(vector<point>& pts) {
	vector<point> visited{pts[0],pts[1],pts[2]};
	bool intersection = false;

	/* The three first points constructs a triangle*/
	edge e0,e1,e2;
	e0.p1 = pts[0]; e0.p2 = pts[1];
	e1.p1 = pts[0]; e1.p2 = pts[2];
	e2.p1 = pts[1]; e2.p2 = pts[2];
	vector<edge> edges{e0,e1,e2};

	/* From this point add points to the only triangl incrementally. */
	for (size_t i = 3; i < pts.size(); ++i){
		point& p0 = pts[i];
		
		/* Target point pi */
		for (auto pi = visited.rbegin(); pi!=visited.rend(); ++pi) {

			/* Verify that the segment p0-pi doesn't intersect e */
			for (auto e = edges.rbegin(); e!=edges.rend(); ++e) {
				point pk = e->p1;
				point pj = e->p2;

				if (segment_intersect(p0,*pi,pj,pk)) {
					intersection = true;
					break; // as soon as something intersects
				}
			}		

			if (!intersection){
				edge e1;
				e1.p1 = p0;
				e1.p2 = *pi;
				edges.push_back(e1);
			}

			intersection = false;
		}

		visited.push_back(p0);
	}

	return edges;
}